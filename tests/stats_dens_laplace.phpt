--TEST--
stats_dens_laplace()
--FILE--
<?php
// check for each x
foreach (range(-2, 2, 0.5) as $x) {
    var_dump(round(stats_dens_laplace($x, 1, 2), 6));
}

// check for each ave
foreach (range(-2, 2, 0.5) as $ave) {
    var_dump(round(stats_dens_laplace(0, $ave, 2), 6));
}

// check for each stdev
foreach (range(0.5, 2, 0.5) as $stdev) {
    var_dump(round(stats_dens_laplace(0, 1, $stdev), 6));
}

// error cases
var_dump(stats_dens_laplace(0, 1, 0));  // stdev == 0
?>
--EXPECTF--
float(0.055783)
float(0.071626)
float(0.09197)
float(0.118092)
float(0.151633)
float(0.1947)
float(0.25)
float(0.1947)
float(0.151633)
float(0.09197)
float(0.118092)
float(0.151633)
float(0.1947)
float(0.25)
float(0.1947)
float(0.151633)
float(0.118092)
float(0.09197)
float(0.135335)
float(0.18394)
float(0.171139)
float(0.151633)

Warning: stats_dens_laplace(): stdev is 0.0 in %s on line %d
bool(false)
