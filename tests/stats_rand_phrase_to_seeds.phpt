--TEST--
stats_rand_phrase_to_seeds()
--FILE--
<?php
$retval = stats_rand_phrase_to_seeds('pecl_math_stats');
var_dump(is_int($retval[0]));
var_dump(is_int($retval[1]));
var_dump(1 <= $retval[0] && $retval[0] <= (1 << 30));
var_dump(1 <= $retval[1] && $retval[1] <= (1 << 30));
?>
--EXPECTF--
bool(true)
bool(true)
bool(true)
bool(true)
