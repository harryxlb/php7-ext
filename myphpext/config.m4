PHP_ARG_ENABLE(myphpext,
	[Wether to enable "myphpext" extension],
	[--enable-myphpext	Enable "myphpext"]
)

if test $PHP_MYPHPEXT != "no"; then
	PHP_SUBST(MYPHPEXT_SAHRED_LIBADD)
	PHP_NEW_EXTENSION(myphpext, myphpext.c, $ext_shared)
fi
