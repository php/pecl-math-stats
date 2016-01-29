--TEST--
stats_cdf_exponential()
--FILE--
<?php
// which = 1 : calculate P from (X, SCALE)
var_dump(round(stats_cdf_exponential(1, 2, 1), 6));
var_dump(round(stats_cdf_exponential(4, 3, 1), 6));

// which = 2 : calculate X from (P, SCALE)
var_dump(round(stats_cdf_exponential(0.39346934, 2, 2), 6));
var_dump(round(stats_cdf_exponential(0.736402862, 3, 2), 6));

// which = 3 : calculate SCALE from (P, X)
var_dump(round(stats_cdf_exponential(0.39346934, 1, 3), 6));
var_dump(round(stats_cdf_exponential(0.736402862, 4, 3), 6));

// error cases
var_dump(stats_cdf_exponential(1, 2, 0));   // which < 1
var_dump(stats_cdf_exponential(4, 3, 4));   // which > 3
?>
--EXPECTF--
float(0.393469)
float(0.736403)
float(1)
float(4)
float(2)
float(3)

Warning: stats_cdf_exponential(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)

Warning: stats_cdf_exponential(): Third parameter should be in the 1..3 range in %s on line %d
bool(false)
