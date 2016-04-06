--TEST--
stats_rand_getsd()
--FILE--
<?php
stats_rand_setall(10, 20);
$sd = stats_rand_getsd();
echo $sd[0], "\n";
echo $sd[1], "\n";
?>
--EXPECTF--
10
20
