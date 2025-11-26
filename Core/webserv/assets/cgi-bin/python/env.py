#!/usr/bin/python3
import os

print("Content-Type: text/html; charset=utf-8\n")
print("""<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>Python CGI - Environment Variables</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: 'Courier New', monospace; background: #1e1e2e; color: #e0e0e0; padding: 40px; }
        .container { background: #2d2d44; border: 2px solid #00ff88; padding: 30px; border-radius: 10px; max-width: 800px; margin: 0 auto; }
        h1 { color: #00ff88; text-shadow: 0 0 10px rgba(0, 255, 136, 0.5); margin-bottom: 20px; }
        table { width: 100%; border-collapse: collapse; margin-top: 20px; }
        th { background: #00ff88; color: #1e1e2e; padding: 12px; text-align: left; font-weight: bold; }
        td { padding: 12px; border-bottom: 1px solid #00ff88; }
        tr:hover { background: rgba(0, 255, 136, 0.05); }
        td:first-child { color: #00ff88; font-weight: bold; }
        td:last-child { color: #aaa; word-break: break-all; }
        a { color: #00ff88; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>

</head>
<body>
    <div class="container">
        <h1>🔧 CGI Environment Variables (Python)</h1>
        <table>
            <tr><th>Variable</th><th>Value</th></tr>""")

for key, value in sorted(os.environ.items()):
    print(f"<tr><td><strong>{key}</strong></td><td>{value}</td></tr>")

print("""        </table>
        <p style="margin-top: 20px;"><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>""")