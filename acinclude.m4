dnl Function to detect if libfsclfs dependencies are available
AC_DEFUN([AX_LIBFSCLFS_CHECK_LOCAL],
 [dnl Check for internationalization functions in libfsclfs/libfsclfs_i18n.c 
 AC_CHECK_FUNCS([bindtextdomain])
 ])

