--TEST--
math_covariance() tests
--FILE--
<?php
include 'common.php';
$a_1 = array(
 15, 16, 8, 6, 15, 12, 12, 18, 12, 20, 12, 14,
);

$a_2 = array(
 17.24, 15, 14.91, 4.5, 18, 6.29, 19.23, 18.69, 7.21, 42.06, 7.5, 8,
);

var_dump(sprintf("%2.9f", stats_covariance($a_1, $a_2)));
var_dump(stats_covariance(array(2,1), array(1)));
var_dump(stats_covariance(array(), array(0)));
?>
--EXPECTF--
string(12) "25.460555556"

Warning: stats_covariance(): The datasets are not of the same size in %s on line %d
bool(false)

Warning: stats_covariance(): The first array has zero elements in %s on line %d
bool(false)