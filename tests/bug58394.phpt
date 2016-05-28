--TEST--
Bug #58394 stats_cdf_chisquare() dies when which=2,3
--FILE--
<?php
var_dump(round(stats_cdf_chisquare(0.0525437064989, 283, 2), 6));
var_dump(round(stats_cdf_chisquare(0.0525437064989, 245.56, 3), 6));
?>
--EXPECTF--
float(245.56)
float(283)
