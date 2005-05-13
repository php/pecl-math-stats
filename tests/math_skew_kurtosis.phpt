--TEST--
stats_skew()/stats_kurtosis() tests
--FILE--
<?php
include 'common.php';
var_dump(sprintf("%2.9f", stats_skew(array(99,333,5, 7, 2, 4))));
var_dump(stats_standard_deviation(array()));
var_dump(sprintf("%2.9f", stats_kurtosis(array(1,3,5,7))));
var_dump(stats_standard_deviation(array()));
?>
--EXPECTF--
string(11) "1.505674536"

Warning: stats_standard_deviation(): The array has zero elements in %s on line %d
bool(false)
string(12) "-1.360000000"

Warning: stats_standard_deviation(): The array has zero elements in %s on line %d
bool(false)