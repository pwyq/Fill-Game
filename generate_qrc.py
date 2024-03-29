"""
# @author      Yanqing Wu
# @email       meet.yanqing.wu@gmail.com
# @create date 2023-02-11 11:16:43
# @modify date 2023-02-11 11:17:29
# @desc This python script is used to generate Qt .qrc file.
Update this file with care.

Usage:
    $ python generate_qrc.py > fillgame.qrc
"""


import os
import sys


def header() -> str:
    t = '''<!--
This file is automatically generated by fillgame/generate_qrc.py
Please do NOT manually update this fillgame.qrc file, nor rename this file.

After adding resource files in fillgame/resource, update this file by following:

    $ python generate_qrc.py > fillgame.qrc

-->

<!DOCTYPE RCC><RCC version="1.0">
<qresource>'''
    return t


def extra_files() -> str:
    t = '''    <file>resource/css_files/darkstyle.qss</file>'''
    return t


def body() -> str:
    excluding = ['.md', '.MD', '.zip', '.ZIP', '.osgt', '.keep']
    os.chdir("./resource")
    root_dir = os.path.dirname(os.path.realpath(__file__))
    prefix_len = len(root_dir) + 1

    output_text = ""

    for subdir, dirs, files in os.walk(root_dir):
        for file in files:
            file_name, file_extension = os.path.splitext(file)
            if file_extension in excluding:
                continue
            res = os.path.join(subdir, file)
            if "css_files" in res:
                continue
            if "resource" in res:
                if sys.platform.startswith('win32'):
                    file_path = res[prefix_len:].replace("\\", "/")
                elif sys.platform.startswith('linux'):
                    file_path = res[prefix_len:]
                else:
                    sys.exit(
                        'The OS is not supported yet. Please manually update.')
                res_str = "    <file>resource/" + file_path + "</file>\n"
                output_text += res_str
    output_text = output_text[:-1]  # remove last \n
    return output_text


def footer() -> str:
    t = '''</qresource>
</RCC>'''
    return t


print(header())
# print(extra_files())
print(body())
print(footer())
