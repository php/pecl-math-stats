--TEST--
Bug #61318 (stats_stat_powersum also casts values to floats)
--FILE--
<?php
$data = array(2, 3, 2, 2, 2);
stats_stat_powersum($data, 1);
var_dump($data);
?>
--EXPECTF--
array(5) {
  [0]=>
  int(2)
  [1]=>
  int(3)
  [2]=>
  int(2)
  [3]=>
  int(2)
  [4]=>
  int(2)
}
