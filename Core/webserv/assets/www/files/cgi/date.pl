#!/usr/bin/perl
use strict;
use warnings;
use POSIX qw(strftime);

print "Content-Type: text/html; charset=utf-8\n\n";

my $date = strftime "%A, %B %d, %Y", localtime;
my $time = strftime "%H:%M:%S", localtime;
my $timezone = strftime "%Z", localtime;
my $timestamp = time();

print <<HTML;
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>Perl Date/Time CGI</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: 'Courier New', monospace; background: #1e1e2e; color: #e0e0e0; padding: 40px; }
        .container { background: #2d2d44; border: 2px solid #00ff88; padding: 30px; border-radius: 10px; max-width: 600px; margin: 0 auto; }
        h1 { color: #00ff88; text-shadow: 0 0 10px rgba(0, 255, 136, 0.5); margin-bottom: 20px; }
        .datetime-display { background: rgba(0, 255, 136, 0.15); border: 2px solid #00ff88; color: #00ff88; padding: 30px; border-radius: 10px; margin: 20px 0; text-align: center; }
        .datetime-display h2 { margin: 10px 0; font-size: 2.5em; text-shadow: 0 0 10px rgba(0, 255, 136, 0.3); }
        .datetime-display p { margin: 5px 0; font-size: 1.2em; opacity: 0.9; color: #aaa; }
        .info-grid { display: grid; grid-template-columns: 1fr 1fr; gap: 15px; margin-top: 20px; }
        .info-card { background: rgba(0, 255, 136, 0.1); border: 1px solid #00ff88; padding: 15px; border-radius: 5px; text-align: center; }
        .info-card strong { display: block; color: #00ff88; margin-bottom: 5px; font-weight: bold; }
        .info-card div { color: #aaa; font-size: 0.95em; }
        button { background: linear-gradient(135deg, #00ff88, #00dd66); color: #1e1e2e; padding: 12px 30px; border: none; border-radius: 5px; cursor: pointer; font-weight: bold; margin-top: 20px; box-shadow: 0 0 15px rgba(0, 255, 136, 0.3); }
        button:hover { box-shadow: 0 0 25px rgba(0, 255, 136, 0.5); }
        a { color: #00ff88; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>
    <script>
        function refreshPage() {
            window.location.reload();
        }
    </script>
</head>
<body>
    <div class="container">
        <h1>🕐 Perl Date/Time Display</h1>
        
        <div class="datetime-display">
            <p>$date</p>
            <h2>$time</h2>
            <p>$timezone</p>
        </div>
        
        <div class="info-grid">
            <div class="info-card">
                <strong>Unix Timestamp</strong>
                <div>$timestamp</div>
            </div>
            <div class="info-card">
                <strong>Server Time</strong>
                <div>$time</div>
            </div>
        </div>
        
        <button onclick="refreshPage()">🔄 Refresh Time</button>
        
        <p style="margin-top: 20px;"><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>
HTML
