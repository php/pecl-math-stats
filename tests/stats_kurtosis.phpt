--TEST--
stats_kurtosis()
--FILE--
<?php
var_dump(sprintf("%2.9f", stats_kurtosis(array(1,3,5,7))));
?>
--EXPECTF--
string(12) "-1.360000000"
