/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2004 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.1 of the PHP license,       |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_1.txt.                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Andrey Hristov <andrey@php.net>                              |
  +----------------------------------------------------------------------+
*/

#ifndef PHP_STATS_H
#define PHP_STATS_H

extern zend_module_entry stats_module_entry;
#define phpext_stats_ptr &stats_module_entry

#define PHP_STATS_VERSION "2.1.0"

#ifdef PHP_WIN32
#define PHP_STATS_API __declspec(dllexport)
#else
#define PHP_STATS_API
#endif


PHP_MINFO_FUNCTION(stats);

#ifdef ZTS
#define STATS_D zend_stats_globals *stats_globals
#define STATS_G(v) (stats_globals->v)
#define STATS_FETCH() zend_stats_globals *stats_globals = ts_resource(stats_globals_id)
#else
#define STATS_D
#define STATS_G(v) (stats_globals.v)
#define STATS_FETCH()
#endif

#endif	/* PHP_STATS_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * indent-tabs-mode: t
 * End:
 */
