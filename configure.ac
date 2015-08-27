

AC_INIT([texpack], [1.0],[christopher.kruczek@gmail.com])

AM_INIT_AUTOMAKE
# Checks for programs.
AC_PROG_CC([clang gcc])

# Checks for libraries.
# FIXME: Replace `main' with a function in `-lcurl':
PKG_CHECK_MODULES([libcurl],[libcurl])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
