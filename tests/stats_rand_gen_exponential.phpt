--TEST--
stats_rand_gen_exponential()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_exponential(2)));
var_dump(stats_rand_gen_exponential(0));

// error cases
var_dump(stats_rand_gen_exponential(-0.1)); // av < 0
?>
--EXPECTF--
bool(true)
float(0)

Warning: stats_rand_gen_exponential(): av < 0.0 in %s on line %d
bool(false)
