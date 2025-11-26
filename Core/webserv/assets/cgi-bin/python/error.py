#!/usr/bin/python3
import sys
# Intentionally malformed output (missing Content-Type)
sys.stdout.write("This is malformed CGI output without headers\n")
sys.stdout.flush()
