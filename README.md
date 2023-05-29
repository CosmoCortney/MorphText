# MorphText
A class to process different kinds of texts/strings appearing in video games and elsewhere.

## Constructors
### ``MorphText(std::string& utf8)``
Takes a UTF-8 string as reference to create a new instance.

### ``MorphText(std::wstring& utf16, bool isBigEndian = false)``
Takes a UTF-16 string as reference to create a new instance.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``MorphText(std::u32string& utf32, bool isBigEndian = false)``
Takes a UTF-32 string as reference to create a new instance.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``MorphText(char* charStr, int format = 0)``
Takes a char* string to create a new instance.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``MorphText(wchar_t* charStr, bool isBigEndian = false)``
Takes a UTF-16 wchar_t* string as reference to create a new instance.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``MorphText(char32_t* charStr, bool isBigEndian = false)``
Takes a UTF-32 char32_t* string as reference to create a new instance.
*isBigEndian* (optional): Set true if source strings are big endian.

## Operators
### =
Sets the right-hand value to set the left-hand instance

Supported datatypes:
* MorphText
* std::string (UTF-8)
* std::wstring (UTF-16, Little Endian expected)
* std::u32string (UTF-32, Little Endian expected)
* wchar_t* (UTF-16), Little Endian expected)

## Static Function Calls
### ``std::string ASCII_To_Utf8(char* input)``
Takes an input ASCII char* string and returns it as a UTF-8 string std::string.

### ``char* Utf8_To_ASCII(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a char* ASCII-string.

### ``std::string Utf16LE_To_Utf8(std::wstring input)``
Takes an input little endian UTF-16 std::wstring as reference and returns it as a UTF-8 std::string.

### ``std::wstring Utf8_To_Utf16LE(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a little endian UTF-16 std::wstring.

### ``std::string Utf16BE_To_Utf8(std::wstring input)``
Takes an input big endian UTF-16 std::wstring as reference and returns it as a UTF-8 std::string.

### ``std::wstring Utf8_To_Utf16BE(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a big endian UTF-16 std::wstring.

### ``std::string Utf32LE_To_Utf8(std::u32string input)``
Takes an input little endian UTF-32 std::u32string as reference and returns it as a UTF-8 std::string.

### ``std::u32string Utf8_To_Utf32LE(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a little endian UTF-32 std::u32string.

### ``std::string Utf32BE_To_Utf8(std::u32string input)``
Takes an input big endian UTF-32 std::u32string as reference and returns it as a UTF-8 std::string.

### ``std::u32string Utf8_To_Utf32BE(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a big endian UTF-32 std::u32string.

### ``std::string ShiftJis_To_Utf8(char* input)``
Takes an input Shift-Jis char* string and returns it as a UTF-8 std::string.

### ``char* Utf8_To_ShiftJis(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a char* Shift-Jis string.

### ``std::string ISO8859X_To_Utf8(char* input, int format = LATIN1)``
Takes an input ISO-8849-X char* string and returns it as a UTF-8 std::string.
*format* is the corresponding ISO standard.

* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Invalid format value will perform no conversion (Latin1).

### ``char* Utf8_To_ISO8859X(std::string input, int format = LATIN1)``
Takes an input UTF-8 std::string as reference and returns it as a char* ISO-8849-X string.
*format* is the corresponding ISO standard.

* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Invalid format value will perform no conversion (Latin1).

### ``bool Compare(std::string lhs, std::string rhs, bool caseSensitive = true, bool subString = false)``
Compares the given input std::string for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false

### ``bool Compare(std::wstring lhs, std::wstring rhs, bool caseSensitive = true, bool subString = false, isBigEndian = false)``
Compares the given input std::wstring for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*isBigEndian* (optional): Set true if source strings are big endian.

### ``bool Compare(std::u32string lhs, std::u32string rhs, bool caseSensitive = true, bool subString = false, bool isBigEndian = false)``
Compares the given input std::u32string for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*isBigEndian* (optional): Set true if source strings are big endian.

### ``bool Compare(char* lhs, char* rhs, bool caseSensitive = true, bool subString = false, int format = 0)``
Compares the given input std::wstring for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``std::string ToLower(std::string input)``
Returns the input string with all characters in lowercase.

### ``std::string ToUpper(std::string input)``
Returns the input string with all characters in uppercase.

### ``std::string ToSarcasm(std::string input)``
Returns the input string with sarcastic energy.

### ``std::wstring ToLower(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with all characters in lowercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::wstring ToUpper(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with all characters in uppercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::wstring ToSarcasm(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with sarcastic energy.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToLower(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with all characters in lowercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToUpper(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with all characters in uppercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToSarcasm(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with sarcastic energy.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``char* ToLower(char* input, int type)``
Returns the input char* with all characters in lowercase.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``char* ToUpper(char* input, int type)``
Returns the input char* with all characters in uppercase.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``char* ToSarcasm(char* input, int type)``
Returns the input char* with sarcastic energy.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-1 (Latin1): MorphText::LATIN1
* ISO-8849-2 (Latin2): MorphText::LATIN2
* ISO-8849-3 (Latin3): MorphText::LATIN3
* ISO-8849-4 (Latin4): MorphText::LATIN4
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

## Member Functions
### ``std::string GetUTF8()``
Returns the instance's UTF-8 std::string.

### ``std::wstring GetUTF16(bool isBigEndian = false)``
Returns the instance's UTF-16 std::wstring.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string GetUTF32(bool isBigEndian = false)``
Returns the instance's UTF-32 std::u32string.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::string GetASCII()``
Returns the instance's ASCII char* string.

### ``std::string GetShiftJis()``
Returns the instance's Shift Jis char* string.

### ``void SetBigEndian(const bool shall_I)``
Sets the Big Endian flag to alter certain conversions.

### ``template<typename T> T ToLower(int format = 0)``
Returns the instance's string of given value type in lowercase.

### ``template<typename T> T ToUpper(int format = 0)``
Returns the instance's string of given value type in uppercase.

### ``template<typename T> T ToSarcasm(int format = 0)``
Returns the instance's string of given value with sarcastic energy.
