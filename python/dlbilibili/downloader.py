import os
import req
import utils


class dler:
    def __init__(self, title='dl_video'):
        self.title = title

    def file_size(self, path):
        try:
            return os.path.getsize(path)
        except FileNotFoundError:
            return 0

    def write2file(self, f, url, headers):
        html, err = req.Get(url)
        written = f.write(html.content)
        return written

    def save(self, info, path):
        headers = req.FakeHeader
        headers['Referer'] = 'https://www.bilibili.com/'
        tempFile = path + '.dl'
        tempSize = self.file_size(tempFile)
        if tempSize > 0:
            f = open(tempFile, 'ab')
            headers['Range'] = 'bytes={}-'.format(tempSize)
        else:
            f = open(tempFile, 'xb')

        self.write2file(f, info['url'], headers)

        f.close()
        os.rename(tempFile, path)  # rename file

    def download(self, dlinfo):
        filePath = './' + self.title + '.' + dlinfo['video']['type']
        if os.path.exists(filePath):
            print('{}: file already exists!!! nothing to do.'.format(filePath))
            exit(0)

        paths = []
        for i, info in enumerate(dlinfo):
            partPath = './' + self.title + \
                '[{}].'.format(i) + dlinfo[info]['type']
            paths.append(partPath)
            self.save(dlinfo[info], partPath)
        utils.merge(paths, filePath)
        for i in paths:
            if os.path.exists(i):
                os.remove(i)
