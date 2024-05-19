#pragma once
#include <algorithm>
#include <codecvt>
#include <cstdint>
#include <cwctype>
#include <iostream>
#include <locale>
#include "Lookup.h"
#include <string>
#ifndef NDEBUG
#include <assert.h>
#include <vector>
#endif

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
        ISO_8859_1,
        ISO_8859_2,
        ISO_8859_3,
        ISO_8859_4,
        ISO_8859_5,
        ISO_8859_6,
        ISO_8859_7,
        ISO_8859_8,
        ISO_8859_9,
        ISO_8859_10,
        ISO_8859_11,
        ISO_8859_13,
        ISO_8859_14,
        ISO_8859_15,
        ISO_8859_16,
        SHIFTJIS,
        JIS_X_0201_FULLWIDTH,
        JIS_X_0201_HALFWIDTH,
        KS_X_1001,
        Reserved,
        LATIN1 = ISO_8859_1,
        LATIN2 = ISO_8859_2,
        LATIN3 = ISO_8859_3,
        LATIN4 = ISO_8859_4,
        CYRILLIC = ISO_8859_5,
        ARABIC = ISO_8859_6,
        GREEK = ISO_8859_7,
        HEBREW = ISO_8859_8,
        TURKISH = ISO_8859_9,
        LATIN5 = ISO_8859_9,
        NORDIC = ISO_8859_10,
        LATIN6 = ISO_8859_10,
        THAI = ISO_8859_11,
        BALTIC = ISO_8859_13,
        LATIN7 = ISO_8859_13,
        CELTIC = ISO_8859_14,
        LATIN8 = ISO_8859_14,
        WEST_EUROPEAN = ISO_8859_15,
        LATIN9 = ISO_8859_15,
        SOUTHEAST_EUROPEAN = ISO_8859_16,
        LATIN10 = ISO_8859_16,
        EUC_KR = KS_X_1001
    };

private:
    std::string _utf8;
    std::wstring _utf16LE;
    std::wstring _utf16BE;
    std::u32string _utf32LE;
    std::u32string _utf32BE;
    std::string _ascii;
    std::string _iso_8859_1;
    std::string _iso_8859_2;
    std::string _iso_8859_3;
    std::string _iso_8859_4;
    std::string _iso_8859_5;
    std::string _iso_8859_6;
    std::string _iso_8859_7;
    std::string _iso_8859_8;
    std::string _iso_8859_9;
    std::string _iso_8859_10;
    std::string _iso_8859_11;
    std::string _iso_8859_13;
    std::string _iso_8859_14;
    std::string _iso_8859_15;
    std::string _iso_8859_16;
    std::string _shiftJis;
    std::string _jis_x_0201_halfwidth;
    std::string _jis_x_0201_fullwidth;
    std::wstring _ks_x_1001;
    int _updatedFlags = 0;
    int _primaryFormat;
    uint32_t _maxLength = -1;

    enum Flags
    {
        FLAG_UTF8 = 1 << Formats::UTF8,
        FLAG_UTF16LE = 1 << Formats::UTF16LE,
        FLAG_UTF16BE = 1 << Formats::UTF16BE,
        FLAG_UTF32LE = 1 << Formats::UTF32LE,
        FLAG_UTF32BE = 1 << Formats::UTF32BE,
        FLAG_ASCII = 1 << Formats::ASCII,
        FLAG_ISO_8859_1 = 1 << Formats::ISO_8859_1,
        FLAG_ISO_8859_2 = 1 << Formats::ISO_8859_2,
        FLAG_ISO_8859_3 = 1 << Formats::ISO_8859_3,
        FLAG_ISO_8859_4 = 1 << Formats::ISO_8859_4,
        FLAG_ISO_8859_5 = 1 << Formats::ISO_8859_5,
        FLAG_ISO_8859_6 = 1 << Formats::ISO_8859_6,
        FLAG_ISO_8859_7 = 1 << Formats::ISO_8859_7,
        FLAG_ISO_8859_8 = 1 << Formats::ISO_8859_8,
        FLAG_ISO_8859_9 = 1 << Formats::ISO_8859_9,
        FLAG_ISO_8859_10 = 1 << Formats::ISO_8859_10,
        FLAG_ISO_8859_11 = 1 << Formats::ISO_8859_11,
        FLAG_ISO_8859_13 = 1 << Formats::ISO_8859_13,
        FLAG_ISO_8859_14 = 1 << Formats::ISO_8859_14,
        FLAG_ISO_8859_15 = 1 << Formats::ISO_8859_15,
        FLAG_ISO_8859_16 = 1 << Formats::ISO_8859_16,
        FLAG_SHIFTJIS = 1 << Formats::SHIFTJIS,
        FLAG_JIS_X_0201_FULLWIDTH = 1 << Formats::JIS_X_0201_FULLWIDTH,
        FLAG_JIS_X_0201_HALFWIDTH = 1 << Formats::JIS_X_0201_HALFWIDTH,
        FLAG_KS_X_1001 = 1 << Formats::KS_X_1001,
        FLAG_Reserved = 1 << Formats::Reserved
    };

    static bool compareRaw(const char* lhs, const char* rhs)
    {
        const int len = strlen(lhs);

        for (int i = 0; i < len; ++i)
            if (lhs[i] != rhs[i])
                return false;

        return true;
    }

    static bool compareRaw(const wchar_t* lhs, const wchar_t* rhs)
    {
        const int len = wcslen(lhs);

        for (int i = 0; i < len; ++i)
            if (lhs[i] != rhs[i])
                return false;

        return true;
    }

    static void replaceIllegalChars(std::u32string& str, const bool isBE = false)
    {
        if (isBE)
        {
            for (char32_t& ch : str)
            {
                if (ch > 0xffff1000)
                    ch = 0x3f000000;
            }
        }
        else
        {
            for (char32_t& ch : str)
            {
                if (ch > 0x10FFFF)
                    ch = 0x3f;
            }
        }
    }

    static void swapBytes(const wchar_t* src)
    {
        char* ref = (char*)src;
        *ref ^= *(ref + 1);
        *(ref + 1) ^= *ref;
        *ref ^= *(ref + 1);
    }

    static void swapBytes(const char32_t* src)
    {
        char* ref = (char*)src;
        *ref ^= *(ref + 3);
        *(ref + 3) ^= *ref;
        *ref ^= *(ref + 3);

        *(ref + 1) ^= *(ref + 2);
        *(ref + 2) ^= *(ref + 1);
        *(ref + 1) ^= *(ref + 2);
    }

    void convertToUtf8()
    {
        if (_updatedFlags & FLAG_UTF8)
            return;

        if (_updatedFlags & FLAG_ISO_8859_1)
            iso8859xToUtf8(FLAG_ISO_8859_1);
        else if (_updatedFlags & FLAG_ISO_8859_2)
            iso8859xToUtf8(FLAG_ISO_8859_2);
        else if (_updatedFlags & FLAG_ISO_8859_3)
            iso8859xToUtf8(FLAG_ISO_8859_3);
        else if (_updatedFlags & FLAG_ISO_8859_4)
            iso8859xToUtf8(FLAG_ISO_8859_4);
        else if (_updatedFlags & FLAG_ISO_8859_5)
            iso8859xToUtf8(FLAG_ISO_8859_5);
        else if (_updatedFlags & FLAG_ISO_8859_6)
            iso8859xToUtf8(FLAG_ISO_8859_6);
        else if (_updatedFlags & FLAG_ISO_8859_7)
            iso8859xToUtf8(FLAG_ISO_8859_7);
        else if (_updatedFlags & FLAG_ISO_8859_8)
            iso8859xToUtf8(FLAG_ISO_8859_8);
        else if (_updatedFlags & FLAG_ISO_8859_9)
            iso8859xToUtf8(FLAG_ISO_8859_9);
        else if (_updatedFlags & FLAG_ISO_8859_10)
            iso8859xToUtf8(FLAG_ISO_8859_10);
        else if (_updatedFlags & FLAG_ISO_8859_11)
            iso8859xToUtf8(FLAG_ISO_8859_11);
        else if (_updatedFlags & FLAG_ISO_8859_13)
            iso8859xToUtf8(FLAG_ISO_8859_13);
        else if (_updatedFlags & FLAG_ISO_8859_14)
            iso8859xToUtf8(FLAG_ISO_8859_14);
        else if (_updatedFlags & FLAG_ISO_8859_15)
            iso8859xToUtf8(FLAG_ISO_8859_15);
        else if (_updatedFlags & FLAG_ISO_8859_16)
            iso8859xToUtf8(FLAG_ISO_8859_16);
        else if (_updatedFlags & FLAG_UTF16LE)
            utf16LeToUtf8();
        else if (_updatedFlags & FLAG_UTF16BE)
            utf16BeToUtf8();
        else if (_updatedFlags & FLAG_UTF32LE)
            utf32LeToUtf8();
        else if (_updatedFlags & FLAG_UTF32BE)
            utf32BeToUtf8();
        else if (_updatedFlags & FLAG_JIS_X_0201_FULLWIDTH)
            jisX0201FWToUtf8();
        else if (_updatedFlags & FLAG_JIS_X_0201_HALFWIDTH)
            jisX0201HWToUtf8();
        else if (_updatedFlags & FLAG_KS_X_1001)
            ksX1001ToUtf8();
        else
            asciiToUtf8();
    }

//format to utf8, utf8 to format--------------------------------------------------------

    void jisX0201FWToUtf8()
    {
        _utf8 = JIS_X_0201_FullWidth_To_Utf8(_jis_x_0201_fullwidth);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToJisX0201FW()
    {
        _jis_x_0201_fullwidth = Utf8_To_JIS_X_0201_FullWidth(_utf8);
        _updatedFlags |= FLAG_JIS_X_0201_FULLWIDTH;
    }

    void jisX0201HWToUtf8()
    {
        _utf8 = JIS_X_0201_HalfWidth_To_Utf8(_jis_x_0201_halfwidth);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToJisX0201HW()
    {
        _jis_x_0201_halfwidth = Utf8_To_JIS_X_0201_HalfWidth(_utf8);
        _updatedFlags |= FLAG_JIS_X_0201_HALFWIDTH;
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
        _utf8 = ASCII_To_Utf8(_ascii);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToAscii()
    {
        _ascii = Utf8_To_ASCII(_utf8);
        _updatedFlags |= FLAG_ASCII;
    }

    void iso8859xToUtf8(const int format)
    {
        std::string txt;

        switch (format)
        {
        case ISO_8859_2:
            txt = _iso_8859_2;
            break;
        case ISO_8859_3:
            txt = _iso_8859_3;
            break;
        case ISO_8859_4:
            txt = _iso_8859_4;
            break;
        case ISO_8859_5:
            txt = _iso_8859_5;
            break;
        case ISO_8859_6:
            txt = _iso_8859_6;
            break;
        case ISO_8859_7:
            txt = _iso_8859_7;
            break;
        case ISO_8859_8:
            txt = _iso_8859_8;
            break;
        case ISO_8859_9:
            txt = _iso_8859_9;
            break;
        case ISO_8859_10:
            txt = _iso_8859_10;
            break;
        case ISO_8859_11:
            txt = _iso_8859_11;
            break;
        case ISO_8859_13:
            txt = _iso_8859_13;
            break;
        case ISO_8859_14:
            txt = _iso_8859_14;
            break;
        case ISO_8859_15:
            txt = _iso_8859_15;
            break;
        case ISO_8859_16:
            txt = _iso_8859_16;
            break;
        default: //ISO_8859_1
            txt = _iso_8859_1;
        }

        _utf8 = ISO8859X_To_Utf8(txt, format);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToIso8859x(const int format)
    {
        switch (format)
        {
        case ISO_8859_2:
            _iso_8859_2 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_3:
            _iso_8859_3 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_4:
            _iso_8859_4 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_5:
            _iso_8859_5 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_6:
            _iso_8859_6 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_7:
            _iso_8859_7 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_8:
            _iso_8859_8 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_9:
            _iso_8859_9 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_10:
            _iso_8859_10 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_11:
            _iso_8859_11 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_13:
            _iso_8859_13 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_14:
            _iso_8859_14 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_15:
            _iso_8859_15 = Utf8_To_ISO8859X(_utf8, format);
            break;
        case ISO_8859_16:
            _iso_8859_16 = Utf8_To_ISO8859X(_utf8, format);
            break;
        default:// ISO 8859-1
            _iso_8859_1 = Utf8_To_ISO8859X(_utf8, format);
            break;
        }
        
        _updatedFlags |= (format >= ISO_8859_1 && format <= ISO_8859_16) ? (1 << format) : ISO_8859_1;
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

    void utf8ToKsX1001(const bool highRange = false)
    {
        _ks_x_1001 = Utf8_To_KSX1001(_utf8, highRange);
        _updatedFlags |= FLAG_KS_X_1001;
    }

    void ksX1001ToUtf8()
    {
        _utf8 = KSX1001_To_Utf8(_ks_x_1001);
        _updatedFlags |= FLAG_UTF8;
    }

    static void cleanString(std::string& dirt)
    {
        if(dirt.size())
            for (int i = 0; i < dirt.size() - 1; ++i)
                if (dirt[i] == 0 && dirt[i + 1] != 0)
                    for (; i < dirt.size(); ++i)
                        dirt[i] = 0;
    }

public:
    MorphText()
    {
    }

    MorphText(const std::string& str, const int format = UTF8)
    {
        switch (format)
        {
            case ASCII: {
                _ascii = str;
                _updatedFlags |= FLAG_ASCII;
            } break;
            case ISO_8859_1: {
                _iso_8859_1 = str;
                _updatedFlags |= FLAG_ISO_8859_1;
            } break;
            case ISO_8859_2: {
                _iso_8859_2 = str;
                _updatedFlags |= FLAG_ISO_8859_2;
            } break;
            case ISO_8859_3: {
                _iso_8859_3 = str;
                _updatedFlags |= FLAG_ISO_8859_3;
            } break;
            case ISO_8859_4: {
                _iso_8859_4 = str;
                _updatedFlags |= FLAG_ISO_8859_4;
            } break;
            case ISO_8859_5: {
                _iso_8859_5 = str;
                _updatedFlags |= FLAG_ISO_8859_5;
            } break;
            case ISO_8859_6: {
                _iso_8859_6 = str;
                _updatedFlags |= FLAG_ISO_8859_6;
            } break;
            case ISO_8859_7: {
                _iso_8859_7 = str;
                _updatedFlags |= FLAG_ISO_8859_7;
            } break;
            case ISO_8859_8: {
                _iso_8859_8 = str;
                _updatedFlags |= FLAG_ISO_8859_8;
            } break;
            case ISO_8859_9: {
                _iso_8859_9 = str;
                _updatedFlags |= FLAG_ISO_8859_9;
            } break;
            case ISO_8859_10: {
                _iso_8859_10 = str;
                _updatedFlags |= FLAG_ISO_8859_10;
            } break;
            case ISO_8859_11: {
                _iso_8859_11 = str;
                _updatedFlags |= FLAG_ISO_8859_11;
            } break;
            case ISO_8859_13: {
                _iso_8859_13 = str;
                _updatedFlags |= FLAG_ISO_8859_13;
            } break;
            case ISO_8859_14: {
                _iso_8859_14 = str;
                _updatedFlags |= FLAG_ISO_8859_14;
            } break;
            case ISO_8859_15: {
                _iso_8859_15 = str;
                _updatedFlags |= FLAG_ISO_8859_15;
            } break;
            case ISO_8859_16: {
                _iso_8859_16 = str;
                _updatedFlags |= FLAG_ISO_8859_16;
            } break;
            case SHIFTJIS: {
                _shiftJis = str;
                _updatedFlags |= FLAG_SHIFTJIS;
            } break;
            case JIS_X_0201_FULLWIDTH: {
                _jis_x_0201_fullwidth = str;
                _updatedFlags |= FLAG_JIS_X_0201_FULLWIDTH;
            } break;
            case JIS_X_0201_HALFWIDTH: {
                _jis_x_0201_halfwidth = str;
                _updatedFlags |= FLAG_JIS_X_0201_HALFWIDTH;
            } break;
            default: // UTF8
            {
                _utf8 = str;
                _updatedFlags |= FLAG_UTF8;
            }
        }

        _primaryFormat = format;
    }

    MorphText(const std::wstring& str, const bool bigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            _ks_x_1001 = str;
            _updatedFlags |= FLAG_KS_X_1001;
            _primaryFormat = FLAG_KS_X_1001;
            return;
        }

        if (bigEndian)
        {
            _utf16BE = str;
            _updatedFlags |= FLAG_UTF16BE;
            _primaryFormat = UTF16BE;
        }
        else
        {
            _utf16LE = str;
            _updatedFlags |= FLAG_UTF16LE;
            _primaryFormat = UTF16LE;
        }
    }

    MorphText(const std::u32string& utf32, const bool bigEndian = false)
    {
        if (bigEndian)
        {
            _utf32BE = utf32;
            _updatedFlags |= FLAG_UTF32BE;
            _primaryFormat = UTF32BE;
        }
        else
        {
            _utf32LE = utf32;
            _updatedFlags |= FLAG_UTF32LE;
            _primaryFormat = UTF32LE;
        }
    }

    MorphText(const char* charStr, const int format = UTF8)
    {
       *this = MorphText(std::string(charStr), format);
    }

    MorphText(const wchar_t* charStr, const bool bigEndian = false, const int format = UTF16LE)
    {
        *this = MorphText(std::wstring(charStr), bigEndian, format);
    }

    MorphText(const MorphText& other)
    {
        *this = other;
    }

    MorphText(const char32_t* charStr, const bool bigEndian = false)
    {
        *this = MorphText(std::u32string(charStr), bigEndian);
    }

    ~MorphText()
    {
    }

//public utf8 to format, format to utf8-------------------------------------------------

    /// <summary>
    /// Converts the passed Shift-Jis char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
    static std::string ShiftJis_To_Utf8(const std::string& input)
    {
        int inputIndex = -1;
        std::string output(input.size(), 0);
        std::wstring temp(input.size(), 0);
        wchar_t* lookup = (wchar_t*)_shift_jis_CP932_map;

        for (int i = 0; i < input.size(); ++i)
        {
            ++inputIndex;

            if (inputIndex >= input.size())
                break;

            uint8_t ch = (uint8_t)input[inputIndex];

            if (input[inputIndex] == 0x5C)
                temp[i] = L'¥';
            else if (input[inputIndex] == 0x7E)
                temp[i] = L'‾';
            else if (input[inputIndex] == L'\0')
                break;
            else if (input[inputIndex] > 0xFD)
                temp[i] = L'©';
            else if (input[inputIndex] > 0xFE)
                temp[i] = L'™';
            else if (input[inputIndex] > 0xFF)
                temp[i] = L'…';
            else if ((input[inputIndex] > 0x7f && input[inputIndex+1] < 0x40) && (input[inputIndex] <= 0xA0 && input[inputIndex + 1] > 0x4F))
                temp[i] = L'?';

            
            
            else if (ch > 0xA0 && ch < 0xE0) //Half Width Katakana and such
                temp[i] = 0xFEC0 + ch;
            
            
            
            else if (ch >= 0x81 && ch <= 0xFC)
            {
                uint16_t sjIndex = ch << 8;
                ++inputIndex;
                sjIndex |= input[inputIndex] & 0xFF;
                temp[i] = lookup[sjIndex - 0x8140];
            }
            else if (input[inputIndex] < 0x80)
                temp[i] = input[inputIndex];
            else
                temp[i] = 0x8148;
        }

        temp = temp.c_str();
        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a Shift-Jis char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf8_To_ShiftJis(const std::string& input)
    {
        int outputIndex = -1;
        std::wstring utf16 = Utf8_To_Utf16LE(input);
        int length = utf16.size();
        std::string output(length * 2 +1, '\0');
        wchar_t* lookup = (wchar_t*)_shift_jis_CP932_map;

        for (int i = 0; i < utf16.size(); ++i)
        {
            ++outputIndex;
            wchar_t ch = utf16[i];

            if (utf16[i] == L'¥')
                output[outputIndex] = 0x5C;
            else if (utf16[i] == L'‾')
                output[outputIndex] = 0x7E;
            else if (utf16[i] == L'©')
                output[outputIndex] = 0xFD;
            else if (utf16[i] == L'™')
                output[outputIndex] = 0xFE;
            else if (utf16[i] == L'…')
                output[outputIndex] = 0xFF;
            else if (utf16[i] < 0x80)
                output[outputIndex] = (char)utf16[i];            
            else if (utf16[i] > 0xFF60 && utf16[i] < 0xFFA0) //Half Width Katakana and such
                output[outputIndex] = utf16[i] - 0xFEC0;
            else if (utf16[i] >= 0xF0 && utf16[i] <= 0xFD)
                output[outputIndex] = '\?';
            else if (utf16[i] == L'\0')
                break;
            else
                for (uint16_t lookupIndex = 0; lookupIndex < 0x7B10; ++lookupIndex)
                {
                    if (lookup[lookupIndex] == ch)
                    {
                        output[outputIndex] = static_cast<char>((lookupIndex + 0x8140) >> 8);
                        ++outputIndex;
                        output[outputIndex] = static_cast<char>(lookupIndex + 0x8140);
                        break;
                    }
                    else if (lookupIndex == 0x7B0F)
                        output[outputIndex] = 0x8148;
                }
        }

        return output.c_str();
    }

    /// <summary>
    /// Converts the passed KS X 1001 std::wstring&amp; to an UTF-8 std::string&amp;.
    /// <param><c>std::wstring&amp; input: KS X 1001 wstring to be processed</param>
    /// </summary>
    static std::string KSX1001_To_Utf8(const std::wstring& input)
    {
        const uint16_t charOffset = (input[0] < 0x8000 ? 0x2120 : 0xA1A0); //whether it starts at 0x2121 or 0xA1A1
        std::wstring temp(input.size(), '\0');
        int32_t currentCharOffset;

        for (int i = 0; i < input.size(); ++i)
        {
            currentCharOffset = input[i] - charOffset;

            if (currentCharOffset < 0 || currentCharOffset > 0x7D7F)
            {
                temp[i] = 0xFF1F; //？
                continue;
            }

            temp[i] = _ks_x_1001_map[currentCharOffset] == 0x0000 ? 0xFF1F/*？*/ : _ks_x_1001_map[currentCharOffset];
        }

        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed UTF-8 std::string&amp; to a KS X 1001 std::wstring&amp;.
    /// <param><c>std::string&amp; input: string to be processed, highRange: whether the KS X 1001 string is encoded in the 0x2120 or 0xA1A0 range</param>
    /// </summary>
    static std::wstring Utf8_To_KSX1001(const std::string& input, const bool highRange = false)
    {
        const uint16_t charOffset = highRange ? 0x8080 : 0; //whether to add 0x8080 to each char
        std::wstring output = Utf8_To_Utf16LE(input);

        for (int ch = 0; ch < output.size(); ++ch)
        {
            switch (output[ch])
            {
                case L' ':
                {
                    output[ch] = 0x2121 + charOffset; //ideographic space
                    continue;
                }
                case L'\\':
                {
                    output[ch] = 0x212C + charOffset; //ideographic backslash
                    continue;
                }
                case L'~':
                {
                    output[ch] = 0x2226 + charOffset; //ideographic tilde
                    continue;
                }
                case L'¯':
                {
                    output[ch] = 0x237E + charOffset; //ideographic macron
                    continue;
                }
                case L'!': case L'"': case L'#': case L'$': case L'%': case L'&': case L'\'': case L'(': case L')': case L'*': case L'+': case L',': case L'-': case L'.': case L'/':
                case L'0': case L'1': case L'2': case L'3': case L'4': case L'5': case L'6': case L'7': case L'8': case L'9': case L':': case L';': case L'<': case L'=': case L'>': case L'?':
                case L'@': case L'A': case L'B': case L'C': case L'D': case L'E': case L'F': case L'G': case L'H': case L'I': case L'J': case L'K': case L'L': case L'M': case L'N': case L'O':
                case L'P': case L'Q': case L'R': case L'S': case L'T': case L'U': case L'V': case L'W': case L'X': case L'Y': case L'Z': case L'[': case L']': case L'^ ': case L'_':
                case L'`': case L'a': case L'b': case L'c': case L'd': case L'e': case L'f': case L'g': case L'h': case L'i': case L'j': case L'k': case L'l': case L'm': case L'n': case L'o':
                case L'p': case L'q': case L'r': case L's': case L't': case L'u': case L'v': case L'w': case L'x': case L'y': case L'z': case L'{': case L'|': case L'}':
                {
                    output[ch] = 0x2320 - 0x20 + output[ch]; //Misc ASCII
                    continue;
                }
            }

            for (int i = 0; i < 0x5C80; ++i)
            {
                if (_ks_x_1001_map[i] == output[ch])
                {
                    output[ch] = i + 0x2120 + charOffset;
                    continue;
                }

                if (i > 0x5C8E)
                {
                    output[ch] = 0x2330 + charOffset; //ideographic ？
                    break;
                }
            }
        }

        return output;
    }


    /// <summary>
    /// Converts the passed big endian UTF-16 std::u32string&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::wstring&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf16LE_To_Utf8(const std::wstring& input)
    {
        return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(input);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-16 little endian std::wstring&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::wstring Utf8_To_Utf16LE(const std::string& input)
    {
        std::string temp = input;
        cleanString(temp);
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(temp);
    }

    /// <summary>
    /// Converts the passed big endian UTF-16 std::wstring&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::wstring&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf16BE_To_Utf8(const std::wstring& input)
    {
        std::wstring temp;

        for (wchar_t c : input)
        {
            swapBytes(&c);
            temp.push_back(c);
        }

        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-16 big endian std::wstring&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::wstring Utf8_To_Utf16BE(const std::string& input)
    {
        std::wstring utf16 = Utf8_To_Utf16LE(input);
        std::wstring output;
        output.reserve(utf16.size());

        for (char16_t c : utf16)
            output.push_back(static_cast<wchar_t>((c >> 8) | (c << 8)));

        return output;
    }

    /// <summary>
    /// Converts the passed little endian UTF-32 std::u32string&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::u32string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf32LE_To_Utf8(const std::u32string& input)
    {
        std::u32string unchecked = input;
        replaceIllegalChars(unchecked);
        return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(unchecked);
    }
    
    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-32 little endian std::u32string&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::u32string Utf8_To_Utf32LE(const std::string& input)
    {
        std::string temp = input;
        cleanString(temp);
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.from_bytes(temp);;
    }

    /// <summary>
    /// Converts the passed big endian UTF-32 std::u32string&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::u32string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf32BE_To_Utf8(const std::u32string& input)
    {
        std::u32string inputLE;

        for (char32_t c: input)
        {
            swapBytes(&c);
            inputLE.push_back(c);
        }

        return Utf32LE_To_Utf8(inputLE);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-32 big endian std::u32string&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::u32string Utf8_To_Utf32BE(const std::string& input)
    {
        std::u32string utf32 = Utf8_To_Utf32LE(input);

        for (int i = 0; i < utf32.size(); ++i)
            swapBytes(&utf32[i]);

        return utf32;
    }

    /// <summary>
    /// Converts the passed ASCII char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
    static std::string ASCII_To_Utf8(const std::string input, const int32_t maxLength = -1) //Converts the ASCII input to UTF-8
    {
        std::string output = maxLength == -1 ? input : std::string(input.c_str(), maxLength);

        for (int i = 0; i < output.size() && i < maxLength; ++i)
            output[i] = input[i] < 0 ? '?' : input[i];

        return output;
    }

    /// <summary>
    /// Converts the passed std::string&amp; to an ASCII char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf8_To_ASCII(const std::string& input)
    {
        std::wstring temp = Utf8_To_Utf16LE(input);
        //cleanString(temp);

            for (wchar_t& ch: temp)
            {
                if (ch > 0x7f)
                    ch = '?';
            }

        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed JIS-X-0201 Full Width char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
    static std::string JIS_X_0201_FullWidth_To_Utf8(const std::string& input)
    {
        std::string output(input.size(), 0);
        std::wstring temp(input.size(), 0);
        wchar_t* lookup = (wchar_t*)_jis_x_0201_fullwidth_map;

        for (int i = 0; i < input.size(); ++i)
        {
            wchar_t ch = (uint8_t)input[i];

            if (ch > 0xA0 && ch < 0xE0)
                temp[i] = lookup[ch - 0xA0];
            else if (input[i] == 0x5C)
                temp[i] = L'¥';
            else if (input[i] == 0x7E)
                temp[i] = L'‾';
            else if (input[i] == L'\0')
                break;
            else if (input[i] > 0xDF)
                input[i] == L'?';
            else if (input[i] > 0x7f && input[i] < 0xA1)
                input[i] == L'?';
            else
                temp[i] = input[i];
        }

        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed JIS-X-0201 Half Width char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
    static std::string JIS_X_0201_HalfWidth_To_Utf8(const std::string& input)
    {
        std::wstring temp(input.size(), 0);

        for (int i = 0; i < input.size(); ++i)
        {
            uint8_t ch = input[i];

            if (ch > 0xA0 && ch < 0xE0)
                temp[i] = ch + 0xFEC0;
            else if (ch == 0x5C)
                temp[i] = L'¥';
            else if (ch == 0x7E)
                temp[i] = L'‾';
            else if (ch == L'\0')
                break;
            else if (input[i] > 0xDF)
                input[i] == L'?';
            else if (input[i] > 0x7f && input[i] < 0xA1)
                input[i] == L'?';
            else
                temp[i] = input[i];
        }

        return Utf16LE_To_Utf8(temp);
    }

    /// <summary>
    /// Converts the passed ISO-8859-X char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.
    /// <c>int format: ISO-8859 format of the passed string.</param>
    /// </summary>
    static std::string ISO8859X_To_Utf8(const std::string input, const int format = ISO_8859_1)
    {
        std::wstring temp(input.size(), '\0');
        wchar_t* lookup;

        switch (format)
        {
        case ISO_8859_2:
            lookup = (wchar_t*)_iso8859_2_map;
            break;
        case ISO_8859_3:
            lookup = (wchar_t*)_iso8859_3_map;
            break;
        case ISO_8859_4:
            lookup = (wchar_t*)_iso8859_4_map;
            break;
        case ISO_8859_5:
            lookup = (wchar_t*)_iso8859_5_map;
            break;
        case ISO_8859_6:
            lookup = (wchar_t*)_iso8859_6_map;
            break;
        case ISO_8859_7:
            lookup = (wchar_t*)_iso8859_7_map;
            break;
        case ISO_8859_8:
            lookup = (wchar_t*)_iso8859_8_map;
            break;
        case ISO_8859_9:
            lookup = (wchar_t*)_iso8859_9_map;
            break;
        case ISO_8859_10:
            lookup = (wchar_t*)_iso8859_10_map;
            break;
        case ISO_8859_11:
            lookup = (wchar_t*)_iso8859_11_map;
            break;
        case ISO_8859_13:
            lookup = (wchar_t*)_iso8859_13_map;
            break;
        case ISO_8859_14:
            lookup = (wchar_t*)_iso8859_14_map;
            break;
        case ISO_8859_15:
            lookup = (wchar_t*)_iso8859_15_map;
            break;
        case ISO_8859_16:
            lookup = (wchar_t*)_iso8859_16_map;
            break;
        default: //ISO 8859-1
            lookup = (wchar_t*)_iso8859_1_map;
        }

        for (int index = 0; index < input.size(); ++index)
        {
            wchar_t ch = (uint8_t)input[index];
            temp[index] = (ch > 0xA0) ? lookup[ch - 0xA0] : ch;
            if (ch == '\0') break;
        }

        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        std::string output = converter.to_bytes(temp);
        return output;
    }

    /// <summary>
    /// Converts the passed std::string&amp; to an ISO-8859-X char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.
    /// <c>int format</c>: ISO-8859 format for the string to be returned.</param>
    /// </summary>
    static std::string Utf8_To_ISO8859X(const std::string& input, const int format = ISO_8859_1)
    {
        const std::wstring utf16 = Utf8_To_Utf16LE(input);
        wchar_t* lookup;

        switch (format)
        {
        case ISO_8859_2:
            lookup = (wchar_t*)_iso8859_2_map;
            break;
        case ISO_8859_3:
            lookup = (wchar_t*)_iso8859_3_map;
            break;
        case ISO_8859_4:
            lookup = (wchar_t*)_iso8859_4_map;
            break;
        case ISO_8859_5:
            lookup = (wchar_t*)_iso8859_5_map;
            break;
        case ISO_8859_6:
            lookup = (wchar_t*)_iso8859_6_map;
            break;
        case ISO_8859_7:
            lookup = (wchar_t*)_iso8859_7_map;
            break;
        case ISO_8859_8:
            lookup = (wchar_t*)_iso8859_8_map;
            break;
        case ISO_8859_9:
            lookup = (wchar_t*)_iso8859_9_map;
            break;
        case ISO_8859_10:
            lookup = (wchar_t*)_iso8859_10_map;
            break;
        case ISO_8859_11:
            lookup = (wchar_t*)_iso8859_11_map;
            break;
        case ISO_8859_13:
            lookup = (wchar_t*)_iso8859_13_map;
            break;
        case ISO_8859_14:
            lookup = (wchar_t*)_iso8859_14_map;
            break;
        case ISO_8859_15:
            lookup = (wchar_t*)_iso8859_15_map;
            break;
        case ISO_8859_16:
            lookup = (wchar_t*)_iso8859_16_map;
            break;
        default: //ISO_8859_1
        {
            lookup = (wchar_t*)_iso8859_1_map;
        }
        }

        std::string output(utf16.size(), '\0');

        for (int index = 0; index < utf16.size(); ++index)
        {
            wchar_t ch = utf16[index];

            if (ch > 0xA0)
            {
                output[index] = '?';

                for (uint8_t lookupIndex = 0; lookupIndex < 0x60; ++lookupIndex)
                {
                    if (lookup[lookupIndex] == ch)
                    {
                        output[index] = lookupIndex + 0xA0;
                        break;
                    }
                }
            }
            else
                output[index] = ch;
        }
        
        return output;
    }

    /// <summary>
    /// Converts the passed UTF-8 string to a JIS-X-0201 Full Width string.
    /// <param><c>std::string input: string to be processed.</param>
    /// </summary>
    static std::string Utf8_To_JIS_X_0201_FullWidth(const std::string& input)
    {
        std::wstring utf16 = Utf8_To_Utf16LE(input);
        std::string output(utf16.size(), 0);
        wchar_t* lookup = (wchar_t*)_jis_x_0201_fullwidth_map;

        for (int i = 0; i < utf16.size(); ++i)
        {
            wchar_t ch = utf16[i];

            if (utf16[i] == L'¥')
                output[i] = 0x5C;
            else if (utf16[i] == L'‾')
                output[i] = 0x7E;
            else if (utf16[i] == 0x3000) //ideographic space
                output[i] = 0x20;
            else if(utf16[i] < 0xA1)
                output[i] = (char)utf16[i];
            else if (utf16[i] == L'\0')
                break;
            else
                for (uint8_t lookupIndex = 0; lookupIndex < 0x60; ++lookupIndex)
                {
                    if (lookup[lookupIndex] == ch)
                    {
                        output[i] = lookupIndex + 0xA0;
                        break;
                    }
                    else if(lookupIndex == 0x5F)
                        output[i] = L'?';
                }
        }

        return output;
    }

    /// <summary>
    /// Converts the passed UTF-8 string to a JIS-X-0201 Half Width string.
    /// <param><c>std::string input: string to be processed.</param>
    /// </summary>
    static std::string Utf8_To_JIS_X_0201_HalfWidth(const std::string input)
    {
        std::wstring utf16 = Utf8_To_Utf16LE(input);
        std::string output(utf16.size(), '\0');

        for (int i = 0; i < utf16.size(); ++i)
        {
            wchar_t ch = utf16[i];

            if (utf16[i] == L'¥')
                output[i] = 0x5C;
            else if (utf16[i] == L'‾')
                output[i] = 0x7E;
            else if (utf16[i] < 0xA1)
                output[i] = (char)utf16[i];
            else if (utf16[i] == 0x3000) //ideographic space
                output[i] = 0x20;
            else if (utf16[i] == L'\0')
                break;
            else
                for (uint16_t charCode = 0xFF61; charCode < 0xFFB0; ++charCode)
                {
                    if (ch == charCode)
                    {
                        output[i] = char(charCode - 0xFEC0);
                        break;
                    }
                    else if (charCode == 0xFFAF)
                        output[i] = '?';
                }
        }

        return output;
    }

//Find----------------------------------------------------------------------------------

    /// <summary>
    /// Checks if the right-hand std::string&amp; parameter appears within the left-hand std::string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::string&amp; rhs</c>: std::string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    static int Find(const std::string& superset, const std::string& subset, const int format, const bool caseSensitive = true)
    {
        switch (format)//all except default call this function recursively
        {
            case SHIFTJIS:
                return Find(ShiftJis_To_Utf8(superset), ShiftJis_To_Utf8(subset), UTF8, caseSensitive);
            case JIS_X_0201_FULLWIDTH:
                return Find(JIS_X_0201_FullWidth_To_Utf8(superset), JIS_X_0201_FullWidth_To_Utf8(subset), UTF8, caseSensitive);
            case JIS_X_0201_HALFWIDTH:
                return Find(JIS_X_0201_HalfWidth_To_Utf8(superset), JIS_X_0201_HalfWidth_To_Utf8(subset), UTF8, caseSensitive);
            case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:  case ISO_8859_4:
            case ISO_8859_5:  case ISO_8859_6:  case ISO_8859_7:  case ISO_8859_8: 
            case ISO_8859_9:  case ISO_8859_10: case ISO_8859_11: case ISO_8859_13: 
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
                return Find(ISO8859X_To_Utf8(superset, format), ISO8859X_To_Utf8(subset, format), UTF8, caseSensitive);
            default: //UTF8, ASCII
            {
                const std::string sups = caseSensitive ? superset : ToLower(superset);
                const std::string subs = caseSensitive ? subset : ToLower(subset);
                return sups.find(subs);
            }
        }
    }

    /// <summary>
    /// Checks if the right-hand std::wstring&amp; parameter appears within the left-hand std::wstring. Returns the position of appearance, otherwise -1.
    /// <param><c>std::wstring&amp; lhs</c>: left-hand std::wstring&amp;. 
    /// <c>std::wstring&amp; rhs</c>: std::wstring&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static int Find(const std::wstring& superset, const std::wstring& subset, const bool caseSensitive = true, const bool bigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            if (caseSensitive)
                return KSX1001_To_Utf8(superset).find(KSX1001_To_Utf8(subset));

            return ToLower(KSX1001_To_Utf8(superset)).find(ToLower(KSX1001_To_Utf8(subset)));
        }

        if (bigEndian)
        {
            if (caseSensitive)
                return Utf16BE_To_Utf8(superset).find(Utf16BE_To_Utf8(subset));

            return ToLower(Utf16BE_To_Utf8(superset)).find(ToLower(Utf16BE_To_Utf8(subset)));
        }
        
        if (caseSensitive)
            return Utf16LE_To_Utf8(superset).find(Utf16LE_To_Utf8(subset));

        return ToLower(Utf16LE_To_Utf8(superset)).find(ToLower(Utf16LE_To_Utf8(subset)));
    }

    /// <summary>
    /// Checks if the right-hand std::u32string&amp; parameter appears within the left-hand std::u32string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::u32string&amp; lhs</c>: left-hand std::u32string&amp;. 
    /// <c>std::u32string&amp; rhs</c>: std::u32string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static int Find(const std::u32string& superset, const std::u32string& subset, const bool caseSensitive = true, const bool bigEndian = false)
    {
        if (bigEndian)
        {
            if (caseSensitive)
                return Utf32BE_To_Utf8(superset).find(Utf32BE_To_Utf8(subset));

            return ToLower(Utf32BE_To_Utf8(superset)).find(ToLower(Utf32BE_To_Utf8(subset)));
        }

        if (caseSensitive)
            return Utf32LE_To_Utf8(superset).find(Utf32LE_To_Utf8(subset));

        return ToLower(Utf32LE_To_Utf8(superset)).find(ToLower(Utf32LE_To_Utf8(subset)));
    }

//Compare-------------------------------------------------------------------------------

    /// <summary>
    /// Checks if the right-hand std::string&amp; parameter matches the left-hand std::string. Returns true if they match, otherwise false.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::string&amp; rhs</c>: right-hand std::string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    static bool Compare(const std::string& lhs, const std::string& rhs, const bool caseSensitive = true)
    {
        std::string lhsOperand = caseSensitive ? lhs : ToLower(lhs);
        std::string rhsOperand = caseSensitive ? rhs : ToLower(rhs);

        return lhsOperand.compare(rhsOperand) == 0;
    }

    /// <summary>
    /// Checks if the right-hand std::wstring&amp; parameter matches the left-hand std::wstring. Returns true if they match, otherwise false.
    /// <param><c>std::wstring&amp; lhs</c>: left-hand std::wstring&amp;. 
    /// <c>std::wstring&amp; rhs</c>: right-hand std::wstring&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static bool Compare(const std::wstring& lhs, const std::wstring& rhs, const bool caseSensitive = true, const bool isBigEndian = false, const int format = UTF16LE)
    {
        std::string lhsOperand;
        std::string rhsOperand;

        if (format == KS_X_1001)
        {
            lhsOperand = caseSensitive ? KSX1001_To_Utf8(lhs) : ToLower(KSX1001_To_Utf8(lhs));
            rhsOperand = caseSensitive ? KSX1001_To_Utf8(rhs) : ToLower(KSX1001_To_Utf8(rhs));
        }

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

        return lhsOperand.compare(rhsOperand) == 0;
    }

    /// <summary>
    /// Checks if the right-hand std::u32string&amp; parameter matches the left-hand std::u32string. Returns true if they match, otherwise false.
    /// <param><c>std::u32string&amp; lhs</c>: left-hand std::u32string&amp;. 
    /// <c>std::wstring&amp; rhs</c>: right-hand std::u32string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static bool Compare(const std::u32string& lhs, const std::u32string& rhs, const bool caseSensitive = true, const bool isBigEndian = false)
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

        return lhsOperand.compare(rhsOperand) == 0;
    }

    /// <summary>
    /// Checks if the right-hand std::string&amp; parameter matches the left-hand std::string. Returns true if they match, otherwise false.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::string&amp; rhs</c>: right-hand std::string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    static bool Compare(const char* lhs, const char* rhs, const bool caseSensitive = true, const int format = 0)
    {
        switch (format)
        {
            case SHIFTJIS: case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH:
            case ISO_8859_1: case ISO_8859_2: case ISO_8859_3: case ISO_8859_4:
            case ISO_8859_5: case ISO_8859_6: case ISO_8859_7: case ISO_8859_8:
            case ISO_8859_9: case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
            {
                if (!caseSensitive)
                {
                    const std::string lowerLhs = ToLower(lhs, format);
                    const std::string lowerRhs = ToLower(rhs, format);
                    return compareRaw(lowerLhs.c_str(), lowerRhs.c_str());
                }

                return compareRaw(lhs, rhs);
            }
            default:
            {        
                if (!caseSensitive)
                {
                    const std::string lowerLhs = ToLower(lhs, format);
                    const std::string lowerRhs = ToLower(rhs, format);
                    return strcmp(lowerLhs.c_str(), lowerRhs.c_str()) == 0;
                }
                return strcmp(lhs, rhs) == 0;
            }
        }
    }

    static bool Compare(const wchar_t* lhs, const wchar_t* rhs, const bool caseSensitive = true, const bool isBigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            if (!caseSensitive)
            {
                const std::wstring lowerLhs = ToLower(lhs, false, format);
                const std::wstring lowerRhs = ToLower(rhs, false, format);
                return compareRaw(lowerLhs.c_str(), lowerRhs.c_str());
            }

            return compareRaw(lhs, rhs);
        }

        if (!caseSensitive)
        {
            const wchar_t* lowerLhs = ToLower(lhs, isBigEndian);
            const wchar_t* lowerRhs = ToLower(rhs, isBigEndian);
            const int result = wcscmp(lowerLhs, lowerRhs);
            delete[] lowerLhs;
            delete[] lowerRhs;
            return result == 0;
        }
        return wcscmp(lhs, rhs) == 0;
    }

    static bool Compare(const char32_t* lhs, const char32_t* rhs, const bool caseSensitive = true, const bool isBigEndian = false)
    {
        const int lhsLength = std::char_traits<char32_t>::length(lhs) + 1;
        const int lhrLength = std::char_traits<char32_t>::length(rhs) + 1;

        if (!caseSensitive)
        {
            const char32_t* lowerLhs = ToLower(lhs, isBigEndian);
            const char32_t* lowerRhs = ToLower(rhs, isBigEndian);
            const int result = std::char_traits<char32_t>::compare(lowerLhs, lowerRhs, lhsLength);
            delete[] lowerLhs;
            delete[] lowerRhs;
            return result == 0;
        }
        return std::char_traits<char32_t>::compare(lhs, rhs, lhsLength) == 0;
    }

//ToLower, ToUpper, ToSarcasm-----------------------------------------------------------

    /// <summary>
    /// Returns the passed std::string&amp; in <b>uppercase</b>.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToLower(const std::string& input, const int format = UTF8)
    {
        std::string result = input;

        switch (format)
        {
            case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
            case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
            case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
            case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
            {
                std::string temp = ISO8859X_To_Utf8(input, format);
                temp = ToLower(temp, UTF8);
                return Utf8_To_ISO8859X(temp);
            }
            case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH: {
                for (int i = 0; i < result.size(); ++i)
                    if (result[i] < 0x7F)
                        result[i] = std::tolower(result[i]);

                return result;
            }
            case SHIFTJIS: {
                for (size_t i = 0; i < result.size();)
                {
                    if (static_cast<unsigned char>(result[i]) < 0x80)
                    {
                        if (i > 0 && static_cast<unsigned char>(result[i - 1]) < 0x80)
                            result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
                        else
                            result[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(result[i])));
                        ++i;
                    }
                    else
                    {
                        uint16_t current = static_cast<unsigned char>(result[i]) << 8;
                        current |= static_cast<unsigned char>(result[i + 1]);
                        if ((current > 0x839E && current < 0x83A7) ||
                            (current > 0x843F && current < 0x8462))
                        {
                            current += 0x20;
                        }
                        else if ((current > 0x8260 && current < 0x827A))
                            current += 0x21;

                        result[i] = static_cast<char>(current >> 8);
                        result[i + 1] = static_cast<char>(current & 0xFF);
                        i += 2;
                    }
                }

                return result;
            }
            default: { //UTF8, ASCII
                std::transform(result.begin(), result.end(), result.begin(), tolower);
                return result;
            }
        }
    }

    /// <summary>
    /// Returns the passed std::string&amp; in <b>uppercase</b>.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToUpper(const std::string& input, const int format = UTF8)
    {
        std::string result = input;

        switch (format)
        {
            case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
            case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
            case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
            case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
            {
                std::string temp = ISO8859X_To_Utf8(input, format);
                temp = ToUpper(temp, UTF8);
                return Utf8_To_ISO8859X(temp);
            }
            case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH: {
                for (int i = 0; i < result.size(); ++i)
                    if (result[i] < 0x7F)
                        result[i] = std::toupper(result[i]);

                return result;
            }
            case SHIFTJIS: {
                for (size_t i = 0; i < result.size();)
                {
                    if (static_cast<unsigned char>(result[i]) < 0x80)
                    {
                        if (i > 0 && static_cast<unsigned char>(result[i - 1]) < 0x80)
                            result[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[i])));
                        else
                            result[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[i])));
                        ++i;
                    }
                    else
                    {
                        uint16_t current = static_cast<unsigned char>(result[i]) << 8;
                        current |= static_cast<unsigned char>(result[i + 1]);
                        if ((current > 0x839E && current < 0x83A7) ||
                            (current > 0x843F && current < 0x8462))
                        {
                            current += 0x20;
                        }
                        else if ((current > 0x8260 && current < 0x827A))
                            current += 0x21;

                        result[i] = static_cast<char>(current >> 8);
                        result[i + 1] = static_cast<char>(current & 0xFF);
                        i += 2;
                    }
                }

                return result;
            }
            default: { //UTF8, ASCII
                std::transform(result.begin(), result.end(), result.begin(), toupper);
                return result;
            }
        }
    }

    /// <summary>
    /// Returns the passed std::string&amp; with sarcastic energy.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToSarcasm(const std::string& input, const int format = UTF8)
    {
        std::string result = input;

        switch (format)
        {
            case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
            case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
            case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
            case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
            {

                result = ISO8859X_To_Utf8(input, format);
                result = ToSarcasm(result, UTF8);
                return Utf8_To_ISO8859X(result);
            }
            case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH:
            {
                for (int i = 0; i < result.size(); ++i)
                    if (result[i] < 0x7F)
                        result[i] = i & 1 ? std::tolower(result[i]) : std::toupper(result[i]);

                return result;
            }
            case SHIFTJIS: 
            {
                result = ShiftJis_To_Utf8(input);
                result = ToSarcasm(result, UTF8);
                return Utf8_To_ShiftJis(result);
            }
            default: { //UTF8, ASCII
                for (int i = 0; i < result.size(); ++i)
                    result[i] = (i & 1) ? std::tolower(input[i]) : std::toupper(input[i]);

                return result;
            }
        }
    }

    /// <summary>
    /// Returns the passed std::u32string&amp; in <b>uppercase</b>.
    /// <param><c>std::u32string&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToLower(const std::wstring& input, const bool isBigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            std::wstring output = input;

            for (int i = 0; i < output.size(); ++i)
            {
                if (output[i] >= 0x2341 && output[i] <= 0x235A)
                    output[i] |= 0x20;
            }

            return output;
        }

        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToLower(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    /// <summary>
    /// Returns the passed std::wstring&amp; in <b>uppercase</b>.
    /// <param><c>std::wstring&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToUpper(const std::wstring& input, const bool isBigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            std::wstring output = input;

            for (int i = 0; i < output.size(); ++i)
            {
                if (output[i] >= 0x2361 && output[i] <= 0x237A)
                    output[i] &= 0xFFDF;
            }

            return output;
        }

        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToUpper(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    /// <summary>
    /// Returns the passed std::wstring&amp; with sarcastic energy.
    /// <param><c>std::wstring&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToSarcasm(const std::wstring& input, const bool isBigEndian = false, const int format = UTF16LE)
    {
        if (format == KS_X_1001)
        {
            std::wstring output = input;

            for (int i = 0; i < output.size(); ++i)
            {
                if (i & 1)
                {
                    if (output[i] >= 0x2361 && output[i] <= 0x237A)
                        output[i] &= 0xDF;
                }
                else
                {
                    if (output[i] >= 0x2341 && output[i] <= 0x235A)
                        output[i] |= 0x20;
                }
            }

            return output;
        }

        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToSarcasm(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    /// <summary>
    /// Returns the passed std::u32string&amp; in <b>lowercase</b>.
    /// <param><c>std::u32string&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::u32string ToLower(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToLower(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    /// <summary>
    /// Returns the passed std::u32string&amp; in <b>uppercase</b>.
    /// <param><c>std::u32string&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::u32string ToUpper(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToUpper(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    /// <summary>
    /// Returns the passed std::u32string&amp; with sarcastic energy.
    /// <param><c>std::u32string&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::u32string ToSarcasm(const std::u32string& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf32BE_To_Utf8(input) : Utf32LE_To_Utf8(input);
        temp = ToSarcasm(temp);
        return isBigEndian ? Utf8_To_Utf32BE(temp) : Utf8_To_Utf32LE(temp);
    }

    static wchar_t* ToLower(const wchar_t* input, const bool isBigEndian = true)
    {
        const int length = wcslen(input) + 1;
        wchar_t* result = new wchar_t[length];
        wcscpy_s(result, length, input);

        if (isBigEndian)
        {
            for (wchar_t* i = result; i < result+length; ++i)
            {
                swapBytes(i);

                if (*i != '\0')
                    break;

                *i = std::towlower(*i);
                swapBytes(i);
            }
        }
        else
        {
            for (wchar_t* i = result; *i != '\0'; ++i)
                *i = std::towlower(*i);
        }

        return result;
    }

    static wchar_t* ToUpper(const wchar_t* input, const bool isBigEndian = true)
    {
        const int length = wcslen(input) + 1;
        wchar_t* result = new wchar_t[length];
        wcscpy_s(result, length, input);

        if (isBigEndian)
        {
            for (wchar_t* i = result; i < result + length; ++i)
            {
                swapBytes(i);

                if (*i != '\0')
                    break;

                *i = std::towupper(*i);
                swapBytes(i);
            }
        }
        else
        {
            for (wchar_t* i = result; *i != '\0'; ++i)
                *i = std::towupper(*i);
        }

        return result;
    }

    static wchar_t* ToSarcasm(const wchar_t* input, const bool isBigEndian = true)
    {
        const int length = wcslen(input) + 1;
        wchar_t* result = new wchar_t[length];
        wcscpy_s(result, length, ToSarcasm(std::wstring(input), isBigEndian).c_str());
        return result;
    }

    static char32_t* ToLower(const char32_t* input, const bool isBigEndian = true)
    {
        const int length = std::char_traits<char32_t>::length(input) + 1;
        char32_t* result = new char32_t[length];
        std::char_traits<char32_t>::copy(result, input, length);

        if (isBigEndian)
        {
            for (char32_t* i = result; i < result + length; ++i)
            {
                swapBytes(i);

                if (*i != '\0')
                    break;

                *i = std::towlower(*i);
                swapBytes(i);
            }
        }
        else
        {
            for (char32_t* i = result; *i != '\0'; ++i)
                *i = std::towlower(*i);
        }

        return result;
    }

    static char32_t* ToUpper(const char32_t* input, const bool isBigEndian = true)
    {
        int length = std::char_traits<char32_t>::length(input) + 1;
        char32_t* result = new char32_t[length];
        std::char_traits<char32_t>::copy(result, input, length);

        if (isBigEndian)
        {
            for (char32_t* i = result; i < result + length; ++i)
            {
                swapBytes(i);

                if (*i != '\0')
                    break;

                *i = std::towupper(*i);
                swapBytes(i);
            }
        }
        else
        {
            for (char32_t* i = result; *i != '\0'; ++i)
                *i = std::towupper(*i);
        }

        return result;
    }

    static char32_t* ToSarcasm(const char32_t* input, const bool isBigEndian = true)
    {
        const int length = std::char_traits<char32_t>::length(input) + 1;
        char32_t* result = new char32_t[length];
        std::char_traits<char32_t>::copy(result, ToSarcasm(std::u32string(input), isBigEndian).c_str(), length);
        return result;
    }

    /// <summary>
    /// Returns the <b>lowercase</b> string of type T.
    /// <param><c>int format</c>: set format to select char&ast; type strings or big/little endiand wstring/u32string.</param>
    /// </summary>
    template<typename T> T ToLower(const int format = UTF8)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToLower(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (format)
            {
                case UTF16BE:
                utf8ToUtf16Be();
                    return ToLower(_utf16BE, true);
                case KS_X_1001:
                    utf8ToKsX1001();
                    return ToLower(_ks_x_1001, false, KS_X_1001);
                default:// UTF16LE
            utf8ToUtf16Le();
                    return ToLower(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToLower(_utf32BE, true);
            }

            utf8ToUtf32Le();
            return ToLower(_utf32LE, false);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
            case ASCII: {
                utf8ToAscii();
                return ToLower(_ascii, ASCII);
            }
            case JIS_X_0201_FULLWIDTH: {
                utf8ToJisX0201FW();
                return ToLower(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
            }
            case JIS_X_0201_HALFWIDTH: {
                utf8ToJisX0201HW();
                return ToLower(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
            }
            case SHIFTJIS: {
                utf8ToShiftJis();
                return ToLower(_shiftJis, SHIFTJIS);
            }
            default: { //ISO 8859-X
                utf8ToIso8859x();
                return ToLower(_ascii, ASCII);
            }
            }
        }
    }

    /// <summary>
    /// Returns the <b>uppercase</b> string of type T.
    /// <param><c>int format</c>: set format to select char&ast; type strings or big/little endiand wstring/u32string.</param>
    /// </summary>
    template<typename T> T ToUpper(const int format = UTF8)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToUpper(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (format)
            {
            case UTF16BE:
                utf8ToUtf16Be();
                return ToUpper(_utf16BE, true);
            case KS_X_1001:
                utf8ToKsX1001();
                return ToUpper(_ks_x_1001, false, KS_X_1001);
            default:// UTF16LE
            utf8ToUtf16Le();
                return ToUpper(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToUpper(_utf32BE, true);
            }

            utf8ToUtf32Le();
            return ToUpper(_utf32LE, false);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
                case ASCII: {
                    utf8ToAscii();
                    return ToUpper(_ascii, ASCII);
                } break;
                case JIS_X_0201_FULLWIDTH: {
                    utf8ToJisX0201FW();
                    return ToUpper(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
                }
                case JIS_X_0201_HALFWIDTH: {
                    utf8ToJisX0201HW();
                    return ToUpper(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
                }
                case SHIFTJIS: {
                    utf8ToShiftJis();
                    return ToUpper(_shiftJis, SHIFTJIS);
                }
                default: { //ISO 8859-X
                    utf8ToIso8859x();
                    return ToUpper(_ascii, ASCII);
                }
            }
        }
    }

    /// <summary>
    /// Returns the string of type T with sarcastic energy.
    /// <param><c>int format</c>: set format to select char&ast; type strings or big/little endiand wstring/u32string.</param>
    /// </summary>
    template<typename T> T ToSarcasm(const int format = UTF8)
    {
        convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToSarcasm(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (format)
            {
            case UTF16BE:
                utf8ToUtf16Be();
                return ToSarcasm(_utf16BE, true);
            case KS_X_1001:
                utf8ToKsX1001();
                return ToSarcasm(_ks_x_1001, false, KS_X_1001);
            default:// UTF16LE
            utf8ToUtf16Le();
                return ToSarcasm(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (format == UTF32BE)
            {
                utf8ToUtf32Be();
                return ToSarcasm(_utf32BE, true);
            }

            utf8ToUtf32Le();
            return ToSarcasm(_utf32LE, false);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (format)
            {
            case SHIFTJIS: {
                utf8ToShiftJis();
                return ToSarcasm(_shiftJis, SHIFTJIS);
            }
            case JIS_X_0201_FULLWIDTH: {
                utf8ToJisX0201FW();
                return ToSarcasm(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
            }
            case JIS_X_0201_HALFWIDTH: {
                utf8ToJisX0201HW();
                return ToSarcasm(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
            }
            default: { //ASCII
                utf8ToAscii();
                return ToSarcasm(_ascii, ASCII);
            }
            }
        }
    }

//Compare-------------------------------------------------------------------------------

    /// <summary>
    /// Checks if the std::string&amp; parameter matches the instance's std::string. Returns true if they match, otherwise false.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::string&amp; rhs</c>: right-hand std::string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    bool Compare(const std::string& rhs, const bool caseSensitive = true) const
    {
        return Compare(_utf8, rhs, caseSensitive);
    }

    /// <summary>
    /// Checks if the std::wstring&amp; parameter matches the instance's std::wstring. Returns true if they match, otherwise false.
    /// <param><c>std::wstring&amp; lhs</c>: left-hand std::wstring&amp;. 
    /// <c>std::wstring&amp; rhs</c>: right-hand std::wstring&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    bool Compare(const std::wstring& rhs, const bool caseSensitive = true, const bool bigEndian = false, const int format = UTF16LE) const
    {
        if (format == KS_X_1001)
        {
            return compareRaw(_ks_x_1001.data(), rhs.data());
        }

        if(bigEndian)
            return Compare(_utf16BE, rhs, caseSensitive, true);

        return Compare(_utf16LE, rhs, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the std::u32string&amp; parameter matches the instance's std::u32string. Returns true if they match, otherwise false.
    /// <param><c>std::u32string&amp; lhs</c>: left-hand std::u32string&amp;. 
    /// <c>std::u32string&amp; rhs</c>: right-hand std::u32string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    bool Compare(const std::u32string& rhs, const bool caseSensitive = true, const bool bigEndian = false) const
    {
        if (bigEndian)
            return Compare(_utf32BE, rhs, caseSensitive, true);

        return Compare(_utf32LE, rhs, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the char&ast; parameter matches the instance's char&ast; string. Returns true if they match, otherwise false.
    /// <param><c>std::wstring&amp; lhs</c>: left-hand char&ast;. 
    /// <c>char&ast; rhs</c>: right-hand char&ast; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>int format</c>: The format the strings should be interpreted as.</param>
    /// </summary>
    bool Compare(const char* rhs, const bool caseSensitive = true, const int format = UTF8) const
    {
        switch (format)
        {
        case ASCII:
            return Compare(_ascii.c_str(), rhs, caseSensitive, format);
        case SHIFTJIS:
            return Compare(_shiftJis.c_str(), rhs, caseSensitive, format);
        case JIS_X_0201_FULLWIDTH:
            return Compare(_jis_x_0201_fullwidth.c_str(), rhs, caseSensitive, format);
        case JIS_X_0201_HALFWIDTH: 
            return Compare(_jis_x_0201_halfwidth.c_str(), rhs, caseSensitive, format);
        case ISO_8859_1:
            return Compare(_iso_8859_1.c_str(), rhs, caseSensitive, format);
        case ISO_8859_2:
            return Compare(_iso_8859_2.c_str(), rhs, caseSensitive, format);
        case ISO_8859_3:
            return Compare(_iso_8859_3.c_str(), rhs, caseSensitive, format);
        case ISO_8859_4:
            return Compare(_iso_8859_4.c_str(), rhs, caseSensitive, format);
        case ISO_8859_5:
            return Compare(_iso_8859_5.c_str(), rhs, caseSensitive, format);
        case ISO_8859_6:
            return Compare(_iso_8859_6.c_str(), rhs, caseSensitive, format);
        case ISO_8859_7:
            return Compare(_iso_8859_7.c_str(), rhs, caseSensitive, format);
        case ISO_8859_8:
            return Compare(_iso_8859_8.c_str(), rhs, caseSensitive, format);
        case ISO_8859_9:
            return Compare(_iso_8859_9.c_str(), rhs, caseSensitive, format);
        case ISO_8859_10:
            return Compare(_iso_8859_10.c_str(), rhs, caseSensitive, format);
        case ISO_8859_11:
            return Compare(_iso_8859_11.c_str(), rhs, caseSensitive, format);
        case ISO_8859_13:
            return Compare(_iso_8859_13.c_str(), rhs, caseSensitive, format);
        case ISO_8859_14:
            return Compare(_iso_8859_14.c_str(), rhs, caseSensitive, format);
        case ISO_8859_15:
            return Compare(_iso_8859_15.c_str(), rhs, caseSensitive, format);
        case ISO_8859_16:
            return Compare(_iso_8859_16.c_str(), rhs, caseSensitive, format);
        default: //UTF8
            return Compare(_utf8.c_str(), rhs, caseSensitive, format);
        }
    }

    bool Compare(const wchar_t* rhs, const bool caseSensitive = true, const bool isBigEndian = false, const int format = UTF16LE) const
    {
        if (format == KS_X_1001)
        {
            if (caseSensitive)
                return compareRaw(_ks_x_1001.data(), rhs);
            else
                return compareRaw(ToLower(_ks_x_1001, false, KS_X_1001).data(), ToLower(rhs, false, KS_X_1001).data());
        }

        return Compare(isBigEndian ? _utf16BE.c_str() : _utf16LE.c_str(), rhs, caseSensitive, isBigEndian);
    }

    bool Compare(const char32_t* rhs, const bool caseSensitive = true, const bool isBigEndian = false) const
    {
        return Compare(isBigEndian ? _utf32BE.c_str() : _utf32LE.c_str(), rhs, caseSensitive, isBigEndian);
    }

//Find (instance) ----------------------------------------------------------------------

    /// <summary>
    /// Checks if the std::string&amp; string parameter appears within the instance's std::string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::string&amp; subset</c>: std::string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    int Find(const std::string& subset, const bool caseSensitive = true, const int format = UTF8) const
    {
        return Find(_utf8, subset, format, caseSensitive);
    }

    /// <summary>
    /// Checks if the std::wstring&amp; string parameter appears within the instance's std::wstring. Returns the position of appearance, otherwise -1.
    /// <param><c>std::wstring&amp; subset</c>: std::wstring&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    int Find(const std::wstring& subset, const bool caseSensitive = true, const bool bigEndian = false, const int format = UTF16LE) const
    {
        if (format == KS_X_1001)
        {
            const std::wstring sups = Utf8_To_Utf16LE(KSX1001_To_Utf8(_ks_x_1001));
            const std::wstring subs = Utf8_To_Utf16LE(KSX1001_To_Utf8(subset));
            return Find(sups, subs);
        }

        if(bigEndian)
            return Find(_utf16BE, subset, caseSensitive, true);

        return Find(_utf16LE, subset, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the std::u32string&amp; string parameter appears within the instance's std::u32string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::u32string&amp; subset</c>: std::u32string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    int Find(const std::u32string& subset, const bool caseSensitive = true, const bool bigEndian = false) const
    {
        if (bigEndian)
            return Find(_utf32BE, subset, caseSensitive, true);

        return Find(_utf32LE, subset, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the char&ast; string parameter appears within the instance's selected (format) string. Returns the position of appearance, otherwise -1.
    /// <param><c>char&ast; subset</c>: char&ast; to be found. 
    /// <c>int format</c>: format value.
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    int Find(const char* subset, const int format, const bool caseSensitive = true) const
    {
        switch (format)
        {
        case ISO_8859_1:
            return Find(ISO8859X_To_Utf8(_iso_8859_1, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_2:
            return Find(ISO8859X_To_Utf8(_iso_8859_2, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_3:
            return Find(ISO8859X_To_Utf8(_iso_8859_3, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_4:
            return Find(ISO8859X_To_Utf8(_iso_8859_4, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_5:
            return Find(ISO8859X_To_Utf8(_iso_8859_5, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_6:
            return Find(ISO8859X_To_Utf8(_iso_8859_6, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_7:
            return Find(ISO8859X_To_Utf8(_iso_8859_7, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_8:
            return Find(ISO8859X_To_Utf8(_iso_8859_8, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_9:
            return Find(ISO8859X_To_Utf8(_iso_8859_9, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_10:
            return Find(ISO8859X_To_Utf8(_iso_8859_10, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_11:
            return Find(ISO8859X_To_Utf8(_iso_8859_11, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_13:
            return Find(ISO8859X_To_Utf8(_iso_8859_13, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_14:
            return Find(ISO8859X_To_Utf8(_iso_8859_14, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_15:
            return Find(ISO8859X_To_Utf8(_iso_8859_15, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case ISO_8859_16:
            return Find(ISO8859X_To_Utf8(_iso_8859_16, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        case SHIFTJIS:
            return Find(ShiftJis_To_Utf8(_shiftJis), ShiftJis_To_Utf8(subset), caseSensitive);
        case JIS_X_0201_FULLWIDTH: 
            return Find(JIS_X_0201_FullWidth_To_Utf8(_jis_x_0201_fullwidth), JIS_X_0201_FullWidth_To_Utf8(subset), caseSensitive);
        case JIS_X_0201_HALFWIDTH: 
            return Find(JIS_X_0201_HalfWidth_To_Utf8(_jis_x_0201_halfwidth), JIS_X_0201_HalfWidth_To_Utf8(subset), caseSensitive);
        default: //ASCII
            return Find(ASCII_To_Utf8(_ascii), ASCII_To_Utf8(subset), caseSensitive);
        }
    }

//Get-----------------------------------------------------------------------------------

    /// <summary>
    /// Returns the instance's <b>UTF-8</b> value.
    /// </summary>
    std::string GetUTF8()
    {
        if(!(_updatedFlags & FLAG_UTF8))
        convertToUtf8();

        return _utf8;
    }

    /// <summary>
    /// Returns the instance's <b>UTF-16</b> value.
    /// <param><c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    std::wstring GetUTF16(const bool isBigEndian = false)
    {
        if (isBigEndian)
        {
            if (!(_updatedFlags & FLAG_UTF16BE))
                utf8ToUtf16Be();

            return _utf16BE;
        }

        if (!(_updatedFlags & FLAG_UTF16LE))
            utf8ToUtf16Le();

        return _utf16LE;
    }

    /// <summary>
    /// Returns the instance's <b>UTF-32</b> value.
    /// <param><c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    std::u32string GetUTF32(const bool isBigEndian = false)
    {
        if (isBigEndian)
        {
            if (!(_updatedFlags & FLAG_UTF32BE))
                utf8ToUtf32Be();

            return _utf32BE;
        }

        if (!(_updatedFlags & FLAG_UTF32LE))
            utf8ToUtf32Le();

        return _utf32LE;
    }

    /// <summary>
    /// Returns the instance's <b>ASCII</b> value.
    /// </summary>
    std::string GetASCII()
    {
        if (!(_updatedFlags & FLAG_ASCII))
            utf8ToAscii();

        return _ascii;
    }

    /// <summary>
    /// Returns the instance's <b>Shift-Jis</b> value as char*.
    /// </summary>
    std::string GetShiftJis()
    {
        if (!(_updatedFlags & FLAG_SHIFTJIS))
            utf8ToShiftJis();
        return _shiftJis;
    }

    /// <summary>
    /// Returns the instance's <b>KS X 1001</b> value as wchar*.
    /// </summary>
    std::wstring Get_KS_X_1001(const bool highRange = false)
    {
        if (!(_updatedFlags & FLAG_KS_X_1001))
            utf8ToKsX1001(highRange);
        return _ks_x_1001;
    }

    /// <summary>
    /// Returns the instance's <b>ISO-8859-X</b> value as char*.
    /// <param><c>int format</c>: ISO-8859-X format to return.</param>
    /// </summary>
    std::string GetISO8859X(const int format)
    {
        switch (format)
        {
        case ISO_8859_2:
            if(!(_updatedFlags & FLAG_ISO_8859_2))
                utf8ToIso8859x(format);
            return _iso_8859_2;
        case ISO_8859_3:
            if (!(_updatedFlags & FLAG_ISO_8859_3))
                utf8ToIso8859x(format);
            return _iso_8859_3;
        case ISO_8859_4:
            if (!(_updatedFlags & FLAG_ISO_8859_4))
                utf8ToIso8859x(format);
            return _iso_8859_4;
        case ISO_8859_5:
            if (!(_updatedFlags & FLAG_ISO_8859_5))
                utf8ToIso8859x(format);
            return _iso_8859_5;
        case ISO_8859_6:
            if (!(_updatedFlags & FLAG_ISO_8859_6))
                utf8ToIso8859x(format);
            return _iso_8859_6;
        case ISO_8859_7:
            if (!(_updatedFlags & FLAG_ISO_8859_7))
                utf8ToIso8859x(format);
            return _iso_8859_7;
        case ISO_8859_8:
            if (!(_updatedFlags & FLAG_ISO_8859_8))
                utf8ToIso8859x(format);
            return _iso_8859_8;
        case ISO_8859_9:
            if (!(_updatedFlags & FLAG_ISO_8859_9))
                utf8ToIso8859x(format);
            return _iso_8859_9;
        case ISO_8859_10:
            if (!(_updatedFlags & FLAG_ISO_8859_10))
                utf8ToIso8859x(format);
            return _iso_8859_10;
        case ISO_8859_11:
            if (!(_updatedFlags & FLAG_ISO_8859_11))
                utf8ToIso8859x(format);
            return _iso_8859_11;
        case ISO_8859_13:
            if (!(_updatedFlags & FLAG_ISO_8859_13))
                utf8ToIso8859x(format);
            return _iso_8859_13;
        case ISO_8859_14:
            if (!(_updatedFlags & FLAG_ISO_8859_14))
                utf8ToIso8859x(format);
            return _iso_8859_14;
        case ISO_8859_15:
            if (!(_updatedFlags & FLAG_ISO_8859_15))
                utf8ToIso8859x(format);
            return _iso_8859_15;
        case ISO_8859_16:
            if (!(_updatedFlags & FLAG_ISO_8859_16))
                utf8ToIso8859x(format);
            return _iso_8859_16;
        default:
            if (!(_updatedFlags & FLAG_ISO_8859_1))
                utf8ToIso8859x(format);
            return _iso_8859_1;
        }
    }

    std::string GetJisX0201FullWidth()
    {
        if (!(_updatedFlags & FLAG_JIS_X_0201_FULLWIDTH))
            utf8ToJisX0201FW();
        return _jis_x_0201_fullwidth;
    }

    std::string GetJisX0201HalfWidth()
    {
        if (!(_updatedFlags & FLAG_JIS_X_0201_HALFWIDTH))
            utf8ToJisX0201HW();
        return _jis_x_0201_halfwidth;
    }

//Get, Set Format

    /// <summary>
    /// Returns the primary format. This is useful if other parts of your code don't which format to output.
    /// </summary>
    int GetPrimaryFormat() const
    {
        return _primaryFormat;
    }

    /// <summary>
    /// Sets the primary format. This is useful if other parts of your code don't which format to output.
    /// <param><c>int format</c>: ISO-8859 Format.</param>
    /// </summary>
    void SetPrimaryFormat(const int format)
    {
        convertToUtf8();

        switch (format)
        {
        case ASCII:
            utf8ToAscii();
            break;
        case SHIFTJIS:
            utf8ToShiftJis();
            break;
        case KS_X_1001:
            utf8ToKsX1001();
            break;
        case JIS_X_0201_FULLWIDTH:
            utf8ToJisX0201FW();
            break;
        case JIS_X_0201_HALFWIDTH:
            utf8ToJisX0201HW();
            break;
        case UTF16LE:
            utf8ToUtf16Le();
            break;
        case UTF16BE:
            utf8ToUtf16Be();
            break;
        case UTF32LE:
            utf8ToUtf32Le();
            break;
        case UTF32BE:
            utf8ToUtf32Be();
            break;
        default: //ISO-8859-X
            utf8ToIso8859x(format);
        }

        _primaryFormat = format;
    }

//Set-----------------------------------------------------------------------------------

    /// <summary>
    /// Sets the instance's <b>ASCII</b> value.
    /// <param><c>char&ast; input</c>: ASCII char* string to be set.</param>
    /// <example> instance.SetASCII(text);</example>
    /// </summary>
    void SetASCII(const char* input)
    {
        _ascii = input;
        _updatedFlags = FLAG_ASCII;
    }

    /// <summary>
    /// Sets the instance's <b>ASCII</b> value.
    /// <param><c>char&ast; input</c>: ASCII std::string to be set.</param>
    /// <example> instance.SetASCII(text);</example>
    /// </summary>
    void SetASCII(const std::string& input)
    {
        _ascii = input;
        _updatedFlags = FLAG_ASCII;
    }

    /// <summary>
    /// Sets the instance's <b>Shift-Jis</b> value.
    /// <param><c>char&ast; input</c>: Shift-Jis char* string to be set.</param>
    /// <example> instance.SetShiftJis(text);</example>
    /// </summary>
    void SetShiftJis(const std::string& input)
    {
        _shiftJis = input;
        _updatedFlags = FLAG_SHIFTJIS;
    }

    /// <summary>
    /// Sets the instance's <b>KS X 1001</b> value.
    /// <param><c>char&ast; input</c>: KS X 1001 char* string to be set.</param>
    /// <example> instance.SetShiftJis(text);</example>
    /// </summary>
    void Set_KS_X_1001(const std::wstring& input)
    {
        _ks_x_1001 = input;
        _updatedFlags = FLAG_KS_X_1001;
    }

    void SetJisX0201FullWidth(const std::string& input)
    {
        _jis_x_0201_fullwidth = input;
        _updatedFlags = FLAG_JIS_X_0201_FULLWIDTH;
    }

    void SetJisX0201HalfWidth(const char* input)
    {
        _jis_x_0201_halfwidth = input;
        _updatedFlags = FLAG_JIS_X_0201_HALFWIDTH;
    }

    /// <summary>
    /// Sets the instance's <b>ISO-8859-X</b> value.
    /// <param><c>char&ast; input</c>: ISO-8859-X char* string to be set. 
    /// <c>int format</c>: ISO-8859 Format.</param>
    /// <example> instance.SetISO8859X(text, MorphText::ISO_8859_3);</example>
    /// </summary>
    void SetISO8859X(const std::string input, const int format)
    {
        switch (format)
        {
        case ISO_8859_2:
            _iso_8859_2 = input;
            _updatedFlags = FLAG_ISO_8859_2;
            break;
        case ISO_8859_3:
            _iso_8859_3 = input;
            _updatedFlags = FLAG_ISO_8859_3;
            break;
        case ISO_8859_4:
            _iso_8859_4 = input;
            _updatedFlags = FLAG_ISO_8859_4;
            break;
        case ISO_8859_5:
            _iso_8859_5 = input;
            _updatedFlags = FLAG_ISO_8859_5;
            break;
        case ISO_8859_6:
            _iso_8859_6 = input;
            _updatedFlags = FLAG_ISO_8859_6;
            break;
        case ISO_8859_7:
            _iso_8859_7 = input;
            _updatedFlags = FLAG_ISO_8859_7;
            break;
        case ISO_8859_8:
            _iso_8859_8 = input;
            _updatedFlags = FLAG_ISO_8859_8;
            break;
        case ISO_8859_9:
            _iso_8859_9 = input;
            _updatedFlags = FLAG_ISO_8859_9;
            break;
        case ISO_8859_10:
            _iso_8859_10 = input;
            _updatedFlags = FLAG_ISO_8859_10;
            break;
        case ISO_8859_11:
            _iso_8859_11 = input;
            _updatedFlags = FLAG_ISO_8859_11;
            break;
        case ISO_8859_13:
            _iso_8859_13 = input;
            _updatedFlags = FLAG_ISO_8859_13;
            break;
        case ISO_8859_14:
            _iso_8859_14 = input;
            _updatedFlags = FLAG_ISO_8859_14;
            break;
        case ISO_8859_15:
            _iso_8859_15 = input;
            _updatedFlags = FLAG_ISO_8859_15;
            break;
        case ISO_8859_16:
            _iso_8859_16 = input;
            _updatedFlags = FLAG_ISO_8859_16;
            break;
        default:// ISO 8859-1
            _iso_8859_1 = input;
            _updatedFlags = FLAG_ISO_8859_1;
            break;
        }
    }

    /// <summary>
    /// Sets the instance's <b>UTF-8</b> value
    /// <param><c>std::string&amp; input</c>: UTF-8 string to be set.</param>
    /// </summary>
    void SetUTF8(const std::string& str)
    {
        _utf8 = str;
        _updatedFlags = FLAG_UTF8;
    }

    /// <summary>
    /// Sets the instance's <b>UTF-16</b> value
    /// <param><c>std::wstring&amp; input</c>: UTF-16 string to be set. 
    /// <c>bool isBigEndian</c> (optional): Set Big Endian (true = big endian, false = little endian (default)</param>
    /// </summary>
    void SetUTF16(const std::wstring& input, const bool isBigEndian = false)
    {
        if (isBigEndian)
        {
            _utf16BE = input;
            _updatedFlags = FLAG_UTF16BE;
        }
        else
        {
            _utf16LE = input;
            _updatedFlags = FLAG_UTF16LE;
        }
    }

    ///<summary>
    ///Sets the instance's <b>UTF-16</b> value
    ///<parameter><c>wchar_t&ast; input</c>: UTF-16 string to be set. 
    ///<c>bool isBigEndian</c> (optional): Set Big Endian (true = big endian, false = little endian (default)</parameter>
    ///</summary>
    void SetUTF16(const wchar_t* input, const bool isBigEndian = false)
    {
        SetUTF16(std::wstring(input));
    }

    /// <summary>
    /// Sets the instance's <b>UTF-32</b> value
    /// <param><c>std::u32string&amp; input</c>: UTF-32 string to be set. 
    /// <c>bool isBigEndian</c> (optional): Set Big Endian (true = big endian, false = little endian (default)</param>
    /// </summary>
    void SetUTF32(const std::u32string& input, const bool isBigEndian = false)
    {

        if (isBigEndian)
        {
            _utf32BE = input;
            replaceIllegalChars(_utf32BE, isBigEndian);
            _updatedFlags = FLAG_UTF32BE;
        }
        else
        {
            _utf32LE = input;
            replaceIllegalChars(_utf32LE, isBigEndian);
            _updatedFlags = FLAG_UTF32LE;
        }
    }

    /// <summary>
    /// Sets the instance's <b>UTF-32</b> value
    /// <param><c>char32_t&ast; input</c>: UTF-32 string to be set. 
    /// <c>bool isBigEndian</c> (optional): Set Big Endian (true = big endian, false = little endian (default)</param>
    /// </summary>
    void SetUTF32(const char32_t* input, const bool isBigEndian = false)
    {
        SetUTF32(std::u32string(input));
    }

//Misc----------------------------------------------------------------------------------

    void SetMaxLength(const uint32_t length)
    {
        _maxLength = length;
    }

    /// <summary>
    /// Sets the left-hand instance to a <b>copie</b> of the right-hand instance
    /// </summary>
    void operator = (const MorphText& other)
    {
        _utf8 = other._utf8;
        _utf16LE = other._utf16LE;
        _utf16BE = other._utf16BE;
        _utf32LE = other._utf32LE;
        _utf32BE = other._utf32BE;
        _ascii = other._ascii;
        _jis_x_0201_fullwidth = other._jis_x_0201_fullwidth;
        _jis_x_0201_halfwidth = other._jis_x_0201_halfwidth;
        _shiftJis = other._shiftJis;
        _ks_x_1001 = other._ks_x_1001;
        _iso_8859_1 = other._iso_8859_1;
        _iso_8859_2 = other._iso_8859_2;
        _iso_8859_3 = other._iso_8859_3;
        _iso_8859_4 = other._iso_8859_4;
        _iso_8859_5 = other._iso_8859_5;
        _iso_8859_6 = other._iso_8859_6;
        _iso_8859_7 = other._iso_8859_7;
        _iso_8859_8 = other._iso_8859_8;
        _iso_8859_9 = other._iso_8859_9;
        _iso_8859_10 = other._iso_8859_10;
        _iso_8859_11 = other._iso_8859_11;
        _iso_8859_13 = other._iso_8859_13;
        _iso_8859_14 = other._iso_8859_14;
        _iso_8859_15 = other._iso_8859_15;
        _iso_8859_16 = other._iso_8859_16;
        _updatedFlags = other._updatedFlags;
        _primaryFormat = other._primaryFormat;
    }

#ifndef NDEBUG
    void Print()
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        std::cout << "ASCII: " << _ascii << " --- updated: " << (bool)(_updatedFlags & FLAG_ASCII) << "\n";
        std::cout << "ISO 8859 1: " << _iso_8859_1 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_1) << "\n";
        std::cout << "ISO 8859 2: " << _iso_8859_2 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_2) << "\n";
        std::cout << "ISO 8859 3: " << _iso_8859_3 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_3) << "\n";
        std::cout << "ISO 8859 4: " << _iso_8859_4 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_4) << "\n";
        std::cout << "ISO 8859 5: " << _iso_8859_5 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_5) << "\n";
        std::cout << "ISO 8859 6: " << _iso_8859_6 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_6) << "\n";
        std::cout << "ISO 8859 7: " << _iso_8859_7 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_7) << "\n";
        std::cout << "ISO 8859 8: " << _iso_8859_8 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_8) << "\n";
        std::cout << "ISO 8859 9: " << _iso_8859_9 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_9) << "\n";
        std::cout << "ISO 8859 10: " << _iso_8859_10 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_10) << "\n";
        std::cout << "ISO 8859 11: " << _iso_8859_11 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_11) << "\n";
        std::cout << "ISO 8859 13: " << _iso_8859_13 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_13) << "\n";
        std::cout << "ISO 8859 14: " << _iso_8859_14 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_14) << "\n";
        std::cout << "ISO 8859 15: " << _iso_8859_15 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_15) << "\n";
        std::cout << "ISO 8859 16: " << _iso_8859_16 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_16) << "\n";
        std::cout << "UTF-8: " << _utf8 << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF8) << "\n";
        std::wcout << L"UTF-16LE: " << _utf16LE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16LE) << "\n";
        std::wcout << L"UTF-16BE: " << _utf16BE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16BE) << "\n";
        std::cout << "UTF-32LE: " << converter.to_bytes(_utf32LE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32LE) << "\n";
        std::cout << "UTF-32BE: " << converter.to_bytes(_utf32BE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32BE) << "\n";
        std::cout << "Jis x 0201 Full Width: " << _jis_x_0201_fullwidth << " --- updated: " << (bool)(_updatedFlags & JIS_X_0201_FULLWIDTH) << "\n";
        std::cout << "Jis x 0201 Half Width: " << _jis_x_0201_halfwidth << " --- updated: " << (bool)(_updatedFlags & JIS_X_0201_HALFWIDTH) << "\n";
        std::cout << "Shift Jis: " << _shiftJis << " --- updated: " << (bool)(_updatedFlags & SHIFTJIS) << "\n";
        std::cout << "Primary Format: " << _primaryFormat << "\n";
        std::cout << "\n\n\n\n";
    }

    static void PrintHexChars(const std::string& str)
    {
        std::string hex;

        for (int ch = 0; ch < str.size(); ++ch)
        {
            hex += "0x";
            int temp;

            for (int i = 0; i < 2; ++i)
            {
                if (i == 0)
                    temp = (str[ch] >> 4) & 0x0F;
                else
                    temp = str[ch] & 0x0F;

                if (temp < 0xA)
                    hex += 0x30 + temp;
                else
                    hex += 0x37 + temp;
            }

            if(ch < str.size() - 1)
                hex += ", ";
        }

        std::cout << hex << std::endl;
    }

    static void Test()
    {
        {
            std::cout << "Running Tests... ";

            std::string testStr = "Abcd123";
            MorphText test(testStr, UTF8);
            assert(MorphText::Compare(test.ToLower<std::string>(UTF8).c_str(), "abcd123", false, UTF8));
            assert(MorphText::Compare(test.ToUpper<std::string>(UTF8).c_str(), "ABCD123", false, UTF8));
            assert(MorphText::Compare(test.ToSarcasm<std::string>(UTF8).c_str(), "AbCd123", false, UTF8));
            test.SetUTF8("This is a UTF-8 Sample Text.");
            assert(test.Find(std::string("Sample"), true, UTF8) > -1);  //case sensitive
            assert(test.Find(std::string("sAMPLE"), false, UTF8) > -1); //case insensitive
            assert(test.Compare("This is a UTF-8 Sample Text.", true, UTF8));  //case sensitive
            assert(test.Compare("This Is A UTF-8 Sample Text.", false, UTF8)); //case insensitive

            std::wstring utf16L = Utf8_To_Utf16LE("ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니");
            std::wstring utf16R = L"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
            assert(MorphText::Compare(utf16L, utf16R, true, false));
            std::string utf8Comp = "ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
            std::string utf8 = MorphText::Utf16LE_To_Utf8(utf16L);
            assert(MorphText::Compare(utf8Comp, utf8));

            utf16L = Utf8_To_Utf16BE("ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니");
            for(wchar_t& ch : utf16R)
                swapBytes(&ch);
            assert(MorphText::Compare(utf16L, utf16R, true, true));
            utf8 = MorphText::Utf16BE_To_Utf8(utf16L);
            assert(MorphText::Compare(utf8Comp, utf8));

            std::u32string utf32L = Utf8_To_Utf32LE("ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니");
            std::u32string utf32R = U"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
            assert(MorphText::Compare(utf32L, utf32R, true, false));
            utf8 = MorphText::Utf32LE_To_Utf8(utf32L);
            assert(MorphText::Compare(utf8Comp, utf8));

            utf32L = Utf8_To_Utf32BE("ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니");
            for (char32_t& ch : utf32R)
                swapBytes(&ch);
            assert(MorphText::Compare(utf32L, utf32R, true, true));
            utf8 = MorphText::Utf32BE_To_Utf8(utf32L);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ASCII("some ascii lol,.--+!0123");
            std::vector<uint8_t> hexBin = { 0x73, 0x6F, 0x6D, 0x65, 0x20, 0x61, 0x73, 0x63, 0x69, 0x69, 0x20, 0x6C, 0x6F, 0x6C, 0x2C, 0x2E, 0x2D, 0x2D, 0x2B, 0x21, 0x30, 0x31, 0x32, 0x33, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ASCII));
            utf8Comp = "some ascii lol,.--+!0123";
            utf8 = MorphText::ASCII_To_Utf8(testStr);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test äöüÄÖü", ISO_8859_1);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE4, 0xF6, 0xFC, 0xC4, 0xD6, 0xFC, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_1));
            utf8Comp = "test äöüÄÖü";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_1);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ŔÂĂÄĹĆÇ", ISO_8859_2);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xC0, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_2));
            utf8Comp = "test ŔÂĂÄĹĆÇ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_2);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test çèéêëìíîï", ISO_8859_3);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_3));
            utf8Comp = "test çèéêëìíîï";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_3);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ŠĒĢŦ", ISO_8859_4);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xA9, 0xAA, 0xAB, 0xAC, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_4));
            utf8Comp = "test ŠĒĢŦ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_4);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ежз", ISO_8859_5);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD5, 0xD6, 0xD7, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_5));
            utf8Comp = "test ежз";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_5);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test سشصض", ISO_8859_6);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_6));
            utf8Comp = "test سشصض";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_6);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ΦΧΨΩΪ", ISO_8859_7);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_7));
            utf8Comp = "test ΦΧΨΩΪ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_7);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test דהוזחטי", ISO_8859_8);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_8));
            utf8Comp = "test דהוזחטי";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_8);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test åæçèéê", ISO_8859_9);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_9));
            utf8Comp = "test åæçèéê";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_9);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test åæįčé", ISO_8859_10);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_10));
            utf8Comp = "test åæįčé";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_10);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ฃคฅฆ", ISO_8859_11);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xA3, 0xA4, 0xA5, 0xA6, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_11));
            utf8Comp = "test ฃคฅฆ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_11);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ÕÖ×ŲŁŚ", ISO_8859_13);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_13));
            utf8Comp = "test ÕÖ×ŲŁŚ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_13);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ÔÕÖṪØÙ", ISO_8859_14);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_14));
            utf8Comp = "test ÔÕÖṪØÙ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_14);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ÅÆÇÈÉÊËÌ", ISO_8859_15);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_15));
            utf8Comp = "test ÅÆÇÈÉÊËÌ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_15);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = Utf8_To_ISO8859X("test ÄĆ6ÆÇÈÉ", ISO_8859_16);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xC4, 0xC5, 0x36, 0xC6, 0xC7, 0xC8, 0xC9, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_16));
            utf8Comp = "test ÄĆ6ÆÇÈÉ";
            utf8 = MorphText::ISO8859X_To_Utf8(testStr, ISO_8859_16);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = MorphText::Utf8_To_ShiftJis("ooyamaneko ｵｵﾔﾏﾈｺ　オオヤマネコ　おおやまねこ　大山猫");
            hexBin = { 0x6F, 0x6F, 0x79, 0x61, 0x6D, 0x61, 0x6E, 0x65, 0x6B, 0x6F, 0x20, 0xB5, 0xB5, 0xD4, 0xCF, 0xC8, 0xBA, 0x81, 0x40, 0x83, 
                       0x49, 0x83, 0x49, 0x83, 0x84, 0x83, 0x7D, 0x83, 0x6C, 0x83, 0x52, 0x81, 0x40, 0x82, 0xA8, 0x82, 0xA8, 0x82, 0xE2, 0x82,
                       0xDC, 0x82, 0xCB, 0x82, 0xB1, 0x81, 0x40, 0x91, 0xE5, 0x8E, 0x52, 0x94, 0x4C, 0x00 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, SHIFTJIS));
            utf8Comp = "ooyamaneko ｵｵﾔﾏﾈｺ　オオヤマネコ　おおやまねこ　大山猫";
            utf8 = MorphText::ShiftJis_To_Utf8(testStr);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = MorphText::Utf8_To_JIS_X_0201_FullWidth("オオヤマネコ　ABCD abcd");
            hexBin = { 0xB5, 0xB5, 0xD4, 0xCF, 0xC8, 0xBA, 0x20, 0x41, 0x42, 0x43, 0x44, 0x20, 0x61, 0x62, 0x63, 0x64 };
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, JIS_X_0201_FULLWIDTH));
            utf8Comp = "オオヤマネコ ABCD abcd";
            utf8 = MorphText::JIS_X_0201_FullWidth_To_Utf8(testStr);
            assert(MorphText::Compare(utf8Comp, utf8));

            testStr = MorphText::Utf8_To_JIS_X_0201_HalfWidth("ｵｵﾔﾏﾈｺ　ABCD abcd");
            assert(MorphText::Compare(testStr.c_str(), (char*)hexBin.data(), true, JIS_X_0201_HALFWIDTH));
            utf8Comp = "ｵｵﾔﾏﾈｺ ABCD abcd";
            utf8 = MorphText::JIS_X_0201_HalfWidth_To_Utf8(testStr);
            assert(MorphText::Compare(utf8Comp, utf8));

            std::wstring ksx = MorphText::Utf8_To_KSX1001("스라소니", true);
            std::wstring whexBin(4, L'\0'); 
            whexBin = {0xBDBA, 0xB6F3, 0xBCD2, 0xB4CF};
            assert(MorphText::Compare(ksx, whexBin, true, KS_X_1001));
            utf8Comp = "스라소니";
            utf8 = MorphText::KSX1001_To_Utf8(ksx);
            assert(MorphText::Compare(utf8Comp, utf8));

            std::cout << "PASS\n";
        }
    }
#endif
};