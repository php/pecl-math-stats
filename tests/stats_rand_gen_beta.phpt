--TEST--
stats_rand_gen_beta()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_beta(2, 3)));

// error cases
var_dump(stats_rand_gen_beta(1e-38, 1));    // a < 1e-37
var_dump(stats_rand_gen_beta(1, 1e-38));    // b < 1e-37
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_beta(): 'a' or 'b' lower than 1.0E-37. 'a' value :     1.000000E-38  'b' value :      1.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_beta(): 'a' or 'b' lower than 1.0E-37. 'a' value :      1.000000E+0  'b' value :     1.000000E-38 in %s on line %d
bool(false)
