--TEST--
stats_stat_independent_t()
--FILE--
<?php
var_dump(round(stats_stat_independent_t(array(1, 2), array(1, 2)), 8));
var_dump(round(stats_stat_independent_t(array(1, 2), array(2, 3)), 8));
var_dump(stats_stat_independent_t(array(1), array(1, 2)));
var_dump(stats_stat_independent_t(array(1, 2), array(1)));
?>
--EXPECTF--
float(0)
float(-1.41421356)

Warning: stats_stat_independent_t(): Each argument should have more than 1 element in %s on line %d
bool(false)

Warning: stats_stat_independent_t(): Each argument should have more than 1 element in %s on line %d
bool(false)
