--TEST--
stats_dens_pmf_hypergeometric()
--FILE--
<?php

/*
 * Definition from Wikipedia
 * (see https://en.wikipedia.org/wiki/Hypergeometric_distribution)
 *
 * P(X=k) = binom(k, K) * binom(n-k, N-K) / binom(n, N)
 * where
 *   N is the population size,
 *   K is the number of success states in the population,
 *   n is the number of draws,
 *   k is the number of observed successes.
 *
 * Implementation in php_stats.c
 *
 * stats_dens_pmf_hypergeometric(n1, n2, N1, N2)
 *   = binom(n1, N1) * binom(n2, N2) / binom(n1+n2, N1+N2)
 *
 * so the relation between both definitions is
 *   n1 = k        is the number of observed successes,
 *   n2 = n - k    is the number of observed failures,
 *   N1 = K        is the number of success states in the population,
 *   N2 = N - K    is the number of failure states in the population.
 */

// check for each n1
foreach (range(0, 3) as $n1) {
    var_dump(stats_dens_pmf_hypergeometric($n1, 1, 2, 3));
}

// check for each n2
foreach (range(0, 3) as $n2) {
    var_dump(stats_dens_pmf_hypergeometric(1, $n2, 2, 3));
}

// check for each N1
foreach (range(0, 3) as $N1) {
    var_dump(stats_dens_pmf_hypergeometric(1, 1, $N1, 3));
}

// check for each N2
foreach (range(1, 3) as $N2) {
    var_dump(round(stats_dens_pmf_hypergeometric(1, 1, 2, $N2), 6));
}

// error cases
var_dump(stats_dens_pmf_hypergeometric(1, 3, 1, 2)); // n1 + n2 > N1 + N2
?>
--EXPECTF--
float(0.6)
float(0.6)
float(0.3)
float(0)
float(0.4)
float(0.6)
float(0.6)
float(0.4)
float(0)
float(0.5)
float(0.6)
float(0.6)
float(0.666667)
float(0.666667)
float(0.6)

Warning: stats_dens_pmf_hypergeometric(): possible division by zero - n1+n2 >= N1+N2 in %s on line %d
float(NAN)
