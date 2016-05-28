--TEST--
stats_cdf_t()
--FILE--
<?php
// which = 1 : calculate P from (T, DF)
var_dump(round(stats_cdf_t(1, 1, 1), 6));

// which = 2 : calculate T from (P, DF)
var_dump(round(stats_cdf_t(0.75, 1, 2), 6));

// which = 3 : calculate DF from (P, T)
var_dump(round(stats_cdf_t(0.75, 1, 3), 6));

// error cases
var_dump(stats_cdf_t(1, 1, 0));     // which < 1
var_dump(stats_cdf_t(1, 1, 4));     // which > 3
var_dump(stats_cdf_t(1, -0.1, 1));  // DF < 0
var_dump(stats_cdf_t(1, 0, 1));     // DF == 0
?>
--EXPECTF--
float(0.75)
float(1)
float(1)

Warning: stats_cdf_t(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_t(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_t(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_t(): Computation Error in %s on line %d
bool(false)
