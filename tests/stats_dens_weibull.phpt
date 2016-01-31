--TEST--
stats_dens_weibull()
--FILE--
<?php
// check for each x
foreach (range(0, 2, 0.5) as $x) {
    var_dump(round(stats_dens_weibull($x, 2, 3), 6));
}

// check for each a
foreach (range(0.5, 2, 0.5) as $a) {
    var_dump(round(stats_dens_weibull(1, $a, 3), 6));
}

// check for each b
foreach (range(0.5, 2, 0.5) as $b) {
    var_dump(round(stats_dens_weibull(1, 2, $b), 6));
}

// error cases
?>
--EXPECTF--
float(0)
float(0.108067)
float(0.198853)
float(0.2596)
float(0.284969)
float(0.162058)
float(0.238844)
float(0.238138)
float(0.198853)
float(0.146525)
float(0.735759)
float(0.569938)
float(0.3894)
