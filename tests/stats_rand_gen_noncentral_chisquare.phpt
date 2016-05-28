--TEST--
stats_rand_gen_noncentral_chisquare()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_noncentral_chisquare(2, 3)));

// error cases
var_dump(stats_rand_gen_noncentral_chisquare(0.9, 3));  // df < 1
var_dump(stats_rand_gen_noncentral_chisquare(2, -0.1)); // xnonc < 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_noncentral_chisquare(): df < 1 or xnonc < 0. df value :      9.000000E-1  xnonc value :      3.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_noncentral_chisquare(): df < 1 or xnonc < 0. df value :      2.000000E+0  xnonc value :     -1.000000E-1 in %s on line %d
bool(false)
