--TEST--
stats_dens_exponential()
--FILE--
<?php
// check for each x
foreach (range(-0.5, 2, 0.5) as $x) {
    var_dump(round(stats_dens_exponential($x, 2), 6));
}

// check for each scale
foreach (range(0.5, 2, 0.5) as $scale) {
    var_dump(round(stats_dens_exponential(1, $scale), 6));
}

// error cases
var_dump(stats_dens_exponential(1, 0)); // scale == 0
?>
--EXPECTF--
float(0)
float(0.5)
float(0.3894)
float(0.303265)
float(0.236183)
float(0.18394)
float(0.270671)
float(0.367879)
float(0.342278)
float(0.303265)

Warning: stats_dens_exponential(): scale == 0.0 in %s on line %d
bool(false)
