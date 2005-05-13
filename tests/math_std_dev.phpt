--TEST--
stats_standard_deviation()/stats_variance tests
--FILE--
<?php
include 'common.php';
$a=array(4, 1, 7);
$dev=stats_standard_deviation($a);
var_dump(sprintf("%2.9f", $dev));
var_dump(stats_standard_deviation(array()));
$a=array(5,7,8,10,10);
var_dump(stats_standard_deviation($a,1));
echo "---Variance---\n";
$a=array(5,7,8,10,10);
var_dump(stats_variance($a));
var_dump(stats_variance($a, true));
?>
--EXPECTF--
string(11) "2.449489743"

Warning: stats_standard_deviation(): The array has zero elements in %s on line %d
bool(false)
float(2.1213203435596)
---Variance---
float(3.6)
float(4.5)