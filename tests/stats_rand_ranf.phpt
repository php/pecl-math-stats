--TEST--
stats_rand_ranf()
--FILE--
<?php
$r = stats_rand_ranf();
var_dump(is_float($r));
var_dump(0 <= $r && $r < 1);
?>
--EXPECTF--
bool(true)
bool(true)
