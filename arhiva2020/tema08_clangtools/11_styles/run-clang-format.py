import subprocess
import os
import sys

def isccppfile(filename):
    return filename.endswith('.h') \
        or filename.endswith('.c') \
        or filename.endswith('.hpp') \
        or filename.endswith('.cpp') \

if __name__ == "__main__":
    args = sys.argv[1:]
    if len(args) < 2:
        print('Usage: python3 run-clang-format.py <dir> <style>')
        exit(1)

    dir   = args[0]
    style = args[1]

    for dir, _, files in os.walk(dir):
        for filename in files:
            filepath = dir + '/' + filename
            if isccppfile(filename):
                subprocess.run('clang-format -i -style={} {}'.format(style, filepath), shell=True)