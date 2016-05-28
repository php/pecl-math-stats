--TEST--
Bug #57830 wrong storage class for variable in C function gsrgs()
--FILE--
<?php
stats_rand_setall(4711, 88888);
$val = stats_rand_gen_gamma(0.6, 0.1);
echo is_float($val);
?>
--EXPECTF--
1
