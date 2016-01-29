--TEST--
stats_cdf_chisquare()
--FILE--
<?php
// which = 1 : calculate P from (X, DF)
var_dump(round(stats_cdf_chisquare(1, 2, 1), 6));

// which = 2 : calculate X from (P, DF)
var_dump(round(stats_cdf_chisquare(0.393469340, 2, 2), 6));

// which = 3 : calculate DF from (P, X)
var_dump(round(stats_cdf_chisquare(0.393469340, 1, 3), 6));

// error cases
var_dump(stats_cdf_chisquare(1, 2, 0));     // which < 1
var_dump(stats_cdf_chisquare(1, 2, 4));     // which > 3
var_dump(stats_cdf_chisquare(-0.1, 2, 2));  // P < 0
var_dump(stats_cdf_chisquare(1.1, 2, 2));   // P > 1
var_dump(stats_cdf_chisquare(-0.1, 2, 1));  // X < 0
var_dump(stats_cdf_chisquare(1, -0.1, 1));  // DF < 0
?>
--EXPECTF--
float(0.393469)
float(1)
float(2)

Warning: stats_cdf_chisquare(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_chisquare(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_chisquare(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_chisquare(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_chisquare(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_chisquare(): Computation Error in %s on line %d
bool(false)
