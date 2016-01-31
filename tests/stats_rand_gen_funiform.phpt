--TEST--
stats_rand_gen_funiform()
--FILE--
<?php
$x = stats_rand_gen_funiform(1.5, 2.5);
var_dump(is_float($x));
var_dump($x > 1.5);
var_dump($x < 2.5);
var_dump(stats_rand_gen_funiform(1.5, 1.5));

// error cases
var_dump(stats_rand_gen_funiform(2.5, 1.5));    // low > high
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
float(1.5)

Warning: stats_rand_gen_funiform(): low greater than high. low :      2.500000E+0  high :      1.500000E+0 in %s on line %d
bool(false)
