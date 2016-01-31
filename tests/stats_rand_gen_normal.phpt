--TEST--
stats_rand_gen_normal()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_normal(0, 1)));
var_dump(stats_rand_gen_normal(0, 0));

// error cases
var_dump(stats_rand_gen_normal(0, -0.1)); // sd < 0
?>
--EXPECTF--
bool(true)
float(0)

Warning: stats_rand_gen_normal(): sd < 0.0 . sd :     %f in %s on line %d
bool(false)
