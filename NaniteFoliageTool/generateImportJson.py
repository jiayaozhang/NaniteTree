import json
import os

root = {}
data = []
workpath = os.path.abspath('.') + "\\"
print("当前工作路径为 : " + workpath)

#遍历所有路径 生成json数据
def list_files(directory):
    for root, dirs, files in os.walk(directory):
        for file in files:
            '''print(os.path.join(root, file))'''
            fn = os.path.join(root, file)
            ftype = fn.split('.')[1]

            if ftype == "FBX":
                import_path = fn.split('Game')[1].split('SM_')[0]
                filename = "SM_" + fn.split('Game')[1].split('SM_')[1].replace(".FBX","").replace("\\","")
                '''filename += "." + filename'''
                import_path = '\\Game' + import_path
                tex = fn.split('Game')[0].replace(workpath,"").replace(import_path,"").replace("\\","")
                temp = {
                    "Name" : filename,
                    "Mesh": import_path.replace("\\","/") + filename + "." + filename,
                    "Texture":  import_path.replace("\\","/") + "Textures/" + tex + "." +tex,
                    "Path": fn.replace("\\","/"),
                    "LeafMat": "Ignore"
                }
                data.append(temp)
            else:
                print(ftype + "  Pass File!")




def isDir(path):
    if os.path.isdir(path):
        return True
    return False


'''返回json格式数据'''
def getJson(root):
    return json.dumps(root)

list_files(workpath)
out_json = getJson(data)

#写入文件
fp = open(workpath+'out.json','w')
fp.write(out_json)
fp.close()