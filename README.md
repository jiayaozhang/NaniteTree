# NaniteTreePipeline

# Table of contents 导航
1. [Introduction 简介](#Introduction)

2. [Part one Implementation 工具使用流程](#Implementation)
    1. [Use in Houdini 在Houdini中使用](#Houdini)

    2. [Use in UnrealEngine 在虚幻引擎中使用](#Unreal)

3. [Part two Tech details 技术细节](#TechDetails)


## Introduction 简介 <a name="Introduction"></a>
### Toolbox Overview 工具一览
    The features annotated with ” HoudiniHDA “ are implemented with Houdini Digital Asset and depend on the specific version of Houdini (but you can also use our guidelines to annotate the features in different versions of Houdini) 
    
    The features annotated with “ UnrealPlugin ”, we plan to release free Unreal plugin in the mall, for real-time preview and adjustment of relevant Settings in the engine, use NaniteTree functions in the engine (some functions still rely on HoudiniPlugin for Unreal)

    标注了HoudiniHDA的功能是用Houdini Digital Asset实现的，依赖具体的Houdini版本（但你也可以通过我们的指引将功能适配到不同版本的Houdini中

    标注了 UnrealPlugin的功能，我们有计划在商场中发布免费的虚幻插件，用于在引擎内实时预览和调整相关设置，在引擎内使用NaniteTree的功能（部分功能仍依赖HoudiniPlugin for Unreal）

![image](https://hikohiko.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F0d608712-81b7-41af-8caa-374d0e8f6ab6%2F0634b59b-e0eb-4a5f-9a3f-4ca01880fccc%2FUntitled.png?table=block&id=1c590fd1-b87c-4c16-bea4-21535de076fa&spaceId=0d608712-81b7-41af-8caa-374d0e8f6ab6&width=2000&userId=&cache=v2)


This is an automated Nanite Tree Tool designed to convert traditional non-Nanite vegetation models into Nanite models suitable for Unreal Engine 5. 

The core functions of this tool include vertex layout reconstruction, polygon merging, and LOD generation, aiming to simplify the process of vegetation asset creation and improve artistic creation efficiency.

Through our tool, artists can quickly convert original billboard models to leaf modeling vegetation models suitable for Nanite rendering, achieving higher-quality rendering effects and better performance.

这是一个基于流程的自动工具，旨在将传统的非Nanite植被模型一键转换为兼具最佳性能与效果表现的适用于Unreal Engine Nanite技术的模型资产（包括符合UE规范的碰撞体）

通过该工具，美术人员能够将原始插片模型快速转换为适应Nanite渲染（Opaque）的叶片建模植被模型，从而实现更高质量的渲染效果和更高的性能表现。

该工具的核心功能包括顶点布局重建、面数合并和LOD生成，旨在简化植被资产的制作流程并提高美术创作效率。

除提供自动化的资产转换功能外，该工具还允许美术人员根据需要微调参数，以优化最终的渲染效果。通过在引擎中验证每一步修改对最终效果的影响，美术人员可以更快地实现满意的渲染结果。

作为开源技术，我们希望通过推广我们的工具为Unreal Engine 5的植被制作流程提供了可靠的使用Nanite虚拟网格技术的解决方案，为游戏开发社区献出一项实用的技术工具。

通过开源，我们希望激发更多开发者参与其中，共同推动游戏行业的技术进步和创作效率的提升。


## Part Ⅰ Implementation 工具使用流程 <a name="Implementation"></a>
 @Hikohikoyan 

### Use in Houdini 在Houdini中使用 <a name="Houdini"></a>


### Use in UnrealEngine 在虚幻引擎中使用 <a name="Unreal"></a>


### How to Use NaniteTree's node in Houdini of your version
@Jiayaozhang

    如何在你本地版本的Houdini使用NaniteTree的减面节点

1. 创建dso⽂件夹，前往C:\Users\你的电脑名\Documents\houdini19.0创建⼀个dso⽂件夹


2. 设置houdini.env，在⾥⾯写上

```shell
HOUDINI_DSO_PATH = $HOME\houdini19.0\dso;& 
```


这句话是保证你⽣成dll⾃动分配到dso⽂件夹⾥⾯


3. 书写CMakeLists⽂件内容，官⽹有样例 HDK: Compiling HDK Code (sidefx.com)

```cpp
cmake_minimum_required( VERSION 3.6 )
project( NaniteSimplification )

list( APPEND CMAKE_PREFIX_PATH "$ENV{HFS}/toolkit/cmake" )
# Locate Houdini's libraries and header files.
# Registers an imported library target named 'Houdini'.
find_package( Houdini REQUIRED )
find_package(Eigen3 3.1.0 QUIET) #(3.1.0 or greater)

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
target_link_libraries( ${library_name} ${ThirdPartLibPath})
target_link_libraries( ${library_name} Houdini )
# Include ${CMAKE_CURRENT_BINARY_DIR} for the generated header.
target_include_directories( ${library_name} PRIVATE
${CMAKE_CURRENT_BINARY_DIR}
)
# Sets several common target properties, such as the library's output directory.
houdini_configure_target( ${library_name} )
```

4. Installing CGAL with Vcpkg
  `https://doc.cgal.org/latest/Manual/windows.html`

```shell
./vcpkg.exe install cgal:x64-windows
./vcpkg.exe install boost:x64-windows
./vcpkg.exe install eigen:x64-windows
./vcpkg.exe integrate install
```


5. 调⽤CMakeLists⽂件，在houdini中找到Command Line Tools

```shell
mkdir build
cd build
cmake -DCMAKE_TOOLCHAIN_FILE=VCPKG_ROOT\scripts\buildsystems\vcpkg.cmake -DCMAKE_PREFIX_PATH="HOUDINI_ROOT\toolkit\cmake" ..
cmake --build . --clean-first
```
6. 打开生成sln，并点击生成,成功以后就能看到dso⽂件夹里面的⽂件

7. 打开Houdini，创建⼀个Geometry节点，进⼊节点内部，按tab键，找到Coustom就可以看到刚才⽣成的节点。

## Part Ⅱ Tech details 技术细节  <a name="TechDetails"></a>
 @JiayaoZhang
