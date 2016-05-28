--TEST--
Bug #61318 (stats_harmonic_mean also casts values to floats)
--FILE--
<?php
$data = array(1, 2, 3);
stats_harmonic_mean($data);
var_dump($data);
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
