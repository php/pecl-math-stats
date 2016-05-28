--TEST--
Bug #59292 Error in stats package (stats_cdf_t function)
--FILE--
<?php
var_dump(round(stats_cdf_t(3.0, 5.0, 1), 6));      // this one works
var_dump(round(stats_cdf_t(0.984950, 5.0, 2), 6)); // fails on this
var_dump(round(stats_cdf_t(0.984950, 3.0, 3), 6)); // and this
?>
--EXPECTF--
float(0.98495)
float(2.999978)
float(4.9999)
