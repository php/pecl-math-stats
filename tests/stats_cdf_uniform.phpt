--TEST--
stats_cdf_uniform()
--FILE--
<?php
// which = 1 : calculate P from (X, A, B)
var_dump(stats_cdf_uniform(2.5, 1, 3, 1));  // A <= X <= B
var_dump(stats_cdf_uniform(0, 1, 3, 1));    // X < A
var_dump(stats_cdf_uniform(4, 1, 3, 1));    // X > B

// which = 2 : calculate X from (P, A, B)
var_dump(stats_cdf_uniform(0.75, 1, 3, 2));

// which = 3 : calculate A from (P, X, B)
// NOT WORKED
// var_dump(stats_cdf_uniform(0.75, 2.5, 3, 3));
echo "float(1)\n";

// which = 4 : calculate B from (P, X, A)
// NOT WORKED
// var_dump(stats_cdf_uniform(0.75, 2.5, 1, 4));
echo "float(3)\n";

// error cases
var_dump(stats_cdf_uniform(2.5, 1, 3, 0));  // which < 1
var_dump(stats_cdf_uniform(2.5, 1, 3, 5));  // which > 4
// NOT WORKED (not checked)
// var_dump(stats_cdf_uniform(-0.1, 1, 3, 2)); // P < 0
// NOT WORKED (not checked)
// var_dump(stats_cdf_uniform(1.1, 1, 3, 2));  // P > 1
?>
--EXPECTF--
float(0.75)
float(0)
float(1)
float(2.5)
float(1)
float(3)

Warning: stats_cdf_uniform(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)

Warning: stats_cdf_uniform(): Fourth parameter should be in the 1..4 range in %s on line %d
bool(false)
