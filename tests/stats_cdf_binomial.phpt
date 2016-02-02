--TEST--
stats_cdf_binomial()
--FILE--
<?php
// which = 1 : calculate P from (S, XN, PR)
var_dump(round(stats_cdf_binomial(1, 3, 0.7, 1), 6));

// which = 2 : calculate S from (P, XN, PR)
var_dump(round(stats_cdf_binomial(0.216, 3, 0.7, 2), 6));

// which = 3 : calculate XN from (P, S, PR)
var_dump(round(stats_cdf_binomial(0.216, 1, 0.7, 3), 6));

// which = 4 : calculate PR from (P, S, XN)
var_dump(round(stats_cdf_binomial(0.216, 1, 3, 4), 6));

// error cases
var_dump(stats_cdf_binomial(1, 3, 0.7, 0));     // which < 1
var_dump(stats_cdf_binomial(1, 3, 0.7, 5));     // which > 4
var_dump(stats_cdf_binomial(-0.1, 3, 0.7, 2));  // P < 0
var_dump(stats_cdf_binomial(1.1, 3, 0.7, 2));   // P > 1
var_dump(stats_cdf_binomial(-1, 3, 0.7, 1));    // S < 0
var_dump(stats_cdf_binomial(4, 3, 0.7, 1));     // S > XN
var_dump(stats_cdf_binomial(1, -1, 0.7, 1));    // XN < 0
var_dump(stats_cdf_binomial(1, 0, 0.7, 1));     // XN == 0
var_dump(stats_cdf_binomial(1, 3, -0.1, 1));    // PR < 0
var_dump(stats_cdf_binomial(1, 3, 1.1, 1));     // PR > 1
?>
--EXPECTF--
float(0.216)
float(1)
float(3)
float(0.7)

Warning: stats_cdf_binomial(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)

Warning: stats_cdf_binomial(): Computation Error in binomialcdf in %s on line %d
bool(false)
