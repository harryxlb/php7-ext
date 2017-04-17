#ifndef XILOG_H
#define XILOG_H

#define XILOG_VERSION "1.0"
#define XILOG_AUTHOR "xilibo<harryxlb@gmail.com>"
#define LOG_FILE "xlb.log"
#define LOG_LEN 0XFFFF
#define LOG_START_END 0
#define L_INFO 1
#define L_DEBUG 2
#define L_NOTICE 3
#define L_WARNING 4
#define L_ERROR 5

extern zend_module_entry xilog_module_entry;

#ifdef PHP_WIN32
#   define PHP_XILOG_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#   define PHP_XILOG_API __attribute__ ((visibility("default")))
#else
#   define PHP_XILOG_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

PHP_FUNCTION(xilog_write);
PHP_FUNCTION(xilog_version);

PHP_MINIT_FUNCTION(xilog);
PHP_RINIT_FUNCTION(xilog);
PHP_RSHUTDOWN_FUNCTION(xilog);
PHP_MSHUTDOWN_FUNCTION(xilog);
PHP_MINFO_FUNCTION(xilog);


#define XILOG_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(xtool, v)

#if defined(ZTS) && defined(COMPILE_DL_XILOG)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif
