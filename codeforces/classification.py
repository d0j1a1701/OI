import os
import shutil

# 获取当前目录下的所有文件
files = os.listdir()

# 遍历每个文件
for file in files:
    # 只处理以 .cpp 结尾的文件
    if file.endswith('.cpp'):
        # 提取前缀数字和第一个字母
        prefix = ''
        first_letter = ''
        for char in file:
            if char.isdigit():
                prefix += char
            else:
                first_letter = char
                break
        
        # 创建对应的文件夹（如果不存在）
        folder = os.path.join(os.getcwd(), prefix)
        if not os.path.exists(folder):
            os.makedirs(folder)
        
        # 移动文件到对应的文件夹中
        src = os.path.join(os.getcwd(), file)
        dst = os.path.join(folder, file)
        shutil.move(src, dst)

print("文件分类完成！")