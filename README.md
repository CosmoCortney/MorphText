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
* ISO-8849-X: see <i>ISO-8859 Enum Values</i> below
* Shift-Jis: MorphText::SCHIFTJIS
* Jis x 0201 Full Width: MorphText::JIS_X_0201_FULLWIDTH
* Jis x 0201 Half Width: MorphText::JIS_X_0201_HALFWIDTH
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
* wchar_t* (UTF-16, Little Endian expected)

## Static Function Calls
### ``std::string ASCII_To_Utf8(char* input)``
Takes an input ASCII char* string and returns it as a UTF-8 std::string.

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

### ``char* Utf8_To_JIS_X_0201_FullWidth(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a char* JIS X 0201 Full Width string.

### ``std::string JIS_X_0201_FullWidth_To_Utf8(char* input)``
Takes an input JIS X 0201 Full Width char* string and returns it as a UTF-8 std::string.

### ``char* Utf8_To_JIS_X_0201_HalfWidth(std::string input)``
Takes an input UTF-8 std::string as reference and returns it as a char* JIS X 0201 Half Width string.

### ``std::string JIS_X_0201_HalfWidth_To_Utf8(char* input)``
Takes an input JIS X 0201 Half Width char* string and returns it as a UTF-8 std::string.

### ``std::string ISO8859X_To_Utf8(char* input, int format = LATIN1)``
Takes an input ISO-8849-X char* string and returns it as a UTF-8 std::string.
*format* is the corresponding ISO standard. see <i>ISO-8859 Enum Values</i> below
* Invalid format value will perform no conversion (ISO_8859_1/Latin-1).

### ``char* Utf8_To_ISO8859X(std::string input, int format = LATIN1)``
Takes an input UTF-8 std::string as reference and returns it as a char* ISO-8849-X string.
*format* is the corresponding ISO standard.  see <i>ISO-8859 Enum Values</i> below
* Invalid format value will perform no conversion (ISO_8859_1/Latin-1).

### ``bool Compare(std::string lhs, std::string rhs, bool caseSensitive = true)``
Compares the given input std::string for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false

### ``bool Compare(std::wstring lhs, std::wstring rhs, bool caseSensitive = true, isBigEndian = false)``
Compares the given input std::wstring for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*isBigEndian* (optional): Set true if source strings are big endian.

### ``bool Compare(std::u32string lhs, std::u32string rhs, bool caseSensitive = true, bool isBigEndian = false)``
Compares the given input std::u32string for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*isBigEndian* (optional): Set true if source strings are big endian.

### ``bool Compare(char* lhs, char* rhs, bool caseSensitive = true, int format = 0)``
Compares the given input std::wstring for equality. 
*caseSensitive* (optional): Set *caseSensitive* to false to ignore case sensitivity. Default is true.
*subString* (optional): Set true to check if the left-hand string contains the entire right-hand string. Default: false
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-X: see <i>ISO-8859 Enum Values</i> below
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``std::string ToLower(std::string input)``
Returns the input string with all characters lowercase.

### ``std::string ToUpper(std::string input)``
Returns the input string with all characters uppercase.

### ``std::string ToSarcasm(std::string input)``
Returns the input string with sarcastic energy.

### ``std::wstring ToLower(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with all characters lowercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::wstring ToUpper(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with all characters uppercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::wstring ToSarcasm(std::wstring input, bool isBigEndian = false)``
Returns the input std::wstring with sarcastic energy.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToLower(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with all characters lowercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToUpper(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with all characters uppercase.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``std::u32string ToSarcasm(std::u32string input, bool isBigEndian = false)``
Returns the input std::u32string with sarcastic energy.
*isBigEndian* (optional): Set true if source strings are big endian.

### ``char* ToLower(char* input, int type)``
Returns the input char* with all characters lowercase.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-X: see <i>ISO-8859 Enum Values</i> below
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``char* ToUpper(char* input, int type)``
Returns the input char* with all characters uppercase.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-X: see <i>ISO-8859 Enum Values</i> below
* Shift-Jis: MorphText::SCHIFTJIS
* Invalid format value will be considered as ASCII.

### ``char* ToSarcasm(char* input, int type)``
Returns the input char* with sarcastic energy.
*format* (optional): Set the considered string format.
* ASCII: MorphText::ASCII
* ISO-8849-X: see <i>ISO-8859 Enum Values</i> below
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
Returns the instance's Shift-Jis char* string.

### ``std::string GetJisX0201FullWidth()``
Returns the instance's Jis x 0201 Full Width char* string.

### ``std::string GetJisX0201HalfWidth()``
Returns the instance's Jis x 0201 Half Width char* string.

### ``std::string GetISO8859X(int format)``
Returns the instance's ISO-8859 char* string.
*format*: Set the considered string format.
see <i>ISO-8859 Enum Values</i> below

### ``SetASCII(char* input)``
Sets the instance's ASCII value.

### ``SetShiftJis(char* input)``
Sets the instance's ShiftJis value.

### ``SetJisX0201FullWidth(char* input)``
Sets the instance's Jis x 0201 Full Width value.

### ``SetJisX0201HalfWidth(char* input)``
Sets the instance's Jis x 0201 Half Width value.

### ``SetUTF8(std::string& str)``
Sets the instance's UTF-8 value.

### ``SetUTF16(std::wstring& input, bool isBigEndian)``
Sets the instance's UTF-16 value. 
*isBigEndian*: Sets endianness (true = big endian, false = little endian (default)

### ``SetUTF16(wchar_t* input, bool isBigEndian)``
Sets the instance's UTF-16 value. 
*isBigEndian*: Sets endianness (true = big endian, false = little endian (default)

### ``SetUTF32(std::u32string& input, bool isBigEndian)``
Sets the instance's UTF-32 value. 
*isBigEndian*: Sets endianness (true = big endian, false = little endian (default)

### ``SetUTF32(char32_t* input, bool isBigEndian)``
Sets the instance's UTF-32 value. 
*isBigEndian*: Sets endianness (true = big endian, false = little endian (default)

### ``template<typename T> T ToLower(int format = 0)``
Returns the instance's string of given value type lowercase.

### ``template<typename T> T ToUpper(int format = 0)``
Returns the instance's string of given value type uppercase.

### ``template<typename T> T ToSarcasm(int format = 0)``
Returns the instance's string of given value with sarcastic energy.

## ISO-8859 Enum Values
* ISO-8849-1 (Latin-1): MorphText::ISO_8859_1 or MorphText::LATIN1
* ISO-8849-2 (Latin-2): MorphText::ISO_8859_2 or MorphText::LATIN2
* ISO-8849-3 (Latin-3): MorphText::ISO_8859_3 or MorphText::LATIN3
* ISO-8849-4 (Latin-4): MorphText::ISO_8859_4 or MorphText::LATIN4
* ISO-8849-5 (Cyrillic): MorphText::ISO_8859_5 or MorphText::CYRILLIC
* ISO-8849-6 (Arabic): MorphText::ISO_8859_6 or MorphText::ARABIC
* ISO-8849-7 (Greek): MorphText::ISO_8859_7 or MorphText::GREEK
* ISO-8849-8 (Hebrew): MorphText::ISO_8859_8 or MorphText::HEBREW
* ISO-8849-9 (Turkish, Latin-5): MorphText::ISO_8859_9 or MorphText::TURKISH or MorphText::LATIN5
* ISO-8849-10 (Nordic, Latin-6): MorphText::ISO_8859_10 or MorphText::NORDIC or MorphText::LATIN6
* ISO-8849-11 (Thai): MorphText::ISO_8859_11 or MorphText::Thai
* ISO-8849-13 (Baltic, Latin-7): MorphText::ISO_8859_13 or MorphText::LATIN7 or MorphText::LATIN7
* ISO-8849-14 (Celtic, Latin-8): MorphText::ISO_8859_14 or MorphText::CELTIC or MorphText::LATIN8
* ISO-8849-15 (WEST_EUROPEAN, Latin-9): MorphText::ISO_8859_15 or MorphText::WESTERN_EUROPEAN or MorphText::LATIN9
* ISO-8849-16 (Southeast European, Latin-10): MorphText::ISO_8859_16 or MorphText::SOUTHEAST_EUROPEAN or MorphText::LATIN10