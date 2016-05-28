--TEST--
stats_skew()
--FILE--
<?php
var_dump(sprintf("%2.9f", stats_skew(array(99,333,5, 7, 2, 4))));
?>
--EXPECTF--
string(11) "1.505674536"
