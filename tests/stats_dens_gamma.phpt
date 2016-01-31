--TEST--
stats_dens_gamma()
--FILE--
<?php
// check for each x
foreach (range(0.5, 2, 0.5) as $x) {
    var_dump(round(stats_dens_gamma($x, 1, 1), 6));
}

// check for each shape
foreach (range(0.5, 2, 0.5) as $shape) {
    var_dump(round(stats_dens_gamma(1, $shape, 1), 6));
}

// check for each scale
foreach (range(0.5, 2, 0.5) as $scale) {
    var_dump(round(stats_dens_gamma(1, 1, $scale), 6));
}

// error cases
var_dump(stats_dens_gamma(1, 1, 0)); // scale == 0
?>
--EXPECTF--
float(0.606531)
float(0.367879)
float(0.22313)
float(0.135335)
float(0.207554)
float(0.367879)
float(0.415107)
float(0.367879)
float(0.270671)
float(0.367879)
float(0.342278)
float(0.303265)

Warning: stats_dens_gamma(): scale == 0.0 in %s on line %d
bool(false)
