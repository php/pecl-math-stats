--TEST--
stats_rand_gen_ipoisson()
--FILE--
<?php
var_dump(is_int(stats_rand_gen_ipoisson(1)));
var_dump(stats_rand_gen_ipoisson(0));

// error cases
var_dump(stats_rand_gen_ipoisson(-0.1));    // mu < 0
?>
--EXPECTF--
bool(true)
int(0)

Warning: stats_rand_gen_ipoisson(): mu < 0.0 . mu :     -1.000000E-1 in %s on line %d
bool(false)
