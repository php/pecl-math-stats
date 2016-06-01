--TEST--
Bug #68295 Warning: stats_stat_powersum(): Both value and power are zero
--FILE--
<?php
var_dump(stats_stat_powersum(array(1, 2, 0), 2));
?>
--EXPECTF--
float(5)
