# How to Use NaniteTree's node in Houdini of your version

    如何在你本地版本的Houdini使用NaniteTree的减面节点
    How to use NaniteTree's Mesh Simplification node in your native version of Houdini Note

注: 在这里测试了Houdini 18.5以及Houdini 19.5, 编译测试了Visual Studio2019 以及2022均没有问题

ps.Tested Houdini 18.5 and Houdini 19.5 here, compiled and tested Visual Studio2019 and 2022 without problems 
## 1. 创建dso⽂件夹  Create dso folder
前往C:\Users\你的电脑名\Documents\houdini19.0创建⼀个dso⽂件夹

Go to C:\Users\ your computer name \Documents\houdini19.0 Create a dso folder

## 2. 设置houdini.env Set houdini.env
在⾥⾯写上

```shell
HOUDINI_DSO_PATH = $HOME\houdini19.0\dso;& 
```
这句话是保证你⽣成dll⾃动分配到dso⽂件夹⾥⾯

Write these sentences to ensure that you can print out the error Log of the dso when you assign the dll to the DSO folder.


```shell
HOUDINI_DSO_ERROR = 3
```
可以将DSO的error Log打印出来，如果需要提Issue请复制这个log

If you need to Issue, please copy the dso error log in the houdini console when opening hda/hip files 



## 3. 书写CMakeLists⽂件内容 Compiling HDK Code

官⽹有样例 HDK: Compiling HDK Code (sidefx.com)

```cpp
cmake_minimum_required( VERSION 3.6 )
project( NaniteSimplification )
# CMAKE_PREFIX_PATH must contain the path to the toolkit/cmake subdirectory of
# the Houdini installation. See the "Compiling with CMake" section of the HDK
# documentation for more details, which describes several options for
# specifying this path.
list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )
# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )

find_package(Eigen3 3.1.0 QUIET) #(3.1.0 or greater)
# include(CGAL_Eigen3_support)
# if(TARGET CGAL::Eigen3_support)
#   create_single_source_cgal_program("edge_collapse_garland_heckbert.cpp")
#   target_link_libraries(edge_collapse_garland_heckbert PUBLIC CGAL::Eigen3_support)
# else()
#   message(STATUS "NOTICE: Garland-Heckbert polices require the Eigen library, which has not been found; related examples will not be compiled.")
# endif()

set( library_name NaniteSimplification )
# Code generation for the embedded DS file in Mesh_Simplification.cpp.
houdini_generate_proto_headers( FILES Mesh_Simplification.cpp )
# Add a library and its source files.
add_library( ${library_name} SHARED
Mesh_Simplification.cpp
Mesh_Simplification.h
)
#add ThirdPartyInclude
list( APPEND ThirdPartIncludePath "include")
list( APPEND ThirdPartIncludePath "$ENV{BOOST_INCLUDEDIR}")
list( APPEND ThirdPartIncludePath "$ENV{CGAL_DIR}/include")
list( APPEND ThirdPartIncludePath "$ENV{CGAL_DIR}/auxiliary/gmp/include")
# list( APPEND ThirdPartIncludePath "D:/JainiceResearch/vcpkg/installed/x64-window")
target_include_directories( ${library_name} PRIVATE
${ThirdPartIncludePath}
)
#add ThirdPartylib
# list( APPEND ThirdPartLibPath "D:/JainiceResearch/vcpkg/installed/x64-windows/gmp/lib/libmpfr-4.lib")
# list( APPEND ThirdPartLibPath "D:/JainiceResearch/vcpkg/installed/x64-windows/gmp/lib/libgmp-10.lib")
target_link_libraries( ${library_name} ${ThirdPartLibPath})
# Link against the Houdini libraries, and add required include directories and
# compile definitions.
target_link_libraries( ${library_name} Houdini )
# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
${CMAKE_CURRENT_BINARY_DIR}
)
# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )
```

## 4. Installing CGAL, Boost with Vcpkg

  `https://doc.cgal.org/latest/Manual/windows.html`

```shell
./vcpkg.exe install cgal:x64-windows
./vcpkg.exe install boost:x64-windows
./vcpkg.exe integrate install
```

## 5. 配置vcpkg环境变量 Configure Environment variable

本文PATH均为系统变量的PATH
In this article, PATH is the System PATH

```cmd
PATH C:\dev\vcpkg\installed\x64-windows\bin

PATH C:\dev\vcpkg\installed\x64-windows\debug\bin
```

## 6. 调⽤CMakeLists⽂件 Build By CMakeLists

在 **开始菜单** --> 键入**Houdini** 会自动搜索匹配项 --> **Command Line Tools**

 CMakeLists widget in **Start menu** --> Type **Houdini** will automatically search for matches --> **Command Line Tools**

```shell
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 .. 
或者
cmake -G "Visual Studio 17 2022" -A x64 .. 
```

## 7. 打开生成sln Open Solution
鼠标右键NaniteSimplification设置成启动项目并点击生成,成功以后就能看到dso⽂件夹里面的⽂件

Open the generate sln right mouse button set NaniteSimplification to start the project and click Generate. After success, you can see the item

## 8. 创建MeshSimplification节点 Create **MeshSimplification** Node 
打开Houdini，创建⼀个**Geometry**节点，进⼊节点内部，按**tab**键，找到**Custom**就可以看到CPP自定义的节点 **MeshSimplification**

Open Houdini, create a **Geometry** node, go inside the node, press the **tab** key, find Custom node **MeshSimplification**