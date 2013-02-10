#include "BStrings.h"

/*
 @BString
 */

/*
 @init
 
 inits
 */
static void __BString_init(bStrObj *this) {
	this->string = NULL;
	this->length = 0;
}

/*
 @initWithBString
 
 inits with a BString
 */
static void __BString_initWithBString(bStrObj *this, bStrObj *bStr) {
	if (this->string != NULL || bStr->length <= 0 || bStr->string == NULL) return;
	
	this->length = bStr->length;
	
	this->string = (char *)calloc(bStr->length + 1, sizeof(char));
	
	if (this->string == NULL) {
		this->length = 0;
		
		return;
	}
	
	strncpy(this->string, bStr->string, this->length + 1);
	
	this->string[this->length] = '\0';
}

/*
 @initWithString
 
 inits with a constant string
 */
static void __BString_initWithString(bStrObj *this, const char *string) {
	if (this->string != NULL || string == NULL) return;
	
	this->length = strlen(string);
	
	if (this->length <= 0) return;
	
	this->string = (char *)calloc(this->length + 1, sizeof(char));
	
	if (this->string == NULL) {
		this->length = 0;
		
		return;
	}
	
	strncpy(this->string, string, this->length + 1);
	
	this->string[this->length] = '\0';
}

/*
 @initFormat
 
 internal initWithFormat function
*/
static void __initFormat(bStrObj *this, const char *format, va_list args) {
	char *tmp = NULL;
	
	if (this->string != NULL || format == NULL) return;
	
	vasprintf(&tmp, format, args);
	
	this->initWithString(this, tmp);
	
	free(tmp);
}

/*
 @initWithFormat
 
 inits with a constant string format
 */
static void __BString_initWithFormat(bStrObj *this, const char *format, ...) {
	va_list args;

	va_start(args, format);
	
	__initFormat(this, format, args);
	
	va_end(args);
}

/*
 @isEqualToBString
 
 checks if string is equal to a BString
 */
static bool_t __BString_isEqualToBString(bStrObj *this, bStrObj *bStr) {
	if (this->string == NULL || bStr->string == NULL) return false_t;
	
	if (strcmp(this->string, bStr->string) == 0) return true_t;
	
	return false_t;
}

/*
 @isEqualToString
 
 checks if string is equal to another
 */
static bool_t __BString_isEqualToString(bStrObj *this, const char *string) {
	if (this->string == NULL || string == NULL) return false_t;
	
	if (strcmp(this->string, string) == 0) return true_t;
	
	return false_t;
}

/*
 @alloc
 
 allocates new BString
*/
extern bStrObj *__BString_alloc(void) {
	bStrObj *bStr = (bStrObj *)calloc(1, sizeof(bStrObj));
	
	if (bStr == NULL) return bStr;
	
	bStr->string = NULL;
	bStr->length = 0;
	
	bStr->init = __BString_init;
	bStr->initWithBString = __BString_initWithBString;
	bStr->initWithString = __BString_initWithString;
	bStr->initWithFormat = __BString_initWithFormat;
	bStr->isEqualToBString = __BString_isEqualToBString;
	bStr->isEqualToString = __BString_isEqualToString;
	
	return bStr;
}

/*
 @dealloc
 
 deallocates BString
*/
extern void __BString_dealloc(bStrObj **this) {
	free((*this)->string);
	(*this)->string = NULL;
	(*this)->length = 0;
	
	(*this)->init = NULL;
	(*this)->initWithBString = NULL;
	(*this)->initWithString = NULL;
	(*this)->initWithFormat = NULL;
	(*this)->isEqualToBString = NULL;
	(*this)->isEqualToString = NULL;
	
	free((*this));
	
	(*this) = NULL;
}

/*
 @BMutableString
 */

/*
 @init
 
 inits
 */
static void __BMutableString_init(bMStrObj *this) {
	this->string = NULL;
	this->length = 0;
}

/*
 @initWithBString
 
 inits with a BString
 */
static void __BMutableString_initWithBString(bMStrObj *this, bStrObj *bStr) {
	return __BString_initWithBString((bStrObj *)this, bStr);
}

/*
 @initWithString
 
 inits with a constant string
 */
static void __BMutableString_initWithString(bMStrObj *this, const char *string) {
	return __BString_initWithString((bStrObj *)this, string);
}

/*
 @initWithFormat
 
 inits with a constant string format
 */
static void __BMutableString_initWithFormat(bMStrObj *this, const char *format, ...) {
	va_list args;
	
	va_start(args, format);
	
	__initFormat((bStrObj *)this, format, args);
	
	va_end(args);
}

/*
 @appendBString
 
 appends a BString
 */
static void __BMutableString_appendBString(bMStrObj *this, bStrObj *bStr) {
	if (this->string == NULL || bStr->length == 0 || bStr->string == NULL) return;
	
	this->length += bStr->length;
	
	this->string = (char *)realloc(this->string, this->length + 1);
	
	if (this->string == NULL) {
		this->length = 0;
		
		return;
	}
	
	snprintf(this->string, this->length + 1, "%s%s", this->string, bStr->string);
}

/*
 @appendString
 
 appends a constant string
 */
static void __BMutableString_appendString(bMStrObj *this, const char *string) {
	if (this->string == NULL || string == NULL) return;
	
	this->length += strlen(string);
	
	this->string = (char *)realloc(this->string, this->length + 1);
	
	if (this->string == NULL) {
		this->length = 0;
		
		return;
	}
	
	snprintf(this->string, this->length + 1, "%s%s", this->string, string);
}

/*
 @appendFormat
 
 appends a string format
 */
static void __BMutableString_appendFormat(bMStrObj *this, const char *format, ...) {
	va_list args;
	char *tmp;
	
	if (this->string == NULL || format == NULL) return;
	
	va_start(args, format);
	
	vasprintf(&tmp, format, args);
	
	va_end(args);
	
	this->appendString(this, tmp);
	
	free(tmp);
}

/*
 @appendChar
 
 appends a single char
 */
static void __BMutableString_appendChar(bMStrObj* this, const char chr) {
	return this->appendFormat(this, "%c", chr);
}

/*
 @isEqualToBString
 
 checks if string is equal to a BString
 */
static bool_t __BMutableString_isEqualToBString(bMStrObj *this, bStrObj *bStr) {
	return __BString_isEqualToBString((bStrObj *)this, bStr);
}

/*
 @isEqualToString
 
 checks if string is equal to another
 */
static bool_t __BMutableString_isEqualToString(bMStrObj *this, const char *string) {
	return __BString_isEqualToString((bStrObj *)this, string);
}


/*
 @alloc
 
 allocates new BMutableString
 */
extern bMStrObj *__BMutableString_alloc(void) {
	bMStrObj *bMStr = (bMStrObj *)calloc(1, sizeof(bMStrObj));
	
	if (bMStr == NULL) return bMStr;
	
	bMStr->string = NULL;
	bMStr->length = 0;
	
	bMStr->init = __BMutableString_init;
	bMStr->initWithBString = __BMutableString_initWithBString;
	bMStr->initWithString = __BMutableString_initWithString;
	bMStr->initWithFormat = __BMutableString_initWithFormat;
	bMStr->appendBString = __BMutableString_appendBString;
	bMStr->appendString = __BMutableString_appendString;
	bMStr->appendFormat = __BMutableString_appendFormat;
	bMStr->appendChar = __BMutableString_appendChar;
	bMStr->isEqualToBString = __BMutableString_isEqualToBString;
	bMStr->isEqualToString = __BMutableString_isEqualToString;
	
	return bMStr;
}

/*
 @dealloc
 
 deallocates BMutableString
 */
extern void __BMutableString_dealloc(bMStrObj **this) {
	free((*this)->string);
	(*this)->string = NULL;
	(*this)->length = 0;
	
	(*this)->init = NULL;
	(*this)->initWithBString = NULL;
	(*this)->initWithString = NULL;
	(*this)->initWithFormat = NULL;
	(*this)->appendBString = NULL;
	(*this)->appendString = NULL;
	(*this)->appendFormat = NULL;
	(*this)->appendChar = NULL;
	(*this)->isEqualToBString = NULL;
	(*this)->isEqualToString = NULL;
	
	free((*this));
	
	(*this) = NULL;
}
