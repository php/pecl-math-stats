--TEST--
stats_cdf_laplace()
--FILE--
<?php
// which = 1 : calculate P from (X, MEAN, SD)
var_dump(round(stats_cdf_laplace(0, 1, 2, 1), 6));
var_dump(round(stats_cdf_laplace(5, 4, 3, 1), 6));

// which = 2 : calculate X from (P, MEAN, SD)
var_dump(round(stats_cdf_laplace(0.30326533, 1, 2, 2), 6));
var_dump(round(stats_cdf_laplace(0.641734344, 4, 3, 2), 6));

// which = 3 : calculate MEAN from (P, X, SD)
var_dump(round(stats_cdf_laplace(0.30326533, 0, 2, 3), 6));
var_dump(round(stats_cdf_laplace(0.641734344, 5, 3, 3), 6));

// which = 4 : calculate SD from (P, X, MEAN)
var_dump(round(stats_cdf_laplace(0.30326533, 0, 1, 4), 6));
var_dump(round(stats_cdf_laplace(0.641734344, 5, 4, 4), 6));

// error cases
var_dump(stats_cdf_laplace(0, 1, 2, 0));    // which < 1
var_dump(stats_cdf_laplace(0, 1, 2, 5));    // which < 4
?>
--EXPECTF--
float(0.303265)
float(0.641734)
float(0)
float(5)
float(1)
float(4)
float(2)
float(3)

Warning: stats_cdf_laplace(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_laplace(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)
