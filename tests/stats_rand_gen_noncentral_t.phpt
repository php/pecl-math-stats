--TEST--
stats_rand_gen_noncentral_t()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_noncentral_t(2, 1)));

// error cases
var_dump(stats_rand_gen_noncentral_t(-0.1, 1)); // df < 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_noncentral_t(): df <= 0 . df :     -1.000000E-1 in %s on line %d
bool(false)
