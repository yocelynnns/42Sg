#!/usr/bin/env python3

# This CGI simulates checking for POST when GET is used
# But actually, we'll use HTML form redirect to trigger real 405

import cgi
import os

print("Content-Type: text/html\r")
print("\r")

method = os.environ.get('REQUEST_METHOD', 'GET')

print("""
<!DOCTYPE html>
<html>
<head>
    <title>405 Test</title>
    <script>
        // Redirect to a POST-only location using GET
        window.location.href = '/post-only/test.html';
    </script>
</head>
<body>
    <h1>Redirecting to trigger 405...</h1>
    <p>You'll be redirected to a POST-only location using GET method.</p>
</body>
</html>
""")
