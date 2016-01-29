--TEST--
stats_cdf_logistic()
--FILE--
<?php
// which = 1 : calculate P from (X, MEAN, SD)
var_dump(round(stats_cdf_logistic(1, 2, 3, 1), 6));
var_dump(round(stats_cdf_logistic(6, 5, 4, 1), 6));

// which = 2 : calculate X from (P, MEAN, SD)
var_dump(round(stats_cdf_logistic(0.417429794, 2, 3, 2), 6));
var_dump(round(stats_cdf_logistic(0.562176501, 5, 4, 2), 6));

// which = 3 : calcualte MEAN from (P, X, SD)
var_dump(round(stats_cdf_logistic(0.417429794, 1, 3, 3), 6));
var_dump(round(stats_cdf_logistic(0.562176501, 6, 4, 3), 6));

// which = 4 : calcualte SD from (P, X, MEAN)
var_dump(round(stats_cdf_logistic(0.417429794, 1, 2, 4), 6));
var_dump(round(stats_cdf_logistic(0.562176501, 6, 5, 4), 6));

// error cases
var_dump(stats_cdf_logistic(1, 2, 3, 0));   // which < 1
var_dump(stats_cdf_logistic(1, 2, 3, 5));   // which > 4
?>
--EXPECTF--
float(0.41743)
float(0.562177)
float(1)
float(6)
float(2)
float(5)
float(3)
float(4)

Warning: stats_cdf_logistic(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_logistic(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)
