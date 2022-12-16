#! /usr/bin/python3
import cgi

content = cgi.FieldStorage()

print("Content-type: text/html")
print()

print('<html>')
print('<head>')
print('<meta charset="utf-8">')
print('<title>Color</title>')
print('</head>')
print('<body style="background-color:{}">'.format(content.getvalue("color")))
#  print('<h2>Your name is {}.</h2>'.format(content.getvalue("name")))
print('</body>')
print('</html>')
