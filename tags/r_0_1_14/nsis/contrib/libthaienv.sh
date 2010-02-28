if test -n "$LIBTHAI_BASEPATH"; then
  case `uname -a` in
	CYGWIN*)
	  LIBTHAI_BASEPATH=`echo $LIBTHAI_BASEPATH | sed -e 's/\"//g'`
	  LIBTHAI_BASEPATH=`cygpath $LIBTHAI_BASEPATH`;;
	MINGW32*)
	  LIBTHAI_BASEPATH=`echo $LIBTHAI_BASEPATH | sed -e 's/\"//g' -e 's/\\\\/\\//g' -e 's/^\\([a-zA-Z]\\):/\\/\\1/g'`
  esac
  export LIBTHAI_BASEPATH=$LIBTHAI_BASEPATH
  export PATH=$LIBTHAI_BASEPATH/bin:$PATH
#  export ACLOCAL_FLAGS="-I $LIBTHAI_BASEPATH/share/aclocal $ACLOCAL_FLAGS"

  if test "x$C_INCLUDE_PATH" = x; then
	APPEND=
  else
	APPEND=":$C_INCLUDE_PATH"
  fi
  export C_INCLUDE_PATH=$LIBTHAI_BASEPATH/include$APPEND

  if test "x$LIBRARY_PATH" = x; then
	APPEND=
  else
	APPEND=":$LIBRARY_PATH"
  fi
  export LIBRARY_PATH=$LIBTHAI_BASEPATH/lib:/lib/w32api$APPEND

  if test "x$PKG_CONFIG_PATH" = x; then
	APPEND=
  else
	APPEND=":$PKG_CONFIG_PATH"
  fi
  export PKG_CONFIG_PATH=$LIBTHAI_BASEPATH/lib/pkgconfig$APPEND

  if test "x$MANPATH" = x; then
	APPEND=
  else
	APPEND=":$MANPATH"
  fi
  export MANPATH=$LIBTHAI_BASEPATH/share/man$APPEND
fi
