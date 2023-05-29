#include <string>
#include <Windows.h>
#include <locale>
#include <codecvt>
#include<iostream>
#include<algorithm>
#include <cstdint>

class MorphText
{
public:
    enum Formats
    {
        UTF8,
        UTF16LE,
        UTF16BE,
        UTF32LE,
        UTF32BE,
        ASCII,
        LATIN1,
        LATIN2,
        LATIN3,
        LATIN4,
        //LATIN5,
        //LATIN6,
        //LATIN7,
        //LATIN8,
        //LATIN9,
        //LATIN10,
        //LATIN11,
        SHIFTJIS,
    };

private:
    std::string _utf8;
    std::wstring _utf16LE;
    std::wstring _utf16BE;
    std::u32string _utf32LE;
    std::u32string _utf32BE;
    char* _ascii;
    char* _latin1;
    char* _latin2;
    char* _latin3;
    char* _latin4;
    char* _shiftJis;
    int _updatedFlags = 0;
    bool _BE = false;
    static constexpr wchar_t _latin2Lookup[] = {
    0x00A0, 0x0104, 0x02D8, 0x0141, 0x00A4, 0x013D, 0x015A, 0x00A7, 0x00A8, 0x0160,
    0x015E, 0x0164, 0x0179, 0x00AD, 0x017D, 0x017B, 0x00B0, 0x0105, 0x02DB, 0x0142,
    0x00B4, 0x013E, 0x015B, 0x02C7, 0x00B8, 0x0161, 0x015F, 0x0165, 0x017A, 0x02DD,
    0x017E, 0x017C, 0x0154, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7,
    0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E, 0x0110, 0x0143,
    0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7, 0x0158, 0x016E, 0x00DA, 0x0170,
    0x00DC, 0x00DD, 0x0162, 0x00DF, 0x0155, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A,
    0x0107, 0x00E7, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
    0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7, 0x0159, 0x016F,
    0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9 };
    static constexpr wchar_t _latin3Lookup[] = {
    0x00A0, 0x0126, 0x02D8, 0x00A3, 0x00A4, 0x00A5, 0x0124, 0x00A7, 0x00A8, 0x0130,
    0x015E, 0x011E, 0x0134, 0x00AD, 0x017B, 0x00AF, 0x00B0, 0x0127, 0x00B2, 0x00B3,
    0x00B4, 0x00B5, 0x0125, 0x00B7, 0x00B8, 0x0131, 0x015F, 0x011F, 0x0135, 0x00BD,
    0x017C, 0x00BF, 0x00C0, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0106, 0x00C6, 0x00C7,
    0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E, 0x0110, 0x0143,
    0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7, 0x0158, 0x016E, 0x00DA, 0x0170,
    0x00DC, 0x00DD, 0x0162, 0x00DF, 0x0154, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x0107,
    0x00E6, 0x00E7, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
    0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7, 0x0159, 0x016F,
    0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9 };
    static constexpr wchar_t _latin4Lookup[] = {
    0x00A0, 0x0104, 0x0138, 0x0156, 0x00A4, 0x0128, 0x013B, 0x00A7, 0x00A8, 0x0160,
    0x0112, 0x0122, 0x0166, 0x00AD, 0x017D, 0x00AF, 0x00B0, 0x0105, 0x02DB, 0x0157,
    0x00B4, 0x0129, 0x013C, 0x02C7, 0x00B8, 0x0161, 0x0113, 0x0123, 0x0167, 0x014A,
    0x017E, 0x014B, 0x0100, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E,
    0x010C, 0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x012A, 0x0110, 0x0145,
    0x014C, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x0172, 0x00DA, 0x00DB,
    0x00DC, 0x0168, 0x016A, 0x00DF, 0x0101, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5,
    0x00E6, 0x012F, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x012B,
    0x0111, 0x0146, 0x014D, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x0173,
    0x00FA, 0x00FB, 0x00FC, 0x0169, 0x016B, 0x02D9};

    enum Flags
    {
        FLAG_UTF8 = 1 << Formats::UTF8,
        FLAG_UTF16LE = 1 << Formats::UTF16LE,
        FLAG_UTF16BE = 1 << Formats::UTF16BE,
        FLAG_UTF32LE = 1 << Formats::UTF32LE,
        FLAG_UTF32BE = 1 << Formats::UTF32BE,
        FLAG_ASCII = 1 << Formats::ASCII,
        FLAG_LATIN1 = 1 << Formats::LATIN1,
        FLAG_LATIN2 = 1 << Formats::LATIN2,
        FLAG_LATIN3 = 1 << Formats::LATIN3,
        FLAG_LATIN4 = 1 << Formats::LATIN4,
        FLAG_SHIFTJIS = 1 << Formats::SHIFTJIS,
    };

    void convertToUtf8()
    {
        if (_updatedFlags & FLAG_UTF8)
            return;

        if (_updatedFlags & FLAG_LATIN1)
            ;
        else if (_updatedFlags & FLAG_LATIN2)
            ;
        else if (_updatedFlags & FLAG_LATIN3)
            ;
        else if (_updatedFlags & FLAG_LATIN4)
            ;
        else if (_updatedFlags & FLAG_UTF16LE)
            utf16LeToUtf8();
        else if (_updatedFlags & FLAG_UTF16BE)
            utf16BeToUtf8();
        else if (_updatedFlags & FLAG_UTF32LE)
            utf32LeToUtf8();
        else if (_updatedFlags & FLAG_UTF32BE)
            utf32BeToUtf8();
        else
            asciiToUtf8();
    }

    void utf16LeToUtf8()
    {
        _utf8 = Utf16LE_To_Utf8(_utf16LE);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToUtf16Le()
    {
        _utf16LE = Utf8_To_Utf16LE(_utf8);
        _updatedFlags |= FLAG_UTF16LE;
    }

    void utf16BeToUtf8()
    {
        _utf8 = Utf16BE_To_Utf8(_utf16BE);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToUtf16Be()
    {
        _utf16BE = Utf8_To_Utf16BE(_utf8);
        _updatedFlags |= FLAG_UTF16BE;
    }

    void utf32LeToUtf8()
    {
        _utf8 = Utf32LE_To_Utf8(_utf32LE);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToUtf32Le()
    {
        _utf32LE = Utf8_To_Utf32LE(_utf8);
        _updatedFlags |= FLAG_UTF32LE;
    }

    void utf32BeToUtf8()
    {
        _utf8 = Utf32BE_To_Utf8(_utf32BE);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToUtf32Be()
    {
        _utf32BE = Utf8_To_Utf32BE(_utf8);
        _updatedFlags |= FLAG_UTF32BE;
    }

    void asciiToUtf8()
    {
        _utf8 = std::string(_ascii);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToAscii()
    {
        strcpy(_ascii, _utf8.c_str());
        _updatedFlags |= FLAG_ASCII;
    }

    void utf8ToShiftJis()
    {
        _shiftJis = Utf8_To_ShiftJis(_utf8);
        _updatedFlags |= FLAG_SHIFTJIS;
    }

    void shiftJisToUtf8()
    {
        _utf8 = ShiftJis_To_Utf8(_shiftJis);
        _updatedFlags |= FLAG_UTF8;
    }

    void initArrays()
    {
        _ascii = nullptr;
        _latin1 = nullptr;
        _latin2 = nullptr;
        _latin3 = nullptr;
        _latin4 = nullptr;
        _shiftJis = nullptr;
    }

public:
    MorphText(const std::string& utf8)
    {
        initArrays();
        _utf8 = utf8;
        _updatedFlags |= FLAG_UTF8;
    }

    MorphText(const std::wstring& utf16, bool bigEndian = false)
    {
        initArrays();

        if (bigEndian)
        {
            _utf16BE = utf16;
            _updatedFlags |= FLAG_UTF16BE;
        }
        else
        {
            _utf16LE = utf16;
            _updatedFlags |= FLAG_UTF16LE;
        }
    }

    MorphText(const std::u32string& utf32, bool bigEndian = false)
    {
        initArrays();

        if (bigEndian)
        {
            _utf32BE = utf32;
            _updatedFlags |= FLAG_UTF32BE;
        }
        else
        {
            _utf32LE = utf32;
            _updatedFlags |= FLAG_UTF32LE;
        }
    }

    MorphText(const char* charStr, int strType = 0)
    {

        initArrays();

        int length = strlen(charStr);
        switch (strType)
        {
        case Formats::UTF8: {
            *this = MorphText(std::string(charStr));
        } break;
        case LATIN1: {

        } break;
        case Formats::SHIFTJIS: {
            _shiftJis = new char[length + 1];
            _shiftJis[length] = '/0';
            strcpy(_shiftJis, charStr);
            _updatedFlags |= FLAG_SHIFTJIS;
        } break;
        default: // ASCII
        {
            _ascii = new char[length + 1];
            _ascii[length] = '/0';
            strcpy(_ascii, charStr);
            _updatedFlags |= FLAG_ASCII;
        }
        }
    }

    MorphText(const wchar_t* charStr, bool bigEndian = false)
    {
        initArrays();
        *this = MorphText(std::wstring(charStr), bigEndian);
    }

    MorphText(const MorphText& other)
    {
        *this = other;
    }

    MorphText(const char32_t* charStr, bool bigEndian = false)
    {
        initArrays();
        *this = MorphText(std::u32string(charStr), bigEndian);
    }

    ~MorphText()
    {
        delete[] _ascii;
        delete[] _latin1;
        delete[] _latin2;
        delete[] _latin3;
        delete[] _latin4;
        delete[] _shiftJis;
    }

    void operator = (const MorphText& other)
    {
        _utf8 = other._utf8;
        _utf16LE = other._utf16LE;
        _utf16BE = other._utf16BE;
        _utf32LE = other._utf32LE;
        _utf32BE = other._utf32BE;
        strcpy(_ascii, other._ascii);
        strcpy(_latin1, other._latin1);
        strcpy(_latin2, other._latin2);
        strcpy(_latin3, other._latin3);
        strcpy(_latin4, other._latin4);
        strcpy(_shiftJis, other._shiftJis);
        _updatedFlags = other._updatedFlags;
    }

    void operator = (const std::string& str)
    {
        _utf8 = str;
        _updatedFlags = Flags::FLAG_UTF8;
    }

    void operator = (const std::wstring& str)
    {
        if (_BE)
        {
            _utf16BE = str;
            _updatedFlags = Flags::FLAG_UTF16BE;
        }
        else
        {
            _utf16LE = str;
            _updatedFlags = Flags::FLAG_UTF16LE;
        }
    }

    void operator = (const std::u32string& str)
    {
        if (_BE)
        {
            _utf32LE = str;
            _updatedFlags = Flags::FLAG_UTF32BE;
        }
        else
        {
            _utf32LE = str;
            _updatedFlags = Flags::FLAG_UTF32LE;
        }
    }

    void operator = (const wchar_t* str)
    {
        *this = std::wstring(str);
    }

    //u32char

    static std::string ShiftJis_To_Utf8(const char* input) {
        int length = MultiByteToWideChar(932, 0, input, -1, NULL, 0);

        if (!length)
            return "";

        wchar_t* wideStr = new wchar_t[length];
        if (MultiByteToWideChar(932, 0, input, -1, wideStr, length) == 0)
        {
            delete[] wideStr;
            return "";
        }

        int mbLength = WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, NULL, 0, NULL, NULL);
        if (!mbLength)
        {
            delete[] wideStr;
            return "";
        }

        char* mbStr = new char[mbLength];
        if (WideCharToMultiByte(CP_UTF8, 0, wideStr, -1, mbStr, mbLength, NULL, NULL) == 0)
        {
            delete[] wideStr;
            delete[] mbStr;
            return "";
        }

        std::string output(mbStr);

        delete[] wideStr;
        delete[] mbStr;

        return output;
    }

    static char* Utf8_To_ShiftJis(const std::string& input)
    {
        int wideLength = MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, NULL, 0);

        if (!wideLength)
            return nullptr;

        wchar_t* wideStr = new wchar_t[wideLength];

        if (MultiByteToWideChar(CP_UTF8, 0, input.c_str(), -1, wideStr, wideLength) == 0)
        {
            delete[] wideStr;
            return nullptr;
        }

        int sjisLength = WideCharToMultiByte(932, 0, wideStr, -1, NULL, 0, NULL, NULL);

        if (!sjisLength)
        {
            delete[] wideStr;
            return nullptr;
        }

        char* sjisStr = new char[sjisLength];

        if (WideCharToMultiByte(932, 0, wideStr, -1, sjisStr, sjisLength, NULL, NULL) == 0)
        {
            delete[] wideStr;
            delete[] sjisStr;
            return nullptr;
        }

        delete[] wideStr;
        return sjisStr;
    }

    static std::string Utf16LE_To_Utf8(const std::wstring& input) //Converts the Little Endian UTF-16 input to UTF-8
    {
        return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(input);
    }

    static std::wstring Utf8_To_Utf16LE(const std::string& input) //Converts the UTF-8 input to UTF-16 Little Endian (no byte swap)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(input);
    }

    static std::string Utf16BE_To_Utf8(const std::wstring& input) //Converts the Big Endian UTF-16 input to UTF-8
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::codecvt_mode::consume_header>, wchar_t> converter;
        return converter.to_bytes(input);
    }

    static std::wstring Utf8_To_Utf16BE(const std::string& input) //Converts the UTF-8 input to UTF-16 Big Endian (byte swapped)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        std::u16string utf16 = converter.from_bytes(input);
        std::wstring output;
        output.reserve(utf16.size());

        for (char16_t c : utf16)
            output.push_back(static_cast<wchar_t>((c >> 8) | (c << 8)));

        return output;
    }

    static std::string Utf32LE_To_Utf8(const std::u32string& input) //Converts the UTF-32 Little Endian input to UTF-8
    {
        return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(input);
    }

    static std::u32string Utf8_To_Utf32LE(const std::string& input) //Converts the UTF-8 input to UTF-32 Little Endian (no byte swap)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string utf32 = converter.from_bytes(input);
        return utf32.data();
    }

    static std::string Utf32BE_To_Utf8(const std::u32string& input) //Converts the UTF-32 Big Endian input to UTF-8
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(input);
    }

    static std::u32string Utf8_To_Utf32BE(const std::string& input) //Converts the UTF-8 input to UTF-32 Big Endian (bytes swapped)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string utf32 = converter.from_bytes(input);
        std::u32string output;
        output.reserve(utf32.size());

        for (char32_t c : utf32)
            output.push_back(static_cast<wchar_t>((c >> 24) | ((c >> 8) & 0xFF00) | ((c << 8) & 0xFF0000) | (c << 24)));

        return output;
    }

    static std::string ASCII_To_Utf8(const char* input) //Converts the ASCII input to UTF-8
    {
        std::string output(input);

        for (int i = 0; i < output.size(); ++i)
            output[i] = input[i] < 0 ? '?' : input[i];

        return output;
    }

    static char* Utf8_To_ASCII(const std::string& input) //Converts the UTF-8 input to ASCII
    {
        int size = input.size() + 1;
        char* output = new char[size];

        for (int i = 0; i < size; ++i)
            output[i] = input[i] < 0 ? '?' : input[i];

        return output;
    }

    static std::string ISO8859X_To_Utf8(const char* input, int format = LATIN1) //Converts the ISO8859X input to UTF-8
    {
        int length = strlen(input);
        wchar_t* temp = new wchar_t[length+1];
        wchar_t* lookup;

        switch (format)
        {
        case LATIN2:
            lookup = (wchar_t*)_latin2Lookup;
            break;
        case LATIN3:
            lookup = (wchar_t*)_latin3Lookup;
            break;
        case LATIN4:
            lookup = (wchar_t*)_latin4Lookup;
            break;
        default: //latin1
            return std::string(input);
        }


        for (int index = 0; index < length-1; ++index)
        {
            wchar_t ch = (uint8_t)input[index];
            temp[index] = (ch > 0xA0) ? lookup[ch - 0xA0] : ch;
        }

        temp[length-1] = 0;
        std::wstring utf16(temp);
        delete[] temp;
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string output = converter.to_bytes(utf16);
        return output;
    }

    static char* Utf8_To_ISO8859X(const std::string& input, int format = LATIN1) //Converts the UTF-8 input to ISO8859X
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring utf16 = converter.from_bytes(input);
        wchar_t* lookup;

        switch (format)
        {
        case LATIN2:
            lookup = (wchar_t*)_latin2Lookup;
            break;
        case LATIN3:
            lookup = (wchar_t*)_latin3Lookup;
            break;
        case LATIN4:
            lookup = (wchar_t*)_latin4Lookup;
            break;
        default: //latin1
        {
            char* output = new char[input.size() + 1];
            strcpy(output, input.c_str());
            return output;
        }
        }

        int length = utf16.size();
        char* output = new char[length + 1];

        for (int index = 0; index < length; ++index)
        {
            wchar_t ch = utf16[index];

            if (ch > 0xA0)
            {
                for (uint8_t lookupIndex = 0; lookupIndex < 0x60; ++lookupIndex)
                {
                    if (_latin2Lookup[lookupIndex] == ch)
                    {
                        output[index] = lookupIndex + 0xA0;
                        break;
                    }
                    output[index] = L'?';
                }
            }
            else
                output[index] = ch;
        }
        
        output[length] = 0;
        return output;
    }

    static bool Compare(const std::string& lhs, const std::string& rhs, const bool caseSensitive = true, const bool subString = false)
    {
        std::string lhsOperand = caseSensitive ? lhs : ToLower(lhs);
        std::string rhsOperand = caseSensitive ? rhs : ToLower(rhs);

        if (subString)
            return lhsOperand.find(rhsOperand) != (size_t)-1;
        else
            return lhsOperand.compare(rhsOperand) == 0;
    }

    static bool Compare(const std::wstring& lhs, const std::wstring& rhs, const bool caseSensitive = true, const bool subString = false, bool isBigEndian = false)
    {
        std::string lhsOperand;
        std::string rhsOperand;

        if (isBigEndian)
        {
            lhsOperand = caseSensitive ? Utf16BE_To_Utf8(lhs) : ToLower(Utf16BE_To_Utf8(lhs));
            rhsOperand = caseSensitive ? Utf16BE_To_Utf8(rhs) : ToLower(Utf16BE_To_Utf8(rhs));
        }
        else
        {
            lhsOperand = caseSensitive ? Utf16LE_To_Utf8(lhs) : ToLower(Utf16LE_To_Utf8(lhs));
            rhsOperand = caseSensitive ? Utf16LE_To_Utf8(rhs) : ToLower(Utf16LE_To_Utf8(rhs));
        }

        if (subString)
            return lhsOperand.find(rhsOperand) != (size_t)-1;
        else
            return lhsOperand.compare(rhsOperand) == 0;
    }

    static bool Compare(const std::u32string& lhs, const std::u32string& rhs, const bool caseSensitive = true, const bool subString = false, bool isBigEndian = false)
    {
        std::string lhsOperand;
        std::string rhsOperand;

        if (isBigEndian)
        {
            lhsOperand = caseSensitive ? Utf32BE_To_Utf8(lhs) : ToLower(Utf32BE_To_Utf8(lhs));
            rhsOperand = caseSensitive ? Utf32BE_To_Utf8(rhs) : ToLower(Utf32BE_To_Utf8(rhs));
        }
        else
        {
            lhsOperand = caseSensitive ? Utf32LE_To_Utf8(lhs) : ToLower(Utf32LE_To_Utf8(lhs));
            rhsOperand = caseSensitive ? Utf32LE_To_Utf8(rhs) : ToLower(Utf32LE_To_Utf8(rhs));
        }

        if (subString)
            return lhsOperand.find(rhsOperand) != (size_t)-1;
        else
            return lhsOperand.compare(rhsOperand) == 0;
    }

    static bool Compare(const char* lhs, const char* rhs, const bool caseSensitive = true, const bool subString = false, const int format = 0)
    {
        std::string lhsOperand;
        std::string rhsOperand;

        switch (format)
        {
        case SHIFTJIS: {
            lhsOperand = caseSensitive ? ShiftJis_To_Utf8(lhs) : ToLower(ShiftJis_To_Utf8(lhs));
            rhsOperand = caseSensitive ? ShiftJis_To_Utf8(rhs) : ToLower(ShiftJis_To_Utf8(rhs));
        }break;
        default: { //ASCII
            lhsOperand = caseSensitive ? ASCII_To_Utf8(lhs) : ToLower(ASCII_To_Utf8(lhs));
            rhsOperand = caseSensitive ? ASCII_To_Utf8(rhs) : ToLower(ASCII_To_Utf8(rhs));
        }
        }

        if (subString)
            return lhsOperand.find(rhsOperand) != (size_t)-1;
        else
            return lhsOperand.compare(rhsOperand) == 0;
    }

    static std::string ToLower(const std::string& input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), tolower);
        return result;
    }

    static std::string ToUpper(const std::string& input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), toupper);
        return result;
    }

    static std::string ToSarcasm(const std::string& input)
    {
        std::string result = input;

        for (int i = 0; i < result.size(); ++i)
                result[i] = (i & 1) ? std::tolower(input[i]) : std::toupper(input[i]);

        return result;
    }

    static std::wstring ToLower(const std::wstring& input, bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToLower(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    static std::wstring ToUpper(const std::wstring& input, bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToUpper(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    static std::wstring ToSarcasm(const std::wstring& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToSarcasm(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    static std::u32string ToLower(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToLower(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    static std::u32string ToUpper(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToUpper(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    static std::u32string ToSarcasm(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToSarcasm(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    static char* ToLower(const char* input, const int format)
    {
        std::string temp;
        char* result;

        switch (format)
        {
        case SHIFTJIS: {
            temp = ShiftJis_To_Utf8(input);
            temp = ToLower(temp);
            result = Utf8_To_ShiftJis(temp);
        }break;
        default: { //ASCII
            temp = ASCII_To_Utf8(input);
            temp = ToLower(temp);
            result = Utf8_To_ASCII(temp);
        }
        }

        return result;
    }

    static char* ToUpper(const char* input, const int format)
    {
        std::string temp;
        char* result;

        switch (format)
        {
        case SHIFTJIS: {
            temp = ShiftJis_To_Utf8(input);
            temp = ToUpper(temp);
            result = Utf8_To_ShiftJis(temp);
        }break;
        default: { //ASCII
            temp = ASCII_To_Utf8(input);
            temp = ToUpper(temp);
            result = Utf8_To_ASCII(temp);
        }
        }

        return result;
    }

    static char* ToSarcasm(const char* input, const int format)
    {
        std::string temp;
        char* result;

        switch (format)
        {
        case SHIFTJIS: {
            temp = ShiftJis_To_Utf8(input);
            temp = ToSarcasm(temp);
            result = Utf8_To_ShiftJis(temp);
        }break;
        default: { //ASCII
            temp = ASCII_To_Utf8(input);
            temp = ToSarcasm(temp);
            result = Utf8_To_ASCII(temp);
        }
        }

        return result;
    }

    template<typename T> T ToLower(const int format = 0)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToLower(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            if (format == UTF16BE)
            {
                utf8ToUtf16Be();
                return ToLower(_utf16BE);
            }

            utf8ToUtf16Le();
            return ToLower(_utf16LE);
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToLower(_utf32BE);
            }

            utf8ToUtf32Le();
            return ToLower(_utf32LE);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
                case SHIFTJIS: {
                    utf8ToShiftJis();
                    return ToLower(_shiftJis, SHIFTJIS);
                }
                default: { //ASCII
                    utf8ToAscii();
                    return ToLower(_ascii, ASCII);
                }
            }
        }
    }

    template<typename T> T ToUpper(const int format = 0)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToUpper(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            if (format == UTF16BE)
            {
                utf8ToUtf16Be();
                return ToUpper(_utf16BE);
            }

            utf8ToUtf16Le();
            return ToUpper(_utf16LE);
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToUpper(_utf32BE);
            }

            utf8ToUtf32Le();
            return ToUpper(_utf32LE);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
                case SHIFTJIS: {
                    utf8ToShiftJis();
                    return ToUpper(_shiftJis, SHIFTJIS);
                }
                default: { //ASCII
                    utf8ToAscii();
                    return ToUpper(_ascii, ASCII);
                }
            }
        }
    }

    template<typename T> T ToSarcasm(const int format = 0)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToSarcasm(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            if (format == UTF16BE)
            {
                utf8ToUtf16Be();
                return ToSarcasm(_utf16BE, true);
            }

            utf8ToUtf16Le();
            return ToSarcasm(_utf16LE);
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToSarcasm(_utf32BE, true);
            }

            utf8ToUtf32Le();
            return ToSarcasm(_utf32LE);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
            case SHIFTJIS: {
                utf8ToShiftJis();
                return ToSarcasm(_shiftJis, SHIFTJIS);
            }
            default: { //ASCII
                utf8ToAscii();
                return ToSarcasm(_ascii, ASCII);
            }
            }
        }
    }

    std::string GetUTF8()
    {
        convertToUtf8();
        return _utf8;
    }

    std::wstring GetUTF16(bool isBigEndian = false)
    {
        if (isBigEndian)
        {
            if (_updatedFlags & FLAG_UTF16BE)
                utf8ToUtf16Be();

            return _utf16BE;
        }

        if (_updatedFlags & FLAG_UTF16LE)
            utf8ToUtf16Le();

        return _utf16LE;
    }

    std::u32string GetUTF32(bool isBigEndian = false)
    {
        if (isBigEndian)
        {
            if (_updatedFlags & FLAG_UTF32BE)
                utf8ToUtf32Be();

            return _utf32BE;
        }

        if (_updatedFlags & FLAG_UTF32LE)
            utf8ToUtf32Le();

        return _utf32LE;
    }

    std::string GetASCII()
    {
        if (_updatedFlags & FLAG_ASCII)
            utf8ToAscii();

        return _ascii;
    }

    std::string GetShiftJis()
    {
        if (_updatedFlags & FLAG_SHIFTJIS)
            utf8ToShiftJis();

        return _shiftJis;
    }

    void SetBigEndian(const bool shall_I)
    {
        _BE = shall_I;
    }

    void Test()
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        std::cout << "ASCII: " << _ascii << " --- updated: " << (bool)(_updatedFlags & FLAG_ASCII) << "\n";
        std::cout << "LATIN1: " << _latin1 << " --- updated: " << (bool)(_updatedFlags & FLAG_LATIN1) << "\n";
        std::cout << "LATIN2: " << _latin2 << " --- updated: " << (bool)(_updatedFlags & FLAG_LATIN2) << "\n";
        std::cout << "LATIN3: " << _latin3 << " --- updated: " << (bool)(_updatedFlags & FLAG_LATIN3) << "\n";
        std::cout << "LATIN4: " << _latin4 << " --- updated: " << (bool)(_updatedFlags & FLAG_LATIN4) << "\n";
        std::cout << "UTF-8: " << _utf8 << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF8) << "\n";
        std::wcout << L"UTF-16LE: " << _utf16LE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16LE) << "\n";
        std::wcout << L"UTF-16BE: " << _utf16BE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16BE) << "\n";
        std::cout << "UTF-32LE: " << converter.to_bytes(_utf32LE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32LE) << "\n";
        std::cout << "UTF-32BE: " << converter.to_bytes(_utf32BE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32BE) << "\n";
        std::cout << "\n\n\n\n";
    }
};
