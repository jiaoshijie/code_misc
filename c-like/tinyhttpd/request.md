# request
## chrome GET

```
GET / HTTP/1.1\r\n
Host: localhost:8088\r\n
Connection: keep-alive\r\n
Upgrade-Insecure-Requests: 1\r\n
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/75.0.3770.100 Safari/537.36\r\n
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3\r\n
Accept-Encoding: gzip, deflate, br\r\n
Accept-Language: en\r\n\r\n
```

## curl GET

  - `GET / HTTP/1.1\r\nHost: localhost:8088\r\nUser-Agent: curl/7.65.3\r\nAccept: */*\r\n\r\n`

## chrome POST(后面会自动加上form的method)

```
POST HTTP/1.1\r\n
Host: localhost:58239
Connection: keep-alive
Content-Length: 12
Cache-Control: max-age=0
Origin: http://localhost:58239
Upgrade-Insecure-Requests: 1
Content-Type: application/x-www-form-urlencoded
User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/76.0.3809.132 Safari/537.36
Sec-Fetch-Mode: navigate
Sec-Fetch-User: ?1
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3
Sec-Fetch-Site: same-origin
Referer: http://localhost:58239/
Accept-Encoding: gzip, deflate, br
Accept-Language: en
```

# questions
## cgi如何获取参数

1. GET 请求
  - 通过环境变量`QUERY_STRING`获取参数(只能处理简单的cgi程序)
2. POST 请求
  - post请求是通过读取stdin中的数据

## 为什么有时候printf函数必须输入\n符才可以打印到屏幕?

1. 在accept() 函数执行后, 会出现printf函数必须有\n符才可以打印到屏幕的问题.
2. 或者使用fflush(stdout)；
3. 因为shell是存在行缓冲的（每次攒够一行（出现换行符））才会输出，所以这里在printf的末尾加上\n就可以正常输出了
