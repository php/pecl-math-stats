--TEST--
stats_dens_pmf_binomial()
--FILE--
<?php
// check for each x
foreach (range(0, 3) as $x) {
    var_dump(stats_dens_pmf_binomial($x, 3, 0.7));
}

// check for each n
foreach (range(0, 3) as $n) {
    var_dump(stats_dens_pmf_binomial(1, $n, 0.7));
}

// check for each pi
foreach (range(0, 1, 0.2) as $pi) {
    var_dump(stats_dens_pmf_binomial(1, 3, $pi));
}

// error cases
var_dump(stats_dens_pmf_binomial(0, 0, 0.7));   // x == n == 0
var_dump(stats_dens_pmf_binomial(0, 3, 0));     // x == pi == 0
var_dump(stats_dens_pmf_binomial(3, 3, 1));     // x == n, pi == 1
?>
--EXPECTF--
float(0.027)
float(0.189)
float(0.441)
float(0.343)
float(0)
float(0.7)
float(0.42)
float(0.189)
float(0)
float(0.384)
float(0.432)
float(0.288)
float(0.096)
float(0)

Warning: stats_dens_pmf_binomial(): Params leading to pow(0, 0). x:     %f  n:     %f  pi:     %f in %s on line %d
bool(false)

Warning: stats_dens_pmf_binomial(): Params leading to pow(0, 0). x:     %f  n:     %f  pi:     %f in %s on line %d
bool(false)

Warning: stats_dens_pmf_binomial(): Params leading to pow(0, 0). x:     %f  n:     %f  pi:     %f in %s on line %d
bool(false)
