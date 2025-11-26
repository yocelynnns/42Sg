#!/usr/bin/env python3

print("Content-Type: text/html\r")
print("\r")

# Generate a page with a huge form that exceeds client_max_body_size
print("""
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>413 Test - Payload Too Large</title>
    <style>
        body { font-family: Arial; padding: 20px; }
        .warning { background: #fff3cd; padding: 15px; border-left: 4px solid #ffc107; }
        button { padding: 10px 20px; background: #dc3545; color: white; border: none; cursor: pointer; }
    </style>
</head>
<body>
    <h1>413 - Payload Too Large Test</h1>
    <div class="warning">
        <strong>Warning:</strong> Clicking submit will send 100KB+ of data to a location with 50KB limit.
    </div>
    
    <form method="POST" action="/upload-small">
        <input type="hidden" name="large_data" value="
""")

# Output 100KB of data
print("A" * 100000)

print("""">
        <p><button type="submit">Submit Large Payload (Trigger 413)</button></p>
    </form>
    
    <p><a href="/error-test.html">← Back to Error Tests</a></p>
</body>
</html>
""")
