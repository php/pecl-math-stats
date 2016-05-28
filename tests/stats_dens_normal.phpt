--TEST--
stats_dens_normal()
--FILE--
<?php
// check for each x
foreach (range(-2, 2, 0.5) as $x) {
    var_dump(round(stats_dens_normal($x, 0, 1), 6));
}

// check for each ave
foreach (range(-2, 2, 0.5) as $ave) {
    var_dump(round(stats_dens_normal(1, $ave, 1), 6));
}

// check for each stdev
foreach (range(0.5, 2, 0.5) as $stdev) {
    var_dump(round(stats_dens_normal(1, 0, $stdev), 6));
}

// error cases
var_dump(stats_dens_normal(1, 0, 0)); // stdev == 0
?>
--EXPECTF--
float(0.053991)
float(0.129518)
float(0.241971)
float(0.352065)
float(0.398942)
float(0.352065)
float(0.241971)
float(0.129518)
float(0.053991)
float(0.004432)
float(0.017528)
float(0.053991)
float(0.129518)
float(0.241971)
float(0.352065)
float(0.398942)
float(0.352065)
float(0.241971)
float(0.107982)
float(0.241971)
float(0.212965)
float(0.176033)

Warning: stats_dens_normal(): stdev is 0.0 in %s on line %d
bool(false)
