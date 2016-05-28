--TEST--
stats_rand_ignlgi()
--FILE--
<?php
$r = stats_rand_ignlgi();
var_dump(is_int($r));
var_dump($r >= 1);
?>
--EXPECTF--
bool(true)
bool(true)
