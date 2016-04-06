--TEST--
stats_stat_percentile()
--FILE--
<?php
var_dump(stats_stat_percentile(array(1, 3, 2, 4), 50));
var_dump(stats_stat_percentile(array(1, 3, 5, 2, 4), 50));
?>
--EXPECTF--
float(2)
float(3)
