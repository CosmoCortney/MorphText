# MorphText
A class to process and convert different kinds of texts/character encodings appearing in video games and elsewhere.

## Encoding Identifiers
These are used to tell certain functions how to process input and output strings.
* `PRIMARY`: Processes operation according to the previously set primary encoding
* `UTF8`: [UTF-8](https://en.wikipedia.org/wiki/UTF-8)
* `UTF16LE`: [UTF-16](https://en.wikipedia.org/wiki/UTF-16) in [Little Endian](https://en.wikipedia.org/wiki/Endianness)
* `UTF16BE`: UTF-16 in Big Endian
* `UTF32LE`: [UTF-32](https://en.wikipedia.org/wiki/UTF-32) in Little Endian
* `UTF32BE`: UTF-32 in Big Endian
* `ASCII`: [ASCII](https://en.wikipedia.org/wiki/ASCII)
* `ISO_8859_1`: [ISO-8859-1](https://en.wikipedia.org/wiki/ISO/IEC_8859-1). Available aliases: `LATIN1`
* `ISO_8859_2`: [ISO-8859-2](https://en.wikipedia.org/wiki/ISO/IEC_8859-2). Available aliases: `LATIN2`
* `ISO_8859_3`: [ISO-8859-3](https://en.wikipedia.org/wiki/ISO/IEC_8859-3). Available aliases: `LATIN3`
* `ISO_8859_4`: [ISO-8859-4](https://en.wikipedia.org/wiki/ISO/IEC_8859-4). Available aliases: `LATIN4`
* `ISO_8859_5`: [ISO-8859-5](https://en.wikipedia.org/wiki/ISO/IEC_8859-5). Available aliases: `CYRILLIC`
* `ISO_8859_6`: [ISO-8859-6](https://en.wikipedia.org/wiki/ISO/IEC_8859-6). Available aliases: `ARABIC`
* `ISO_8859_7`: [ISO-8859-7](https://en.wikipedia.org/wiki/ISO/IEC_8859-7). Available aliases: `GREEK`
* `ISO_8859_8`: [ISO-8859-8](https://en.wikipedia.org/wiki/ISO/IEC_8859-8). Available aliases: `HEBREW`
* `ISO_8859_9`: [ISO-8859-9](https://en.wikipedia.org/wiki/ISO/IEC_8859-9). Available aliases: `TURKISH`, `LATIN5`
* `ISO_8859_10`: [ISO-8859-10](https://en.wikipedia.org/wiki/ISO/IEC_8859-10). Available aliases: `NORDIC`, `LATIN6`
* `ISO_8859_11`: [ISO-8859-11](https://en.wikipedia.org/wiki/ISO/IEC_8859-11). Available aliases: `THAI`
* `ISO_8859_13`: [ISO-8859-13](https://en.wikipedia.org/wiki/ISO/IEC_8859-13). Available aliases: `BALTIC`, `LATIN7`
* `ISO_8859_14`: [ISO-8859-14](https://en.wikipedia.org/wiki/ISO/IEC_8859-14). Available aliases: `CELTIC`, `LATIN8`
* `ISO_8859_15`: [ISO-8859-15](https://en.wikipedia.org/wiki/ISO/IEC_8859-15). Available aliases: `WEST_EUROPEAN`, `LATIN9`
* `ISO_8859_16`: [ISO-8859-16](https://en.wikipedia.org/wiki/ISO/IEC_8859-16). Available aliases: `SOUTHEAST_EUROPEAN`, `LATIN10`
* `SHIFTJIS_CP932`: [Shift Jis](https://en.wikipedia.org/wiki/Shift_JIS) Code Page 932. Available aliases: `CP932`, `SHIFT_JIS_CP932`, `SJIS932`, `MS932`
* `JIS_X_0201_FULLWIDTH`: [JIS X 0201](https://en.wikipedia.org/wiki/JIS_X_0201) in [Full Width](https://en.wikipedia.org/wiki/Katakana#Computer_encoding) Katakana
* `JIS_X_0201_HALFWIDTH`: JIS X 0201 in [Half Width](https://en.wikipedia.org/wiki/Half-width_kana) Katakana
* `KS_X_1001`: [KS X 1001](https://en.wikipedia.org/wiki/KS_X_1001). Available aliases: `EUC_KR`, `KS_C_5601`
* `POKEMON_GEN1_ENGLISH`: [Pokémon Gen I English](https://bulbapedia.bulbagarden.net/wiki/Character_encoding_(Generation_I))
* `POKEMON_GEN1_FRENCH_GERMAN`: [Pokémon Gen I French & German](https://bulbapedia.bulbagarden.net/wiki/Character_encoding_(Generation_I)#French_&_German)
* `POKEMON_GEN1_ITALIAN_SPANISH`: [Pokémon Gen I Italian & Spanish](https://bulbapedia.bulbagarden.net/wiki/Character_encoding_(Generation_I)#Italian_&_Spanish)
* `POKEMON_GEN1_JAPANESE`: [Pokémon Gen I Japanese](https://bulbapedia.bulbagarden.net/wiki/Character_encoding_(Generation_I)#Japanese)

## Supported String Types
UTF16LE, UTF16BE relate to `std::wstring`, `const wchar_t*`, and `wchar_t*` types.

UTF32LE, UTF32BE relate to `std::u32string`, `const char32_t*`, and `char32_t*` types.

All others relate to `std::string`, `const char*`, and `char*` types.

## Constructors
### `MorphText()`
Creates an empty instance.

### `MorphText(<String Type> str, const int encoding)`
* str: input string of any supported type
* encoding: Encoding identifier of the input string

### `MorphText(MorphText& other)`
Creates a copy of anoher instance
* other: source instance

## Operators
### =
The left-hand instance becomes a copy of the right-hand one.

## Conversions
### `outT Convert<inT, outT>(inT input, const int inputEncoding, const int outputEncoding)`
Converts an input string of one encoding type to another.

* Template Parameters:
  * `inT`: The type of the input string.
  * `outT`: The type of the output string.
* Parameters
  * `input`: The input string of type `inT`
  * `inputEncoding`: Character encoding identifier of the input string
  * `outputEncoding`: Character encoding identifier of the output string
* Returns: A string of type `outT`, encoded as `outputEncoding`.

#### Example:
```cpp
std::wstring utf16le = MorphText::Convert<const char*, std::wstring>("an example", UTF8, UTF16LE);
```

Note: If you want to convert the assigned string of a MorphText instane, simply return it with the GetString() function.

### `inT ToLower(inT input, const int encoding)`
Creates an all-lowercase copy of the input string.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `input`: The input string of type `inT`
  * `inputEncoding`: Character encoding identifier of the input string
* Returns: A string of type `inT` encoded as `inputEncoding` in all lowercase

#### Example:
```cpp
std::string utf8 = MorphText::ToLower("Make Lowercase", UTF8);
```

### `inT ToUpper(inT input, const int encoding)`
Creates an all-uppercase copy of the input string.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `input`: The input string of type `inT`
  * `inputEncoding`: Character encoding identifier of the input string
* Returns: A string of type `inT` encoded as `inputEncoding` in all uppercase

#### Example:
```cpp
std::string utf8 = MorphText::ToUpper("make uppercase", UTF8);
```

### `inT ToSarcasm(inT input, const int encoding)`
Creates a sarcastic copy of the input string.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `input`: The input string of type `inT`
  * `inputEncoding`: Character encoding identifier of the input string
* Returns: A string of type `inT` encoded as `inputEncoding` with sarcastic energy

#### Example:
```cpp
std::string utf8 = MorphText::ToSarcasm("you shouldn't be using camelcase for your projects", UTF8);
```

### `bool Compare(inT lhs, inT rhs, const bool caseSensitive, const int encoding)`
Compares two strings for equality.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `lhs`: Left-hand side string
  * `rhs`: Right-hand side string
  * `caseSensitive`: whether to consider case sensitivity
  * `encoding`: Encoding identifier of the input strings
* Returns: true if both strings are identcal, otherwise false.

#### Note
Comparing C-style strings might be faster

#### Example:
```cpp
bool match = MorphText::Compare("test", "test", true, UTF8);
```


### `bool Compare(inT rhs, const bool caseSensitive, const int encoding)`
Compares the instance against another string for equality.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `rhs`: Right-hand side string
  * `caseSensitive`: whether to consider case sensitivity
  * `encoding`: Encoding identifier of the input strings
* Returns: true if both strings are identcal, otherwise false.

#### Note
Comparing C-style strings might be faster.

#### Example:
```cpp
bool match = MorphText::Compare("Test", false, ASCII);
```


### `int Find(intT superset, inT subset, const bool caseSensitive, const int encoding)`
Finds the occurence of a subset string within a superset string.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `superset`: String that may contain the substring
  * `subset`: Substring that may appear within the superset string
  * `caseSensitive`: whether to consider case sensitivity
  * `encoding`: Encoding identifier of the input strings
* Returns: The position of the subset appearing within the superset. Returns -1 if the subset has no occurence. If subset is empty 0 is being returned.

#### Note
Finding C-style strings might be faster.

#### Example:
```cpp
int pos = MorphText::Find("where banana?", "banana", true, ASCII);
```

### `int Find(inT subset, const bool caseSensitive, const int encoding)`
Finds the occurence of a subset string within the instance.

* Data types:
  * `inT`: Any supported string type
* Parameters
  * `subset`: Substring that may appear within the instance
  * `caseSensitive`: whether to consider case sensitivity
  * `encoding`: Encoding identifier of the input strings
* Returns: The position of the subset appearing within the superset. Returns -1 if the subset has no occurence. If subset is empty 0 is being returned.

#### Note
Finding C-style strings might be faster.

#### Example:
```cpp
int pos = MorphText::Find("banana", false, ASCII);
```

### `T GetString(const int encoding)`
Returns the instance's string by the desired encoding identifier.

* Template Parameter
  * `T`: string type
* Parameter
  * `encoding`: Encoding identifier of the output strings
* Returns: The instance's string in the desired encoding and string type

#### Example:
```cpp
MorphText test("ニコニコ二ー", UTF8);
test.GetString<std::string>(SHIFT_JIS);
```

### `SetString<T>(T input, const int encoding)`
Sets the instance's string in the desired encoding identifier.

* Datatype
  * `T`: string type
* Parameter
  * `encoding`: Encoding identifier of the input strings
* Returns: The instance's string in the desired encoding and string type

#### Example:
```cpp
MorphText test;
test.SetString("ニコニコ二ー", UTF8);
```

### `SetPrimaryEncoding(const int encoding)`
Sets the instance's string in the desired encoding identifier.

* Parameter
  * `encoding`: Encoding identifier of the input strings

### `Print()`
A test function that prints all class members. Only available in debug mode.

### `Test()`
A test function that runs all functions. Only available in debug mode.

## ToDo
* check if double-byte characters of Shift-Jis are stored in LE on LE machines
* check if double-byte characters of KS X 1001 are stored in BE on BE machines and in LE on LE machines
* public static C-String type conversion specialization (convertToUTF8, convertFromUTF8)
* fix convertToUTF8(), convertFromUTF8(), Convert() to be able to use references of std::string, std::wstring, and std::u32string
* Pokémon character encodings (Gen II and later + spin-offs)
* add Shift-Jis CP10001/2000, Shift-Jis CP10001/2016
* improve ToLower, ToUpper, ToSarcasm functions by specializing them and considering characters like umlauts, full-width letters, etc
* improve comparisons by specializing them for each encoding
* make member comparison overloads for c-style input string work
* specialize findRaw() function for any other encoding than ASCII or any other UTF type to consider umlauts, fullwidth letters, etc for case insensitivity
* test on a big-endian system
  * add necessary endianness checks to UTF-16 and UTF32-operations
	
## Credits
* Lawn Meower: Idea, Code
* [sozysozbot](https://github.com/sozysozbot): original KS X 1001 table
* [Bulbapedia](https://bulbapedia.bulbagarden.net/wiki/Main_Page) wiki at [Bulbagarden](https://bulbagarden.net/home/): Documenting the Pokémon character encodings