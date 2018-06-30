dnl config.m4 for extension stats

PHP_ARG_ENABLE(stats, whether to enable stats support,
[  --enable-stats           Enable statistics support])

if test "$PHP_STATS" != "no"; then
  PHP_NEW_EXTENSION(stats, php_stats.c com.c dcdflib.c ipmpar.c linpack.c randlib.c , $ext_shared)
fi
