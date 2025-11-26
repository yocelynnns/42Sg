#!/usr/bin/python3
import os
import urllib.parse

# Parse query string
query_string = os.environ.get('QUERY_STRING', '')
params = urllib.parse.parse_qs(query_string)

# Get parameters
a = float(params.get('a', [0])[0])
b = float(params.get('b', [0])[0])
op = params.get('op', ['add'])[0]

# Perform calculation
result = 0
operation_name = ""

if op == 'add':
    result = a + b
    operation_name = "Addition"
elif op == 'sub':
    result = a - b
    operation_name = "Subtraction"
elif op == 'mul':
    result = a * b
    operation_name = "Multiplication"
elif op == 'div':
    if b != 0:
        result = a / b
        operation_name = "Division"
    else:
        result = "Error: Division by zero"
        operation_name = "Division"
else:
    result = "Unknown operation"
    operation_name = "Unknown"

print("Content-Type: text/html; charset=utf-8\n")
print(f"""<!DOCTYPE html>
<html>
<head>
<link rel="icon" href="data:,">
    <title>Python Calculator CGI</title>
    <style>
        * {{ margin: 0; padding: 0; box-sizing: border-box; }}
        body {{ font-family: 'Courier New', monospace; background: #1e1e2e; color: #e0e0e0; padding: 40px; }}
        .container {{ background: #2d2d44; border: 2px solid #00ff88; padding: 30px; border-radius: 10px; max-width: 600px; margin: 0 auto; }}
        h1 {{ color: #00ff88; text-shadow: 0 0 10px rgba(0, 255, 136, 0.5); margin-bottom: 20px; }}
        h3 {{ color: #00ff88; margin: 25px 0 15px; }}
        .result {{ background: rgba(0, 255, 136, 0.15); border: 2px solid #00ff88; padding: 20px; border-radius: 10px; margin: 20px 0; text-align: center; }}
        .result p {{ color: #aaa; margin-bottom: 10px; }}
        .result h2 {{ margin: 10px 0 0; color: #00ff88; font-size: 2em; text-shadow: 0 0 10px rgba(0, 255, 136, 0.3); }}
        .calculator {{ margin-top: 30px; }}
        .form-group {{ margin: 15px 0; }}
        label {{ display: block; margin-bottom: 6px; font-weight: bold; color: #00ff88; font-size: 0.95em; }}
        input, select {{ width: 100%; padding: 10px 12px; border: 1px solid #00ff88; border-radius: 5px; background: rgba(0, 255, 136, 0.05); color: #e0e0e0; font-family: inherit; font-size: 14px; }}
        input:focus, select:focus {{ outline: none; border-color: #00dd66; box-shadow: 0 0 10px rgba(0, 255, 136, 0.2); }}
        button {{ background: linear-gradient(135deg, #00ff88, #00dd66); color: #1e1e2e; padding: 12px 30px; border: none; border-radius: 5px; cursor: pointer; font-weight: bold; margin-top: 15px; box-shadow: 0 0 15px rgba(0, 255, 136, 0.3); }}
        button:hover {{ box-shadow: 0 0 25px rgba(0, 255, 136, 0.5); }}
        .examples {{ background: rgba(0, 255, 136, 0.1); border-left: 4px solid #00ff88; padding: 15px; border-radius: 5px; margin-top: 20px; color: #aaa; }}
        .examples code {{ background: rgba(0, 0, 0, 0.3); padding: 4px 8px; border-radius: 3px; color: #00ff88; font-size: 0.9em; }}
        a {{ color: #00ff88; text-decoration: none; }}
        a:hover {{ text-decoration: underline; }}
    </style>
</head>
<body>
    <div class="container">
        <h1>🧮 Python Calculator</h1>
        
        <div class="result">
            <p><strong>{operation_name}:</strong> {a} {op} {b}</p>
            <h2>Result: {result}</h2>
        </div>
        
        <div class="calculator">
            <h3>Try Another Calculation</h3>
            <form method="GET" action="/cgi-mixed/calc.py">
                <div class="form-group">
                    <label>Number A:</label>
                    <input type="number" name="a" value="{a}" step="any" required>
                </div>
                <div class="form-group">
                    <label>Operation:</label>
                    <select name="op">
                        <option value="add" {'selected' if op == 'add' else ''}>Addition (+)</option>
                        <option value="sub" {'selected' if op == 'sub' else ''}>Subtraction (-)</option>
                        <option value="mul" {'selected' if op == 'mul' else ''}>Multiplication (×)</option>
                        <option value="div" {'selected' if op == 'div' else ''}>Division (÷)</option>
                    </select>
                </div>
                <div class="form-group">
                    <label>Number B:</label>
                    <input type="number" name="b" value="{b}" step="any" required>
                </div>
                <button type="submit">Calculate</button>
            </form>
        </div>
        
        <div class="examples">
            <strong>Example URLs:</strong><br>
            <code>/cgi-mixed/calc.py?a=10&b=5&op=add</code><br>
            <code>/cgi-mixed/calc.py?a=20&b=4&op=div</code><br>
            <code>/cgi-mixed/calc.py?a=7&b=3&op=mul</code>
        </div>
        
        <p style="margin-top: 20px;"><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>""")
