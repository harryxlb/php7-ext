#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "myphpext.h"

PHP_FUNCTION(myphpext)
{
	int x;

	for(x = 0; x < 5; x++)
        php_printf("myphpext is loop %d.\n", x);
}

PHP_MINFO_FUNCTION(myphpext)
{
    php_info_print_table_start();
	php_info_print_table_row(2, "myphpext for DEVELOPMENT/PRODUCT", "DEVELOPMENT");
	php_info_print_table_row(2, "myphpext version", MYPHPEXT_VERSION);
	php_info_print_table_row(2, "myphpext author", MYPHPEXT_AUTHOR);
    php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}

const zend_function_entry myphpext_functions[] = {
	PHP_FE(myphpext, NULL)
	PHP_FE_END
};

zend_module_entry myphpext_module_entry = {
    STANDARD_MODULE_HEADER,
    "myphpext",
    myphpext_functions,
    NULL, // PHP_MINIT(myphpext),
    NULL, // PHP_MSHUTDOWN(myphpext),
    NULL, // PHP_RINIT(myphpext),       /* Replace with NULL if there's nothing to do at request start */
    NULL, // PHP_RSHUTDOWN(myphpext),   /* Replace with NULL if there's nothing to do at request end */
    PHP_MINFO(myphpext),
    MYPHPEXT_VERSION,
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_MYPHPEXT
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(myphpext)
#endif
