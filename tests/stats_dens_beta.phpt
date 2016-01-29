--TEST--
stats_dens_beta()
--FILE--
<?php
// check for each x
foreach (range(0.1, 0.9, 0.2) as $x) {
    var_dump(round(stats_dens_beta($x, 2, 3), 6));
}

// check for each a
foreach (range(0.5, 3, 0.5) as $a) {
    var_dump(round(stats_dens_beta(0.4, $a, 3), 6));
}

// check for each b
foreach (range(0.5, 3, 0.5) as $b) {
    var_dump(round(stats_dens_beta(0.4, 2, $b), 6));
}
?>
--EXPECTF--
float(0.972)
float(1.764)
float(1.5)
float(0.756)
float(0.108)
float(0.533634)
float(1.08)
float(1.494176)
float(1.728)
float(1.793011)
float(1.728)
float(0.387298)
float(0.8)
float(1.161895)
float(1.44)
float(1.626653)
float(1.728)
