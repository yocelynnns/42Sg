#!/usr/bin/env python3

# Try to import a non-existent module
import this_module_does_not_exist_at_all

print("Content-Type: text/html\r")
print("\r")
print("<h1>This should never be displayed</h1>")
