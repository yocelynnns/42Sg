#!/usr/bin/env python3

print("Content-Type: text/html\r")
print("\r")

print("""
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>400 Test Info</title>
    <style>
        body { font-family: Arial; padding: 20px; }
        .note { background: #e7f3ff; padding: 15px; border-left: 4px solid #2196F3; margin: 15px 0; }
        .code { background: #f4f4f4; padding: 10px; font-family: monospace; margin: 10px 0; }
    </style>
</head>
<body>
    <h1>400 - Bad Request Test</h1>
    
    <div class="note">
        <strong>Note:</strong> Modern browsers always send well-formed HTTP requests. 
        You cannot trigger 400 Bad Request via browser click.
    </div>
    
    <h2>Use telnet/netcat instead:</h2>
    
    <div class="code">
        echo -e "GET / HTTP/1.1\\r\\nBad Header\\r\\n\\r\\n" | nc 127.0.0.1 8015
    </div>
    
    <p>Or send request without Host header:</p>
    <div class="code">
        echo -e "GET / HTTP/1.1\\r\\n\\r\\n" | nc 127.0.0.1 8015
    </div>
    
    <p><a href="/error-test.html">← Back to Error Tests</a></p>
</body>
</html>
""")
