/*
Copyright 2012-2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP
#define BOOST_SMART_PTR_ALLOCATE_SHARED_ARRAY_HPP

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/enable_if.hpp>
#include <boost/type_traits/is_bounded_array.hpp>
#include <boost/type_traits/is_unbounded_array.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_constructor.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/remove_all_extents.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_extent.hpp>
#include <boost/type_traits/type_with_alignment.hpp>

namespace boost {
namespace detail {

template<class T>
struct sp_array_scalar {
    typedef typename boost::remove_cv<typename
        boost::remove_all_extents<T>::type>::type type;
};

template<class T, class U>
struct sp_array_count {
    enum {
        value = sizeof(T) / sizeof(U)
    };
};

template<std::size_t N, std::size_t M>
struct sp_max_size {
    enum {
        value = N < M ? M : N
    };
};

template<std::size_t N, std::size_t M>
struct sp_align_up {
    enum {
        value = (N + M - 1) & ~(M - 1)
    };
};

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A, class T>
struct sp_bind_allocator {
    typedef typename std::allocator_traits<A>::template rebind_alloc<T> type;
};
#else
template<class A, class T>
struct sp_bind_allocator {
    typedef typename A::template rebind<T>::other type;
};
#endif

template<class T>
BOOST_CONSTEXPR inline std::size_t
sp_objects(std::size_t size) BOOST_SP_NOEXCEPT
{
    return (size + sizeof(T) - 1) / sizeof(T);
}

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    boost::has_trivial_destructor<T>::value>::type
sp_array_destroy(A&, T*, std::size_t) BOOST_SP_NOEXCEPT { }

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    !boost::has_trivial_destructor<T>::value>::type
sp_array_destroy(A&, T* ptr, std::size_t size)
{
    while (size > 0) {
        ptr[--size].~T();
    }
}

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<bool E, class A, class T>
inline typename boost::enable_if_<E>::type
sp_array_destroy(A& allocator, T* ptr, std::size_t size)
{
    while (size > 0) {
        std::allocator_traits<A>::destroy(allocator, ptr + --size);
    }
}
#endif

template<bool E, class A, class T>
class sp_destroyer {
public:
    sp_destroyer(A& allocator, T* ptr) BOOST_SP_NOEXCEPT
        : allocator_(allocator),
          ptr_(ptr),
          size_(0) { }

    ~sp_destroyer() {
        sp_array_destroy<E>(allocator_, ptr_, size_);
    }

    std::size_t& size() BOOST_SP_NOEXCEPT {
        return size_;
    }

private:
    sp_destroyer(const sp_destroyer&);
    sp_destroyer& operator=(const sp_destroyer&);

    A& allocator_;
    T* ptr_;
    std::size_t size_;
};

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    boost::has_trivial_constructor<T>::value &&
    boost::has_trivial_assign<T>::value &&
    boost::has_trivial_destructor<T>::value>::type
sp_array_construct(A&, T* ptr, std::size_t size)
{
    for (std::size_t i = 0; i < size; ++i) {
        ptr[i] = T();
    }
}

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    boost::has_trivial_constructor<T>::value &&
    boost::has_trivial_assign<T>::value &&
    boost::has_trivial_destructor<T>::value>::type
sp_array_construct(A&, T* ptr, std::size_t size, const T* list,
    std::size_t count)
{
    for (std::size_t i = 0; i < size; ++i) {
        ptr[i] = list[i % count];
    }
}

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    !(boost::has_trivial_constructor<T>::value &&
      boost::has_trivial_assign<T>::value &&
      boost::has_trivial_destructor<T>::value)>::type
sp_array_construct(A& none, T* ptr, std::size_t size)
{
    sp_destroyer<E, A, T> hold(none, ptr);
    for (std::size_t& i = hold.size(); i < size; ++i) {
        ::new(static_cast<void*>(ptr + i)) T();
    }
    hold.size() = 0;
}

template<bool E, class A, class T>
inline typename boost::enable_if_<!E &&
    !(boost::has_trivial_constructor<T>::value &&
      boost::has_trivial_assign<T>::value &&
      boost::has_trivial_destructor<T>::value)>::type
sp_array_construct(A& none, T* ptr, std::size_t size, const T* list,
    std::size_t count)
{
    sp_destroyer<E, A, T> hold(none, ptr);
    for (std::size_t& i = hold.size(); i < size; ++i) {
        ::new(static_cast<void*>(ptr + i)) T(list[i % count]);
    }
    hold.size() = 0;
}

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<bool E, class A, class T>
inline typename boost::enable_if_<E>::type
sp_array_construct(A& allocator, T* ptr, std::size_t size)
{
    sp_destroyer<E, A, T> hold(allocator, ptr);
    for (std::size_t& i = hold.size(); i < size; ++i) {
        std::allocator_traits<A>::construct(allocator, ptr + i);
    }
    hold.size() = 0;
}

template<bool E, class A, class T>
inline typename boost::enable_if_<E>::type
sp_array_construct(A& allocator, T* ptr, std::size_t size, const T* list,
    std::size_t count)
{
    sp_destroyer<E, A, T> hold(allocator, ptr);
    for (std::size_t& i = hold.size(); i < size; ++i) {
        std::allocator_traits<A>::construct(allocator, ptr + i,
            list[i % count]);
    }
    hold.size() = 0;
}
#endif

template<class A, class T>
inline typename
    boost::enable_if_<boost::has_trivial_constructor<T>::value>::type
sp_array_default(A&, T*, std::size_t) BOOST_SP_NOEXCEPT { }

template<class A, class T>
inline typename
    boost::enable_if_<!boost::has_trivial_constructor<T>::value>::type
sp_array_default(A& none, T* ptr, std::size_t size)
{
    sp_destroyer<false, A, T> hold(none, ptr);
    for (std::size_t& i = hold.size(); i < size; ++i) {
        ::new(static_cast<void*>(ptr + i)) T;
    }
    hold.size() = 0;
}

template<class A>
class sp_array_state {
public:
    typedef A type;

    template<class U>
    sp_array_state(const U& _allocator, std::size_t _size) BOOST_SP_NOEXCEPT
        : allocator_(_allocator),
          size_(_size) { }

    A& allocator() BOOST_SP_NOEXCEPT {
        return allocator_;
    }

    std::size_t size() const BOOST_SP_NOEXCEPT {
        return size_;
    }

private:
    A allocator_;
    std::size_t size_;
};

template<class A, std::size_t N>
class sp_size_array_state {
public:
    typedef A type;

    template<class U>
    sp_size_array_state(const U& _allocator, std::size_t) BOOST_SP_NOEXCEPT
        : allocator_(_allocator) { }

    A& allocator() BOOST_SP_NOEXCEPT {
        return allocator_;
    }

    BOOST_CONSTEXPR std::size_t size() const BOOST_SP_NOEXCEPT {
        return N;
    }

private:
    A allocator_;
};

#if !defined(BOOST_NO_CXX11_ALLOCATOR)
template<class A>
struct sp_use_construct {
    enum {
        value = true
    };
};

template<class T>
struct sp_use_construct<std::allocator<T> > {
    enum {
        value = false
    };
};
#else
template<class>
struct sp_use_construct {
    enum {
        value = false
    };
};
#endif

template<class T, class U>
struct sp_array_alignment {
    enum {
        value = sp_max_size<boost::alignment_of<T>::value,
            boost::alignment_of<U>::value>::value
    };
};

template<class T, class U>
struct sp_array_offset {
    enum {
        value = sp_align_up<sizeof(T), sp_array_alignment<T, U>::value>::value
    };
};

template<class T, class U>
struct sp_array_storage {
    enum {
        value = sp_array_alignment<T, U>::value
    };
    typedef typename boost::type_with_alignment<value>::type type;
};

template<class T, class U>
inline U*
sp_array_start(void* base) BOOST_SP_NOEXCEPT
{
    enum {
        size = sp_array_offset<T, U>::value
    };
    return reinterpret_cast<U*>(static_cast<char*>(base) + size);
}

template<class A, class T>
class sp_array_creator {
    typedef typename A::value_type scalar;

    enum {
        offset = sp_array_offset<T, scalar>::value
    };

    typedef typename sp_array_storage<T, scalar>::type type;

public:
    template<class U>
    sp_array_creator(const U& other, std::size_t size) BOOST_SP_NOEXCEPT
        : other_(other),
          size_(sp_objects<type>(offset + sizeof(scalar) * size)) { }

    T* create() {
        return reinterpret_cast<T*>(other_.allocate(size_));
    }

    void destroy(T* base) {
        other_.deallocate(reinterpret_cast<type*>(base), size_);
    }

private:
    typename sp_bind_allocator<A, type>::type other_;
    std::size_t size_;
};

struct sp_default { };

template<class T, bool E = sp_use_construct<T>::value>
class BOOST_SYMBOL_VISIBLE sp_array_base
    : public sp_counted_base {
    typedef typename T::type allocator;

public:
    typedef typename allocator::value_type type;

    template<class A>
    sp_array_base(const A& other, std::size_t size, type* start)
        : state_(other, size) {
        sp_array_construct<E>(state_.allocator(), start, state_.size());
    }

    template<class A>
    sp_array_base(const A& other, std::size_t size, const type* list,
        std::size_t count, type* start)
        : state_(other, size) {
        sp_array_construct<E>(state_.allocator(), start, state_.size(), list,
            count);
    }

    template<class A>
    sp_array_base(sp_default, const A& other, std::size_t size, type* start)
        : state_(other, size) {
        sp_array_default(state_.allocator(), start, state_.size());
    }

    T& state() BOOST_SP_NOEXCEPT {
        return state_;
    }

    virtual void dispose() BOOST_SP_NOEXCEPT {
        sp_array_destroy<E>(state_.allocator(),
            sp_array_start<sp_array_base, type>(this), state_.size());
    }

    virtual void destroy() BOOST_SP_NOEXCEPT {
        sp_array_creator<allocator, sp_array_base> other(state_.allocator(),
            state_.size());
        this->~sp_array_base();
        other.destroy(this);
    }

    virtual void* get_deleter(const sp_typeinfo&) BOOST_SP_NOEXCEPT {
        return 0;
    }

    virtual void* get_local_deleter(const sp_typeinfo&) BOOST_SP_NOEXCEPT {
        return 0;
    }

    virtual void* get_untyped_deleter() BOOST_SP_NOEXCEPT {
        return 0;
    }

private:
    T state_;
};

template<class A, class T>
struct sp_array_result {
public:
    template<class U>
    sp_array_result(const U& other, std::size_t size)
        : creator_(other, size),
          result_(creator_.create()) { }

    ~sp_array_result() {
        if (result_) {
            creator_.destroy(result_);
        }
    }

    T* get() const {
        return result_;
    }

    void release() {
        result_ = 0;
    }

private:
    sp_array_result(const sp_array_result&);
    sp_array_result& operator=(const sp_array_result&);

    sp_array_creator<A, T> creator_;
    T* result_;
};

} /* detail */

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator, std::size_t count)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    typedef detail::sp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    std::size_t size = count * detail::sp_array_count<type, scalar>::value;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(allocator, size, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    enum {
        size = detail::sp_array_count<T, scalar>::value
    };
    typedef detail::sp_size_array_state<other, size> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(allocator, size, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator, std::size_t count,
    const typename remove_extent<T>::type& value)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    typedef detail::sp_array_state<other> state;
    typedef detail::sp_array_base<state> base;
    enum {
        total = detail::sp_array_count<type, scalar>::value
    };
    std::size_t size = count * total;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(allocator, size,
        reinterpret_cast<const scalar*>(&value), total, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared(const A& allocator,
    const typename remove_extent<T>::type& value)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    enum {
        size = detail::sp_array_count<T, scalar>::value
    };
    typedef detail::sp_size_array_state<other, size> state;
    typedef detail::sp_array_base<state> base;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(allocator, size,
        reinterpret_cast<const scalar*>(&value),
        detail::sp_array_count<type, scalar>::value, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

template<class T, class A>
inline typename enable_if_<is_unbounded_array<T>::value, shared_ptr<T> >::type
allocate_shared_noinit(const A& allocator, std::size_t count)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    typedef detail::sp_array_state<other> state;
    typedef detail::sp_array_base<state, false> base;
    std::size_t size = count * detail::sp_array_count<type, scalar>::value;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(detail::sp_default(), allocator,
        size, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

template<class T, class A>
inline typename enable_if_<is_bounded_array<T>::value, shared_ptr<T> >::type
allocate_shared_noinit(const A& allocator)
{
    typedef typename remove_extent<T>::type type;
    typedef typename detail::sp_array_scalar<T>::type scalar;
    typedef typename detail::sp_bind_allocator<A, scalar>::type other;
    enum {
        size = detail::sp_array_count<T, scalar>::value
    };
    typedef detail::sp_size_array_state<other, size> state;
    typedef detail::sp_array_base<state, false> base;
    detail::sp_array_result<other, base> result(allocator, size);
    detail::sp_counted_base* node = result.get();
    scalar* start = detail::sp_array_start<base, scalar>(node);
    ::new(static_cast<void*>(node)) base(detail::sp_default(), allocator,
        size, start);
    result.release();
    return shared_ptr<T>(detail::sp_internal_constructor_tag(),
        reinterpret_cast<type*>(start), detail::shared_count(node));
}

} /* boost */

#endif
