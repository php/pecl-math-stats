--TEST--
stats_dens_f()
--FILE--
<?php
// check for each x
foreach (range(0, 3, 0.5) as $x) {
    var_dump(round(stats_dens_f($x, 3, 2), 6));
}

// check for each dfr1
foreach (range(0.5, 3, 0.5) as $dfr1) {
    var_dump(round(stats_dens_f(1, $dfr1, 2), 6));
}

// check for each dfr2
foreach (range(0.5, 3, 0.5) as $dfr2) {
    var_dump(round(stats_dens_f(1, 3, $dfr2), 6));
}
?>
--EXPECTF--
float(0)
float(0.48097)
float(0.278855)
float(0.177241)
float(0.121785)
float(0.088606)
float(0.067279)
float(0.133748)
float(0.19245)
float(0.227008)
float(0.25)
float(0.266463)
float(0.278855)
float(0.139548)
float(0.206748)
float(0.249129)
float(0.278855)
float(0.301042)
float(0.31831)
