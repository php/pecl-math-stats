--TEST--
Bug #61318 (stats_stat_innerproduct also casts values to floats)
--FILE--
<?php
$data1 = array(1, 2, 3);
$data2 = array(4, 5, 6);
stats_stat_innerproduct($data1, $data2);
var_dump($data1);
var_dump($data2);
?>
--EXPECTF--
array(3) {
  [0]=>
  int(1)
  [1]=>
  int(2)
  [2]=>
  int(3)
}
array(3) {
  [0]=>
  int(4)
  [1]=>
  int(5)
  [2]=>
  int(6)
}
