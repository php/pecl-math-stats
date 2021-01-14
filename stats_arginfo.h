/* This is a generated file, edit the .stub.php file instead.
 * Stub hash: e6cfe06b9c3e187348f16fd6a34bb7eafc5042d9 */

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_cdf_t, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, par1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, which, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_cdf_normal, 0, 4, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, par1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, which, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_cdf_gamma arginfo_stats_cdf_normal

#define arginfo_stats_cdf_chisquare arginfo_stats_cdf_t

#define arginfo_stats_cdf_beta arginfo_stats_cdf_normal

#define arginfo_stats_cdf_binomial arginfo_stats_cdf_normal

#define arginfo_stats_cdf_noncentral_chisquare arginfo_stats_cdf_normal

#define arginfo_stats_cdf_f arginfo_stats_cdf_normal

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_cdf_noncentral_f, 0, 5, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, par1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par3, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, par4, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, which, IS_LONG, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_cdf_noncentral_t arginfo_stats_cdf_normal

#define arginfo_stats_cdf_negative_binomial arginfo_stats_cdf_normal

#define arginfo_stats_cdf_poisson arginfo_stats_cdf_t

#define arginfo_stats_cdf_laplace arginfo_stats_cdf_normal

#define arginfo_stats_cdf_cauchy arginfo_stats_cdf_normal

#define arginfo_stats_cdf_logistic arginfo_stats_cdf_normal

#define arginfo_stats_cdf_weibull arginfo_stats_cdf_normal

#define arginfo_stats_cdf_uniform arginfo_stats_cdf_normal

#define arginfo_stats_cdf_exponential arginfo_stats_cdf_t

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_stats_rand_setall, 0, 2, _IS_BOOL, 0)
	ZEND_ARG_TYPE_INFO(0, iseed1, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, iseed2, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_stats_rand_getsd, 0, 0, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_iuniform, 0, 2, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, low, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, high, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_funiform, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, low, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, high, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_stats_rand_ignlgi, 0, 0, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_ranf, 0, 0, MAY_BE_DOUBLE|MAY_BE_FALSE)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_beta, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_chisquare, 0, 1, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, df, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_exponential, 0, 1, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, av, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_f, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, dfn, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dfd, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_gamma, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, r, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_noncentral_chisquare, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, df, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, xnonc, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_noncentral_f, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, dfn, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dfd, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, xnonc, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_rand_gen_noncenral_f arginfo_stats_rand_gen_noncentral_f

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_normal, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, av, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, sd, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_phrase_to_seeds, 0, 1, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, phrase, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_ibinomial, 0, 2, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, pp, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_ibinomial_negative, 0, 2, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, p, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_ipoisson, 0, 1, MAY_BE_LONG|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, mu, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_rand_gen_noncentral_t arginfo_stats_rand_gen_noncentral_chisquare

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_rand_gen_t, 0, 1, MAY_BE_ARRAY|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, df, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_normal, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, ave, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, stdev, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_dens_cauchy arginfo_stats_dens_normal

#define arginfo_stats_dens_laplace arginfo_stats_dens_normal

#define arginfo_stats_dens_logistic arginfo_stats_dens_normal

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_beta, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, a, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_dens_weibull arginfo_stats_dens_beta

#define arginfo_stats_dens_uniform arginfo_stats_dens_beta

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_chisquare, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dfr, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_dens_t arginfo_stats_dens_chisquare

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_gamma, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, shape, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_exponential, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, scale, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_f, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dfr1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, dfr2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_pmf_binomial, 0, 3, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, pi, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_pmf_poisson, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, lb, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_dens_pmf_negative_binomial arginfo_stats_dens_pmf_binomial

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_dens_pmf_hypergeometric, 0, 4, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, n1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, n2, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, N1, IS_DOUBLE, 0)
	ZEND_ARG_TYPE_INFO(0, N2, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_stat_powersum, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, arr, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, power, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_stat_innerproduct, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, arr1, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, arr2, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_stat_independent_t arginfo_stats_stat_innerproduct

#define arginfo_stats_stat_paired_t arginfo_stats_stat_innerproduct

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_stat_percentile, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, arr, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, perc, IS_DOUBLE, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_stat_correlation arginfo_stats_stat_innerproduct

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_stat_binomial_coef, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, x, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_stat_factorial, 0, 1, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, n, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_variance, 0, 1, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO_WITH_DEFAULT_VALUE(0, sample, _IS_BOOL, 0, "false")
ZEND_END_ARG_INFO()

#define arginfo_stats_standard_deviation arginfo_stats_variance

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_absolute_deviation, 0, 1, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_ARRAY, 0)
ZEND_END_ARG_INFO()

#define arginfo_stats_harmonic_mean arginfo_stats_absolute_deviation

#define arginfo_stats_skew arginfo_stats_absolute_deviation

#define arginfo_stats_kurtosis arginfo_stats_absolute_deviation

ZEND_BEGIN_ARG_WITH_RETURN_TYPE_MASK_EX(arginfo_stats_covariance, 0, 2, MAY_BE_DOUBLE|MAY_BE_FALSE)
	ZEND_ARG_TYPE_INFO(0, a, IS_ARRAY, 0)
	ZEND_ARG_TYPE_INFO(0, b, IS_ARRAY, 0)
ZEND_END_ARG_INFO()


ZEND_FUNCTION(stats_cdf_t);
ZEND_FUNCTION(stats_cdf_normal);
ZEND_FUNCTION(stats_cdf_gamma);
ZEND_FUNCTION(stats_cdf_chisquare);
ZEND_FUNCTION(stats_cdf_beta);
ZEND_FUNCTION(stats_cdf_binomial);
ZEND_FUNCTION(stats_cdf_noncentral_chisquare);
ZEND_FUNCTION(stats_cdf_f);
ZEND_FUNCTION(stats_cdf_noncentral_f);
ZEND_FUNCTION(stats_cdf_noncentral_t);
ZEND_FUNCTION(stats_cdf_negative_binomial);
ZEND_FUNCTION(stats_cdf_poisson);
ZEND_FUNCTION(stats_cdf_laplace);
ZEND_FUNCTION(stats_cdf_cauchy);
ZEND_FUNCTION(stats_cdf_logistic);
ZEND_FUNCTION(stats_cdf_weibull);
ZEND_FUNCTION(stats_cdf_uniform);
ZEND_FUNCTION(stats_cdf_exponential);
ZEND_FUNCTION(stats_rand_setall);
ZEND_FUNCTION(stats_rand_getsd);
ZEND_FUNCTION(stats_rand_gen_iuniform);
ZEND_FUNCTION(stats_rand_gen_funiform);
ZEND_FUNCTION(stats_rand_ignlgi);
ZEND_FUNCTION(stats_rand_ranf);
ZEND_FUNCTION(stats_rand_gen_beta);
ZEND_FUNCTION(stats_rand_gen_chisquare);
ZEND_FUNCTION(stats_rand_gen_exponential);
ZEND_FUNCTION(stats_rand_gen_f);
ZEND_FUNCTION(stats_rand_gen_gamma);
ZEND_FUNCTION(stats_rand_gen_noncentral_chisquare);
ZEND_FUNCTION(stats_rand_gen_noncentral_f);
ZEND_FUNCTION(stats_rand_gen_normal);
ZEND_FUNCTION(stats_rand_phrase_to_seeds);
ZEND_FUNCTION(stats_rand_ibinomial);
ZEND_FUNCTION(stats_rand_ibinomial_negative);
ZEND_FUNCTION(stats_rand_gen_ipoisson);
ZEND_FUNCTION(stats_rand_gen_noncentral_t);
ZEND_FUNCTION(stats_rand_gen_t);
ZEND_FUNCTION(stats_dens_normal);
ZEND_FUNCTION(stats_dens_cauchy);
ZEND_FUNCTION(stats_dens_laplace);
ZEND_FUNCTION(stats_dens_logistic);
ZEND_FUNCTION(stats_dens_beta);
ZEND_FUNCTION(stats_dens_weibull);
ZEND_FUNCTION(stats_dens_uniform);
ZEND_FUNCTION(stats_dens_chisquare);
ZEND_FUNCTION(stats_dens_t);
ZEND_FUNCTION(stats_dens_gamma);
ZEND_FUNCTION(stats_dens_exponential);
ZEND_FUNCTION(stats_dens_f);
ZEND_FUNCTION(stats_dens_pmf_binomial);
ZEND_FUNCTION(stats_dens_pmf_poisson);
ZEND_FUNCTION(stats_dens_pmf_negative_binomial);
ZEND_FUNCTION(stats_dens_pmf_hypergeometric);
ZEND_FUNCTION(stats_stat_powersum);
ZEND_FUNCTION(stats_stat_innerproduct);
ZEND_FUNCTION(stats_stat_independent_t);
ZEND_FUNCTION(stats_stat_paired_t);
ZEND_FUNCTION(stats_stat_percentile);
ZEND_FUNCTION(stats_stat_correlation);
ZEND_FUNCTION(stats_stat_binomial_coef);
ZEND_FUNCTION(stats_stat_factorial);
ZEND_FUNCTION(stats_variance);
ZEND_FUNCTION(stats_standard_deviation);
ZEND_FUNCTION(stats_absolute_deviation);
ZEND_FUNCTION(stats_harmonic_mean);
ZEND_FUNCTION(stats_skew);
ZEND_FUNCTION(stats_kurtosis);
ZEND_FUNCTION(stats_covariance);


static const zend_function_entry ext_functions[] = {
	ZEND_FE(stats_cdf_t, arginfo_stats_cdf_t)
	ZEND_FE(stats_cdf_normal, arginfo_stats_cdf_normal)
	ZEND_FE(stats_cdf_gamma, arginfo_stats_cdf_gamma)
	ZEND_FE(stats_cdf_chisquare, arginfo_stats_cdf_chisquare)
	ZEND_FE(stats_cdf_beta, arginfo_stats_cdf_beta)
	ZEND_FE(stats_cdf_binomial, arginfo_stats_cdf_binomial)
	ZEND_FE(stats_cdf_noncentral_chisquare, arginfo_stats_cdf_noncentral_chisquare)
	ZEND_FE(stats_cdf_f, arginfo_stats_cdf_f)
	ZEND_FE(stats_cdf_noncentral_f, arginfo_stats_cdf_noncentral_f)
	ZEND_FE(stats_cdf_noncentral_t, arginfo_stats_cdf_noncentral_t)
	ZEND_FE(stats_cdf_negative_binomial, arginfo_stats_cdf_negative_binomial)
	ZEND_FE(stats_cdf_poisson, arginfo_stats_cdf_poisson)
	ZEND_FE(stats_cdf_laplace, arginfo_stats_cdf_laplace)
	ZEND_FE(stats_cdf_cauchy, arginfo_stats_cdf_cauchy)
	ZEND_FE(stats_cdf_logistic, arginfo_stats_cdf_logistic)
	ZEND_FE(stats_cdf_weibull, arginfo_stats_cdf_weibull)
	ZEND_FE(stats_cdf_uniform, arginfo_stats_cdf_uniform)
	ZEND_FE(stats_cdf_exponential, arginfo_stats_cdf_exponential)
	ZEND_FE(stats_rand_setall, arginfo_stats_rand_setall)
	ZEND_FE(stats_rand_getsd, arginfo_stats_rand_getsd)
	ZEND_FE(stats_rand_gen_iuniform, arginfo_stats_rand_gen_iuniform)
	ZEND_FE(stats_rand_gen_funiform, arginfo_stats_rand_gen_funiform)
	ZEND_FE(stats_rand_ignlgi, arginfo_stats_rand_ignlgi)
	ZEND_FE(stats_rand_ranf, arginfo_stats_rand_ranf)
	ZEND_FE(stats_rand_gen_beta, arginfo_stats_rand_gen_beta)
	ZEND_FE(stats_rand_gen_chisquare, arginfo_stats_rand_gen_chisquare)
	ZEND_FE(stats_rand_gen_exponential, arginfo_stats_rand_gen_exponential)
	ZEND_FE(stats_rand_gen_f, arginfo_stats_rand_gen_f)
	ZEND_FE(stats_rand_gen_gamma, arginfo_stats_rand_gen_gamma)
	ZEND_FE(stats_rand_gen_noncentral_chisquare, arginfo_stats_rand_gen_noncentral_chisquare)
	ZEND_FE(stats_rand_gen_noncentral_f, arginfo_stats_rand_gen_noncentral_f)
	ZEND_FALIAS(stats_rand_gen_noncenral_f, stats_rand_gen_noncentral_f, arginfo_stats_rand_gen_noncenral_f)
	ZEND_FE(stats_rand_gen_normal, arginfo_stats_rand_gen_normal)
	ZEND_FE(stats_rand_phrase_to_seeds, arginfo_stats_rand_phrase_to_seeds)
	ZEND_FE(stats_rand_ibinomial, arginfo_stats_rand_ibinomial)
	ZEND_FE(stats_rand_ibinomial_negative, arginfo_stats_rand_ibinomial_negative)
	ZEND_FE(stats_rand_gen_ipoisson, arginfo_stats_rand_gen_ipoisson)
	ZEND_FE(stats_rand_gen_noncentral_t, arginfo_stats_rand_gen_noncentral_t)
	ZEND_FE(stats_rand_gen_t, arginfo_stats_rand_gen_t)
	ZEND_FE(stats_dens_normal, arginfo_stats_dens_normal)
	ZEND_FE(stats_dens_cauchy, arginfo_stats_dens_cauchy)
	ZEND_FE(stats_dens_laplace, arginfo_stats_dens_laplace)
	ZEND_FE(stats_dens_logistic, arginfo_stats_dens_logistic)
	ZEND_FE(stats_dens_beta, arginfo_stats_dens_beta)
	ZEND_FE(stats_dens_weibull, arginfo_stats_dens_weibull)
	ZEND_FE(stats_dens_uniform, arginfo_stats_dens_uniform)
	ZEND_FE(stats_dens_chisquare, arginfo_stats_dens_chisquare)
	ZEND_FE(stats_dens_t, arginfo_stats_dens_t)
	ZEND_FE(stats_dens_gamma, arginfo_stats_dens_gamma)
	ZEND_FE(stats_dens_exponential, arginfo_stats_dens_exponential)
	ZEND_FE(stats_dens_f, arginfo_stats_dens_f)
	ZEND_FE(stats_dens_pmf_binomial, arginfo_stats_dens_pmf_binomial)
	ZEND_FE(stats_dens_pmf_poisson, arginfo_stats_dens_pmf_poisson)
	ZEND_FE(stats_dens_pmf_negative_binomial, arginfo_stats_dens_pmf_negative_binomial)
	ZEND_FE(stats_dens_pmf_hypergeometric, arginfo_stats_dens_pmf_hypergeometric)
	ZEND_FE(stats_stat_powersum, arginfo_stats_stat_powersum)
	ZEND_FE(stats_stat_innerproduct, arginfo_stats_stat_innerproduct)
	ZEND_FE(stats_stat_independent_t, arginfo_stats_stat_independent_t)
	ZEND_FE(stats_stat_paired_t, arginfo_stats_stat_paired_t)
	ZEND_FE(stats_stat_percentile, arginfo_stats_stat_percentile)
	ZEND_FE(stats_stat_correlation, arginfo_stats_stat_correlation)
	ZEND_FE(stats_stat_binomial_coef, arginfo_stats_stat_binomial_coef)
	ZEND_FE(stats_stat_factorial, arginfo_stats_stat_factorial)
	ZEND_FE(stats_variance, arginfo_stats_variance)
	ZEND_FE(stats_standard_deviation, arginfo_stats_standard_deviation)
	ZEND_FE(stats_absolute_deviation, arginfo_stats_absolute_deviation)
	ZEND_FE(stats_harmonic_mean, arginfo_stats_harmonic_mean)
	ZEND_FE(stats_skew, arginfo_stats_skew)
	ZEND_FE(stats_kurtosis, arginfo_stats_kurtosis)
	ZEND_FE(stats_covariance, arginfo_stats_covariance)
	ZEND_FE_END
};
