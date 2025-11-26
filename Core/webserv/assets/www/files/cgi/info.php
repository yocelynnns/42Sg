<?php
header('Content-Type: text/html; charset=utf-8');

// Get fibonacci count from query string
$count = isset($_GET['count']) ? max(1, min(50, intval($_GET['count']))) : 15;

// Generate fibonacci sequence
$fib = [];
$a = 0;
$b = 1;

for ($i = 0; $i < $count; $i++) {
    $fib[] = $a;
    $temp = $a + $b;
    $a = $b;
    $b = $temp;
}

$sum = array_sum($fib);
$max = max($fib);
$avg = $count > 0 ? round($sum / $count, 2) : 0;

?>
<!DOCTYPE html>
<html>
<head>
	<link rel="icon" href="data:,">
    <title>PHP Fibonacci Generator</title>
    <style>
        * { margin: 0; padding: 0; box-sizing: border-box; }
        body { font-family: 'Courier New', monospace; background: #1e1e2e; color: #e0e0e0; padding: 40px; }
        .container { background: #2d2d44; border: 2px solid #00ff88; padding: 30px; border-radius: 10px; max-width: 700px; margin: 0 auto; }
        h1 { color: #00ff88; text-shadow: 0 0 10px rgba(0, 255, 136, 0.5); margin-bottom: 20px; }
        .sequence-box { background: rgba(0, 255, 136, 0.15); border: 2px solid #00ff88; padding: 20px; border-radius: 10px; margin: 20px 0; min-height: 100px; }
        .sequence-box p { color: #00ff88; font-size: 1.1em; word-wrap: break-word; line-height: 1.8; }
        .stats-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(140px, 1fr)); gap: 12px; margin: 20px 0; }
        .stat-card { background: rgba(0, 255, 136, 0.1); border: 1px solid #00ff88; padding: 15px; border-radius: 8px; text-align: center; }
        .stat-label { color: #aaa; font-size: 0.85em; margin-bottom: 5px; }
        .stat-value { color: #00ff88; font-size: 1.5em; font-weight: bold; }
        .form-group { margin: 20px 0; }
        label { display: block; margin-bottom: 8px; color: #00ff88; font-weight: bold; }
        input { width: 100%; max-width: 200px; padding: 10px; border: 1px solid #00ff88; border-radius: 5px; background: rgba(0, 255, 136, 0.05); color: #e0e0e0; font-family: inherit; }
        input:focus { outline: none; border-color: #00dd66; box-shadow: 0 0 10px rgba(0, 255, 136, 0.2); }
        button { background: linear-gradient(135deg, #00ff88, #00dd66); color: #1e1e2e; padding: 12px 30px; border: none; border-radius: 5px; cursor: pointer; font-weight: bold; margin-top: 10px; box-shadow: 0 0 15px rgba(0, 255, 136, 0.3); }
        button:hover { box-shadow: 0 0 25px rgba(0, 255, 136, 0.5); }
        .examples { background: rgba(0, 255, 136, 0.1); border-left: 4px solid #00ff88; padding: 15px; border-radius: 5px; margin-top: 20px; color: #aaa; }
        .examples a { color: #00ff88; text-decoration: none; }
        .examples a:hover { text-decoration: underline; }
        a { color: #00ff88; text-decoration: none; }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🔢 PHP Fibonacci Generator</h1>
        
        <div class="sequence-box">
            <p><?php echo implode(', ', $fib); ?></p>
        </div>
        
        <div class="stats-grid">
            <div class="stat-card">
                <div class="stat-label">Count</div>
                <div class="stat-value"><?php echo $count; ?></div>
            </div>
            <div class="stat-card">
                <div class="stat-label">Sum</div>
                <div class="stat-value"><?php echo $sum; ?></div>
            </div>
            <div class="stat-card">
                <div class="stat-label">Max</div>
                <div class="stat-value"><?php echo $max; ?></div>
            </div>
            <div class="stat-card">
                <div class="stat-label">Average</div>
                <div class="stat-value"><?php echo $avg; ?></div>
            </div>
        </div>
        
        <div class="form-group">
            <form method="GET">
                <label>Generate (1-50 numbers):</label>
                <input type="number" name="count" value="<?php echo $count; ?>" min="1" max="50">
                <button type="submit">🚀 Generate Fibonacci</button>
            </form>
        </div>
        
        <div class="examples">
            <strong>Quick Examples:</strong><br>
            <a href="?count=5">5 numbers</a> | 
            <a href="?count=15">15 numbers</a> | 
            <a href="?count=25">25 numbers</a> | 
            <a href="?count=50">50 numbers</a>
        </div>
        
        <p style="margin-top: 20px;"><a href="/">← Back to Tests</a></p>
    </div>
</body>
</html>
