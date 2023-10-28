import os
import re
import shutil

# 获取当前目录下的所有文件
files = os.listdir()

# 遍历每个文件
for file in files:
    # 只处理以 .cpp 结尾的文件
    if file.endswith('.cpp'):
        # 提取字母部分和数字部分
        match = re.match(r'([A-Za-z])(\d+)', file)
        if match:
            letter = match.group(1)
            digits = match.group(2)
            
            # 提取除最后两位外的数字部分
            digits_except_last_two = digits[:-2]
            
            # 创建对应的文件夹（如果不存在）
            folder = os.path.join(os.getcwd(), f'{letter}{digits_except_last_two}XX')
            if not os.path.exists(folder):
                os.makedirs(folder)
            
            # 移动文件到对应的文件夹中
            src = os.path.join(os.getcwd(), file)
            dst = os.path.join(folder, file)
            shutil.move(src, dst)

print("文件分类完成！")