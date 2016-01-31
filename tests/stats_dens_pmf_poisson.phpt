--TEST--
stats_dens_pmf_poisson()
--FILE--
<?php
// check for each x
foreach (range(0, 5) as $x) {
    var_dump(round(stats_dens_pmf_poisson($x, 1), 6));
}

// check for each lb
foreach (range(0.5, 3, 0.5) as $lb) {
    var_dump(round(stats_dens_pmf_poisson(1, $lb), 6));
}
?>
--EXPECTF--
float(0.367879)
float(0.367879)
float(0.18394)
float(0.061313)
float(0.015328)
float(0.003066)
float(0.303265)
float(0.367879)
float(0.334695)
float(0.270671)
float(0.205212)
float(0.149361)
