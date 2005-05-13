--TEST--
stats_absolute_deviation()
--FILE--
<?php
include 'common.php';
var_dump(sprintf("%2.9f", stats_absolute_deviation(array(4,1,7))));
var_dump(sprintf("%2.9f", stats_absolute_deviation(array(2,1,3))));
var_dump(stats_absolute_deviation(array()));
?>
--EXPECTF--
string(11) "2.000000000"
string(11) "0.666666667"

Warning: stats_absolute_deviation(): The array has zero elements in %s on line %d
bool(false)