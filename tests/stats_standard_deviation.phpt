--TEST--
stats_standard_deviation()
--FILE--
<?php
$a=array(4, 1, 7);
$dev=stats_standard_deviation($a);
var_dump(sprintf("%2.9f", $dev));
var_dump(stats_standard_deviation(array()));
$a=array(5,7,8,10,10);
var_dump(stats_standard_deviation($a,1));
?>
--EXPECTF--
string(11) "2.449489743"

Warning: stats_standard_deviation(): The array has zero elements in %s on line %d
bool(false)
float(2.1213203435596)
