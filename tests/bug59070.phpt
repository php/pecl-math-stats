--TEST--
Bug #59070 Percentile Stat Function
--FILE--
<?php
$values = array(3, 1, 5, 2, 4);
stats_stat_percentile($values, 50);
var_dump($values);
?>
--EXPECTF--
array(5) {
  [0]=>
  int(3)
  [1]=>
  int(1)
  [2]=>
  int(5)
  [3]=>
  int(2)
  [4]=>
  int(4)
}
