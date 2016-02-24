--TEST--
Bug #57831 wrong storage class for variable in C functions gscgn() and gssst()
--FILE--
<?php
$low = 0.6;
$high = 2.1;
$rand1 = stats_rand_gen_funiform($low, $high);
$rand2 = stats_rand_gen_funiform($low, $high);
$rand3 = stats_rand_gen_funiform($low, $high);
echo ($rand1 !== $rand2) . "\n";
echo ($rand2 !== $rand3) . "\n";
?>
--EXPECTF--
1
1
