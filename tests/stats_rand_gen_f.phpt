--TEST--
stats_rand_gen_f()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_f(3, 2)));

// error cases
var_dump(stats_rand_gen_f(-0.1, 2));    // dfn < 0
var_dump(stats_rand_gen_f(3, -0.1));    // dfr < 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_f(): Degrees of freedom nonpositive. DFN value:    -1.000000E-1 DFD value:     2.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_f(): Degrees of freedom nonpositive. DFN value:     3.000000E+0 DFD value:    -1.000000E-1 in %s on line %d
bool(false)
