# use ffmpeg to merge video and audio
import os


def merge(paths, output):
    args = ''
    for i in paths:
        args += '-i ' + i + ' '
    args += '-c:v copy -c:a copy ' + output
    os.system('ffmpeg ' + args)
