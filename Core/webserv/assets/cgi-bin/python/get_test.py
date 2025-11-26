#!/usr/bin/python3
import os, sys, urllib.parse

method = os.environ.get("REQUEST_METHOD", "GET")
print("Content-Type: text/html\n")

print("<html><body><h1>CGI GET/POST Echo</h1><pre>")

if method == "GET":
    query = os.environ.get("QUERY_STRING", "")
    print("QUERY_STRING:", query)
    params = urllib.parse.parse_qs(query)
elif method == "POST":
    length = int(os.environ.get("CONTENT_LENGTH", 0))
    body = sys.stdin.read(length)
    print("POST BODY:", body)
    params = urllib.parse.parse_qs(body)
else:
    print(f"Unsupported method: {method}")
    params = {}

print("\nParsed parameters:\n")
for k, v in params.items():
    print(f"{k} = {v}")
print("</pre></body></html>")
