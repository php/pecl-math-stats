--TEST--
stats_dens_chisquare()
--FILE--
<?php
// check for each x
foreach (range(0.5, 3, 0.5) as $x) {
    var_dump(round(stats_dens_chisquare($x, 3), 6));
}

// check for each dfr
foreach (range(0.5, 3, 0.5) as $dfr) {
    var_dump(round(stats_dens_chisquare(1, $dfr), 6));
}
?>
--EXPECTF--
float(0.219696)
float(0.241971)
float(0.230799)
float(0.207554)
float(0.180722)
float(0.15418)
float(0.140674)
float(0.241971)
float(0.294304)
float(0.303265)
float(0.281348)
float(0.241971)
