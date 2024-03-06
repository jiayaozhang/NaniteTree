import unreal
import json
import os

#json路径
pypath = os.path.abspath(__file__).split("\\")[:-1]
pypath = "/".join(pypath)
AssetsJsonPath= pypath +'\\out.json'
assetpath=pypath
print(AssetsJsonPath)
print(assetpath)


#导入方法（需要导出的资产，导出路径）


def build_import_task(src_path, des_path,asset_name):
        task = unreal.AssetImportTask()
        task.set_editor_property('automated', True)
        task.set_editor_property('destination_name', asset_name)
        task.set_editor_property('destination_path', des_path)
        task.set_editor_property('filename', src_path)
        task.set_editor_property('replace_existing', True)
        task.set_editor_property('save', True)
        return task


tasks=[]
def startimport():
    with open(AssetsJsonPath,'r') as load_aj:
        load_aj_dict = json.load(load_aj)
        print(load_aj_dict)

    for asset in load_aj_dict[0:2]:

        meshpath=asset["Path"]
        #assetpath+'/'.join(asset["Mesh"].split(".")[:-1])+".FBX"

        despath='/'.join(asset["Mesh"].split("/")[:-1])

        meshnaeme=asset["Mesh"].split("/")[-1].split(".")[0]
        #print(meshpath,despath,meshnaeme)

        tasks.append(build_import_task(meshpath, despath, meshnaeme))#创建导入任务列表
    unreal.AssetToolsHelpers.get_asset_tools().import_asset_tasks(tasks)

startimport()

