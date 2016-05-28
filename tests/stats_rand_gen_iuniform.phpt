--TEST--
stats_rand_gen_iuniform()
--FILE--
<?php
var_dump(in_array(stats_rand_gen_iuniform(1, 3), array(1, 2, 3)));
var_dump(stats_rand_gen_iuniform(1, 1));

// error cases
var_dump(stats_rand_gen_iuniform(2, 1));    // low > high
?>
--EXPECTF--
bool(true)
int(1)

Warning: stats_rand_gen_iuniform(): low greater than high. low :                2  high                1 in %s on line %d
bool(false)
