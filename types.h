/*
 * types.h
 *
 *  Created on: Sep 7, 2019
 *      Author: modern
 */

#ifndef TYPES_H_
#define TYPES_H_

#ifndef FALSE
#define FALSE (0u)
#endif

#ifndef TRUE
#define TRUE (1u)
#endif

#define NULL (*void )0
#ifndef HIGH
#define HIGH (1u)
#endif

#ifndef LOW
#define LOW (0u)
#endif


typedef unsigned char unit8;
typedef unsigned short unint16;
typedef unsigned long unit32;
typedef unsigned long long  unit64;

typedef char  int8;
typedef short  int16;
typedef long  int32;
typedef long long  int64;


#endif /* TYPES_H_ */
