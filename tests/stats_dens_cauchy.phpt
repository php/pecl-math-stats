--TEST--
stats_dens_cauchy()
--FILE--
<?php
// check for each x
foreach (range(-2, 2, 0.5) as $x) {
    var_dump(round(stats_dens_cauchy($x, 2, 3), 6));
}

// check for each ave
foreach (range(-2, 2, 0.5) as $ave) {
    var_dump(round(stats_dens_cauchy(1, $ave, 3), 6));
}

// check for each stdev
foreach (range(0.5, 2, 0.5) as $stdev) {
    var_dump(round(stats_dens_cauchy(1, 2, $stdev), 6));
}

// error cases
var_dump(stats_dens_cauchy(1, 2, 0));   // stdev == 0
?>
--EXPECTF--
float(0.038197)
float(0.044938)
float(0.053052)
float(0.062618)
float(0.073456)
float(0.084883)
float(0.095493)
float(0.103236)
float(0.106103)
float(0.053052)
float(0.062618)
float(0.073456)
float(0.084883)
float(0.095493)
float(0.103236)
float(0.106103)
float(0.103236)
float(0.095493)
float(0.127324)
float(0.159155)
float(0.146912)
float(0.127324)

Warning: stats_dens_cauchy(): stdev is 0.0 in %s on line %d
bool(false)
