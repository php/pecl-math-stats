--TEST--
stats_cdf_gamma()
--FILE--
<?php
// which = 1 : calculate P from (X, SHAPE, SCALE)
var_dump(round(stats_cdf_gamma(5, 3, 2, 1), 6));

// which = 2 : calculate X from (P, SHAPE, SCALE)
var_dump(round(stats_cdf_gamma(0.456186884, 3, 2, 2), 6));

// which = 3 : calculate SHAPE from (P, X, SCALE)
var_dump(round(stats_cdf_gamma(0.456186884, 5, 2, 3), 6));

// which = 4 : calculate SCALE from (P, X, SHAPE)
var_dump(round(stats_cdf_gamma(0.456186884, 5, 3, 4), 6));

// error cases
var_dump(stats_cdf_gamma(1, 0, 1, 0));      // which < 1
var_dump(stats_cdf_gamma(1, 0, 1, 5));      // which > 4
var_dump(stats_cdf_gamma(-0.1, 3, 2, 2));   // P < 0
var_dump(stats_cdf_gamma(1.1, 3, 2, 2));    // P > 1
var_dump(stats_cdf_gamma(-0.1, 3, 2, 1));   // X < 0
var_dump(stats_cdf_gamma(5, -0.1, 2, 1));   // SHAPE < 0
var_dump(stats_cdf_gamma(5, 0, 2, 1));      // SHAPE == 0
var_dump(stats_cdf_gamma(5, 3, -0.1, 1));   // SCALE < 0
var_dump(stats_cdf_gamma(5, 3, 0, 1));      // SCALE == 0
?>
--EXPECTF--
float(0.456187)
float(5)
float(3)
float(2)

Warning: stats_cdf_gamma(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_gamma(): Computation Error in %s on line %d
bool(false)
