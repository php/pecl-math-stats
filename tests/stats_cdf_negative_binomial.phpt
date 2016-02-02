--TEST--
stats_cdf_negative_binomial()
--FILE--
<?php
// which = 1 : calculate P from (S, XN, PR)
var_dump(round(stats_cdf_negative_binomial(2, 1, 0.4, 1), 6));

// which = 2 : calculate S from (P, XN, PR)
var_dump(round(stats_cdf_negative_binomial(0.784, 1, 0.4, 2), 6));

// which = 3 : calculate XN from (P, S, PR)
var_dump(round(stats_cdf_negative_binomial(0.784, 2, 0.4, 3), 6));

// which = 4 : calculate PR from (P, S, XN)
var_dump(round(stats_cdf_negative_binomial(0.784, 2, 1, 4), 6));

// error cases
var_dump(stats_cdf_negative_binomial(2, 1, 0.4, 0));    // which < 1
var_dump(stats_cdf_negative_binomial(2, 1, 0.4, 5));    // which > 4
var_dump(stats_cdf_negative_binomial(-0.1, 1, 0.4, 2)); // P < 0
var_dump(stats_cdf_negative_binomial(1.1, 1, 0.4, 2));  // P > 0
var_dump(stats_cdf_negative_binomial(-1, 1, 0.4, 1));   // S < 0
var_dump(stats_cdf_negative_binomial(2, -1, 0.4, 1));   // XN < 0
var_dump(stats_cdf_negative_binomial(2, 1, -0.1, 1));   // PR < 0
var_dump(stats_cdf_negative_binomial(2, 1, 1.1, 1));    // PR > 1

?>
--EXPECTF--
float(0.784)
float(2)
float(1)
float(0.4)

Warning: stats_cdf_negative_binomial(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)

Warning: stats_cdf_negative_binomial(): Computation Error in cdfnbn in %s on line %d
bool(false)
