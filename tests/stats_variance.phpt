--TEST--
stats_variance()
--FILE--
<?php
$a=array(5,7,8,10,10);
var_dump(stats_variance($a));
var_dump(stats_variance($a, true));
?>
--EXPECTF--
float(3.6)
float(4.5)
