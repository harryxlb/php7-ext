#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_xilog.h"
// #include "ext/date/php_date.h"
// #include "ext/standard/datetime.h"
#ifndef PHP_WIN32
#include "time.h"
#else
#include "win32/time.h"
#endif

#include <sys/file.h>

ZEND_BEGIN_ARG_INFO_EX(arginfo_xilog_write, 0, 0, 1)
    ZEND_ARG_INFO(0, log)
    ZEND_ARG_INFO(0, level)
    ZEND_ARG_INFO(0, file)
ZEND_END_ARG_INFO()

zend_long xilog_write(char *log, zend_long level, char *file);

PHP_FUNCTION(xilog_write)
{
	char *log, *log_file;
	zend_long log_level = L_INFO;
	zend_long log_len, log_file_len;
	zend_long resultl = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s|ls", &log, &log_len, &log_level, &log_file, &log_file_len) == FAILURE){
		return;	
	}

	if (ZEND_NUM_ARGS() == 3){
		resultl = xilog_write(log, log_level, log_file);
	} else if (ZEND_NUM_ARGS() == 2){
		resultl = xilog_write(log, log_level, NULL);
	} else if (ZEND_NUM_ARGS() == 1){
		resultl = xilog_write(log, L_INFO, NULL);
	} else {
		php_error_docref(NULL, E_ERROR, "[xilog.PHP_FUNCTION_xilog_write] Arguments count at least 1, most 3.");
	}

	RETURN_LONG(resultl);
}

PHP_FUNCTION(xilog_version){
	RETURN_STRING(XILOG_VERSION);
}

PHP_MINIT_FUNCTION(xilog){
	if (LOG_START_END)
	    xilog_write("MINIT: Module Init ok.", L_INFO, NULL);
	// puts("MINIT: Module Init ok.\n");
}

PHP_RINIT_FUNCTION(xilog){
	if (LOG_START_END)
	    xilog_write("RINIT: Request Init ok.", L_INFO, NULL);
	 // puts("RINIT: Request Init ok.\n");
}

PHP_RSHUTDOWN_FUNCTION(xilog){
	if (LOG_START_END)
	    xilog_write("RSHUTDOWN: Request Shutdown ok.", L_INFO, NULL);	
	 // puts("RSHUTDOWN: Request Shutdown ok.\n");	
}

PHP_MSHUTDOWN_FUNCTION(xilog){
	if (LOG_START_END)
	    xilog_write("MSHUTDOWN: Module Shutdown ok.", L_INFO, NULL);
	// puts("MSHUTDOWN: Module Shutdown ok.\n");
}

PHP_MINFO_FUNCTION(xilog)
{
    php_info_print_table_start();
	php_info_print_table_row(2, "xilog for DEVELOPMENT/PRODUCT", "DEVELOPMENT");
	php_info_print_table_row(2, "xilog version", XILOG_VERSION);
	php_info_print_table_row(2, "xilog author", XILOG_AUTHOR);
    php_info_print_table_end();
}

const zend_function_entry xilog_functions[] = {
	PHP_FE(xilog_version, NULL)
	PHP_FE(xilog_write, arginfo_xilog_write)
	PHP_FE_END
};

zend_module_entry xilog_module_entry = {
    STANDARD_MODULE_HEADER,
    "xilog",
    xilog_functions,
    PHP_MINIT(xilog),
    PHP_MSHUTDOWN(xilog),
    PHP_RINIT(xilog),
    PHP_RSHUTDOWN(xilog),
    PHP_MINFO(xilog),
    XILOG_VERSION,
    STANDARD_MODULE_PROPERTIES
};

zend_long xilog_write(char *log, zend_long level, char *file)
{
	FILE *plog = NULL;
	char *log_s = (char *) emalloc(sizeof(char) * LOG_LEN);
	memset(log_s, 0, sizeof(char) * LOG_LEN);
	char *level_tip;

	if (file == NULL){
	    plog = fopen(LOG_FILE, "a");
	} else {
	    plog = fopen(file, "a");
	}

	php_printf("log file: %s\n", LOG_FILE);
	php_printf("LEVEL: %d\n", level);

	if (plog == NULL){
		php_error(E_ERROR, "[xilog.xilog_write] File open failed.");
		return -1;
	}
	
	if (log == NULL) {
		php_error(E_WARNING, "[xilog.xilog_write] log content must not be empty.");
		return -2;
	}

	switch (level){
		case L_INFO:
			level_tip = "[INFO]";
			break;
		case L_NOTICE:
			level_tip = "[NOTICE]";
			break;
		case L_DEBUG:
			level_tip = "[DEBUG]";
			break;
		case L_WARNING:
			level_tip = "[WARNING ";
			break;
		case L_ERROR:
			level_tip = "[ERROR] ";
			break;
		default:
			level_tip = "[INFO] ";
			break;
	}

	php_printf("log: %s\n", log);
	time_t ts = time(NULL);
	const char *dformat = "%t(%Y-%m-%d %H:%M:%S)%n";
	char now_time[25];
	strftime(now_time, sizeof(now_time), dformat, localtime(&ts));

	strcat(log_s, level_tip);
	strcat(log_s, "\t");
	strcat(log_s, log);
	strcat(log_s, now_time);
	flock(fileno(plog), LOCK_EX);
	zend_long log_length = fwrite(log_s, strlen(log_s), 1, plog);
	flock(fileno(plog), LOCK_UN);
	fclose(plog);
	plog = NULL;
	
	return log_length;

}

#ifdef COMPILE_DL_XILOG
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(xilog)
#endif
