--TEST--
stats_rand_gen_chisquare()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_chisquare(3)));

// error cases
var_dump(stats_rand_gen_chisquare(-0.1));   // df < 0
var_dump(stats_rand_gen_chisquare(0));      // df == 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_chisquare(): df <= 0.0. df :     -1.000000E-1 in %s on line %d
bool(false)

Warning: stats_rand_gen_chisquare(): df <= 0.0. df :      0.000000E+0 in %s on line %d
bool(false)
