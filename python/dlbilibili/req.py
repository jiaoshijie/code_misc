import requests


FakeHeader = {
    "Accept":          "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8",
    "Accept-Charset":  "UTF-8,*;q=0.5",
    "Accept-Encoding": "gzip,deflate,sdch",
    "Accept-Language": "en-US,en;q=0.8",
    "User-Agent":      "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_13_6) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/69.0.3497.81 Safari/537.36",
}


class HttpError(Exception):
    pass


def Get(url, headers=FakeHeader, referer=""):
    if "Referer" not in headers:
        headers["Referer"] = url if referer == "" else referer
    html = requests.get(url, headers=headers)
    if html.status_code >= 400:
        return html, HttpError("connot connect the server.")

    return html, 0


def Size(url):
    html, err = Get(url, referer="https://www.bilibili.com/")
    if err != 0:
        return -1, err
    return html.headers['Content-Length'], 0
