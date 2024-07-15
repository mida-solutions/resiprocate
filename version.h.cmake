/*
 * WARNING: do not edit!
 * Generated by CMake from ./version.h.cmake
 * Expected to use it as `#include <resip/version.h>`.
 */

#ifndef VERSION_H
#define VERSION_H

/* The idea is borrowed from the OpenSSL library versioning,
 * except for the nibble status. It can be expanded in the future.
 * https://www.openssl.org/docs/man1.1.1/man3/OPENSSL_VERSION_NUMBER.html
 * https://www.openssl.org/docs/man3.2/man3/OPENSSL_VERSION_NUMBER.html
 * Numeric release version identifier:
 *      0xMNNPP00SL: major minor patch reserved status
 * For example,
 * resiprocate-1.9.2            0x1090200f
 * resiprocate-1.9.11           0x1090B00f
 * resiprocate-1.12.0_alpha1    0x10C00000
 * resiprocate-1.12.0_beta14    0x10C00000
 * resiprocate-1.12.0           0x10C0000f
 */

/*
 * SECTION 1: VERSION DATA.  These will change for each release.
 */

/*
 * Base version macros.
 *
 * These macros express version number MAJOR.MINOR.PATCH exactly.
 */
#define RESIPROCATE_VERSION_MAJOR @PROJECT_VERSION_MAJOR@
#define RESIPROCATE_VERSION_MINOR @PROJECT_VERSION_MINOR@
#define RESIPROCATE_VERSION_PATCH @PROJECT_VERSION_PATCH@

/*
 * Additional version information.
 */

/* Could be: #define RESIPROCATE_VERSION_PRE_RELEASE "beta1" */
#cmakedefine RESIPROCATE_VERSION_PRE_RELEASE "@RESIPROCATE_VERSION_PRE_RELEASE@"

/*
 * Macros to get the version in easily digested string form, both the short
 * "MAJOR.MINOR.PATCH" variant (where MAJOR, MINOR and PATCH are replaced
 * with the values from the corresponding RESIPROCATE_VERSION_ macros) and the
 * longer variant with RESIPROCATE_VERSION_PRE_RELEASE appended.
 */
#define RESIPROCATE_VERSION_STR "@PROJECT_VERSION@"
#ifdef RESIPROCATE_VERSION_PRE_RELEASE
#   define RESIPROCATE_VERSION_FULL_STR "@PROJECT_VERSION@-@RESIPROCATE_VERSION_PRE_RELEASE@"
#else
#   define RESIPROCATE_VERSION_FULL_STR "@PROJECT_VERSION@"
#endif

/*
 * SECTION 2: BACKWARD COMPATIBILITY
 */

/* Synthesize RESIPROCATE_VERSION_NUMBER with the layout 0xMNNPP00SL */
#ifdef RESIPROCATE_VERSION_PRE_RELEASE
#   define _RESIPROCATE_VERSION_PRE_RELEASE 0x0L
#else
#   define _RESIPROCATE_VERSION_PRE_RELEASE 0xfL
#endif
#define RESIPROCATE_VERSION_NUMBER          \
   ( (RESIPROCATE_VERSION_MAJOR<<28)        \
     |(RESIPROCATE_VERSION_MINOR<<20)       \
     |(RESIPROCATE_VERSION_PATCH<<12)       \
     |_RESIPROCATE_VERSION_PRE_RELEASE )

/*
 * SECTION 3: USEFUL MACROS
 */

/* For checking general API compatibility when preprocessing */
#define RESIPROCATE_VERSION_PREREQ(maj,min,patch)   \
    ( (RESIPROCATE_VERSION_MAJOR << 16) +           \
      (RESIPROCATE_VERSION_MINOR << 8) +            \
       RESIPROCATE_VERSION_PATCH >=                 \
      ((maj) << 16) + ((min) << 8) + patch )

#endif /* VERSION_H */
