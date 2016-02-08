--TEST--
stats_cdf_noncentral_f()
--FILE--
<?php
// which = 1 : calculate P from (F, DFN, DFD, PNONC)
var_dump(round(stats_cdf_noncentral_f(5, 2, 3, 4, 1), 6));

// which = 2 : calculate F from (P, DFN, DFD, PNONC)
var_dump(round(stats_cdf_noncentral_f(0.650459043, 2, 3, 4, 2), 6));

// which = 3 : calculate DFN from (P, F, DFD, PNONC)
var_dump(round(stats_cdf_noncentral_f(0.650459043, 5, 3, 4, 3), 6));

// which = 4 : calculate DFD from (P, F, DFN, PNONC)
var_dump(round(stats_cdf_noncentral_f(0.650459043, 5, 2, 4, 4), 6));

// which = 5 : calculate PNONC from (P, F, DFN, DFD)
var_dump(round(stats_cdf_noncentral_f(0.650459043, 5, 2, 3, 5), 6));

// error cases
var_dump(round(stats_cdf_noncentral_f(1, 2, 3, 4, 0), 6));      // which < 1
var_dump(round(stats_cdf_noncentral_f(1, 2, 3, 4, 6), 6));      // which > 5
var_dump(round(stats_cdf_noncentral_f(-0.1, 2, 3, 4, 2), 6));   // P < 0
var_dump(round(stats_cdf_noncentral_f(1.1, 2, 3, 4, 2), 6));    // P > 1
var_dump(round(stats_cdf_noncentral_f(-0.1, 2, 3, 4, 1), 6));   // F < 0
var_dump(round(stats_cdf_noncentral_f(1, -0.1, 3, 4, 1), 6));   // DFN < 0
var_dump(round(stats_cdf_noncentral_f(1, 0, 3, 4, 1), 6));      // DFN == 0
var_dump(round(stats_cdf_noncentral_f(1, 2, -0.1, 4, 1), 6));   // DFR < 0
var_dump(round(stats_cdf_noncentral_f(1, 2, 0, 4, 1), 6));      // DFR == 0
var_dump(round(stats_cdf_noncentral_f(1, 2, 3, -0.1, 1), 6));   // PNONC < 0

?>
--EXPECTF--
float(0.650459)
float(5)
float(2)
float(3)
float(4)

Warning: stats_cdf_noncentral_f(): Fifth parameter should be in the 1..5 range in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Fifth parameter should be in the 1..5 range in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)

Warning: stats_cdf_noncentral_f(): Computation Error in cdffnc in %s on line %d
float(0)
