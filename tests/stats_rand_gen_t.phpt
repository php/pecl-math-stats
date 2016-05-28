--TEST--
stats_rand_gen_t()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_t(1)));

// error cases
var_dump(stats_rand_gen_t(-0.1));   // df < 0
var_dump(stats_rand_gen_t(0));      // df == 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_t(): df <= 0 . df :     -1.000000E-1 in %s on line %d
bool(false)

Warning: stats_rand_gen_t(): df <= 0 . df :      0.000000E+0 in %s on line %d
bool(false)
