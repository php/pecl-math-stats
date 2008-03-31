/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2004 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.0 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_0.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Andrey Hristov <andrey@php.net>                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_STATISTICS_H
#define PHP_STATISTICS_H

extern zend_module_entry stats_module_entry;
#define phpext_stats_ptr &stats_module_entry

#define PHP_STATS_VERSION "1.0.3-dev"

#ifdef PHP_WIN32
#define PHP_STATS_API __declspec(dllexport)
#else
#define PHP_STATS_API
#endif


PHP_MINFO_FUNCTION(stats);

PHP_FUNCTION(stats_bin_counts);
PHP_FUNCTION(stats_cdf_t);
PHP_FUNCTION(stats_cdf_normal); 
PHP_FUNCTION(stats_cdf_gamma);
PHP_FUNCTION(stats_cdf_chisquare);
PHP_FUNCTION(stats_cdf_beta);
PHP_FUNCTION(stats_cdf_binomial);
PHP_FUNCTION(stats_cdf_noncentral_chisquare);
PHP_FUNCTION(stats_cdf_f);
PHP_FUNCTION(stats_cdf_noncentral_f);
PHP_FUNCTION(stats_cdf_noncentral_t);
PHP_FUNCTION(stats_cdf_negative_binomial);
PHP_FUNCTION(stats_cdf_poisson);
PHP_FUNCTION(stats_cdf_laplace);
PHP_FUNCTION(stats_cdf_cauchy);
PHP_FUNCTION(stats_cdf_logistic);
PHP_FUNCTION(stats_cdf_weibull);
PHP_FUNCTION(stats_cdf_uniform);
PHP_FUNCTION(stats_cdf_exponential);
PHP_FUNCTION(stats_rand_setall); 
PHP_FUNCTION(stats_rand_getsd); 
PHP_FUNCTION(stats_rand_gen_iuniform);
PHP_FUNCTION(stats_rand_gen_funiform);
PHP_FUNCTION(stats_rand_ignlgi);
PHP_FUNCTION(stats_rand_ranf);
PHP_FUNCTION(stats_rand_gen_beta);
PHP_FUNCTION(stats_rand_gen_chisquare);
PHP_FUNCTION(stats_rand_gen_exponential);
PHP_FUNCTION(stats_rand_gen_f);
PHP_FUNCTION(stats_rand_gen_gamma);
PHP_FUNCTION(stats_rand_gen_noncentral_chisquare);
PHP_FUNCTION(stats_rand_gen_noncenral_f);
PHP_FUNCTION(stats_rand_gen_normal);
PHP_FUNCTION(stats_rand_phrase_to_seeds);
PHP_FUNCTION(stats_rand_ibinomial);
PHP_FUNCTION(stats_rand_ibinomial_negative);
PHP_FUNCTION(stats_rand_gen_ipoisson);
PHP_FUNCTION(stats_rand_gen_noncentral_t);
PHP_FUNCTION(stats_rand_gen_t);
PHP_FUNCTION(stats_dens_normal);
PHP_FUNCTION(stats_dens_cauchy);
PHP_FUNCTION(stats_dens_laplace);
PHP_FUNCTION(stats_dens_logistic);
PHP_FUNCTION(stats_dens_beta);
PHP_FUNCTION(stats_dens_weibull);
PHP_FUNCTION(stats_dens_uniform);
PHP_FUNCTION(stats_dens_chisquare);
PHP_FUNCTION(stats_dens_t);
PHP_FUNCTION(stats_dens_gamma);
PHP_FUNCTION(stats_dens_exponential);
PHP_FUNCTION(stats_dens_f);
PHP_FUNCTION(stats_dens_pmf_binomial);
PHP_FUNCTION(stats_dens_pmf_poisson);
PHP_FUNCTION(stats_dens_pmf_negative_binomial);
PHP_FUNCTION(stats_dens_pmf_hypergeometric);
PHP_FUNCTION(stats_stat_powersum);
PHP_FUNCTION(stats_stat_innerproduct);
PHP_FUNCTION(stats_stat_independent_t);
PHP_FUNCTION(stats_stat_paired_t);
PHP_FUNCTION(stats_stat_percentile);
PHP_FUNCTION(stats_stat_correlation);
PHP_FUNCTION(stats_stat_binomial_coef);
PHP_FUNCTION(stats_stat_factorial);
PHP_FUNCTION(stats_absolute_deviation);
PHP_FUNCTION(stats_standard_deviation);
PHP_FUNCTION(stats_variance);
PHP_FUNCTION(stats_harmonic_mean);
PHP_FUNCTION(stats_skew);
PHP_FUNCTION(stats_kurtosis);
PHP_FUNCTION(stats_covariance);


#ifdef ZTS
#define STATS_D zend_stats_globals *stats_globals
#define STATS_G(v) (stats_globals->v)
#define STATS_FETCH() zend_stats_globals *stats_globals = ts_resource(stats_globals_id)
#else
#define STATS_D
#define STATS_G(v) (stats_globals.v)
#define STATS_FETCH()
#endif

#endif	/* PHP_STATISTICS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
