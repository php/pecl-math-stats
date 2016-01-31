--TEST--
stats_dens_t()
--FILE--
<?php
// check foreach x
foreach (range(-1, 1, 0.5) as $x) {
    var_dump(round(stats_dens_t($x, 1), 6));
}

// check foreach dfr
foreach (range(0.5, 2, 0.5) as $dfr) {
    var_dump(round(stats_dens_t(0, $dfr), 6));
}

// error cases
var_dump(stats_dens_t(1, 0));   // dfr == 0

?>
--EXPECTF--
float(0.159155)
float(0.254648)
float(0.31831)
float(0.254648)
float(0.159155)
float(0.269676)
float(0.31831)
float(0.340735)
float(0.353553)

Warning: stats_dens_t(): dfr == 0.0 in %s on line %d
bool(false)
