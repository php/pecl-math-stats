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


#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_statistics.h"
#include "ext/standard/info.h"
#include "ext/standard/head.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "randlib.h"
#include "cdflib.h"

#define STATS_PI 3.14159265358979323846


static double logistic_quantile(double p);
static double logistic_cdf(double x);
static double cauchy_quantile(double p);
static double cauchy_cdf(double x);
static double laplace_quantile(double p);
static double laplace_cdf(double x);
static double exponential_quantile(double p);
static double exponential_cdf(double x);
static double binom(double x, double n);

zend_function_entry statistics_functions[] = {
	PHP_FE(stats_cdf_t,					NULL)
	PHP_FE(stats_cdf_normal,			NULL)
	PHP_FE(stats_cdf_gamma,				NULL)
	PHP_FE(stats_cdf_chisquare,			NULL)
	PHP_FE(stats_cdf_beta,				NULL)
	PHP_FE(stats_cdf_binomial,			NULL)
	PHP_FE(stats_cdf_noncentral_chisquare,NULL)
	PHP_FE(stats_cdf_f,					NULL)
	PHP_FE(stats_cdf_noncentral_f,		NULL)
	PHP_FE(stats_cdf_noncentral_t,		NULL)
	PHP_FE(stats_cdf_negative_binomial,	NULL)
	PHP_FE(stats_cdf_poisson,			NULL)
	PHP_FE(stats_cdf_laplace,			NULL)
	PHP_FE(stats_cdf_cauchy,			NULL)
	PHP_FE(stats_cdf_logistic,			NULL)
	PHP_FE(stats_cdf_weibull,			NULL)
	PHP_FE(stats_cdf_uniform,			NULL)
	PHP_FE(stats_cdf_exponential,		NULL)
	PHP_FE(stats_rand_setall,			NULL)
	PHP_FE(stats_rand_getsd,			NULL)
	PHP_FE(stats_rand_gen_iuniform,		NULL)
	PHP_FE(stats_rand_gen_funiform,		NULL)
	PHP_FE(stats_rand_ignlgi,			NULL)
	PHP_FE(stats_rand_ranf,				NULL)
	PHP_FE(stats_rand_gen_beta,			NULL)
	PHP_FE(stats_rand_gen_chisquare,	NULL)
	PHP_FE(stats_rand_gen_exponential,	NULL)
	PHP_FE(stats_rand_gen_f,			NULL)
	PHP_FE(stats_rand_gen_gamma,		NULL)
	PHP_FE(stats_rand_gen_noncentral_chisquare,NULL)
	PHP_FE(stats_rand_gen_noncenral_f,	NULL)
	PHP_FE(stats_rand_gen_normal,		NULL)
	PHP_FE(stats_rand_phrase_to_seeds,	NULL)
	PHP_FE(stats_rand_ibinomial,		NULL)
	PHP_FE(stats_rand_ibinomial_negative,NULL)
	PHP_FE(stats_rand_gen_ipoisson,		NULL)
	PHP_FE(stats_rand_gen_noncentral_t,	NULL)
	PHP_FE(stats_rand_gen_t,			NULL)
	PHP_FE(stats_dens_normal,			NULL)
	PHP_FE(stats_dens_cauchy,			NULL)
	PHP_FE(stats_dens_laplace,			NULL)
	PHP_FE(stats_dens_logistic,			NULL)
	PHP_FE(stats_dens_beta,				NULL)
	PHP_FE(stats_dens_weibull,			NULL)
	PHP_FE(stats_dens_uniform,			NULL)
	PHP_FE(stats_dens_chisquare,		NULL)
	PHP_FE(stats_dens_t,				NULL)
	PHP_FE(stats_dens_gamma,			NULL)
	PHP_FE(stats_dens_exponential,		NULL)
	PHP_FE(stats_dens_f,				NULL)
	PHP_FE(stats_dens_pmf_binomial,		NULL)
	PHP_FE(stats_dens_pmf_poisson,		NULL)
	PHP_FE(stats_dens_pmf_negative_binomial,NULL)
	PHP_FE(stats_dens_pmf_hypergeometric,	NULL)
	PHP_FE(stats_stat_powersum,			NULL)
	PHP_FE(stats_stat_innerproduct,		NULL)
	PHP_FE(stats_stat_independent_t,	NULL)
	PHP_FE(stats_stat_paired_t,			NULL)
	PHP_FE(stats_stat_percentile,		NULL)
	PHP_FE(stats_stat_correlation,		NULL)
	PHP_FE(stats_stat_binomial_coef,	NULL)
	PHP_FE(stats_stat_factorial,		NULL)
	{NULL, NULL, NULL}
};

zend_module_entry statistics_module_entry = {
	STANDARD_MODULE_HEADER,
	"statistics",
	statistics_functions,
 	NULL,
 	NULL,
 	NULL,
 	NULL,
 	PHP_MINFO(statistics),
 	"0.4",
	STANDARD_MODULE_PROPERTIES,
};

#ifdef COMPILE_DL_STATISTICS
ZEND_GET_MODULE(statistics)
#endif


PHP_MINFO_FUNCTION(statistics)
{
	php_info_print_table_start();
	php_info_print_table_row(2, "Statistics Support", "enabled");
	php_info_print_table_end();
}



/* Numbers are always smaller than strings int this function as it
 * anyway doesn't make much sense to compare two different data types.
 * This keeps it consistant and simple.
 *
 * This is not correct any more, depends on what compare_func is set to.
 */
static int stats_array_data_compare(const void *a, const void *b TSRMLS_DC)
{
	Bucket *f;
	Bucket *s;
	pval result;
	pval *first;
	pval *second;
 
	f = *((Bucket **) a);
	s = *((Bucket **) b);
 
	first = *((pval **) f->pData);
	second = *((pval **) s->pData);

	if (numeric_compare_function(&result, first, second TSRMLS_CC) == FAILURE) {
		return 0;
	} 

	if (Z_TYPE(result) == IS_DOUBLE) {
		if (Z_DVAL(result) < 0) {
			return -1;
		} else if (Z_DVAL(result) > 0) {
			return 1;
		} else {
			return 0;
		}
	}

	convert_to_long(&result);

	if (Z_LVAL(result) < 0) {
		return -1;
	} else if (Z_LVAL(result) > 0) {
		return 1;
	} 

	return 0;
}



/**************************************/
/* Cumulative Distributions Functions */
/**************************************/

/******************************************************
               Cumulative Distribution Function
                         T distribution

                             Function


     Calculates any one parameter of the t distribution given
     values for the others.

                              Arguments

     WHICH --> Integer indicating which  argument
               values is to be calculated from the others.
               Legal range: 1..3
               iwhich = 1 : Calculate P and Q from T and DF
               iwhich = 2 : Calculate T from P,Q and DF
               iwhich = 3 : Calculate DF from P,Q and T

        P <--> The integral from -infinity to t of the t-density.
               Input range: (0,1].

        Q <--> 1-P.
               Input range: (0, 1].
               P + Q = 1.0.

        T <--> Upper limit of integration of the t-density.
               Input range: ( -infinity, +infinity).
               Search range: [ -1E100, 1E100 ]

        DF <--> Degrees of freedom of the t-distribution.
                Input range: (0 , +infinity).
                Search range: [1e-100, 1E10]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                             Method

     Formula  26.5.27  of   Abramowitz   and  Stegun,   Handbook   of
     Mathematical Functions  (1966) is used to reduce the computation
     of the cumulative distribution function to that of an incomplete
     beta.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.
******************************************************/

/* {{{ proto float stats_cdf_t(float par1, float par2, int which)
	Calculates any one parameter of the T distribution given values for the others. */
PHP_FUNCTION(stats_cdf_t)
{
	double arg1;
	double arg2;
	double df;
	double bound;
	double p;
	double q;
	double t;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
								 "ddl", &arg1, &arg2, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 3) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Third parameter should be in the 1..3 range");
		RETURN_FALSE;
	}

	if (which < 3 ) {
		df = arg2;
	} else {
		t = arg2;
	}
	if (which == 1) {
		t = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
	
	cdft(&which, &p, &q, &t, &df, &status, &bound);

	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}

	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(t);
		case 3: RETURN_DOUBLE(df);
	}
	RETURN_FALSE; /* should never be reached */
}
/* }}} */

/*********************************************************************
     Cumulative Distribution Function NORmal distribution

     Calculates any one parameter of the normal
     distribution given values for the others.


                              Arguments


     WHICH  --> Integer indicating  which of the  next  parameter
     values is to be calculated using values  of the others.
     Legal range: 1..4
               iwhich = 1 : Calculate P and Q from X,MEAN and SD
               iwhich = 2 : Calculate X from P,Q,MEAN and SD
               iwhich = 3 : Calculate MEAN from P,Q,X and SD
               iwhich = 4 : Calculate SD from P,Q,X and MEAN

     P <--> The integral from -infinity to X of the normal density.
            Input range: (0,1].

     Q <--> 1-P.
            Input range: (0, 1].
            P + Q = 1.0.

     X < --> Upper limit of integration of the normal-density.
             Input range: ( -infinity, +infinity)

     MEAN <--> The mean of the normal density.
               Input range: (-infinity, +infinity)

     SD <--> Standard Deviation of the normal density.
             Input range: (0, +infinity).

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     A slightly modified version of ANORM from

     Cody, W.D. (1993). "ALGORITHM 715: SPECFUN - A Portabel FORTRAN
     Package of Special Function Routines and Test Drivers"
     acm Transactions on Mathematical Software. 19, 22-32.

     is used to calulate the  cumulative standard normal distribution.

     The rational functions from pages  90-95  of Kennedy and Gentle,
     Statistical  Computing,  Marcel  Dekker, NY,  1980 are  used  as
     starting values to Newton's Iterations which compute the inverse
     standard normal.  Therefore no  searches  are necessary for  any
     parameter.

     For X < -15, the asymptotic expansion for the normal is used  as
     the starting value in finding the inverse standard normal.
     This is formula 26.2.12 of Abramowitz and Stegun.

                             Note

     The normal density is proportional to
     exp( - 0.5 * (( X - MEAN)/SD)**2)
***********************************************************************/

/* {{{ proto float stats_stat_gennch(float par1, float par2, float par3, int which)
	Calculates any one parameter of the normal distribution given values for thee others. */
PHP_FUNCTION(stats_cdf_normal) 
{
	double arg1;
	double arg2;
	double arg3;
	double sd;
	double bound;
	double p;
	double q;
	double x;
	double mean;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}

	if (which < 4) {
		sd = arg3;
	} else {
		mean = arg3;
	}
	
	if (which < 3) {
		mean = arg2;
	} else {
		x = arg2;
	}

	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
	
	cdfnor(&which, &p, &q, &x, &mean, &sd, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation error");
		RETURN_FALSE;
	}

	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(x);
	  	case 3: RETURN_DOUBLE(mean);
	  	case 4: RETURN_DOUBLE(sd);
	}
	RETURN_FALSE; /* should never be reached */
}		
/* }}} */


/*********************************************************************
               Cumulative Distribution Function
                         GAMma Distribution


                              Function


     Calculates any one parameter of the gamma
     distribution given values for the others.


                              Arguments


     WHICH --> Integer indicating which of the next four argument
               values is to be calculated from the others.
               Legal range: 1..4
               iwhich = 1 : Calculate P and Q from X,SHAPE and SCALE
               iwhich = 2 : Calculate X from P,Q,SHAPE and SCALE
               iwhich = 3 : Calculate SHAPE from P,Q,X and SCALE
               iwhich = 4 : Calculate SCALE from P,Q,X and SHAPE

     P <--> The integral from 0 to X of the gamma density.
            Input range: [0,1].

     Q <--> 1-P.
            Input range: (0, 1].
            P + Q = 1.0.

     X <--> The upper limit of integration of the gamma density.
            Input range: [0, +infinity).
            Search range: [0,1E100]

     SHAPE <--> The shape parameter of the gamma density.
                Input range: (0, +infinity).
                Search range: [1E-100,1E100]

     SCALE <--> The scale parameter of the gamma density.
                Input range: (0, +infinity).
                Search range: (1E-100,1E100]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1
                10 if the gamma or inverse gamma routine cannot
                   compute the answer.  Usually happens only for
                   X and SHAPE very large (gt 1E10 or more)

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.


                              Method


     Cumulative distribution function (P) is calculated directly by
     the code associated with:

     DiDinato, A. R. and Morris, A. H. Computation of the  incomplete
     gamma function  ratios  and their  inverse.   ACM  Trans.  Math.
     Softw. 12 (1986), 377-393.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.


                              Note



     The gamma density is proportional to
       T**(SHAPE - 1) * EXP(- SCALE * T)
**************************************************************************/
/* {{{ proto float stats_cdf_gamma(float par1, float par2, float par3, int which)
	Calculates any one parameter of the gamma distribution given values for the others. */
PHP_FUNCTION(stats_cdf_gamma)
{
	double arg1;
	double arg2;
	double arg3;
	double bound;
	double p;
	double q;
	double x;
	double shape;
	double scale;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 
	
	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
	
	if (which < 4) {
		scale = arg3;
	} else {
		shape = arg3;
	}

	if (which < 3) {
		shape = arg2;
	} else {
		x = arg2;
	}

	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdfgam(&which, &p, &q, &x, &shape, &scale, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}
	
	switch (which)	{
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(x);
	  	case 3: RETURN_DOUBLE(shape);
	  	case 4: RETURN_DOUBLE(scale);
	}
	RETURN_FALSE; /* should never be reached */
}			
/* }}} */

/*****************************************************************
               Cumulative Distribution Function
               CHI-Square distribution

                              Function

     Calculates any one parameter of the chi-square
     distribution given values for the others.

                              Arguments


     WHICH --> Integer indicating which of the next three argument
               values is to be calculated from the others.
               Legal range: 1..3
               iwhich = 1 : Calculate P and Q from X and DF
               iwhich = 2 : Calculate X from P,Q and DF
               iwhich = 3 : Calculate DF from P,Q and X

     P <--> The integral from 0 to X of the chi-square
            distribution.
            Input range: [0, 1].

     Q <--> 1-P.
            Input range: (0, 1].
            P + Q = 1.0.

     X <--> Upper limit of integration of the non-central
            chi-square distribution.
            Input range: [0, +infinity).
            Search range: [0,1E100]

     DF <--> Degrees of freedom of the
             chi-square distribution.
             Input range: (0, +infinity).
             Search range: [ 1E-100, 1E100]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1
               10 indicates error returned from cumgam.  See
                  references in cdfgam

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.


                              Method


     Formula    26.4.19   of Abramowitz  and     Stegun, Handbook  of
     Mathematical Functions   (1966) is used   to reduce the chisqure
     distribution to the incomplete distribution.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.
*****************************************************************/		
/* {{{ proto float stats_cdf_chisquare(float par1, float par2, float par3, int which)
	Calculates any one parameter of the chi-square distribution given values for the others. */
PHP_FUNCTION(stats_cdf_chisquare)
{	
	double arg1;
	double arg2;
	double bound;
	double p;
	double q;
	double x;
	double df;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddl", &arg1, &arg2, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 3) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Third parameter should be in the 1..3 range");
		RETURN_FALSE;
	}

	if (which < 3 ) {
		df = arg2;
	} else {
		x = arg2;
	}
	
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
 
 	cdfchi(&which, &p, &q, &x, &df, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}

	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(x);
		case 3: RETURN_DOUBLE(df);
	}
	RETURN_FALSE; /* should never be here */
}
/* }}} */

/*******************************************************************
               Cumulative Distribution Function
                         BETa Distribution

                              Function

     Calculates any one parameter of the beta distribution given
     values for the others.

                              Arguments

     WHICH --> Integer indicating which of the next four argument
               values is to be calculated from the others.
               Legal range: 1..4
               iwhich = 1 : Calculate P and Q from X,Y,A and B
               iwhich = 2 : Calculate X and Y from P,Q,A and B
               iwhich = 3 : Calculate A from P,Q,X,Y and B
               iwhich = 4 : Calculate B from P,Q,X,Y and A

     P <--> The integral from 0 to X of the chi-square
            distribution.
            Input range: [0, 1].

     Q <--> 1-P.
            Input range: [0, 1].
            P + Q = 1.0.

     X <--> Upper limit of integration of beta density.
            Input range: [0,1].
            Search range: [0,1]

     Y <--> 1-X.
            Input range: [0,1].
            Search range: [0,1]
            X + Y = 1.0.

     A <--> The first parameter of the beta density.
            Input range: (0, +infinity).
            Search range: [1D-100,1D100]

     B <--> The second parameter of the beta density.
            Input range: (0, +infinity).
            Search range: [1D-100,1D100]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1
                4 if X + Y .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Cumulative distribution function  (P)  is calculated directly by
     code associated with the following reference.

     DiDinato, A. R. and Morris,  A.   H.  Algorithm 708: Significant
     Digit Computation of the Incomplete  Beta  Function Ratios.  ACM
     Trans. Math.  Softw. 18 (1993), 360-373.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

                              Note

     The beta density is proportional to
               t^(A-1) * (1-t)^(B-1)

*******************************************************************/

/* {{{ proto float stats_cdf_beta(float par1, float par2, float par3, int which)
	Calculates any one parameter of the beta distribution given values for the others. */
PHP_FUNCTION(stats_cdf_beta)
{ 
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double bound;
	double y;
	double a;
	double b;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 
	
	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}

	
	if (which < 4) {
		b = arg3;
	} else {
		a = arg3;
	}

	if (which < 3) {
		a = arg2;
	} else {
		x = arg2;
		y = 1.0 - x;
	}
		
	if (which == 1) {
		x = arg1;
		y = 1.0 - x;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdfbet(&which, &p, &q, &x, &y, &a, &b, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}
	
	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(x);
	  	case 3: RETURN_DOUBLE(a);
	  	case 4: RETURN_DOUBLE(b);
	}
	RETURN_FALSE; /* never here */
} 
/* }}} */

/*********************************************************************
               Cumulative Distribution Function
                         BINomial distribution

                              Function

     Calculates any one parameter of the binomial
     distribution given values for the others.

                              Arguments

     WHICH --> Integer indicating which of the next four argument
               values is to be calculated from the others.
               Legal range: 1..4
               iwhich = 1 : Calculate P and Q from S,XN,PR and OMPR
               iwhich = 2 : Calculate S from P,Q,XN,PR and OMPR
               iwhich = 3 : Calculate XN from P,Q,S,PR and OMPR
               iwhich = 4 : Calculate PR and OMPR from P,Q,S and XN

     P <--> The cumulation from 0 to S of the binomial distribution.
            (Probablility of S or fewer successes in XN trials each
            with probability of success PR.)
            Input range: [0,1].

     Q <--> 1-P.
            Input range: [0, 1].
            P + Q = 1.0.

     S <--> The number of successes observed.
            Input range: [0, XN]
            Search range: [0, XN]

     XN  <--> The number of binomial trials.
              Input range: (0, +infinity).
              Search range: [1E-100, 1E100]

     PR  <--> The probability of success in each binomial trial.
              Input range: [0,1].
              Search range: [0,1]

     OMPR  <--> 1-PR
              Input range: [0,1].
              Search range: [0,1]
              PR + OMPR = 1.0

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1
                4 if PR + OMPR .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                             Method

     Formula  26.5.24    of   Abramowitz  and    Stegun,  Handbook   of
     Mathematical   Functions (1966) is   used  to reduce the  binomial
     distribution  to  the  cumulative incomplete    beta distribution.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

*********************************************************************/

/* {{{ proto float stats_cdf_binomial(float par1, float par2, float par3, int which)
	Calculates any one parameter of the binomial distribution given values for the others. */
PHP_FUNCTION(stats_cdf_binomial)
{	  
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double xn;
	double bound;
	double sn;
	double pr;
	double ompr;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 
	
	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
	
	
	if (which < 4)	{
		pr = arg3;
		ompr = 1.0 - pr;
	} else {
		xn = arg3;
	}

	if (which < 3) {
		xn = arg2;
	} else {
		sn = arg2;
	}
			
	if (which == 1) {
		sn = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdfbin(&which, &p, &q, &sn, &xn, &pr, &ompr, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error in binomialcdf");
		RETURN_FALSE;
	}
	
	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(sn);
	  	case 3: RETURN_DOUBLE(xn);
	  	case 4: RETURN_DOUBLE(pr);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/*****************************************************************
               Cumulative Distribution Function
               Non-central Chi-Square

                              Function

     Calculates any one parameter of the non-central chi-square
     distribution given values for the others.

                              Arguments

     WHICH --> Integer indicating which of the next three argument
               values is to be calculated from the others.
               Input range: 1..4
               iwhich = 1 : Calculate P and Q from X and DF
               iwhich = 2 : Calculate X from P,DF and PNONC
               iwhich = 3 : Calculate DF from P,X and PNONC
               iwhich = 3 : Calculate PNONC from P,X and DF

     P <--> The integral from 0 to X of the non-central chi-square
            distribution.
            Input range: [0, 1-1E-16).

     Q <--> 1-P.
            Q is not used by this subroutine and is only included
            for similarity with other cdf* routines.

     X <--> Upper limit of integration of the non-central
            chi-square distribution.
            Input range: [0, +infinity).
            Search range: [0,1E100]

     DF <--> Degrees of freedom of the non-central
             chi-square distribution.
             Input range: (0, +infinity).
             Search range: [ 1E-100, 1E100]

     PNONC <--> Non-centrality parameter of the non-central
                chi-square distribution.
                Input range: [0, +infinity).
                Search range: [0,1E4]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Formula  26.4.25   of   Abramowitz   and   Stegun,  Handbook  of
     Mathematical  Functions (1966) is used to compute the cumulative
     distribution function.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

                            WARNING

     The computation time  required for this  routine is proportional
     to the noncentrality  parameter  (PNONC).  Very large  values of
     this parameter can consume immense  computer resources.  This is
     why the search range is bounded by 10,000.

*****************************************************************/

/* {{{ proto float stats_cdf_noncentral_chisquare(float par1, float par2, float par3, int which)
	Calculates any one parameter of the non-central chi-square distribution given values for the others. */
PHP_FUNCTION(stats_cdf_noncentral_chisquare)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double bound;
	double q;
	double x;
	double df;
	double pnonc;
	double ompr;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 
	
	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}

	if (which < 4) {
		pnonc = arg3;
	} else {
		df = arg3;
	}

	if (which < 3) {
		df = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdfchn(&which, &p, &q, &x, &df, &pnonc, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error in cdfchn");
		RETURN_FALSE;
	}
	
	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(x);
	  	case 3: RETURN_DOUBLE(df);
	  	case 4: RETURN_DOUBLE(pnonc);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/**************************************************************
               Cumulative Distribution Function F distribution

                              Function

     Calculates any one parameter of the F distribution
     given values for the others.

                              Arguments

     WHICH --> Integer indicating which of the next four argument
               values is to be calculated from the others.
               Legal range: 1..4
               iwhich = 1 : Calculate P and Q from F,DFN and DFD
               iwhich = 2 : Calculate F from P,Q,DFN and DFD
               iwhich = 3 : Calculate DFN from P,Q,F and DFD
               iwhich = 4 : Calculate DFD from P,Q,F and DFN

       P <--> The integral from 0 to F of the f-density.
              Input range: [0,1].

       Q <--> 1-P.
              Input range: (0, 1].
              P + Q = 1.0.

       F <--> Upper limit of integration of the f-density.
              Input range: [0, +infinity).
              Search range: [0,1E100]

     DFN < --> Degrees of freedom of the numerator sum of squares.
               Input range: (0, +infinity).
               Search range: [ 1E-100, 1E100]

     DFD < --> Degrees of freedom of the denominator sum of squares.
               Input range: (0, +infinity).
               Search range: [ 1E-100, 1E100]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Formula   26.6.2   of   Abramowitz   and   Stegun,  Handbook  of
     Mathematical  Functions (1966) is used to reduce the computation
     of the  cumulative  distribution function for the  F  variate to
     that of an incomplete beta.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

                              WARNING

     The value of the  cumulative  F distribution is  not necessarily
     monotone in  either degrees of freedom.  There  thus may  be two
     values  that  provide a given CDF  value.   This routine assumes
     monotonicity and will find an arbitrary one of the two values.

**********************************************************************/
/* {{{ proto float stats_cdf_f(float par1, float par2, float par3, int which)
	Calculates any one parameter of the F distribution given values for the others. */
PHP_FUNCTION(stats_cdf_f)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double bound;
	double dfn;
	double q;
	double f;
	double dfd;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
	if (which < 4) {
		dfd = arg3;
	} else {
		dfn = arg3;
	}
	if (which < 3) {
		dfn = arg2;
	} else {
		f = arg2;
	}
	if (which == 1) {
		f = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdff(&which, &p, &q, &f, &dfn, &dfd, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error in cdff");
		RETURN_FALSE;
	}
	
	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(f);
	  	case 3: RETURN_DOUBLE(dfn);
	  	case 4: RETURN_DOUBLE(dfd);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/***********************************************************************
               Cumulative Distribution Function
               Non-central F distribution

                              Function

     Calculates any one parameter of the Non-central F
     distribution given values for the others.

                              Arguments

     WHICH --> Integer indicating which of the next five argument
               values is to be calculated from the others.
               Legal range: 1..5
               iwhich = 1 : Calculate P and Q from F,DFN,DFD and PNONC
               iwhich = 2 : Calculate F from P,Q,DFN,DFD and PNONC
               iwhich = 3 : Calculate DFN from P,Q,F,DFD and PNONC
               iwhich = 4 : Calculate DFD from P,Q,F,DFN and PNONC
               iwhich = 5 : Calculate PNONC from P,Q,F,DFN and DFD

       P <--> The integral from 0 to F of the non-central f-density.
              Input range: [0,1-1E-16).

       Q <--> 1-P.
              Q is not used by this subroutine and is only included
              for similarity with other cdf* routines.

       F <--> Upper limit of integration of the non-central f-density.
              Input range: [0, +infinity).
              Search range: [0,1E100]

     DFN < --> Degrees of freedom of the numerator sum of squares.
               Input range: (0, +infinity).
               Search range: [ 1E-100, 1E100]

     DFD < --> Degrees of freedom of the denominator sum of squares.
               Must be in range: (0, +infinity).
               Input range: (0, +infinity).
               Search range: [ 1E-100, 1E100]

     PNONC <-> The non-centrality parameter
               Input range: [0,infinity)
               Search range: [0,1E4]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Formula  26.6.20   of   Abramowitz   and   Stegun,  Handbook  of
     Mathematical  Functions (1966) is used to compute the cumulative
     distribution function.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

                            WARNING

     The computation time  required for this  routine is proportional
     to the noncentrality  parameter  (PNONC).  Very large  values of
     this parameter can consume immense  computer resources.  This is
     why the search range is bounded by 10,000.

                              WARNING

     The  value  of the  cumulative  noncentral F distribution is not
     necessarily monotone in either degrees  of freedom.  There  thus
     may be two values that provide a given  CDF value.  This routine
     assumes monotonicity  and will find  an arbitrary one of the two
     values.

***********************************************************************/

/* {{{ proto float stats_cdf_noncentral_f(float par1, float par2, float par3, float par4, int which)
	Calculates any one parameter of the Non-central F distribution given values for the others. */
PHP_FUNCTION(stats_cdf_noncentral_f)
{
	double arg1;
	double arg2;
	double arg3;
	double arg4;
	double p;
	double q;
	double f;
	double dfn;
	double dfd;
	double pnonc;
	double bound;
	int which;
	int status = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddddl", &arg1, &arg2, &arg3, &arg4, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 5) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fifth parameter should be in the 1..5 range");
		RETURN_FALSE;
	}
	
	if (which < 5) {
		pnonc = arg4;
	} else {
		dfd = arg4;
	}
		
	if (which < 4) {
		dfd = arg3;
	} else {
		dfn = arg3;
	}

	if (which < 3) {
		dfn = arg2;
	} else {
		f = arg2;
	}
			
	if (which == 1) {
		f = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdffnc(&which, &p, &q, &f, &dfn, &dfd, &pnonc, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error in cdffnc");
		RETURN_FALSE;
	}
	
	switch (which) {
	  	case 1: RETURN_DOUBLE(p);
	  	case 2: RETURN_DOUBLE(f);
	  	case 3: RETURN_DOUBLE(dfn);
	  	case 4: RETURN_DOUBLE(dfd);
		case 5: RETURN_DOUBLE(pnonc);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/************************************************************************
           Cumulative Distribution Function Non-Central T distribution
 
                                Function
 
      Calculates any one parameter of the noncentral t distribution give
      values for the others.
 
                                Arguments
 
      WHICH --> Integer indicating which  argument
                values is to be calculated from the others.
                Legal range: 1..3
                iwhich = 1 : Calculate P and Q from T,DF,PNONC
                iwhich = 2 : Calculate T from P,Q,DF,PNONC
                iwhich = 3 : Calculate DF from P,Q,T
                iwhich = 4 : Calculate PNONC from P,Q,DF,T
 
         P <--> The integral from -infinity to t of the noncentral t-den
               Input range: (0,1].
 
         Q <--> 1-P.
               Input range: (0, 1].
                P + Q = 1.0.
 
         T <--> Upper limit of integration of the noncentral t-density.
                Input range: ( -infinity, +infinity).
                Search range: [ -1E100, 1E100 ]
 
         DF <--> Degrees of freedom of the noncentral t-distribution.
                 Input range: (0 , +infinity).
                 Search range: [1e-100, 1E10]
 
      PNONC <--> Noncentrality parameter of the noncentral t-distributio
                 Input range: [-infinity , +infinity).
                 Search range: [-1e4, 1E4]
 
      STATUS <-- 0 if calculation completed correctly
                -I if input parameter number I is out of range
                 1 if answer appears to be lower than lowest
                   search bound
                 2 if answer appears to be higher than greatest
                   search bound
                 3 if P + Q .ne. 1
 
      BOUND <-- Undefined if STATUS is 0
 
                Bound exceeded by parameter number I if STATUS
                is negative.
 
                Lower search bound if STATUS is 1.
 
                Upper search bound if STATUS is 2.
 
                                 Method
 
      Upper tail    of  the  cumulative  noncentral t is calculated usin
      formulae  from page 532  of Johnson, Kotz,  Balakrishnan, Coninuou
      Univariate Distributions, Vol 2, 2nd Edition.  Wiley (1995)
 
      Computation of other parameters involve a seach for a value that
      produces  the desired  value  of P.   The search relies  on  the
      monotinicity of P with the other parameter.

************************************************************************/

/* {{{ proto float stats_stat_noncentral_t(float par1, float par2, float par3, int which)
	Calculates any one parameter of the noncentral t distribution give values for the others. */
PHP_FUNCTION(stats_cdf_noncentral_t)
{
	double arg1;
	double arg2;
	double arg3;
	double pnonc;
	double bound;
	double p;
	double q;
	double t;
	double df;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		pnonc = arg3;
	} else {
		df = arg3;
	}
	if (which < 3) {
		df = arg2;
	} else {
		t = arg2;
	}

	if (which == 1) {
		t = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	cdftnc(&which, &p, &q, &t, &df, &pnonc, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}
	
	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(t);
		case 3: RETURN_DOUBLE(df);
		case 4: RETURN_DOUBLE(pnonc);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/************************************************************************
         Cumulative Distribution Function Negative BiNomial distribution

                              Function

     Calculates any one parameter of the negative binomial
     distribution given values for the others.

     The  cumulative  negative   binomial  distribution  returns  the
     probability that there  will be  F or fewer failures before  the
     XNth success in binomial trials each of which has probability of
     success PR.

     The individual term of the negative binomial is the probability of
     S failures before XN successes and is
          Choose( S, XN+S-1 ) * PR^(XN) * (1-PR)^S

                              Arguments

     WHICH --> Integer indicating which of the next four argument
               values is to be calculated from the others.
               Legal range: 1..4
               iwhich = 1 : Calculate P and Q from S,XN,PR and OMPR
               iwhich = 2 : Calculate S from P,Q,XN,PR and OMPR
               iwhich = 3 : Calculate XN from P,Q,S,PR and OMPR
               iwhich = 4 : Calculate PR and OMPR from P,Q,S and XN

     P <--> The cumulation from 0 to S of the  negative
            binomial distribution.
            Input range: [0,1].

     Q <--> 1-P.
            Input range: (0, 1].
            P + Q = 1.0.

     S <--> The upper limit of cumulation of the binomial distribution.
            There are F or fewer failures before the XNth success.
            Input range: [0, +infinity).
            Search range: [0, 1E100]

     XN  <--> The number of successes.
              Input range: [0, +infinity).
              Search range: [0, 1E100]

     PR  <--> The probability of success in each binomial trial.
              Input range: [0,1].
              Search range: [0,1].

     OMPR  <--> 1-PR
              Input range: [0,1].
              Search range: [0,1]
              PR + OMPR = 1.0

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1
                4 if PR + OMPR .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Formula   26.5.26   of   Abramowitz  and  Stegun,  Handbook   of
     Mathematical Functions (1966) is used  to  reduce calculation of
     the cumulative distribution  function to that of  an  incomplete
     beta.

     Computation of other parameters involve a seach for a value that
     produces  the desired  value  of P.   The search relies  on  the
     monotinicity of P with the other parameter.

************************************************************************/
	
/* {{{ proto float stats_cdf_negative_binomial(float par1, float par2, float par3, int which)
	Calculates any one parameter of the negative binomial distribution given values for the others. */
PHP_FUNCTION(stats_cdf_negative_binomial)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double bound;
	double sn;
	double xn;
	double pr;
	double ompr;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		pr = arg3;
		ompr = 1.0 - pr;
	} else {
		xn = arg3;
	}

	if (which < 3) {
		xn = arg2;
	} else {
		sn = arg2;
	}

	if (which == 1) {
		sn = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
	
	cdfnbn(&which, &p, &q, &sn, &xn, &pr, &ompr, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error in cdfnbn");
		RETURN_FALSE;
	}
	
	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(sn);
		case 3: RETURN_DOUBLE(xn);
		case 4: RETURN_DOUBLE(pr);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/**********************************************************************
       Cumulative Distribution Function POIsson distribution

                              Function

     Calculates any one parameter of the Poisson
     distribution given values for the others.

                              Arguments

     WHICH --> Integer indicating which  argument
               value is to be calculated from the others.
               Legal range: 1..3
               iwhich = 1 : Calculate P and Q from S and XLAM
               iwhich = 2 : Calculate A from P,Q and XLAM
               iwhich = 3 : Calculate XLAM from P,Q and S

        P <--> The cumulation from 0 to S of the poisson density.
               Input range: [0,1].

        Q <--> 1-P.
               Input range: (0, 1].
               P + Q = 1.0.

        S <--> Upper limit of cumulation of the Poisson.
               Input range: [0, +infinity).
               Search range: [0,1E100]

     XLAM <--> Mean of the Poisson distribution.
               Input range: [0, +infinity).
               Search range: [0,1E100]

     STATUS <-- 0 if calculation completed correctly
               -I if input parameter number I is out of range
                1 if answer appears to be lower than lowest
                  search bound
                2 if answer appears to be higher than greatest
                  search bound
                3 if P + Q .ne. 1

     BOUND <-- Undefined if STATUS is 0

               Bound exceeded by parameter number I if STATUS
               is negative.

               Lower search bound if STATUS is 1.

               Upper search bound if STATUS is 2.

                              Method

     Formula   26.4.21  of   Abramowitz  and   Stegun,   Handbook  of
     Mathematical Functions (1966) is used  to reduce the computation
     of  the cumulative distribution function to that  of computing a
     chi-square, hence an incomplete gamma function.

     Cumulative  distribution function  (P) is  calculated  directly.
     Computation of other parameters involve a seach for a value that
     produces  the desired value of  P.   The  search relies  on  the
     monotinicity of P with the other parameter.

**********************************************************************/

/* {{{ proto float stats_cdf_poisson(float par1, float par2, float par3, int which)
	Calculates any one parameter of the Poisson distribution given values for the others. */
PHP_FUNCTION(stats_cdf_poisson)
{
	double arg1;
	double arg2;
	double p;
	double q;
	double x;
	double xlam;
	double bound;
	int which;
	int status = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddl", &arg1, &arg2, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 3) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Third parameter should be in the 1..3 range");
		RETURN_FALSE;
	}
	
	if (which < 3 ) {
		xlam = arg2;
	} else {
		x = arg2;
	}
	
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
 
	cdfpoi(&which, &p, &q, &x, &xlam, &status, &bound);
	if (status != 0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Computation Error");
		RETURN_FALSE;
	}

	switch (which)	{
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(x);
		case 3: RETURN_DOUBLE(xlam);
	}
	RETURN_FALSE; /* never here */
}
/* }}} */


static double laplace_quantile(double p)
{
	if (p <= 0.5) {
		return log(2.0*p);
	} else {
		return (-log(2.0*(1.0-p)));
	}
}

static double laplace_cdf(double x)
{
	if (x <= 0) {
		return (0.5*exp(x));
	} else {
		return (1.0 - 0.5*exp(-x));
	}
}


/* {{{ proto float stats_cdf_laplace(float par1, float par2, float par3, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_laplace)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double t;
	double mean;
	double sd;
	int which;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		sd = arg3;
	} else {
		mean = arg3;
	}

	if (which < 3) {
		mean = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	if (which == 1) {
		t = (x - mean) / sd;
		p = laplace_cdf(t);
	} else {
		t = laplace_quantile(p);
	}

	
	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(mean + (sd * t));
		case 3: RETURN_DOUBLE(x - (sd * t));
		case 4: RETURN_DOUBLE((x - mean) / t);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

static double cauchy_quantile(double p)
{
	return (tan(STATS_PI*(p-0.5)));
}

static double cauchy_cdf (double x)
{
	return (0.5+(atan(x)/STATS_PI));
}

/* {{{ proto float stats_cdf_cauchy(float par1, float par2, float par3, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_cauchy)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double t;
	double mean;
	double sd;
	int which;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		sd = arg3;
	} else {
		mean = arg3;
	}

	if (which < 3) {
		mean = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	if (which == 1) {
		t = (x - mean) / sd;
		p = cauchy_cdf(t);
	} else {
		t = cauchy_quantile(p);
	}

	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(mean + (sd * t));
		case 3: RETURN_DOUBLE(x - (sd * t));
		case 4: RETURN_DOUBLE((x - mean) / t);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

static double logistic_cdf(double x)
{
	return (1.0/(1.0+exp(-x)));
}

static double logistic_quantile (double p)
{
	return (log(p/(1.0-p)));
}

/* {{{ proto float stats_cdf_logistic(float par1, float par2, float par3, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_logistic)
{
	double arg1;
	double arg2;
	double arg3;
	double sd;
	double p;
	double q;
	double x;
	double t;
	double mean;
	int which;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		sd = arg3;
	} else {
		mean = arg3;
	}

	if (which < 3) {
		mean = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	if (which == 1) {
		t = (x - mean) / sd;
		p = logistic_cdf(t);
	} else {
		t = logistic_quantile(p);
	}
	
	switch (which)	{
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(mean + (sd * t));
		case 3: RETURN_DOUBLE(x - (sd * t));
		case 4: RETURN_DOUBLE((x - mean) / t);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/* {{{ proto float stats_cdf_weibull(float par1, float par2, float par3, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_weibull)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double a;
	double b;
	int which;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		b = arg3;
	} else {
		a = arg3;
	}

	if (which < 3) {
		a = arg2;
	} else {
		x = arg2;
	}
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
	
	if (which == 1) {
		p = 1 - exp(-pow(x / b, a));
	} else {
		x = b * pow(-log(1.0 - p), 1.0 / a);
	}

	switch (which) {
		case 1: RETURN_DOUBLE(p);
		case 2: RETURN_DOUBLE(x);
		case 3: RETURN_DOUBLE(log(-log(1.0 - p)) / log(x / b));
		case 4: RETURN_DOUBLE(x / pow(-log(1.0 - p), 1.0 / a));
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

/* {{{ proto float stats_cdf_uniform(float par1, float par2, float par3, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_uniform)
{
	double arg1;
	double arg2;
	double arg3;
	double p;
	double q;
	double x;
	double a;
	double b;
	int which;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dddl", &arg1, &arg2, &arg3, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 4) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Fourth parameter should be in the 1..4 range");
		RETURN_FALSE;
	}
		
	if (which < 4) {
		b = arg3;
	} else {
		a = arg3;
	}

	if (which < 3) {
		a = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}
	
	if (which == 1) {
		p = 1 - exp(-pow(x / b, a));
	} else {
		x = b * pow(-log(1.0 - p), 1.0 / a);
	}

	switch (which) {
		case 4: RETURN_DOUBLE((x - (1.0 - p) * a) / p);
		case 3: RETURN_DOUBLE((x - p * b) / (1.0 - p));
		case 2: RETURN_DOUBLE(a + p * (b - a));
		case 1:
			if (x < a) {
				p = 0;
			} else {
				if (x > b) {
					p = 1;
				} else {
					p = (x - a) / ( b - a);
				}
			}
			RETURN_DOUBLE(p);
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */

static double exponential_quantile(double p)
{
	return -log(1.0-p);
}

static double exponential_cdf(double x)
{
	return (1.0 - exp(-x));
}

/* {{{ proto float stats_cdf_exponential(float par1, float par2, int which)
	Not documented */
PHP_FUNCTION(stats_cdf_exponential)
{
	double arg1;
	double arg2;
	double p;
	double q;
	double x;
	double scale;
	int which;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddl", &arg1, &arg2, &which) == FAILURE) {
		RETURN_FALSE;
	} 

	if (which < 1 || which > 3) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Third parameter should be in the 1..3 range");
		RETURN_FALSE;
	}
		
	if (which < 3) {
		scale = arg2;
	} else {
		x = arg2;
	}
			
	if (which == 1) {
		x = arg1;
	} else {
		p = arg1;
		q = 1.0 - p;
	}  
	
	switch (which) {
		case 1: RETURN_DOUBLE(exponential_cdf(x / scale));
		case 2: RETURN_DOUBLE(scale * exponential_quantile(p));
		case 3: RETURN_DOUBLE(x / exponential_quantile(p));
	}
	RETURN_FALSE; /* never here */
} 	
/* }}} */


/*********************/
/* RANDLIB functions */
/*********************/

/* {{{ proto void stats_rand_setall(int iseed1, int iseed2)
	Not documented */
PHP_FUNCTION(stats_rand_setall) 
{
	long iseed_1;
	long iseed_2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &iseed_1, &iseed_2) == FAILURE) {
		RETURN_FALSE;
	} 

	setall(iseed_1, iseed_2);
}
/* }}} */

/* {{{ proto array stats_rand_get_seeds(void)
	Not documented */
PHP_FUNCTION(stats_rand_getsd) 
{
	long iseed_1;
	long iseed_2;

	if (ZEND_NUM_ARGS() != 0) {
		WRONG_PARAM_COUNT;
	}
	getsd(&iseed_1, &iseed_2);
	
	array_init(return_value);
	add_next_index_long(return_value, iseed_1);
	add_next_index_long(return_value, iseed_2);
}
/* }}} */

/* {{{ proto int stats_rand_gen_iuniform(int low, int high)
   Generates integer uniformly distributed between LOW (inclusive) and HIGH (inclusive)  */
PHP_FUNCTION(stats_rand_gen_iuniform)
{
	int low;
	int high;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &low, &high) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (high - low > 2147483561L) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "high - low too large. low : %16.6E  high %16.6E", low, high);
		RETURN_FALSE;
	}
	if (low > high) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "low greater than high. low : %16.6E  high %16.6E", low, high);
		RETURN_FALSE;
	}
	
	RETURN_LONG(ignuin(low, high));
}
/* }}} */

/* {{{ proto float stats_rand_gen_funiform(float low, float high)
   Generates uniform float between low (exclusive) and high (exclusive) */
PHP_FUNCTION(stats_rand_gen_funiform)
{
	double low;
	double high;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &low, &high) == FAILURE) {
		RETURN_FALSE;
	}

	if (low > high) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "low greater than high. low : %16.6E  high : %16.6E", low, high);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(genunf(low, high));
}
/* }}} */

/* {{{ proto int stats_rand_gen_int(void)
	Generates integer between 1 and 2147483562 */
PHP_FUNCTION(stats_rand_ignlgi)
{
	if (ZEND_NUM_ARGS() != 0) {
		WRONG_PARAM_COUNT;
	}

	RETURN_LONG(ignlgi());
}
/* }}} */

/* {{{ proto float stats_rand_ranf(void)
	Returns a random floating point number from a uniform distribution over 0 - 1 (endpoints of this interval are not returned) using the current generator */
PHP_FUNCTION(stats_rand_ranf)
{
	if (ZEND_NUM_ARGS() != 0) {
		WRONG_PARAM_COUNT;
	}

	RETURN_DOUBLE(ranf());
}
/* }}} */

/* {{{ proto float stats_rand_gen_beta(float a, float b)
	Generates beta random deviate. Returns a random deviate from the beta distribution with parameters A and B. The density of the beta is x^(a-1) * (1-x)^(b-1) / B(a,b) for 0<x<1. aa - first parameter of the beta distribution. bb - second parameter of the beta distribution. Method R. C. H. Cheng */
PHP_FUNCTION(stats_rand_gen_beta)
{
	double a;
	double b;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &a, &b) == FAILURE) {
		RETURN_FALSE;
	}

	if (a < 1.0E-37 || b < 1.0E-37) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "'a' or 'b' lower than 1.0E-37. 'a' value : %16.6E  'b' value : %16.6E", a, b);
		RETURN_FALSE;
	}
	
	RETURN_DOUBLE(genbet(a, b));
}
/* }}} */

/* {{{ proto float stats_rand_gen_chisquare(float df)
	Generates random deviate from the distribution of a chisquare with "df" degrees of freedom random variable. */
PHP_FUNCTION(stats_rand_gen_chisquare)
{
	double df;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &df) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (df <= 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "df <= 0.0. df : %16.6E", df);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(genchi(df));
}
/* }}} */

/* {{{ proto float stats_rand_gen_exponential(float av)
	Generates a single random deviate from an exponential distribution with mean "av" */
PHP_FUNCTION(stats_rand_gen_exponential)
{
	double av;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &av) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (av < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "av < 0.0");
		RETURN_FALSE;
	}
	
	RETURN_DOUBLE(genexp(av));
}
/* }}} */

/* {{{ proto float stats_rand_gen_f(float dfn, float dfd)
	Generates a random deviate from the F (variance ratio) distribution with "dfn" degrees of freedom in the numerator and "dfd" degrees of freedom in the denominator. Method : directly generates ratio of chisquare variates*/
PHP_FUNCTION(stats_rand_gen_f)
{
	double dfn;
	double dfd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &dfn, &dfd) == FAILURE) {
		RETURN_FALSE;
	}

	if (dfn < 0.0 || dfd < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Degrees of freedom nonpositive. DFN value:%16.6E DFD value:%16.6E", dfn, dfd);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(genf(dfn, dfd));
}
/* }}} */

/* {{{ proto float stats_rand_gen_gamma(float a, float r)
	Generates random deviates from the gamma distribution whose density is (A**R)/Gamma(R) * X**(R-1) * Exp(-A*X). Parameters : a - location parameter of Gamma distribution (a > 0), r - shape parameter of Gamma distribution (r > 0) */
PHP_FUNCTION(stats_rand_gen_gamma)
{
	double a;
	double r;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &a, &r) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (!(a > 0.0 && r > 0.0)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "A or R nonpositive. A value : %16.6E , R value : %16.6E", a, r);
		RETURN_FALSE;
	}
	
	RETURN_DOUBLE(gengam(a, r));
}
/* }}} */

/* {{{ proto float stats_rand_gen_noncenral_chisquare(float df, float xnonc)
	Generates random deviate from the distribution of a noncentral chisquare with "df" degrees of freedom and noncentrality parameter "xnonc". d must be >= 1.0, xnonc must >= 0.0 */
PHP_FUNCTION(stats_rand_gen_noncentral_chisquare)
{
	double df;
	double xnonc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &df, &xnonc) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (df < 1.0 || xnonc < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "df < 1 or xnonc < 0. df value : %16.6E  xnonc value : %16.6E", df, xnonc);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(gennch(df, xnonc));
}
/* }}} */

/* {{{ proto float stats_rand_gen_noncentral_f(float dfn, float dfd, float xnonc)
	Generates a random deviate from the noncentral F (variance ratio) distribution with "dfn" degrees of freedom  in the numerator, and "dfd" degrees of freedom in the denominator, and noncentrality parameter "xnonc". Method : directly generates ratio of noncentral numerator chisquare variate to central denominator chisquare variate. */
PHP_FUNCTION(stats_rand_gen_noncenral_f)
{
	double dfn;
	double dfd;
	double xnonc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &dfn, &dfd, &xnonc) == FAILURE) {
		RETURN_FALSE;
	}

	if (dfn < 1.0 || dfd <= 0.0 || xnonc < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Either (1) Numerator df < 1.0 or (2) Denominator df <= 0.0 or (3) Noncentrality parameter < 0.0. dfn: %16.6E  dfd: %16.6E  xnonc: %16.6E", dfn, dfd, xnonc);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(gennf(dfn, dfd, xnonc));
}
/* }}} */

/* {{{ proto float stats_rand_gen_normal(float av, float sd)
	Generates a single random deviate from a normal distribution with mean, av, and standard deviation, sd (sd >= 0). Method : Renames SNORM from TOMS as slightly modified by BWB to use RANF instead of SUNIF. */
PHP_FUNCTION(stats_rand_gen_normal)
{
	double av;
	double sd;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &av, &sd) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (sd < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "sd < 0.0 . sd : %16.6E", sd);
		RETURN_FALSE;
	}
	
	RETURN_DOUBLE(gennor(av, sd));
}
/* }}} */

/* {{{ proto array stats_rand_phrase_to_seeds(string phrase)
	Uses a phrase (characted string) to generate two seeds for the RGN random number generator. Trailing blanks are eliminated before the seeds are generated. Generated seed values will fall in the range 1..2^30. */
PHP_FUNCTION(stats_rand_phrase_to_seeds)
{
	zval **par1;
	char *arg1 = NULL;
	long seed_1;
	long seed_2;

	if (ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(1, &par1) == FAILURE)  {	
		WRONG_PARAM_COUNT;
	}
	convert_to_string_ex(par1);

	arg1 = estrndup(Z_STRVAL_PP(par1), Z_STRLEN_PP(par1));
	phrtsd(arg1, &seed_1, &seed_2);
	efree(arg1);
	
	array_init(return_value);
	add_next_index_long(return_value, seed_1);
	add_next_index_long(return_value, seed_2);
}
/* }}} */

/* {{{ proto int stats_rand_gen_ibinomial(int n, float pp)
	Generates a single random deviate from a binomial distribution whose number of trials is "n" (n >= 0) and whose probability of an event in each trial is "pp" ([0;1]). Method : algorithm BTPE */
PHP_FUNCTION(stats_rand_ibinomial)
{
	long n;
	double pp;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &n, &pp) == FAILURE) {
		RETURN_FALSE;
	}

	if ((n < 0) || (pp < 0.0) || (pp > 1.0)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Bad values for the arguments. n : %d  pp : %16.6E", n, pp);
		RETURN_FALSE;
	}

	RETURN_LONG(ignbin(n, pp));
}
/* }}} */

/* {{{ proto int stats_rand_gen_ibinomial_negative(int n, float p)
	Generates a single random deviate from a negative binomial distribution. Arguments : n - the number of trials in the negative binomial distribution from which a random deviate is to be generated (n > 0), p - the probability of an event (0 < p < 1)). */
PHP_FUNCTION(stats_rand_ibinomial_negative)
{
	long n;
	double p;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ld", &n, &p) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (n <= 0L) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "n < 0. n : %d", n);
		RETURN_FALSE;
	}
	if (p < 0.0F || p > 1.0F) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "p is out of range. p : %16.E", p);
		RETURN_FALSE;
	}

	RETURN_LONG(ignnbn(n, p));
}
/* }}} */

/* {{{ proto int stats_rand_gen_ipoisson(float mu)
	Generates a single random deviate from a Poisson distribution with mean "mu" (mu >= 0.0). */
PHP_FUNCTION(stats_rand_gen_ipoisson)
{
	double mu;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "d", &mu) == FAILURE) {
		RETURN_FALSE;
	}

	if (mu < 0.0F) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "mu < 0.0 . mu : %16.6E", mu);
		RETURN_FALSE;
	}

	RETURN_LONG(ignpoi(mu));
}
/* }}} */

/* {{{ proto float stats_rand_gen_noncentral_t(float df, float xnonc)
	Generates a single random deviate from a noncentral T distribution. xnonc - noncentrality parameter. df must be >= 0.0*/
PHP_FUNCTION(stats_rand_gen_noncentral_t)
{
	double df;
	double xnonc;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &df, &xnonc) == FAILURE) {
		RETURN_FALSE;
	}

	if (df < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "df <= 0 . df : %16.6E", df);
		RETURN_FALSE;
	}

	RETURN_DOUBLE(gennor(xnonc, 1) / sqrt(genchi(df) / df) );
}
/* }}} */

/* {{{ proto float stats_rand_gen_t(float df)
	Generates a single random deviate from a T distribution. df must be >= 0.0 */
PHP_FUNCTION(stats_rand_gen_t)
{
	zval **arg1;
	double df;

	if (ZEND_NUM_ARGS() != 1 || zend_get_parameters_ex(1, &arg1) == FAILURE) {	
		WRONG_PARAM_COUNT;
	}

	convert_to_double_ex(arg1);
	df = Z_DVAL_PP(arg1);

	if (df < 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "df <= 0 . df : %16.6E", df);
		RETURN_FALSE;
	}
	
	RETURN_DOUBLE(gennor(0, 1) / sqrt(genchi(df) / df));
}		
/* }}} */

/***************************/
/* Start density functions */
/***************************/

/* {{{ proto float stats_dens_normal(float x, float ave, float stdev)
	Not documented */
PHP_FUNCTION(stats_dens_normal)
{
	double stdev;
	double ave;
	double x;
	double y;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &ave, &stdev) == FAILURE) {
		RETURN_FALSE;
	}

	if (stdev == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "stdev is 0.0");
		RETURN_FALSE;
	}
	
	z = (x - ave) / stdev;
	y = (1.0 / (stdev * sqrt(2.0 * STATS_PI))) * exp (-0.5 * z * z);

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_cauchy(float x, float ave, float stdev)
	Not documented */
PHP_FUNCTION(stats_dens_cauchy)
{
	double stdev;
	double ave;
	double x;
	double y;
	double z;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &ave, &stdev) == FAILURE) {
		RETURN_FALSE;
	}

	if (stdev == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "stdev is 0.0");
		RETURN_FALSE;
	}
	
	z = (x - ave) / stdev;
	y = 1.0 / (stdev*STATS_PI * (1.0 + (z * z)));

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_laplace(float x, float ave, float stdev)
	Not documented */
PHP_FUNCTION(stats_dens_laplace)
{
	double stdev;
	double ave;
	double x;
	double y;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &ave, &stdev) == FAILURE) {
		RETURN_FALSE;
	}

	if (stdev == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "stdev is 0.0");
		RETURN_FALSE;
	}
	
	z = fabs((x - ave) / stdev);
	y = (1.0 / (2.0 * stdev)) * exp(- z);
	
	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_logistic(float x, float ave, float stdev)
	Not documented */
PHP_FUNCTION(stats_dens_logistic)
{
	double stdev;
	double ave;
	double x;
	double y;
	double z;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &ave, &stdev) == FAILURE) {
		RETURN_FALSE;
	}

	if (stdev == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "stdev is 0.0");
		RETURN_FALSE;
	}
	
	z = exp((x - ave) / stdev);
	y = z / (stdev * pow(1 + z, 2.0));

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_beta(float x, float a, float b)
	Not documented */
PHP_FUNCTION(stats_dens_beta)
{
	double a;
	double b;
	double beta;
	double x;
	double y;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &a, &b) == FAILURE) {
		RETURN_FALSE;
	}
	
	beta = 1.0 / exp(lgamma(a) + lgamma(b) - lgamma(a + b));
	y = beta * pow(x, a - 1.0) * pow(1.0 - x, b - 1.0);

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_weibull(float x, float a, float b)
	Not documented */
PHP_FUNCTION(stats_dens_weibull)
{
	double a;
	double b;
	double beta;
	double x;
	double y;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &a, &b) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (b == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "b is 0.0");
		RETURN_FALSE;
	}
	
	y = (a / b) * pow(x / b, a - 1.0) * exp(pow(- x / b, a));

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_den_uniform(float x, float a, float b)
	Not documented */
PHP_FUNCTION(stats_dens_uniform)
{
	double a;
	double b;
	double x;
	double y;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &a, &b) == FAILURE) {
		RETURN_FALSE;
	}
	
	if (a == b) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "b == a == %16.6E", a);
		RETURN_FALSE;
	}
	
	if ((x <= b) && (x >= a)) {
		y = 1.0 / (b - a);
	} else {
		y = 0.0;
	}

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_chisquare(float x, float dfr)
	Not documented */
PHP_FUNCTION(stats_dens_chisquare)
{
	double dfr;
	double e;
	double x;
	double y;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &dfr) == FAILURE) {
		RETURN_FALSE;
	}

	e = dfr / 2.0;
	z = ((e - 1.0) * log(x)) - ((x / 2.0) +(e * log(2.0)) + lgamma(e));
	y = exp (z);

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_t(float x, float dfr)
	Not documented */
PHP_FUNCTION(stats_dens_t)
{
	double dfr;
	double e;
	double f;
	double fac1;
	double fac2;
	double fac3;
	double x;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"dd", &x, &dfr) == FAILURE) {
		RETURN_FALSE;
	}

	if (dfr == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "dfr == 0.0");
		RETURN_FALSE;
	}

	e = dfr / 2.0;
	f = e + 0.5;
	fac1 = lgamma(f);
	fac2 = f * log(1.0 + (x * x) / dfr);
	fac3 = lgamma(e) + 0.5 * log(dfr * STATS_PI);

	RETURN_DOUBLE(exp( fac1 - (fac2 + fac3) ));
}
/* }}} */

/* {{{ proto float stats_dens_gamma(float x, float shape, float scale)
	Not documented */
PHP_FUNCTION(stats_dens_gamma)
{
	double shape;
	double scale;
	double x;
	double z;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &x, &shape, &scale) == FAILURE) {
		RETURN_FALSE;
	}

	if (scale == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "scale == 0.0");
		RETURN_FALSE;
	}
	
	z = ((shape - 1.0) * log(x)) - 
			(
				(x / scale) + lgamma(shape) + (shape * log(scale))
			)
		;

	RETURN_DOUBLE(exp(z));
}
/* }}} */

/* {{{ proto float stats_dens_exponential(float x, float scale)
	Not documented */
PHP_FUNCTION(stats_dens_exponential)
{
	double scale;
	double x;
	double y;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &scale) == FAILURE) {
		RETURN_FALSE;
	}

	if (scale == 0.0) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "scale == 0.0");
		RETURN_FALSE;
	}

	if (x < 0) {
		y = 0;
	} else {
		y = exp(-x / scale) / scale;
	}

	RETURN_DOUBLE(y);
}
/* }}} */

/* {{{ proto float stats_dens_f(float x, float dfr1, float dfr2)
	*/
PHP_FUNCTION(stats_dens_f)
{
	double dfr1;
	double dfr2;
	double efr1;
	double efr2;
	double fac1;
	double fac2;
	double fac3;
	double fac4;
	double x;
	double z;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &x, &dfr1, &dfr2) == FAILURE) {
		RETURN_FALSE;
	}

	efr1 = dfr1 / 2.0;
	efr2 = dfr2 / 2.0;
	fac1 = (efr1 - 1.0) * log (x);
	fac2 = (efr1 + efr2) * log (dfr2 + (dfr1 * x));
	fac3 = (efr1 * log (dfr1)) + (efr2 * log (dfr2));
	fac4 = lgamma (efr1) + lgamma (efr2) - lgamma (efr1 + efr2);

	z = (fac1 + fac3) - (fac2 + fac4);

	RETURN_DOUBLE(exp(z));
}
/* }}} */

static double binom(double x, double n)
{
	int i;
	double di;
	double s = 1.0;

	for (i = 0; i < x; ++i) {
		di = (double) i;
		s = (s * (n - di)) / (di + 1.0);
	}

	return s;
}

/* {{{ proto float stats_dens_pmf_binomial(float x, float n, float pi)
	Not documented */
PHP_FUNCTION(stats_dens_pmf_binomial)
{
	double pi;
	double y;
	double n;
	double x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC,
						"ddd", &x, &n, &pi) == FAILURE) {
		RETURN_FALSE;
	}
	
	if ((x == 0.0 && n == 0.0) || (pi == 0.0 && x == 0.0)
		|| ( (1.0 - pi) == 0.0 && (n - x) == 0) ) {

		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Params leading to pow(0, 0). x:%16.6E  n:%16.6E  pi:%16.6E", x, n, pi);
		RETURN_FALSE;
	}
	
	y = binom(x,n) * pow(pi,x) * pow((1.0 - pi), (n - x));

	RETURN_DOUBLE(y);
}	
/* }}} */

/* {{{ proto float stats_dens_pmf_poisson(float x, float lb)
	Not documented */
PHP_FUNCTION(stats_dens_pmf_poisson)
{
	double lb;
	double z;
	double x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dd", &x, &lb) == FAILURE) {
		RETURN_FALSE;
	}

	z = (x * log(lb)) - (lb + lgamma(x + 1.0));

	RETURN_DOUBLE(exp(z));
}	
/* }}} */

/* {{{ proto float stats_dens_negative_binomial(float x, float n, float pi)
	Not documented */
PHP_FUNCTION(stats_dens_pmf_negative_binomial)
{
	double pi;
	double y;
	double n;
	double x;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ddd", &x, &n, &pi) == FAILURE) {
		RETURN_FALSE;
	}

	if ((pi == 0.0 && n == 0.0) || ((1.0 - pi) == 0.0 && x == 0.0)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Params leading to pow(0, 0). x:%16.6E  n:%16.6E  pi:%16.6E", x, n, pi);	
		RETURN_FALSE;
	}
	
	y = binom(x, n + x - 1.0) * pow(pi,n) * pow((1.0 - pi), x);

	RETURN_DOUBLE(y);
}	
/* }}} */

/* {{{ proto float stats_dens_pmf_hypergeometric(float n1, float n2, float N1, float N2)
	*/
PHP_FUNCTION(stats_dens_pmf_hypergeometric)
{
	double pi;
	double y;
	double N1;
	double N2;
	double n1;
	double n2;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "dddd", &n1, &n2, &N1, &N2) == FAILURE) {
		RETURN_FALSE;
	}

	if ((int)(n1 + n2) >= (int)(N1 + N2)) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "possible division by zero - n1+n2 >= N1+N2");
		/* RETURN_FALSE; */
	}
			
	y = binom(n1, N1) * binom (n2, N2)/binom(n1 + n2, N1 + N2);

	RETURN_DOUBLE(y);
}
/* }}} */

/************************/
/* Statistics functions */
/************************/

/* {{{ proto float stats_stat_powersum(array arr, float power)
	Not documented */
PHP_FUNCTION(stats_stat_powersum)
{
	zval **arg1, **arg2, **data;	/* pointer to array entry */
	HashPosition pos; 				/* hash iterator */
	double power;
	double sum = 0.0;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	convert_to_array_ex(arg1);
	convert_to_double_ex(arg2);
	power = Z_DVAL_PP(arg2);
	
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos);
	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data, &pos) == SUCCESS) {
		convert_to_double_ex(data);
		if (Z_DVAL_PP(data) != 0 && power != 0) {
			sum += pow (Z_DVAL_PP(data), power);
		} else {
			php_error_docref(NULL TSRMLS_CC, E_WARNING, "Both value and power are zero");
		}
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos);
	}

	RETURN_DOUBLE(sum);
}
/* }}} */

/* {{{ proto float stats_stat_innerproduct(array arr1, array arr2)
	*/
PHP_FUNCTION(stats_stat_innerproduct)
{
	zval **arg1, **arg2;
	zval **data1, **data2; 		/* pointers to array entries */
	HashPosition pos1; 	/* hash iterator */	
	HashPosition pos2; 	/* hash iterator */
	double sum = 0.0;


	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	convert_to_array_ex(arg1);
	convert_to_array_ex(arg2);

	if (zend_hash_num_elements(Z_ARRVAL_PP(arg1)) != zend_hash_num_elements(Z_ARRVAL_PP(arg2))) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unequal number of X and Y coordinates");
		RETURN_FALSE;
	}	

	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos1);
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg2), &pos2);
	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS
			&& zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg2), (void **)&data2, &pos2) == SUCCESS) {
		convert_to_double_ex(data1);
		convert_to_double_ex(data2);
		sum = Z_DVAL_PP(data1) * Z_DVAL_PP(data2);
		
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg2), &pos2);
	}

	RETURN_DOUBLE(sum);
}
/* }}} */

/* {{{ proto float stats_stat_independent_t(array arr1, array arr2)
	Not documented */
PHP_FUNCTION(stats_stat_independent_t)
{
	zval **arg1, **arg2;
	zval **data1, **data2; 		/* pointers to array entries */
	HashPosition pos1; 	/* hash iterator */	
	HashPosition pos2; 	/* hash iterator */	
	int xnum = 0, ynum = 0;
	double cur;
	double sx  = 0.0;
	double sxx = 0.0;
	double sy  = 0.0;
	double syy = 0.0;
	double mx;
	double vx;
	double my;
	double vy;
	double sp;
	double fc;
	double ts;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	convert_to_array_ex(arg1);
	convert_to_array_ex(arg2);

	xnum = zend_hash_num_elements(Z_ARRVAL_PP(arg1));
	ynum = zend_hash_num_elements(Z_ARRVAL_PP(arg2));
	if ( xnum < 2 ||  ynum < 2) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Each argument should have more than 1 element");
		RETURN_FALSE;	
	}
	
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos1);
	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS) {
		convert_to_double_ex(data1);
		cur = Z_DVAL_PP(data1);
		sx  += cur;
		sxx += cur * cur;
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
	}

	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg2), &pos2);
	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg2), (void **)&data2, &pos2) == SUCCESS) {
		convert_to_double_ex(data2);
		cur = Z_DVAL_PP(data2);
		sy  += cur;
		syy += cur * cur;
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg2), &pos2);
	}
		
	mx = sx / xnum;
	my = sy / ynum;
	vx = (sxx - (xnum * mx * mx)) / (xnum - 1.0);
	vy = (syy - (ynum * my * my)) / (ynum - 1.0);
	sp = (((xnum - 1.0) * vx) + ((ynum - 1.0) * vy)) / (xnum + ynum - 2.0);
	fc = (1.0 / xnum) + (1.0 / ynum);
	ts = (mx - my) / sqrt(sp * fc);
	
	RETURN_DOUBLE(ts);
}
/* }}} */

/* {{{ proto float stats_stat_paired_t(array arr1, array arr2)
	Not documented */
PHP_FUNCTION(stats_stat_paired_t)
{
	zval **arg1, **arg2, **data1, **data2; 		/* pointers to array entries */
	HashPosition pos1; 	/* hash iterator */	
	HashPosition pos2; 	/* hash iterator */	
	int i;
	int xnum = 0;
	int ynum = 0;
	double sd  = 0.0;
	double sdd = 0.0;
	double md;
	double td;
	double ts;
	double cur;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	xnum = zend_hash_num_elements(Z_ARRVAL_PP(arg1));
	ynum = zend_hash_num_elements(Z_ARRVAL_PP(arg2));
	
	if (xnum != ynum) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unequal number of X and Y coordinates");
		RETURN_FALSE;
	}
	if (xnum < 2) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "arr1 should have atleast 2 elements");
	}
	
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos1);
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg2), &pos2);
	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS
			&&
			zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg2), (void **)&data2, &pos2) == SUCCESS) {
		convert_to_double_ex(data1);
		convert_to_double_ex(data2);

		cur = Z_DVAL_PP(data1) - Z_DVAL_PP(data2);
		sd  += cur;
		sdd += cur * cur;
	
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg2), &pos2);
	}

	md = sd / xnum;
	td = sqrt((sdd - (xnum * md * md)) / (xnum - 1.0));
	ts = sqrt((double) xnum) * (md / td);

	RETURN_DOUBLE(ts);
}
/* }}} */

/* {{{ proto float stats_stat_percentile(float df, float xnonc)
	Not documented */
PHP_FUNCTION(stats_stat_percentile)
{
	zval **arg1, **arg2;
	zval **data1;  		/* pointers to array entries */
	HashPosition pos1; 	/* hash iterator */	
	int i;
	int ilow;
	int iupp;
	int xnum = 0;
	int cnt  = -1;
	double xmed;
	double cur;
	double perc;
	double low;
	double upp;
	double val;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}

	convert_to_array_ex(arg1);
	convert_to_double_ex(arg2);
	perc = Z_DVAL_PP(arg2);

	xnum = zend_hash_num_elements(Z_ARRVAL_PP(arg1));
					
	if (zend_hash_sort(Z_ARRVAL_PP(arg1), zend_qsort, stats_array_data_compare, 1 TSRMLS_CC) == FAILURE) {
		RETURN_FALSE;
	}

	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos1);

	low = .01 * perc * (double)xnum;
	upp = .01 * (100.0 - perc) * (double)xnum;
	ilow = floor(low);
	iupp = floor(upp);
	if ((ilow + iupp) == xnum) {
		while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS) {
			if (++cnt == ilow - 1 ) {
				convert_to_double_ex(data1);
				val = Z_DVAL_PP(data1);
				
				zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1);
				convert_to_double_ex(data1);
				val += Z_DVAL_PP(data1);
				val = val / 2.0;
				break;
			}
			zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
		}
	} else {
		while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS) {
			if (++cnt == ilow) {
				convert_to_double_ex(data1);
				val += Z_DVAL_PP(data1);
				break;
			}
			zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
		}
	}

	RETURN_DOUBLE(val);
}
/* }}} */

/* {{{ proto float stats_stat_correlation(array arr1, array arr2)
	Not documented */
PHP_FUNCTION(stats_stat_correlation)
{
	zval **arg1, **arg2;
	zval **data1, **data2; 	/* pointers to array entries */
	HashPosition pos1; 	/* hash iterator */
	HashPosition pos2; 	/* hash iterator */
	int i;
	int xnum = 0;
	int ynum = 0;
	double sx  = 0.0;
	double sy  = 0.0;
	double sxx = 0.0;
	double syy = 0.0;
	double sxy = 0.0;
	double cur;
	double mx;
	double my;
	double vx;
	double vy;
	double cc;
	double rr;

	if (ZEND_NUM_ARGS() != 2 || zend_get_parameters_ex(2, &arg1, &arg2) == FAILURE) {
		WRONG_PARAM_COUNT;
	}
	
	convert_to_array_ex(arg1);
	convert_to_array_ex(arg2);
	
	xnum = zend_hash_num_elements(Z_ARRVAL_PP(arg1));
	ynum = zend_hash_num_elements(Z_ARRVAL_PP(arg2));
	
	if (xnum != ynum) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Unequal number of X and Y coordinates");
		RETURN_FALSE;
	}
	
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg1), &pos1);
	zend_hash_internal_pointer_reset_ex(Z_ARRVAL_PP(arg2), &pos2);

	while (zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg1), (void **)&data1, &pos1) == SUCCESS 
			&& zend_hash_get_current_data_ex(Z_ARRVAL_PP(arg2), (void **)&data2, &pos2) == SUCCESS) {

		convert_to_double_ex(data1);
		convert_to_double_ex(data2);

		sx  += Z_DVAL_PP(data1);
		sxx += Z_DVAL_PP(data1) * Z_DVAL_PP(data1);
		sy  += Z_DVAL_PP(data2);
		syy += Z_DVAL_PP(data2) * Z_DVAL_PP(data2);
		sxy += Z_DVAL_PP(data1) * Z_DVAL_PP(data2);
		
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg1), &pos1);
		zend_hash_move_forward_ex(Z_ARRVAL_PP(arg2), &pos2);
	}

	mx = sx / xnum;
	my = sy / ynum;
	vx = sxx - (xnum * mx * mx);
	vy = syy - (ynum * my * my);
	cc = sxy - (xnum * mx * my);
	rr = cc / sqrt(vx * vy);

	RETURN_DOUBLE(rr);
}
/* }}} */

/* {{{ proto float stats_stat_binomial_coef(int x, int n)
	Not documented */
PHP_FUNCTION(stats_stat_binomial_coef)
{
	int i;
	int n;
	int x;
	double bc = 1.0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ll", &x, &n) == FAILURE) {
		RETURN_FALSE;
	}

	for (i = 0; i < x; ++i) {
		bc = (bc * (n - i)) / (i + 1);
	}

	RETURN_DOUBLE(bc);
}	
/* }}} */

/* {{{ proto float stats_stat_gennch(int n)
	Not documented */
PHP_FUNCTION(stats_stat_factorial)
{
	int n;
	int i;
	double f = 1;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &n) == FAILURE) {
		RETURN_FALSE;
	}
	
	for (i = 1; i <= n; ++i) {
		f *= i;
	}

	RETURN_DOUBLE(f);
}	
/* }}} */

		
/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
