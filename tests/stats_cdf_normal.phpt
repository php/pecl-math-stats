--TEST--
stats_cdf_normal()
--FILE--
<?php
// which = 1 : calculate P from (X, MEAN, SD)
var_dump(round(stats_cdf_normal(1, 0, 1, 1), 6));

// which = 2 : calculate X from (P, MEAN, SD)
var_dump(round(stats_cdf_normal(0.841344746, 0, 1, 2), 6));

// which = 3 : calculate MEAN from (P, X, SD)
var_dump(round(stats_cdf_normal(0.841344746, 1, 1, 3), 6));

// which = 4 : calculate SD from (P, X, MEAN)
var_dump(round(stats_cdf_normal(0.841344746, 1, 0, 4), 6));

// error cases
var_dump(stats_cdf_normal(1, 0, 1, 0));     // which < 1
var_dump(stats_cdf_normal(1, 0, 1, 5));     // which > 4
var_dump(stats_cdf_normal(-0.1, 0, 1, 2));  // P < 0
var_dump(stats_cdf_normal(0, 0, 1, 2));     // P == 0
var_dump(stats_cdf_normal(1.1, 0, 1, 2));   // P > 1
var_dump(stats_cdf_normal(1, 0, -0.1, 1));  // SD < 0
var_dump(stats_cdf_normal(1, 0, 0, 1));     // SD == 0
?>
--EXPECTF--
float(0.841345)
float(1)
float(0)
float(1)

Warning: stats_cdf_normal(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Computation error in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Computation error in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Computation error in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Computation error in %s on line %d
bool(false)

Warning: stats_cdf_normal(): Computation error in %s on line %d
bool(false)
