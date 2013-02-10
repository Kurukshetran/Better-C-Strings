#ifndef _BSTRINGS_H

#define _BSTRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum {
  false_t = 0,
	true_t = 1
} bool_t;

/*
 @BString
 */

typedef struct bstringObj bStrObj;

struct bstringObj {
	/*
	 @string
	 
	 pointer to string
	 */
	char *string;
	
	/*
	 @length
	 
	 length of the string
	 */
	size_t length;
	
	/*
	 @init
	 
	 inits
	 */
	void(*init)(bStrObj *this);
	
	/*
	 @initWithBString
	 
	 inits with a BString
	 */
	void(*initWithBString)(bStrObj *this, bStrObj *bStr);
	
	/*
	 @initWithString
	 
	 inits with a constant string
	 */
	void(*initWithString)(bStrObj *this, const char *string);
	
	/*
	 @initWithFormat
	 
	 inits with a constant string format
	 */
	void(*initWithFormat)(bStrObj *this, const char *format, ...);
	
	/*
	 @isEqualToBString
	 
	 checks if string is equal to a BString
	 */
	bool_t(*isEqualToBString)(bStrObj *this, bStrObj *bStr);
	
	/*
	 @isEqualToString
	 
	 checks if string is equal to another
	 */
	bool_t(*isEqualToString)(bStrObj *this, const char *string);
};

extern bStrObj *__BString_alloc(void);
extern void __BString_dealloc(bStrObj **this);

static void __BString_init(bStrObj *this);
static void __BString_initWithBString(bStrObj *this, bStrObj *bStr);
static void __BString_initWithString(bStrObj *this, const char *string);
static void __BString_initWithFormat(bStrObj *this, const char *format, ...);
static bool_t __BString_isEqualToBString(bStrObj *this, bStrObj *bStr);
static bool_t __BString_isEqualToString(bStrObj *this, const char *string);

static struct {
	bStrObj*(*alloc)(void);
	void(*dealloc)(bStrObj **this);
} BString = {
	.alloc = __BString_alloc,
	.dealloc = __BString_dealloc
};

typedef bStrObj String;

/*
 @BMutableString
 */

typedef struct bMutableStringObj bMStrObj;

struct bMutableStringObj {
	/*
	 @string
	 
	 pointer to string
	 */
	char *string;
	
	/*
	 @length
	 
	 length of the string
	 */
	size_t length;
	
	/*
	 @init
	 
	 inits
	 */
	void(*init)(bMStrObj *this);
	
	/*
	 @initWithBString
	 
	 inits with a BString
	 */
	void(*initWithBString)(bMStrObj *this, bStrObj *bStr);
	
	/*
	 @initWithString
	 
	 inits with a constant string
	 */
	void(*initWithString)(bMStrObj *this, const char *string);
	
	/*
	 @initWithFormat
	 
	 inits with a constant string format
	 */
	void(*initWithFormat)(bMStrObj *this, const char *format, ...);
	
	/*
	 @appendBString
	 
	 appends a BString
	 */
	void(*appendBString)(bMStrObj *this, bStrObj *bStr);
	
	/*
	 @appendString
	 
	 appends a constant string
	 */
	void(*appendString)(bMStrObj *this, const char *string);
	
	/*
	 @appendFormat
	 
	 appends a string format
	 */
	void(*appendFormat)(bMStrObj *this, const char *format, ...);
	
	/*
	 @appendChar
	 
	 appends a single char
	*/
	void(*appendChar)(bMStrObj *this, const char chr);
	
	/*
	 @isEqualToBString
	 
	 checks if string is equal to a BString
	 */
	bool_t(*isEqualToBString)(bMStrObj *this, bStrObj *bStr);
	
	/*
	 @isEqualToString
	 
	 checks if string is equal to another
	 */
	bool_t(*isEqualToString)(bMStrObj *this, const char *string);
};

extern bMStrObj *__BMutableString_alloc(void);
extern void __BMutableString_dealloc(bMStrObj **this);

static void __BMutableString_init(bMStrObj *this);
static void __BMutableString_initWithBString(bMStrObj *this, bStrObj *bStr);
static void __BMutableString_initWithString(bMStrObj *this, const char *string);
static void __BMutableString_initWithFormat(bMStrObj *this, const char *format, ...);
static void __BMutableString_appendBString(bMStrObj *this, bStrObj *bStr);
static void __BMutableString_appendString(bMStrObj *this, const char *string);
static void __BMutableString_appendFormat(bMStrObj *this, const char *format, ...);
static void __BMutableString_appendChar(bMStrObj* this, const char chr);
static bool_t __BMutableString_isEqualToBString(bMStrObj *this, bStrObj *bStr);
static bool_t __BMutableString_isEqualToString(bMStrObj *this, const char *string);

static struct {
	bMStrObj*(*alloc)(void);
	void(*dealloc)(bMStrObj **this);
} BMutableString = {
	.alloc = __BMutableString_alloc,
	.dealloc = __BMutableString_dealloc
};

typedef bMStrObj MutableString;

#endif
