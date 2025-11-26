#!/usr/bin/perl
use strict;
use warnings;

print("Content-Type: text/html; charset=utf-8\n\n");

my ($sec,$min,$hour,$mday,$mon,$year) = localtime();
my $current_time = sprintf "%04d-%02d-%02d %02d:%02d:%02d", $year+1900, $mon+1, $mday, $hour, $min, $sec;
my $request_method = $ENV{'REQUEST_METHOD'} || 'Unknown';
my $script_name = $ENV{'SCRIPT_NAME'} || 'Unknown';
my $query_string = $ENV{'QUERY_STRING'} || 'None';

print <<"HTML";
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>Perl CGI - Hello World</title>
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
        <h1>✅ Perl CGI Working!</h1>
        <p><strong>Current Time:</strong> $current_time</p>
        <div class="info">
            <strong>Request Method:</strong> $request_method<br>
            <strong>Script Name:</strong> $script_name<br>
            <strong>Query String:</strong> $query_string
        </div>
        <p><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>
HTML