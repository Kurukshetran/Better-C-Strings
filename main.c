#include "BStrings.h"

int main(void) {
  String *string;
	MutableString *mutableString;
	
	string = BString.alloc();
	
	string->initWithString(string, " Hello ");
	
	mutableString = BMutableString.alloc();
	
	mutableString->initWithFormat(mutableString, "This is a %s;", "test");
	mutableString->appendBString(mutableString, string);
	mutableString->appendString(mutableString, "World");
	mutableString->appendChar(mutableString, '!');
	
	printf("Final string: %s\nLength of string: %lu", mutableString->string, mutableString->length);
	
	if (mutableString->isEqualToString(mutableString, "This is a test; Hello World!")) {
		printf("\nTest passed!");
	}
	
	BString.dealloc(&string);
	BMutableString.dealloc(&mutableString);
	
	return EXIT_SUCCESS;
}
