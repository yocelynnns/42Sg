#!/usr/bin/perl
use strict;
use warnings;

print "Content-Type: text/html; charset=utf-8\n\n";

print <<'HTML';
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>Perl CGI - Form Handler</title>
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
        <h1>📝 Perl Form Handler</h1>
HTML

if ($ENV{'REQUEST_METHOD'} eq 'POST') {
    my $query_string = '';
    if ($ENV{'REQUEST_METHOD'} eq 'POST') {
        read(STDIN, $query_string, $ENV{'CONTENT_LENGTH'});
    } else {
        $query_string = $ENV{'QUERY_STRING'} || '';
    }
    
    # Parse the form data
    my %form_data;
    my @pairs = split(/&/, $query_string);
    foreach my $pair (@pairs) {
        my ($key, $value) = split(/=/, $pair);
        $key =~ s/\+/ /g;
        $value =~ s/\+/ /g;
        $key =~ s/%([0-9A-Fa-f]{2})/pack('H2', $1)/ge;
        $value =~ s/%([0-9A-Fa-f]{2})/pack('H2', $1)/ge;
        $form_data{$key} = $value;
    }
    
    my $name = $form_data{'name'} || 'Not provided';
    my $email = $form_data{'email'} || 'Not provided';
    my $message = $form_data{'message'} || 'Not provided';
    
    print <<"HTML";
        <div class="result">
            <h2>✅ Form Submitted Successfully!</h2>
            <p><strong>Name:</strong> $name</p>
            <p><strong>Email:</strong> $email</p>
            <p><strong>Message:</strong> $message</p>
        </div>
HTML
}

print <<'HTML';
        <form method="POST" action="/perl/form.pl">
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
</html>
HTML