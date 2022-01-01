//*****************************************************************************
//
// debug.h - Macros for assisting debug of the driver library.
//
// Copyright (c) 2006-2007 Luminary Micro, Inc.  All rights reserved.
// 
// Software License Agreement
// 
// Luminary Micro, Inc. (LMI) is supplying this software for use solely and
// exclusively on LMI's microcontroller products.
// 
// The software is owned by LMI and/or its suppliers, and is protected under
// applicable copyright laws.  All rights are reserved.  Any use in violation
// of the foregoing restrictions may subject the user to criminal sanctions
// under applicable laws, as well as to civil liability for the breach of the
// terms and conditions of this license.
// 
// THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
// OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
// LMI SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
// CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 1716 of the Stellaris Peripheral Driver Library.
//
//*****************************************************************************

#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <stdio.h>
#include <assert.h>
#define DEBUG_LOW		1
#define DEBUG_MEDIUM	2
#define DEBUG_HIGH		3
#define DEBUG_NONE		4

#ifndef DEBUG_LVL
#define DEBUG_LVL		2
#endif

#define CH_ISR		0
#define CH_PROC		1


#if defined(USE_DEBUG_PRINTF)
#define DEBUG(_level,...) \
	do { \
		if(_level>=DEBUG_LVL) { \
			printf (__VA_ARGS__); \
		}; \
	} while(0);

#else
#define DEBUG(_level,...)
#endif

#if defined(USE_LDEBUG_PRINTF)
#define LDEBUG_PRINTF(format,...) 	printf(format,## __VA_ARGS__ )
#define LDEBUG_FPUTS(_str) 			fputs((_str),stdout)
#else
#define LDEBUG_PRINTF(format,...)
#define LDEBUG_FPUTS(_str)
#endif

//*****************************************************************************
//
// Prototype for the function that is called when an invalid argument is passed
// to an API.  This is only used when doing a DEBUG build.
//
//*****************************************************************************
extern void __error__(char *pcFilename, unsigned long ulLine);

//*****************************************************************************
//
// The ASSERT macro, which does the actual assertion checking.  Typically, this
// will be for procedure arguments.
//
//*****************************************************************************
#ifdef DEBUG
#define ASSERT(expr) {                                      \
                         if(!(expr))                        \
                         {                                  \
                             __error__(__FILE__, __LINE__); \
                         }                                  \
                     }
#else
#define ASSERT(expr)
#endif

#endif // __DEBUG_H__