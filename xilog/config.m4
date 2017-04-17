PHP_ARG_ENABLE(xilog,
	[Wether to enable "xilog" extension],
	[--enable-xilog	Enable "xilog"]
)

if test $PHP_XILOG != "no"; then
	PHP_SUBST(XILOG_SAHRED_LIBADD)
	PHP_NEW_EXTENSION(xilog, xilog.c, $ext_shared)
fi
