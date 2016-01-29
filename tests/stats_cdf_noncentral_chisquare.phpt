--TEST--
stats_cdf_noncentral_chisquare()
--FILE--
<?php
// which = 1 : calculate P from (X, DF, PNONC)
var_dump(round(stats_cdf_noncentral_chisquare(4, 2, 3, 1), 6));

// which = 2 : calculate X from (P, DF, PNONC)
var_dump(round(stats_cdf_noncentral_chisquare(0.493562417, 2, 3, 2), 6));

// which = 3 : calculate DF from (P, X, PNONC)
var_dump(round(stats_cdf_noncentral_chisquare(0.493562417, 4, 3, 3), 6));

// which = 4 : calculate PNONC from (P, X, DF)
var_dump(round(stats_cdf_noncentral_chisquare(0.493562417, 4, 2, 4), 6));

// error cases
var_dump(stats_cdf_noncentral_chisquare(4, 2, 3, 0));       // which < 1
var_dump(stats_cdf_noncentral_chisquare(4, 2, 3, 5));       // which > 4
var_dump(stats_cdf_noncentral_chisquare(-0.1, 2, 3, 2));    // P < 0
var_dump(stats_cdf_noncentral_chisquare(1.1, 2, 3, 2));     // P > 1
var_dump(stats_cdf_noncentral_chisquare(-0.1, 2, 3, 1));    // X < 0
var_dump(stats_cdf_noncentral_chisquare(4, -0.1, 3, 1));    // DF < 0
var_dump(stats_cdf_noncentral_chisquare(4, 0, 3, 1));       // DF == 0
var_dump(stats_cdf_noncentral_chisquare(4, 2, -0.1, 1));    // PNONC < 0
?>
--EXPECTF--
float(0.493562)
float(4)
float(2)
float(3)

Warning: stats_cdf_noncentral_chisquare(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)

Warning: stats_cdf_noncentral_chisquare(): Computation Error in cdfchn in %s on line %d
bool(false)
