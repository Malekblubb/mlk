//
// Copyright (c) 2013-2014 Christoph Malek
// See LICENSE for more information.
//

#ifndef MLK_SYSTEM_DETECT_H
#define MLK_SYSTEM_DETECT_H


#if defined(_WIN64) || defined(WIN64)
	#define MLK_WIN 1
#elif defined(WIN32) || defined(_WIN32) || defined(__CYGWIN32__) || defined(__MINGW32__)
	#define MLK_WIN 1
	#define MLK_WIN_32 1
#endif

#if defined(__LINUX__) || defined(__linux__)
	#define MLK_LINUX 1
#endif

#if defined(MACOSX) || defined(__DARWIN__) || defined(__APPLE__)
	#define MLK_OS_MAC 1
#endif



#if defined(WIN_32) || defined(__i386__) || defined(i386) || defined(__x86__)
	#define MLK_ARCH "32"
#endif

#if defined(__amd64) || defined(__amd64__) || defined(__x86_64) || defined(__x86_64__) || defined(_M_X64) || defined(__ia64__) || defined(_M_IA64)
	#define MLK_ARCH "64"
#endif


#endif // MLK_SYSTEM_DETECT_H
