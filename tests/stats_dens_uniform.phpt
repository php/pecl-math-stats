--TEST--
stats_dens_uniform()
--FILE--
<?php
var_dump(stats_dens_uniform(2.5, 1, 3));    // A <= X <= B
var_dump(stats_dens_uniform(0, 1, 3));      // X < A
var_dump(stats_dens_uniform(4, 1, 3));      // X > B

// error cases
var_dump(stats_dens_uniform(1, 1, 1));      // A == B
?>
--EXPECTF--
float(0.5)
float(0)
float(0)

Warning: stats_dens_uniform(): b == a ==      1.000000E+0 in %s on line %d
bool(false)
