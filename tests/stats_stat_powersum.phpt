--TEST--
stats_stat_powersum()
--FILE--
<?php
var_dump(stats_stat_powersum(array(1, 2, 4), 2));
var_dump(stats_stat_powersum(array(1, 2, 4), 0));
var_dump(stats_stat_powersum(array(1, 2, 4), -2));
var_dump(stats_stat_powersum(array(1, 0, 4), 1));
var_dump(stats_stat_powersum(array(1, 0, 4), 0));
var_dump(stats_stat_powersum(array(), 1));
?>
--EXPECTF--
float(21)
float(3)
float(1.3125)
float(5)

Warning: stats_stat_powersum(): Both value and power are zero in %s on line %d
float(2)
float(0)
