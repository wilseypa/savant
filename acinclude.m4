dnl
dnl Check for libclutils
dnl
dnl Usage: CL_LIB_CLUTILS
dnl
AC_DEFUN([CL_LIB_CLUTILS],
[
AC_CACHE_CHECK([for location of libclutils], [cl_cv_lib_clutils],
  [AC_ARG_WITH(clutils,
    AC_HELP_STRING([--with-clutils],
      [location of libclutils (default is /usr)]),
      [
        case "${withval}" in
          yes)  cl_cv_lib_clutils=/usr ;;
          no)   cl_cv_lib_clutils=no ;;
          *)    cl_cv_lib_clutils=$withval ;;
        esac
      ],
      [cl_cv_lib_clutils=/usr]
  )]
)
if test $cl_cv_lib_clutils = no ; then
AC_MSG_ERROR(The clutils package is required.)
fi
if test $cl_cv_lib_clutils != /usr ; then
LDFLAGS="$LDFLAGS -L$cl_cv_lib_clutils/lib -lclutils -lltdl"
CPPFLAGS="$CPPFLAGS -I$cl_cv_lib_clutils/include/clutils-0.0"
fi
AC_CHECK_HEADER( [Debug.h], ,
  AC_MSG_ERROR( [Couldn't find clutils/Debug.h which is required and 
    part of the clutils distribution.  You probably need to install it
    and/or specify the location of it with the --with-clutils option.] ) )
AC_CHECK_LIB([clutils], [fake], ,
  AC_MSG_ERROR([Could not find a workable libclutils.so or libclutils.a.
    You probably need to install clutils and/or specify the location of
    it with the --with-clutils option.]), [-lltdl] )
AC_MSG_CHECKING([whether libclutils can be linked])
#AC_TRY_RUN([extern "C" int fake(); int main(){return fake();}],
#  AC_MSG_RESULT([yes]),
#  AC_MSG_RESULT([no])
#  AC_MSG_ERROR([libclutils cannot be linked. This typically happens
#    if you have installed clutils in a non-standard directory which is not
#    being cached by the ld.so system. You can fix this by prepending configure
#    with LD_LIBRARY_PATH=$cl_cv_lib_clutils/lib or by adding this
#    path in ld.so.conf (typically in /etc) and running ldconfig (man ld.so for
#    more info).]))
]) dnl end CL_LIB_CLUTILS

AC_DEFUN([CL_PROG_PCCTS],
[
AC_SUBST(ANTLR)
AC_SUBST(DLG)
AC_SUBST(PCCTSROOT)


AC_PATH_PROG(ANTLR, antlr, no)
if test $ANTLR = no; then
AC_MSG_ERROR( [Configure could not locate the program "antlr" in your
path.  This program is needed to build the warped system.  It should
be installed as part of the PCCTS system which is available for free
via anonymous ftp from ftp.parr-research.com in the directory
/pub/pccts.  If you have installed PCCTS please verify that "antlr"
is in your path which is currently:
$PATH])
fi

AC_PATH_PROG(DLG, dlg, no)
if test $DLG = no; then
AC_MSG_ERROR( [Configure could not locate the program "dlg" in your
path.  This program is needed to build the warped system.  It should
be installed as part of the PCCTS system which is available for free
via anonymous ftp from ftp.parr-research.com in the directory
/pub/pccts.  If you have installed PCCTS please verify that "dlg"
is in your path which is currently:
$PATH])
fi

AC_CACHE_CHECK([for PCCTS includes], [cl_cv_path_pcctsheaders],
  [AC_ARG_WITH(pccts-headers,
    AC_HELP_STRING([--with-pccts-headers],
      [specify location of PCCTS headers (default is /usr/include/pccts)]),
    [
      case "${withval}" in
        yes)  cl_cv_path_pcctsheaders=/usr/include/pccts ;;
        no)   cl_cv_path_pcctsheaders=no ;;
        *)    cl_cv_path_pcctsheaders=$withval ;;
      esac
    ],
    [cl_cv_path_pcctsheaders=/usr/include/pccts]
  )]
)

if test $cl_cv_path_pcctsheaders = no; then
AC_MSG_ERROR(PCCTS includes required.  Please specify the location with
the --with-pccts-headers option.)
fi
AC_MSG_CHECKING(for PCCTS headers)
if test -f $cl_cv_path_pcctsheaders/AParser.cpp ; then
AC_MSG_RESULT(yes)
PCCTSROOT=$cl_cv_path_pcctsheaders
else
AC_MSG_RESULT(no)
AC_MSG_ERROR(Could not find PCCTS headers in $cl_cv_path_pcctsheaders.
Please specify the correct location with the --with-pccts-headers option.)
fi

]) dnl end CL_PROG_PCCTS
