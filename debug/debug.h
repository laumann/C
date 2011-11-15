#ifndef _DEBUG_H
#define _DEBUG_H

/******************************************************************************
 *
 * File: debug.h
 *
 * Debugging library providing six debugging macros: LOG_{TRACE, DEBUG, INFO, 
 * WARN, ERROR, FATAL}. Very simple and somewhat powerful. Use as printf(...)
 * with a format string and variable arguments. Example (in file main.c):
 *
 *	22:	int i = 42;
 *	23: 	LOG_INFO("main method called, int i=%d", i);
 *	#=>	
 *		[main.c:23] INFO    main method called, int i=42
 *
 * Use gcc compiler flag -D_DEBUG to enable, compile without to remove all
 * references (and calls) to these logging functions.
 *
 *****************************************************************************/

#ifdef DEBUG

#include <stdio.h>
#include <stdarg.h>

#ifndef LOG_INDENT_LVL
# define LOG_INDENT_LVL 5
#endif

char *logg(char *, ...);

#define LOGG(DEBUG_LVL, msg, ...)\
	fprintf(stderr, "[%s:%d] %-*s %s\n",\
	__FILE__, __LINE__, LOG_INDENT_LVL, #DEBUG_LVL, logg(msg, ##__VA_ARGS__));

#define LOG(msg, ...)\
	fprintf(stderr, "[%s:%d] %s\n",\
	__FILE__, __LINE__, logg(msg, ##__VA_ARGS__));

#define LOG_TRACE(msg, ...)	LOGG(TRACE, msg, ##__VA_ARGS__);
#define LOG_DEBUG(msg, ...)	LOGG(DEBUG, msg, ##__VA_ARGS__);
#define LOG_INFO(msg, ...)	LOGG(INFO, msg, ##__VA_ARGS__);
#define LOG_WARN(msg, ...)	LOGG(WARN, msg, ##__VA_ARGS__);
#define LOG_ERROR(msg, ...)	LOGG(ERROR, msg, ##__VA_ARGS__);
#define LOG_FATAL(msg, ...)	LOGG(FATAL, msg, ##__VA_ARGS__);

#else

#define LOG(msg, ...)
#define LOG_TRACE(msg, ...)
#define LOG_DEBUG(msg, ...)
#define LOG_INFO(msg, ...)
#define LOG_WARN(msg, ...)
#define LOG_ERROR(msg, ...)
#define LOG_FATAL(msg, ...)

#endif

#endif/*_DEBUG_H*/
