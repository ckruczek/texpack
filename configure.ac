AC_INIT([texpack], [1.0],[christopher.kruczek@gmail.com])

AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Checks for programs.
AC_PROG_CC([clang gcc])

# Checks for libraries.
PKG_CHECK_MODULES([libcurl],[libcurl])

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_PROG_RANLIB
AM_PROG_AR
# Checks for library functions.
AC_CONFIG_FILES([Makefile src/Makefile lib/Makefile])
AC_OUTPUT
