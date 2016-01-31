--TEST--
stats_dens_pmf_negative_binomial()
--FILE--
<?php
// check for each x
foreach (range(0, 3) as $x) {
    var_dump(stats_dens_pmf_negative_binomial($x, 2, 0.4));
}

// check for each n
foreach (range(0, 3) as $n) {
    var_dump(stats_dens_pmf_negative_binomial(1, $n, 0.4));
}

// check for each pi
foreach (range(0, 1, 0.2) as $pi) {
    var_dump(stats_dens_pmf_negative_binomial(1, 2, $pi));
}

// error cases
var_dump(stats_dens_pmf_negative_binomial(1, 0, 0));    // n == 0 and pi == 0
var_dump(stats_dens_pmf_negative_binomial(0, 2, 1));    // x == 0 and pi == 1
?>
--EXPECTF--
float(0.16)
float(0.192)
float(0.1728)
float(0.13824)
float(0)
float(0.24)
float(0.192)
float(0.1152)
float(0)
float(0.064)
float(0.192)
float(0.288)
float(0.256)
float(0)

Warning: stats_dens_pmf_negative_binomial(): Params leading to pow(0, 0). x:     1.000000E+0  n:     0.000000E+0  pi:     0.000000E+0 in %s on line %d
bool(false)

Warning: stats_dens_pmf_negative_binomial(): Params leading to pow(0, 0). x:     0.000000E+0  n:     2.000000E+0  pi:     1.000000E+0 in %s on line %d
bool(false)
