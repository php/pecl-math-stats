--TEST--
stats_cdf_f()
--FILE--
<?php
// which = 1 : calculate P from (F, DFN, DFD)
var_dump(round(stats_cdf_f(1, 3, 2, 1), 6));

// which = 2 : calculate F from (P, DFN, DFD)
var_dump(round(stats_cdf_f(0.464758002, 3, 2, 2), 6));

// which = 3 : calculate DFN from (P, F, DFD)
var_dump(round(stats_cdf_f(0.464758002, 1, 2, 3), 6));

// which = 4 : calculate DFD from (P, F, DFN)
var_dump(round(stats_cdf_f(0.464758002, 1, 3, 4), 6));

// error cases
var_dump(stats_cdf_f(1, 3, 2, 0));      // which < 1
var_dump(stats_cdf_f(1, 3, 2, 5));      // which > 4
var_dump(stats_cdf_f(-0.1, 3, 2, 2));   // P < 0
var_dump(stats_cdf_f(1.1, 3, 2, 2));    // P > 1
var_dump(stats_cdf_f(-0.1, 3, 2, 1));   // F < 0
var_dump(stats_cdf_f(1, -0.1, 2, 1));   // DFN < 0
var_dump(stats_cdf_f(1, 0, 2, 1));      // DFN == 0
var_dump(stats_cdf_f(1, 3, -0.1, 1));   // DFD < 0
var_dump(stats_cdf_f(1, 3, 0, 1));      // DFD == 0
?>
--EXPECTF--
float(0.464758)
float(1)
float(3)
float(2)

Warning: stats_cdf_f(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_f(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)

Warning: stats_cdf_f(): Computation Error in cdff in %s on line %d
bool(false)
