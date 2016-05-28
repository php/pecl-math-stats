--TEST--
stats_stat_innerproduct()
--FILE--
<?php
var_dump(stats_stat_innerproduct(array(1, 2), array(3, 4)));
var_dump(stats_stat_innerproduct(array(1, 2), array(3, 4, 5)));
?>
--EXPECTF--
float(11)

Warning: stats_stat_innerproduct(): Unequal number of X and Y coordinates in %s on line %d
bool(false)
