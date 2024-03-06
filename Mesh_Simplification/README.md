## Update Issue   Dev提交说明
### 2024/2/28 Dso-Error Incompatible compiler version
一直遇到一个BUG就是Houdini怎么也识别不出编译出来的

https://www.cnblogs.com/Ligo-Z/p/17475723.html 博客中看到可以用dumpbin找到依赖项

并把dll依赖放在同一目录下（或者环境变量之中）

```cpp
Dump of file C:\Users\YourUserName\Documents\houdini xx.xx\dso\NaniteSimplification.dll

File Type: DLL

  Image has the following dependencies:

    libOP.dll
    libUT.dll
    libPRM.dll
    libGU.dll
    libGEO.dll
    libGA.dll
    libSOP.dll
    MSVCP140.dll
    VCRUNTIME140.dll
    VCRUNTIME140_1.dll
    api-ms-win-crt-runtime-l1-1-0.dll
    api-ms-win-crt-string-l1-1-0.dll
    api-ms-win-crt-heap-l1-1-0.dll
    api-ms-win-crt-math-l1-1-0.dll
    api-ms-win-crt-time-l1-1-0.dll
    api-ms-win-crt-stdio-l1-1-0.dll
    KERNEL32.dll

  Summary

        1000 .00cfg
        3000 .data
        E000 .idata
       16000 .pdata
       44000 .rdata
        3000 .reloc
        1000 .rsrc
       EB000 .text
        1000 .tls
```
Issue Log :
```txt
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_GLTF.dll:Calling newDriverOperator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Time elapsed 0.000543s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Find newDriverOperator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/ROP_OpenGL.dll:Calling newDriverOperator()
DSO_INFO:DONE Running newDriverOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newDriverOperator:Time elapsed 0.125054s
DSO_INFO:Running newChopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newChopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newChopNetOperator:Time elapsed 0.000097s
DSO_INFO:Running newChopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Time elapsed 0.000440s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Find newChopOperator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Gamepad.dll:Calling newChopOperator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Time elapsed 0.000404s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Find newChopOperator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/CHOP_Mouse3D.dll:Calling newChopOperator()
DSO_INFO:DONE Running newChopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newChopOperator:Time elapsed 0.092081s
DSO_INFO:Running newShopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newShopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newShopOperator:Time elapsed 0.000065s
DSO_INFO:Running newShopClerk() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newShopClerk() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newShopClerk:Time elapsed 0.045333s
DSO_INFO:Running newCopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newCopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newCopNetOperator:Time elapsed 0.000066s
DSO_INFO:Running newCop2Operator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Time elapsed 0.000207s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_EnableGPU.dll:Calling newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Time elapsed 0.000289s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUEnvironment.dll:Calling newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Time elapsed 0.000347s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUFog.dll:Calling newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Time elapsed 0.000416s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPULighting.dll:Calling newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Time elapsed 0.000433s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/COP2_GPUZComposite.dll:Calling newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Time elapsed 0.001106s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Find newCop2Operator()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_Substance.dll:Calling newCop2Operator()
DSO_INFO:DONE Running newCop2Operator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newCop2Operator:Time elapsed 0.278745s
DSO_INFO:Running newVopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newVopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newVopNetOperator:Time elapsed 0.000071s
DSO_INFO:Running newVopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newVopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newVopOperator:Time elapsed 0.000067s
DSO_INFO:Running newLopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newLopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newLopOperator:Time elapsed 0.000065s
DSO_INFO:Running newAutoCollection() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/USD_Ops.dll:Find newAutoCollection()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/USD_Ops.dll:Calling newAutoCollection()
DSO_INFO:DONE Running newAutoCollection() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newAutoCollection:Time elapsed 0.037345s
DSO_INFO:Running newTopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newTopNetOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newTopNetOperator:Time elapsed 0.000065s
DSO_INFO:Running newTopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newTopOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newTopOperator:Time elapsed 0.000060s
DSO_INFO:Running registerPDGTypes() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Time elapsed 0.000328s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Find registerPDGTypes()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_NodeTypes.dll:Calling registerPDGTypes()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Time elapsed 0.000237s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Find registerPDGTypes()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdg/PDG_SchedulerTypes.dll:Calling registerPDGTypes()
DSO_INFO:DONE Running registerPDGTypes() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:registerPDGTypes:Time elapsed 0.001460s
DSO_INFO:Running registerPDGDTypes() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Time elapsed 0.000598s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Find registerPDGDTypes()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/pdgd/PDGD_Types.dll:Calling registerPDGDTypes()
DSO_INFO:DONE Running registerPDGDTypes() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:registerPDGDTypes:Time elapsed 0.024684s
DSO_INFO:Running CLregisterClipReader() in reverse order in search path
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Time elapsed 0.000702s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Find CLregisterClipReader()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_AudiereClipReader.dll:Calling CLregisterClipReader()
DSO_INFO:DONE Running CLregisterClipReader() in reverse order in search path
DSO_INFO:CLregisterClipReader in reverse order:Time elapsed 0.049392s
DSO_INFO:Running CLregisterClipWriter() in reverse order in search path
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Time elapsed 0.000576s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Find CLregisterClipWriter()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/audio/CL_SndfileClipWriter.dll:Calling CLregisterClipWriter()
DSO_INFO:DONE Running CLregisterClipWriter() in reverse order in search path
DSO_INFO:CLregisterClipWriter in reverse order:Time elapsed 0.049565s
DSO_INFO:Running newManagerOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newManagerOperator() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newManagerOperator:Time elapsed 0.000068s
DSO_INFO:libLOP.dll:Attempt load
DSO_INFO:libLOP.dll:Loaded
DSO_INFO:libLOP.dll:Time elapsed 0.000029s
DSO_INFO:libPBR.dll:Attempt load
DSO_INFO:libPBR.dll:Loaded
DSO_INFO:libPBR.dll:Time elapsed 0.000252s
DSO_INFO:libGVEX.dll:Attempt load
DSO_INFO:libGVEX.dll:Loaded
DSO_INFO:libGVEX.dll:Time elapsed 0.000029s
DSO_INFO:libVMAT.dll:Attempt load
DSO_INFO:libVMAT.dll:Loaded
DSO_INFO:libVMAT.dll:Time elapsed 0.003314s
DSO_INFO:Running newVEXOp() in path[1] with C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll:Time elapsed 0.000269s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll:Find newVEXOp()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll:Calling newVEXOp()
DSO_INFO:DONE Running newVEXOp() in path[1] with C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/vex/VEX_OpRender.dll
DSO_INFO:Time elapsed: 0.000460 s
DSO_INFO:Running newRenderOption() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newRenderOption() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newRenderOption:Time elapsed 0.000079s
DSO_INFO:Running newRenderHook() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Attempt load
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Loaded
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Time elapsed 0.000306s
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Finding HoudiniDSOVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Calling HoudiniDSOVersion
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Finding HoudiniCompilerVersion()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:HoudiniDSOVersion() and HoudiniCompilerVersion() check success
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Find newRenderHook()
DSO_INFO:C:/PROGRA~1/SIDEEF~1/HOUDIN~1.383/houdini/dso/SOP_VDBUI.dll:Calling newRenderHook()
DSO_INFO:DONE Running newRenderHook() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newRenderHook:Time elapsed 0.000613s
DSO_INFO:Running DMnewEventHook() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running DMnewEventHook() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DMnewEventHook:Time elapsed 0.000075s
DSO_INFO:Running newVisualizerType() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:DONE Running newVisualizerType() in HOUDINI_DSO_PATH, HOUDINI_IMAGE_DSO_PATH, HOUDINI_AUDIO_DSO_PATH
DSO_INFO:newVisualizerType:Time elapsed 0.000072s
-- 1 ---------------------------------------------------------------------------
```

## How to Use NaniteTree's node in Houdini of your version

    如何在你本地版本的Houdini使用NaniteTree的减面节点

注: 在这里测试了Houdini 18.5以及Houdini 19.5, 编译测试了Visual Studio2019 以及2022均没有问题

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

4. Installing CGAL, Boost with Vcpkg
  `https://doc.cgal.org/latest/Manual/windows.html`

```shell
./vcpkg.exe install cgal:x64-windows
./vcpkg.exe install boost:x64-windows
./vcpkg.exe integrate install
```

5. 配置vcpkg环境变量,本文PATH均为系统变量的PATH，即下半个界面

```cmd
PATH C:\dev\vcpkg\installed\x64-windows\bin

PATH C:\dev\vcpkg\installed\x64-windows\debug\bin
```

6. 调⽤CMakeLists⽂件，在houdini中找到Command Line Tools

```shell
mkdir build
cd build
cmake -G "Visual Studio 16 2019" -A x64 .. 
或者
cmake -G "Visual Studio 17 2022" -A x64 .. 
```

7. 打开生成sln，鼠标右键NaniteSimplification设置成启动项目并点击生成,成功以后就能看到dso⽂件夹里面的⽂件

8. 打开Houdini，创建⼀个Geometry节点，进⼊节点内部，按tab键，找到Coustom就可以看到刚才⽣成的节点。
