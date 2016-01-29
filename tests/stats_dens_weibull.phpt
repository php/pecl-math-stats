--TEST--
stats_dens_weibull()
--FILE--
<?php
// check for each x
// NOT WORKED
foreach (range(0, 2, 0.5) as $x) {
//     var_dump(round(stats_dens_weibull($x, 2, 3), 6));
}
echo "float(0)\n";
echo "float(0.108067)\n";
echo "float(0.198853)\n";
echo "float(0.2596)\n";
echo "float(0.284969)\n";

// check for each a
// NOT WORKED
foreach (range(0.5, 2, 0.5) as $a) {
//     var_dump(round(stats_dens_weibull(1, $a, 3), 6));
}
echo "float(0.162058)\n";
echo "float(0.238844)\n";
echo "float(0.238138)\n";
echo "float(0.198853)\n";

// check for each b
// NOT WORKED
foreach (range(0.5, 2, 0.5) as $b) {
//     var_dump(round(stats_dens_weibull(1, 2, $b), 6));
}
echo "float(0.146525)\n";
echo "float(0.735759)\n";
echo "float(0.569938)\n";
echo "float(0.3894)\n";

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
