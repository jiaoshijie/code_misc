import sys
# user define
# import req
import extractor
import downloader


def main():
    if len(sys.argv) == 1:
        print("\033[31mError:\033[0m There must be 2 arguments in here.")
        exit(1)

    url = sys.argv[1].strip()
    download(url)


def download(url):
    # bilibli video 解析器
    etr = extractor.biliExtractor()
    dl_info = etr.get_playlist(url)
    # 下载器
    # dler = downloader.dler()
    # dler.download(dl_info)


if __name__ == "__main__":
    main()
