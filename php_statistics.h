/*
   +----------------------------------------------------------------------+
   | PHP version 4.0                                                      |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997, 1998, 1999, 2000, 2001 The PHP Group             |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors:                                                             |
   |                                                                      |
   +----------------------------------------------------------------------+
 */

#ifndef PHP_STATISTICS_H
#define PHP_STATISTICS_H

extern zend_module_entry statistics_module_entry;
#define phpext_statistics_ptr &statistics_module_entry

#ifdef PHP_WIN32
#define PHP_STATISTICS_API __declspec(dllexport)
#else
#define PHP_STATISTICS_API
#endif


PHP_MINFO_FUNCTION(statistics);

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

/*
PHP_FUNCTION(stats_studentcdf);
PHP_FUNCTION(stats_normalcdf);
PHP_FUNCTION(stats_gammacdf);
PHP_FUNCTION(stats_chi2cdf);
PHP_FUNCTION(stats_betacdf);
PHP_FUNCTION(stats_binomialcdf);
PHP_FUNCTION(stats_noncentralchi2cdf);
PHP_FUNCTION(stats_fcdf);
PHP_FUNCTION(stats_noncentralfcdf);
PHP_FUNCTION(stats_noncentraltcdf);
PHP_FUNCTION(stats_negbinomialcdf);
PHP_FUNCTION(stats_poissoncdf);
PHP_FUNCTION(stats_laplacecdf);
PHP_FUNCTION(stats_cauchycdf);
PHP_FUNCTION(stats_logisticcdf);
PHP_FUNCTION(stats_weibullcdf);
PHP_FUNCTION(stats_uniformcdf);
PHP_FUNCTION(stats_exponentialcdf);
PHP_FUNCTION(stats_setall);
PHP_FUNCTION(stats_getsd);
PHP_FUNCTION(stats_ignuin);
PHP_FUNCTION(stats_genunf);
PHP_FUNCTION(stats_ignlgi);
PHP_FUNCTION(stats_ranf);
PHP_FUNCTION(stats_genbet);
PHP_FUNCTION(stats_genchi);
PHP_FUNCTION(stats_genexp);
PHP_FUNCTION(stats_genf);
PHP_FUNCTION(stats_gengam);
PHP_FUNCTION(stats_gennch);
PHP_FUNCTION(stats_gennf);
PHP_FUNCTION(stats_gennor);
PHP_FUNCTION(stats_phrtsd);
PHP_FUNCTION(stats_genprm);
PHP_FUNCTION(stats_ignbin);
PHP_FUNCTION(stats_ignnbn);
PHP_FUNCTION(stats_ignpoi);
PHP_FUNCTION(stats_gennt);
PHP_FUNCTION(stats_gent);
PHP_FUNCTION(stats_normaldens);
PHP_FUNCTION(stats_cauchydens);
PHP_FUNCTION(stats_laplacedens);
PHP_FUNCTION(stats_logisticdens);
PHP_FUNCTION(stats_betadens);
PHP_FUNCTION(stats_weibulldens);
PHP_FUNCTION(stats_uniformdens);
PHP_FUNCTION(stats_chi2dens);
PHP_FUNCTION(stats_gammadens);
PHP_FUNCTION(stats_studentdens);
PHP_FUNCTION(stats_exponentialdens);
PHP_FUNCTION(stats_fdens);
PHP_FUNCTION(stats_binomialpmf);
PHP_FUNCTION(stats_poissonpmf);
PHP_FUNCTION(stats_negbinomialpmf);
PHP_FUNCTION(stats_hypergeometricpmf);
PHP_FUNCTION(stats_powersum);
PHP_FUNCTION(stats_innerproduct);
PHP_FUNCTION(stats_independent_t);
PHP_FUNCTION(stats_paired_t);
PHP_FUNCTION(stats_percentile);
PHP_FUNCTION(stats_correlation);
PHP_FUNCTION(stats_binomialcoefficient);
PHP_FUNCTION(stats_factorial);
*/

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(statistics)
	int   global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(statistics)
*/

/* In every function that needs to use variables in php_statistics_globals,
   do call STATISTICS_LS_FUNCTIONTCH(); after declaring other variables used by
   that function, and always reFUNCTIONr to them as STATISTICS_G(variable).
   You are encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define STATISTICS_D zend_statistics_globals *statistics_globals
#define STATISTICS_G(v) (statistics_globals->v)
#define STATISTICS_FETCH() zend_statistics_globals *statistics_globals = ts_resource(statistics_globals_id)
#else
#define STATISTICS_D
#define STATISTICS_G(v) (statistics_globals.v)
#define STATISTICS_FETCH()
#endif

#endif	/* PHP_STATISTICS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
