--TEST--
stats_rand_gen_gamma()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_gamma(1, 1)));

// error cases
var_dump(stats_rand_gen_gamma(-0.1, 1));    // a < 0
var_dump(stats_rand_gen_gamma(0, 1));       // a == 0
var_dump(stats_rand_gen_gamma(1, -.1));     // r < 0
var_dump(stats_rand_gen_gamma(1, 0));       // r == 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_gamma(): A or R nonpositive. A value :     -1.000000E-1 , R value :      1.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_gamma(): A or R nonpositive. A value :      0.000000E+0 , R value :      1.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_gamma(): A or R nonpositive. A value :      1.000000E+0 , R value :     -1.000000E-1 in %s on line %d
bool(false)

Warning: stats_rand_gen_gamma(): A or R nonpositive. A value :      1.000000E+0 , R value :      0.000000E+0 in %s on line %d
bool(false)
