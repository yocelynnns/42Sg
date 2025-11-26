#!/usr/bin/env python3
import time

print("Content-Type: text/html\r")
print("\r")
print("<html><body>")
print("<h1>This should never display</h1>")
print("</body></html>")

# Infinite loop to trigger timeout
while True:
    time.sleep(1)