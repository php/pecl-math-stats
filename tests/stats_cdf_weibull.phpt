--TEST--
stats_cdf_weibull()
--FILE--
<?php
// which = 1 : calculate P from (X, A, B)
var_dump(round(stats_cdf_weibull(1, 2, 3, 1), 6));
var_dump(round(stats_cdf_weibull(6, 5, 4, 1), 6));

// which = 2 : calculate X from (P, A, B)
var_dump(round(stats_cdf_weibull(0.105160683, 2, 3, 2), 6));
var_dump(round(stats_cdf_weibull(0.999496411, 5, 4, 2), 6));

// which = 3 : calcualte A from (P, X, B)
var_dump(round(stats_cdf_weibull(0.105160683, 1, 3, 3), 6));
var_dump(round(stats_cdf_weibull(0.999496411, 6, 4, 3), 6));

// which = 4 : calculate B from (P, X, A)
var_dump(round(stats_cdf_weibull(0.105160683, 1, 2, 4), 6));
var_dump(round(stats_cdf_weibull(0.999496411, 6, 5, 4), 6));

// error cases
var_dump(stats_cdf_weibull(1, 2, 3, 0));    // which < 1
var_dump(stats_cdf_weibull(1, 2, 3, 5));    // which > 4
?>
--EXPECTF--
float(0.105161)
float(0.999496)
float(1)
float(6)
float(2)
float(5)
float(3)
float(4)

Warning: stats_cdf_weibull(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_weibull(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)
