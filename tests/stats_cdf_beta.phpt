--TEST--
stats_cdf_beta()
--FILE--
<?php
// which = 1 : calculate P from (X, A, B)
var_dump(round(stats_cdf_beta(0.5, 2, 4, 1), 6));

// which = 2 : calculate X from (P, A, B)
var_dump(round(stats_cdf_beta(0.8125, 2, 4, 2), 6));

// which = 3 : calculate A from (P, X, B)
var_dump(round(stats_cdf_beta(0.8125, 0.5, 4, 3), 6));

// which = 4 : calculate B from (P, X, A)
var_dump(round(stats_cdf_beta(0.8125, 0.5, 2, 4), 6));

// error cases
var_dump(stats_cdf_beta(0.5, 2, 4, 0));     // which < 1
var_dump(stats_cdf_beta(0.5, 2, 4, 5));     // which > 4
var_dump(stats_cdf_beta(-0.1, 2, 4, 2));    // P < 0
var_dump(stats_cdf_beta(1.1, 2, 4, 2));     // P > 1
var_dump(stats_cdf_beta(-0.1, 2, 4, 1));    // X < 0
var_dump(stats_cdf_beta(1.1, 2, 4, 1));     // X > 1
var_dump(stats_cdf_beta(0.5, -0.1, 4, 1));  // A < 0
var_dump(stats_cdf_beta(0.5, 0, 4, 1));     // A == 0
var_dump(stats_cdf_beta(0.5, 2, -0.1, 1));  // B < 0
var_dump(stats_cdf_beta(0.5, 2, 0, 1));     // B == 0
?>
--EXPECTF--
float(0.8125)
float(0.5)
float(2)
float(4)

Warning: stats_cdf_beta(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_beta(): Computation Error in %s on line %d
bool(false)
