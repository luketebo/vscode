import os
import requests
url=input("请输入图片的url地址：")
root="D://Desktop//"
path=root+"图片."+url.split('.')[-1]
try:
    if not os.path.exists(root):
        os.mkdir(root)
    if not os.path.exists(path):
        r=requests.get(url)
        with open(path, 'wb') as f:
            f.write(r.content)
            f.close()
            print("文件保存成功!")
    else:
        print("文件已存在!")
except:
    print("爬取失败!")