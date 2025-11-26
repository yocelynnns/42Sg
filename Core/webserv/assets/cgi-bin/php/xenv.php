#!/usr/bin/php-cgi
<?php
// Start output buffering immediately
ob_start();

// Force all errors to be displayed
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);

// Headers must come first
header("Content-Type: text/plain; charset=utf-8");

echo "=== PHP CGI DEBUG ===\n";
echo "PHP Version: " . phpversion() . "\n";
echo "Current Dir: " . getcwd() . "\n";
echo "Script: " . $_SERVER['SCRIPT_FILENAME'] . "\n";
echo "SAPI: " . php_sapi_name() . "\n\n";

echo "=== Environment Variables ===\n";
foreach ($_SERVER as $key => $value) {
    echo "$key: $value\n";
}

echo "\n=== PHP Configuration ===\n";
echo "output_buffering: " . ini_get('output_buffering') . "\n";
echo "implicit_flush: " . ini_get('implicit_flush') . "\n";
echo "display_errors: " . ini_get('display_errors') . "\n";

// Test if we can write to output
echo "\n=== Output Test ===\n";
echo "This is a test line.\n";

// Force flush all buffers
while (ob_get_level() > 0) {
    ob_end_flush();
}
?>