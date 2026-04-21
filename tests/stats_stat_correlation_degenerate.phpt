--TEST--
stats_stat_correlation() degenerate inputs
--FILE--
<?php
// empty arrays
var_dump(stats_stat_correlation(array(), array()));

// single-element arrays
var_dump(stats_stat_correlation(array(1), array(2)));

// zero variance in X
var_dump(stats_stat_correlation(array(1, 1, 1), array(1, 2, 3)));

// zero variance in Y
var_dump(stats_stat_correlation(array(1, 2, 3), array(5, 5, 5)));
?>
--EXPECTF--
Warning: stats_stat_correlation(): Correlation requires at least 2 data points in %s on line %d
bool(false)

Warning: stats_stat_correlation(): Correlation requires at least 2 data points in %s on line %d
bool(false)

Warning: stats_stat_correlation(): Correlation is undefined when one or both arrays have zero variance in %s on line %d
bool(false)

Warning: stats_stat_correlation(): Correlation is undefined when one or both arrays have zero variance in %s on line %d
bool(false)
