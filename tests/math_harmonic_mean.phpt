--TEST--
stats_harmonic_mean() tests
--FILE--
<?php
include 'common.php';
var_dump(sprintf("%2.9f", stats_harmonic_mean(array(1,3,5,7))));
var_dump(stats_standard_deviation(array()));
?>
--EXPECTF--
string(11) "2.386363636"

Warning: stats_standard_deviation(): The array has zero elements in %s on line %d
bool(false)