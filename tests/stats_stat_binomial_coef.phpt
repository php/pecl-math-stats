--TEST--
stats_stat_binomial_coef()
--FILE--
<?php
var_dump(stats_stat_binomial_coef(0, 4));
var_dump(stats_stat_binomial_coef(1, 4));
var_dump(stats_stat_binomial_coef(2, 4));
var_dump(stats_stat_binomial_coef(3, 4));
var_dump(stats_stat_binomial_coef(4, 4));
?>
--EXPECTF--
float(1)
float(4)
float(6)
float(4)
float(1)
