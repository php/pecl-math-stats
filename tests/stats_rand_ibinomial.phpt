--TEST--
stats_rand_ibinomial()
--FILE--
<?php
var_dump(in_array(stats_rand_ibinomial(3, 0.7), array(0, 1, 2, 3)));
var_dump(stats_rand_ibinomial(0, 0.7));
var_dump(stats_rand_ibinomial(3, 0));
var_dump(stats_rand_ibinomial(3, 1));

// error cases
var_dump(stats_rand_ibinomial(-1, 0.7));    // n < 0
var_dump(stats_rand_ibinomial(3, -0.1));    // pp < 0
var_dump(stats_rand_ibinomial(3, 1.1));     // pp > 1
?>
--EXPECTF--
bool(true)
int(0)
int(0)
int(3)

Warning: stats_rand_ibinomial(): Bad values for the arguments. n : -1  pp :      7.000000E-1 in %s on line %d
bool(false)

Warning: stats_rand_ibinomial(): Bad values for the arguments. n : 3  pp :     -1.000000E-1 in %s on line %d
bool(false)

Warning: stats_rand_ibinomial(): Bad values for the arguments. n : 3  pp :      1.100000E+0 in %s on line %d
bool(false)
