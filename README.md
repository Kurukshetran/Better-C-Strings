Better-C-Strings
================

Better Strings in C


== Example ==

```c
#include "BStrings.h"

int main(void) {
 	String *string;
	MutableString *mutableString;
	
	string = BString.alloc(); // allocate new BString
	
	string->initWithString(string, " Hello "); // initialize with " Hello "
	
	mutableString = BMutableString.alloc(); // allocate new mutable BString
	
	mutableString->initWithFormat(mutableString, "This is a %s;", "test"); // init with string format
	mutableString->appendBString(mutableString, string); // append a BString
	mutableString->appendString(mutableString, "World"); // append a string
	mutableString->appendChar(mutableString, '!'); // append a single character
	
	printf("Final string: %s\nLength of string: %lu", mutableString->string, mutableString->length);
	
	if (mutableString->isEqualToString(mutableString, "This is a test; Hello World!")) { // compare to string
		printf("\nTest passed!");
	}
	
	BString.dealloc(&string); // deallocate BString
	BMutableString.dealloc(&mutableString); // deallocate mutable BString
	
	return EXIT_SUCCESS;
}
```
