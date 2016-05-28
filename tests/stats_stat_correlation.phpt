--TEST--
stats_stat_correlation()
--FILE--
<?php
var_dump(stats_stat_correlation(array(1, 2, 3), array(1, 2, 3)));
var_dump(stats_stat_correlation(array(1, 2, 3), array(1, 2, 1)));
var_dump(stats_stat_correlation(array(1, 2, 3), array(3, 2, 1)));
var_dump(stats_stat_correlation(array(1, 2, 3), array(1, 2, 3, 4)));
?>
--EXPECTF--
float(1)
float(0)
float(-1)

Warning: stats_stat_correlation(): Unequal number of X and Y coordinates in %s on line %d
bool(false)
