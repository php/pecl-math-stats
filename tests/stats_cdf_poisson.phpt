--TEST--
stats_cdf_poisson()
--FILE--
<?php
// which = 1 : calculate P from (S, XLAM)
var_dump(round(stats_cdf_poisson(1, 2, 1), 6));

// which = 2 : calculate A from (P, XLAM)
var_dump(round(stats_cdf_poisson(0.40600585, 2, 2), 6));

// which = 3 : calculate XLAM from (P, S)
var_dump(round(stats_cdf_poisson(0.40600585, 1, 3), 6));

// error cases
var_dump(stats_cdf_poisson(1, 2, 0));       // which < 1
var_dump(stats_cdf_poisson(1, 2, 4));       // which > 3
var_dump(stats_cdf_poisson(-0.1, 2, 2));    // P < 0
var_dump(stats_cdf_poisson(1.1, 2, 2));     // P > 0
var_dump(stats_cdf_poisson(-0.1, 2, 1));    // S < 0
var_dump(stats_cdf_poisson(1, -0.1, 1));    // XLAM < 0
?>
--EXPECTF--
float(0.406006)
float(1)
float(2)

Warning: stats_cdf_poisson(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_poisson(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_poisson(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_poisson(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_poisson(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_poisson(): Computation Error in %s on line %d
bool(false)
