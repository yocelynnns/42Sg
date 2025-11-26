#!/usr/bin/python3
import cgi, os

upload_dir = "./uploads"
os.makedirs(upload_dir, exist_ok=True)

form = cgi.FieldStorage()

print("Content-Type: text/html\n")
print("""<html>
<head>
    <link rel="icon" href="data:,">
    <meta charset="UTF-8">
    <title>File Upload Result</title>
</head>
<body>
    <h1>File Upload Result</h1>""")

# Extract the name field
name = form.getvalue("name")  # returns None if not submitted
if name:
    print(f"<p>👤 Name: {name}</p>")

if "uploadfile" in form:
    file_item = form["uploadfile"]
    if file_item.filename:
        filename = os.path.basename(file_item.filename)
        filepath = os.path.join(upload_dir, filename)
        with open(filepath, "wb") as f:
            f.write(file_item.file.read())
        print(f"<p>✅ Uploaded as: {filepath}</p>")
    else:
        print("<p>No file selected!</p>")
else:
    print("<p>No file received!</p>")

print("</body></html>")
