--TEST--
stats_rand_gen_noncentral_f()
--FILE--
<?php
var_dump(is_float(stats_rand_gen_noncentral_f(2, 3, 4)));

// error cases
var_dump(stats_rand_gen_noncentral_f(0.9, 3, 4));    // dfn < 1
var_dump(stats_rand_gen_noncentral_f(2, -0.1, 4));   // dfd < 0
var_dump(stats_rand_gen_noncentral_f(2, 0, 4));      // dfd == 0
var_dump(stats_rand_gen_noncentral_f(2, 3, -0.1));   // xnonc < 0
?>
--EXPECTF--
bool(true)

Warning: stats_rand_gen_noncentral_f(): Either (1) Numerator df < 1.0 or (2) Denominator df <= 0.0 or (3) Noncentrality parameter < 0.0. dfn:      9.000000E-1  dfd:      3.000000E+0  xnonc:      4.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_noncentral_f(): Either (1) Numerator df < 1.0 or (2) Denominator df <= 0.0 or (3) Noncentrality parameter < 0.0. dfn:      2.000000E+0  dfd:     -1.000000E-1  xnonc:      4.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_noncentral_f(): Either (1) Numerator df < 1.0 or (2) Denominator df <= 0.0 or (3) Noncentrality parameter < 0.0. dfn:      2.000000E+0  dfd:      0.000000E+0  xnonc:      4.000000E+0 in %s on line %d
bool(false)

Warning: stats_rand_gen_noncentral_f(): Either (1) Numerator df < 1.0 or (2) Denominator df <= 0.0 or (3) Noncentrality parameter < 0.0. dfn:      2.000000E+0  dfd:      3.000000E+0  xnonc:     -1.000000E-1 in %s on line %d
bool(false)
