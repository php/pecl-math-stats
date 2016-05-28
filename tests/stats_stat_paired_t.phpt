--TEST--
stats_stat_paired_t()
--FILE--
<?php
var_dump(stats_stat_paired_t(array(1, 2), array(1, 1)));
var_dump(stats_stat_paired_t(array(1, 2), array(2, 1)));
var_dump(stats_stat_paired_t(array(1, 2), array(2, 2)));
var_dump(stats_stat_paired_t(array(1, 2), array(1, 2, 3)));
var_dump(stats_stat_paired_t(array(1), array(2)));
?>
--EXPECTF--
float(1)
float(0)
float(-1)

Warning: stats_stat_paired_t(): Unequal number of X and Y coordinates in %s on line %d
bool(false)

Warning: stats_stat_paired_t(): arr1 should have atleast 2 elements in %s on line %d
bool(false)
