AC_INIT([pknotsRG], [1.3],
        [Peter Steffen],
        [pknotsRG])
AC_DEFINE(RELEASE_DATE, ["Sep. 19. 2006"], [Release date of current version])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE

AC_PROG_INSTALL
AC_CONFIG_FILES([Makefile src/Makefile man/Makefile])

# editline check adapted from Ville Laurikari <vl@iki.fi>
# http://autoconf-archive.cryp.to/vl_lib_readline.html
AC_CACHE_CHECK([for editline library],
                vl_cv_lib_editline, [
  ORIG_LIBS="$LIBS"
  for editline_lib in edit editline readline; do
    for termcap_lib in "" termcap curses ncurses; do
      if test -z "$termcap_lib"; then
        TRY_LIB="-l$editline_lib"
      else
        TRY_LIB="-l$editline_lib -l$termcap_lib"
      fi
      LIBS="$ORIG_LIBS $TRY_LIB"
      AC_TRY_LINK_FUNC(readline, vl_cv_lib_editline="$TRY_LIB")
      if test -n "$vl_cv_lib_editline"; then
        break
      fi
    done
    if test -n "$vl_cv_lib_editline"; then
      break
    fi
  done
  if test -z "$vl_cv_lib_editline"; then
    vl_cv_lib_editline="no"
    LIBS="$ORIG_LIBS"
  fi
])

if test "$vl_cv_lib_editline" != "no"; then
  AC_DEFINE(HAVE_LIBEDITLINE, 1,
            [Define if you have the editline library])
fi

AC_OUTPUT

if test "$vl_cv_lib_editline" == "no"; then
AC_MSG_NOTICE([
***  Editline-support disabled.                                ***
***  To get a more convenient interactive sequence input, you  ***
***  could install the editline-library. Download from:        ***
***     http://www.thrysoee.dk/editline/                       ***
])
fi

AC_MSG_NOTICE([
Configuration completed. Type "make" to compile and "make install" to install.
])
