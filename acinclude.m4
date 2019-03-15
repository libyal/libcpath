dnl Checks for required headers and functions
dnl
dnl Version: 20190308

dnl Function to detect if mkdir is available
dnl Also checks how to use mkdir
AC_DEFUN([AX_LIBCPATH_CHECK_FUNC_MKDIR],
  [AC_CHECK_FUNCS([mkdir])

  AS_IF(
    [test "x$ac_cv_func_mkdir" = xyes],
    [AC_MSG_CHECKING(
      [how to use mkdir])

    SAVE_CFLAGS="$CFLAGS"
    CFLAGS="$CFLAGS -Wall -Werror"
    AC_LANG_PUSH(C)

    AC_LINK_IFELSE(
      [AC_LANG_PROGRAM(
        [[#include <sys/stat.h>
#include <sys/types.h>]],
        [[mkdir( "", 0 )]] )],
        [AC_MSG_RESULT(
          [with additional mode argument])
        ac_cv_cv_mkdir_mode=yes],
        [ac_cv_cv_mkdir_mode=no])

    AS_IF(
      [test "x$ac_cv_cv_mkdir_mode" = xno],
      [AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
          [[#include <io.h>]],
          [[mkdir( "" )]] )],
        [AC_MSG_RESULT(
          [with single argument])
        ac_cv_cv_mkdir=yes],
        [ac_cv_cv_mkdir=no])
      ])

    AC_LANG_POP(C)
    CFLAGS="$SAVE_CFLAGS"

    AS_IF(
      [test "x$ac_cv_cv_mkdir_mode" = xno && test "x$ac_cv_cv_mkdir" = xno],
      [AC_MSG_WARN(
        [unknown])
      ac_cv_func_mkdir=no])

    AS_IF(
      [test "x$ac_cv_func_mkdir" = xyes],
      [AC_DEFINE(
        [HAVE_MKDIR],
        [1],
        [Define to 1 if you have the mkdir function.])
      ])

    AS_IF(
      [test "x$ac_cv_cv_mkdir_mode" = xyes],
      [AC_DEFINE(
        [HAVE_MKDIR_MODE],
        [1],
        [Define to 1 if you have the mkdir function with a second mode argument.])
      ])
    ])

  AS_IF(
    [test "x$ac_cv_func_mkdir" = xno],
    [AC_MSG_FAILURE(
      [Missing function: mkdir],
      [1])
    ])
  ])

dnl Function to detect if libcpath dependencies are available
AC_DEFUN([AX_LIBCPATH_CHECK_LOCAL],
  [dnl Headers included in libcpath/libcpath_path.h
  AC_CHECK_HEADERS([errno.h sys/stat.h sys/syslimits.h])

  dnl Path functions used in libcpath/libcpath_path.h
  AC_CHECK_FUNCS([chdir getcwd])

  AS_IF(
    [test "x$ac_cv_func_chdir" != xyes],
    [AC_MSG_FAILURE(
      [Missing functions: chdir],
      [1])
    ])

  AS_IF(
    [test "x$ac_cv_func_getcwd" != xyes],
    [AC_MSG_FAILURE(
      [Missing functions: getcwd],
      [1])
    ])

  AX_LIBCPATH_CHECK_FUNC_MKDIR
  ])

