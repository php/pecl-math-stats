--TEST--
stats_rand_ibinomial_negative()
--FILE--
<?php
var_dump(is_int(stats_rand_ibinomial_negative(2, 0.5)));

// error cases
var_dump(stats_rand_ibinomial_negative(-1, 0.5));   // n < 0
var_dump(stats_rand_ibinomial_negative(1, -0.1));   // pp < 0
var_dump(stats_rand_ibinomial_negative(1, 1.1));    // pp > 1

?>
--EXPECTF--
bool(true)

Warning: stats_rand_ibinomial_negative(): n < 0. n : -1 in %s on line %d
bool(false)

Warning: stats_rand_ibinomial_negative(): p is out of range. p :            -1E-1 in %s on line %d
bool(false)

Warning: stats_rand_ibinomial_negative(): p is out of range. p :             1E+0 in %s on line %d
bool(false)
