#!/usr/bin/python3
import sys
import os
import urllib.parse

# Read POST data
content_length = int(os.environ.get('CONTENT_LENGTH', 0))
post_data = sys.stdin.read(content_length) if content_length > 0 else ''
form_data = urllib.parse.parse_qs(post_data)

print("Content-Type: text/html; charset=utf-8\n")
print("""<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>Python CGI - Form Handler</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: 'Courier New', monospace; background: #1e1e2e; color: #e0e0e0; padding: 40px; }
        .container { background: #2d2d44; border: 2px solid #00ff88; padding: 30px; border-radius: 10px; max-width: 600px; margin: 0 auto; }
        h1 { color: #00ff88; text-shadow: 0 0 10px rgba(0, 255, 136, 0.5); margin-bottom: 20px; }
        .info { background: rgba(0, 255, 136, 0.1); border-left: 4px solid #00ff88; padding: 15px; border-radius: 5px; margin-top: 20px; color: #aaa; line-height: 1.6; }
        .form-group { margin-bottom: 15px; }
        label { display: block; margin-bottom: 6px; font-weight: bold; color: #00ff88; font-size: 0.95em; }
        input, textarea { width: 100%; padding: 10px 12px; border: 1px solid #00ff88; border-radius: 5px; background: rgba(0, 255, 136, 0.05); color: #e0e0e0; font-family: inherit; font-size: 14px; }
        input:focus, textarea:focus { outline: none; border-color: #00dd66; box-shadow: 0 0 10px rgba(0, 255, 136, 0.2); }
        button { background: linear-gradient(135deg, #00ff88, #00dd66); color: #1e1e2e; padding: 10px 20px; border: none; border-radius: 5px; font-weight: bold; cursor: pointer; margin-top: 10px; }
        button:hover { box-shadow: 0 0 15px rgba(0, 255, 136, 0.4); }
        a { color: #00ff88; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <div class="container">
        <h1>📝 Python Form Handler</h1>""")

if os.environ.get('REQUEST_METHOD') == 'POST' and form_data:
    name = form_data.get('name', ['Not provided'])[0]
    email = form_data.get('email', ['Not provided'])[0]
    message = form_data.get('message', ['Not provided'])[0]
    
    print(f"""        <div class="result">
            <h2>✅ Form Submitted Successfully!</h2>
            <p><strong>Name:</strong> {name}</p>
            <p><strong>Email:</strong> {email}</p>
            <p><strong>Message:</strong> {message}</p>
        </div>""")

print("""        <form method="POST" action="/python/form.py">
            <div class="form-group">
                <label>Name:</label>
                <input type="text" name="name" required>
            </div>
            <div class="form-group">
                <label>Email:</label>
                <input type="email" name="email" required>
            </div>
            <div class="form-group">
                <label>Message:</label>
                <textarea name="message" rows="4" required></textarea>
            </div>
            <button type="submit">Submit Form</button>
        </form>
        <p style="margin-top: 20px;"><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>""")