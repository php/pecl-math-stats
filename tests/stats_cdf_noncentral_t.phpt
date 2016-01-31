--TEST--
stats_cdf_noncentral_t()
--FILE--
<?php
// which = 1 : calculate P from (T, DF, PNONC)
var_dump(round(stats_cdf_noncentral_t(3, 2, 1, 1), 6));

// which = 2 : calculate T from (P, DF, PNONC)
var_dump(round(stats_cdf_noncentral_t(0.833559426, 2, 1, 2), 6));

// which = 3 : calculate DF from (P, T, PNONC)
var_dump(round(stats_cdf_noncentral_t(0.833559426, 3, 1, 3), 6));

// which = 4 : calculate PNONC from (P, DF, T)
var_dump(round(stats_cdf_noncentral_t(0.833559426, 3, 2, 4), 6));

// error cases
var_dump(stats_cdf_noncentral_t(3, 2, 1, 0));       // which < 0
var_dump(stats_cdf_noncentral_t(3, 2, 1, 5));       // which > 4
var_dump(stats_cdf_noncentral_t(-0.1, 2, 1, 2));    // P < 0
var_dump(stats_cdf_noncentral_t(1.1, 2, 1, 2));     // P > 1
var_dump(stats_cdf_noncentral_t(3, -0.1, 1, 1));    // DF < 0
var_dump(stats_cdf_noncentral_t(3, 0, 1, 1));       // DF == 1
?>
--EXPECTF--
float(0.833559)
float(3)
float(2)
float(1)

Warning: stats_cdf_noncentral_t(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_t(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_t(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_t(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_t(): Computation Error in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_t(): Computation Error in %s on line %d
bool(false)
