--TEST--
stats_dens_logistic()
--FILE--
<?php
// check for each x
foreach (range(-2, 2, 0.5) as $x) {
    var_dump(round(stats_dens_logistic($x, 2, 3), 6));
}

// check for each ave
foreach (range(-2, 2, 0.5) as $ave) {
    var_dump(round(stats_dens_logistic(1, $ave, 3), 6));
}

// check for each stdev
foreach (range(0.5, 2, 0.5) as $stdev) {
    var_dump(round(stats_dens_logistic(1, 2, $stdev), 6));
}

// error cases
var_dump(stats_dens_logistic(1, 2, 0)); // stdev == 0
?>
--EXPECTF--
float(0.05503)
float(0.060357)
float(0.065537)
float(0.070389)
float(0.074719)
float(0.078335)
float(0.081061)
float(0.082757)
float(0.083333)
float(0.065537)
float(0.070389)
float(0.074719)
float(0.078335)
float(0.081061)
float(0.082757)
float(0.083333)
float(0.082757)
float(0.081061)
float(0.209987)
float(0.196612)
float(0.149438)
float(0.117502)

Warning: stats_dens_logistic(): stdev is 0.0 in %s on line %d
bool(false)
