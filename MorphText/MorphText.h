#pragma once
#include <algorithm>
#include <assert.h>
#include <codecvt>
#include <cstdint>
#include <cwctype>
#include <iostream>
#include <locale>
#include "Lookup.h"
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

template <typename T> concept AllowedStringType =
    std::is_same_v<std::remove_cvref_t<T>, std::string>
    || std::is_same_v<std::remove_cvref_t<T>, std::wstring>
    || std::is_same_v<std::remove_cvref_t<T>, std::u32string>
    || std::is_same_v<std::remove_cvref_t<T>, const std::string>
    || std::is_same_v<std::remove_cvref_t<T>, const std::wstring>
    || std::is_same_v<std::remove_cvref_t<T>, const std::u32string>
    || std::is_same_v<std::remove_cvref_t<T>, char*>
    || std::is_same_v<std::remove_cvref_t<T>, wchar_t*>
    || std::is_same_v<std::remove_cvref_t<T>, char32_t*>
    || std::is_same_v<std::remove_cvref_t<T>, const char*>
    || std::is_same_v<std::remove_cvref_t<T>, const wchar_t*>
    || std::is_same_v<std::remove_cvref_t<T>, const char32_t*>;

template <typename T> concept AllowedStdStringType =
       std::is_same_v<std::remove_cvref_t<T>, const std::string>
    || std::is_same_v<std::remove_cvref_t<T>, const std::wstring>
    || std::is_same_v<std::remove_cvref_t<T>, const std::u32string>
    || std::is_same_v<std::remove_cvref_t<T>, std::string>
    || std::is_same_v<std::remove_cvref_t<T>, std::wstring>
    || std::is_same_v<std::remove_cvref_t<T>, std::u32string>;

template <typename T> concept AllowedCStringType =
       std::is_same_v<std::remove_cvref_t<T>, char*>
    || std::is_same_v<std::remove_cvref_t<T>, wchar_t*>
    || std::is_same_v<std::remove_cvref_t<T>, char32_t*>
    || std::is_same_v<std::remove_cvref_t<T>, const char*>
    || std::is_same_v<std::remove_cvref_t<T>, const wchar_t*>
    || std::is_same_v<std::remove_cvref_t<T>, const char32_t*>;

class MorphText
{
public:
    enum Encodings
    {
        PRIMARY,
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
        SHIFTJIS_CP932,
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
        CP932 = SHIFTJIS_CP932,
        SHIFT_JIS_CP932 = SHIFTJIS_CP932,
        SJIS932 = SHIFTJIS_CP932,
        MS932 = SHIFTJIS_CP932,
        EUC_KR = KS_X_1001,
        KS_C_5601 = KS_X_1001
    };

    MorphText() = default;
    MorphText(const std::string& str, const int encoding = UTF8);
    MorphText(const std::wstring& str, const int encoding = UTF16LE);
    MorphText(const std::u32string& str, const int encoding = UTF32LE);
    MorphText(const char* charStr, const int encoding = UTF8);
    MorphText(const wchar_t* charStr, const int encoding = UTF16LE);
    MorphText(const char32_t* charStr, const int encoding = UTF32LE);
    MorphText(char* charStr, const int encoding = UTF8);
    MorphText(wchar_t* charStr, const int encoding = UTF16LE);
    MorphText(char32_t* charStr, const int encoding = UTF32LE);
    MorphText(const MorphText& other);
    ~MorphText() = default;

    /// <summary>
    /// Converts the input string of a certain encoding to a string of another encoding
    /// </summary>
    /// <typeparam name="inT">Input string type</typeparam>
    /// <typeparam name="outT">Output string type</typeparam>
    /// <param name="input">Input string to be converted</param>
    /// <param name="inputEncoding">Encoding identifier of the input string</param>
    /// <param name="outputEncoding">Encoding identifier of the output string</param>
    /// <returns>String of type outT encoded as outputEncoding</returns>
    template<AllowedStringType inT, AllowedStringType outT> static outT Convert(inT input, const int inputEncoding = UTF8, const int outputEncoding = UTF8)
    {
        std::string utf8 = convertToUTF8<inT>(input, inputEncoding);
        return convertFromUTF8<outT>(utf8, outputEncoding);
    }

    template <AllowedStringType inT, AllowedStdStringType outT> static outT Convert(...)
    {
        static_assert(AllowedStringType<inT>, "Error: Specified type inT of Convert<inT, outT>() must be one of the following types: std::string, std::wstring, std::u32string, const char*, const wchar_t*, const char32_t*, char*, wchar_t, or char32_t*.");
        static_assert(AllowedStdStringType<outT>, "Error: Specified type outT of Convert<inT, outT>() must be one of the following types: std::string, std::wstring, std::u32string.");
        return outT{};
    }

    /// <summary>
    /// Returns the passed string all lowercase.
    /// </summary>
    /// <param name="input">Input string</param>
    /// <param name="encoding">Encoding identifier of the input string</param>
    /// <returns>Output string with all letters lowercase</returns>
    static std::string ToLower(const std::string& input, const int encoding = UTF8);
    static std::wstring ToLower(const std::wstring& input, const int encoding = UTF16LE);
    static std::u32string ToLower(const std::u32string& input, const int encoding = UTF32LE);
    //static char* ToLower(const char* input, const int encoding = UTF8);
    static wchar_t* ToLower(const wchar_t* input, const int encoding = UTF16LE);
    static char32_t* ToLower(const char32_t* input, const int encoding = UTF32LE);

    /// <summary>
    /// Returns the instance's string all lowercase.
    /// <typeparam name="T">Output string type</typeparam>
    /// <param name="encoding">Encoding Identifier of the string to be returned</param>
    /// <returns>String of type T encoded as <i>encoding</i> all lowercase</returns>
    template<AllowedStdStringType T> T ToLower(const int encoding = UTF8)
    {
        m_convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToLower(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (encoding)
            {
            case UTF16BE:
                m_utf8ToUtf16Be();
                return ToLower(_utf16BE, true);
            default:
                m_utf8ToUtf16le();
                return ToLower(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (encoding == UTF32BE)
            {
                m_utf8ToUtf32Be();
                return ToLower(_utf32BE, true);
            }

            m_utf8ToUtf32Le();
            return ToLower(_utf32LE, false);
        }
        else
        {
            switch (encoding)
            {
                case ASCII: {
                    m_utf8ToAscii();
                    return ToLower(_ascii, ASCII);
                }
                case JIS_X_0201_FULLWIDTH: {
                    m_utf8ToJisX0201FW();
                    return ToLower(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
                }
                case JIS_X_0201_HALFWIDTH: {
                    m_utf8ToJisX0201HW();
                    return ToLower(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
                }
                case SHIFTJIS_CP932: {
                    m_utf8ToShiftJis();
                    return ToLower(_shiftJis_cp932, SHIFTJIS_CP932);
                }
                case KS_X_1001:
                    m_utf8ToKsX1001();
                    return ToLower(_ks_x_1001, false, KS_X_1001);
                default: { //ISO 8859-X
                    m_utf8ToIso8859x();
                    return ToLower(_ascii, ASCII);
                }
            }
        }
    }

    /// <summary>
    /// Returns the passed string all uppercase.
    /// </summary>
    /// <param name="input">Input string</param>
    /// <param name="encoding">Encoding identifier of the input string</param>
    /// <returns>Output string with all letters uppercase</returns>
    static std::string ToUpper(const std::string& input, const int encoding = UTF8);
    static std::wstring ToUpper(const std::wstring& input, const int encoding = UTF16LE);
    static std::u32string ToUpper(const std::u32string& input, const int encoding = UTF32LE);
    //static char* ToUpper(const char* input, const int encoding = UTF8);
    static wchar_t* ToUpper(const wchar_t* input, const int encoding = UTF16LE);
    static char32_t* ToUpper(const char32_t* input, const int encoding = UTF32LE);

    /// <summary>
    /// Returns the instance's string all uppercase.
    /// <typeparam name="T">Output string type</typeparam>
    /// <param name="encoding">Encoding identifier of the string to be returned</param>
    /// <returns>String of type T encoded as <i>encoding</i> all uppercase</returns>
    template<AllowedStdStringType T> T ToUpper(const int encoding = UTF8)
    {
        m_convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToUpper(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (encoding)
            {
            case UTF16BE:
                m_utf8ToUtf16Be();
                return ToUpper(_utf16BE, true);
            default:// UTF16LE
                m_utf8ToUtf16le();
                return ToUpper(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (encoding == UTF32BE)
            {
                m_utf8ToUtf32Be();
                return ToUpper(_utf32BE, true);
            }

            m_utf8ToUtf32Le();
            return ToUpper(_utf32LE, false);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (encoding)
            {
                case ASCII: {
                    m_utf8ToAscii();
                    return ToUpper(_ascii, ASCII);
                } break;
                case JIS_X_0201_FULLWIDTH: {
                    m_utf8ToJisX0201FW();
                    return ToUpper(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
                }
                case JIS_X_0201_HALFWIDTH: {
                    m_utf8ToJisX0201HW();
                    return ToUpper(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
                }
                case SHIFTJIS_CP932: {
                    m_utf8ToShiftJis();
                    return ToUpper(_shiftJis_cp932, SHIFTJIS_CP932);
                }
                case KS_X_1001:
                    m_utf8ToKsX1001();
                    return ToUpper(_ks_x_1001, false, KS_X_1001);
                default: { //ISO 8859-X
                    m_utf8ToIso8859x();
                    return ToUpper(_ascii, ASCII);
                }
            }
        }
    }

    /// <summary>
    /// Returns the passed string with sarcastic energy.
    /// </summary>
    /// <param name="input">Input string</param>
    /// <param name="encoding">Encoding identifier of the input string</param>
    /// <returns>Output string with sarcastic energy</returns>
    static std::string ToSarcasm(const std::string& input, const int encoding = UTF8);
    static std::wstring ToSarcasm(const std::wstring& input, const int encoding = UTF16LE);
    static std::u32string ToSarcasm(const std::u32string& input, const int encoding = UTF16LE);
    //static char* ToSarcasm(const char* input, const int encoding = UTF8);
    static wchar_t* ToSarcasm(const wchar_t* input, const int encoding = UTF16LE);
    static char32_t* ToSarcasm(const char32_t* input, const int encoding = UTF16LE);

    /// <summary>
    /// Returns the instance's string with sarcastic energy.
    /// <typeparam name="T">Output string type</typeparam>
    /// <param name="encoding">Encoding identifier of the string to be returned</param>
    /// <returns>String of type T encoded as <i>encoding</i> with sarcastic energy.</returns>
    template<AllowedStdStringType T> T ToSarcasm(const int encoding = UTF8)
    {
        m_convertToUtf8();

        if constexpr (std::is_same_v<T, std::string>)
        {
            return ToSarcasm(_utf8);
        }
        else if constexpr (std::is_same_v<T, std::wstring>)
        {
            switch (encoding)
            {
                case UTF16BE:
                    m_utf8ToUtf16Be();
                    return ToSarcasm(_utf16BE, true);
                default:// UTF16LE
                    m_utf8ToUtf16le();
                    return ToSarcasm(_utf16LE, false);
            }
        }
        else if constexpr (std::is_same_v<T, std::u32string>)
        {
            if (encoding == UTF32BE)
            {
                m_utf8ToUtf32Be();
                return ToSarcasm(_utf32BE, true);
            }

            m_utf8ToUtf32Le();
            return ToSarcasm(_utf32LE, false);
        }
        else // ASCII, ANSI, Shift Jist, ...
        {
            switch (encoding)
            {
                case SHIFTJIS_CP932: {
                    m_utf8ToShiftJis();
                    return ToSarcasm(_shiftJis_cp932, SHIFTJIS_CP932);
                }
                case KS_X_1001:
                    m_utf8ToKsX1001();
                    return ToSarcasm(_ks_x_1001, false, KS_X_1001);
                case JIS_X_0201_FULLWIDTH: {
                    m_utf8ToJisX0201FW();
                    return ToSarcasm(_jis_x_0201_fullwidth, JIS_X_0201_FULLWIDTH);
                }
                case JIS_X_0201_HALFWIDTH: {
                    m_utf8ToJisX0201HW();
                    return ToSarcasm(_jis_x_0201_halfwidth, JIS_X_0201_HALFWIDTH);
                }
                default: { //ASCII
                    utf8ToAscii();
                    return ToSarcasm(_ascii, ASCII);
                }
            }
        }
    }

    /// <summary>
    /// Compares two input strings for equality.
    /// </summary>
    /// <param name="lhs">Left-hand input string</param>
    /// <param name="rhs">Right-hand input string</param>
    /// <param name="caseSensitive">Whether to consider case sensitivity</param>
    /// <param name="encoding">Encoding identifier of the input strings.</param>
    /// <returns>true if both input strings match, otherwise false</returns>
    static bool Compare(const std::string& lhs, const std::string& rhs, const bool caseSensitive = true, const int encoding = UTF8);
    static bool Compare(const std::wstring& lhs, const std::wstring& rhs, const bool caseSensitive = true, const int encoding = UTF16LE);
    static bool Compare(const std::u32string& lhs, const std::u32string& rhs, const bool caseSensitive = true, const int encoding = UTF32LE);
    static bool Compare(const char* lhs, const char* rhs, const bool caseSensitive = true, const int encoding = UTF8);
    static bool Compare(const wchar_t* lhs, const wchar_t* rhs, const bool caseSensitive = true, const int encoding = UTF16LE);
    static bool Compare(const char32_t* lhs, const char32_t* rhs, const bool caseSensitive = true, const int encoding = UTF32LE);
    
    /// <summary>
    /// Compares an input strings for equality against the instance.
    /// </summary>
    /// <param name="rhs">String to compare against</param>
    /// <param name="caseSensitive"Whether to consider case sensitivity></param>
    /// <param name="encoding">Encoding identifier of the input string.</param>
    /// <returns></returns>
    bool Compare(const std::string& rhs, const bool caseSensitive = true, const int encoding = UTF8);
    bool Compare(const std::wstring& rhs, const bool caseSensitive = true, const int encoding = UTF16LE);
    bool Compare(const std::u32string& rhs, const bool caseSensitive = true, const int encoding = UTF32LE);
    bool Compare(const char* rhs, const bool caseSensitive = true, const int encoding = UTF8);
    bool Compare(const wchar_t* rhs, const bool caseSensitive = true, const int encoding = UTF16LE);
    bool Compare(const char32_t* rhs, const bool caseSensitive = true, const int encoding = UTF32BE);

    /// <summary>
    /// Searches for the first occurence of a subset string within a superset string.
    /// </summary>
    /// <param name="superset">String that may contain the subset string.</param>
    /// <param name="subset">String to be searched for within the superset string.</param>
    /// <param name="encoding">Encoding identifier of the strings.</param>
    /// <param name="caseSensitive">Whether to consider case sensitivity.</param>
    /// <returns>Position of the subset string's first occurence withing the superset string. Returns -1 if not found, 0 if subset is empty.</returns>
    static int Find(const std::string& superset, const std::string& subset, const bool caseSensitive = true, const int encoding = UTF8);
    static int Find(const std::wstring& superset, const std::wstring& subset, const bool caseSensitive = true, const int encoding = UTF16LE);
    static int Find(const std::u32string& superset, const std::u32string& subset, const bool caseSensitive = true, const int encoding = UTF32LE);
    
    /// <summary>
    /// Searches for the first occurence of a subset string within the instance.
    /// </summary>
    /// <param name="subset">String to be searched for within the instance.</param>
    /// <param name="caseSensitive">Whether to consider case sensitivity.</param>
    /// <param name="encoding">Encoding identifier of the substring.</param>
    /// <returns>Position of the subset string's first occurence withing the instance. Returns -1 if not found, 0 if subset is empty.</returns>
    int Find(const std::string& subset, const bool caseSensitive = true, const int encoding = UTF8);
    int Find(const std::wstring& subset, const bool caseSensitive = true, const int encoding = UTF16LE);
    int Find(const std::u32string& subset, const bool caseSensitive = true, const int encoding = UTF32LE);
    int Find(const char* subset, const bool caseSensitive = true, const int encoding = UTF8) const;

    /// <summary>
    /// Returns the string of the specified encoding identifier and type.
    /// </summary>
    /// <typeparam name="T">Return type.</typeparam>
    /// <param name="encoding">Encoding identifiew:</param>
    /// <returns>The string of the specified format of type T</returns>
    /// <note> It is possible to return mismatched types like UTF-8 as std::wstring. Do this only if you really know what you're doing. Any other unsupported types will thorw an error.</note>
    template<AllowedStringType T> T GetString(const int encoding = PRIMARY)
    {
        switch (encoding)
        {
            case UTF8:
            {
                if (!(_updatedFlags & FLAG_UTF8))
                    m_convertToUtf8();

                return passString<std::string, T>(_utf8);
            }
            case UTF16LE:
            {
                if (!(_updatedFlags & FLAG_UTF16LE))
                    m_utf8ToUtf16le();

                return passString<std::wstring, T>(_utf16LE);
            }
            case UTF16BE:
            {
                if (!(_updatedFlags & FLAG_UTF16BE))
                    m_utf8ToUtf16Be();

                return passString<std::wstring, T>(_utf16BE);
            }
            case UTF32LE:
            {
                if (!(_updatedFlags & FLAG_UTF32LE))
                    m_utf8ToUtf32Le();

                return passString<std::u32string, T>(_utf32LE);
            }
            case UTF32BE:
            {
                if (!(_updatedFlags & FLAG_UTF32BE))
                    m_utf8ToUtf32Be();

                return passString<std::u32string, T>(_utf32BE);
            }
            case ASCII:
            {
                if (!(_updatedFlags & FLAG_ASCII))
                    m_utf8ToAscii();

                return passString<std::string, T>(_ascii);
            }
            case ISO_8859_1:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_1))
                    m_utf8ToIso8859x(FLAG_ISO_8859_1);

                return passString<std::string, T>(_iso_8859_1);
            }
            case ISO_8859_2:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_2))
                    m_utf8ToIso8859x(FLAG_ISO_8859_2);

                return passString<std::string, T>(_iso_8859_2);
            }
            case ISO_8859_3:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_3))
                    m_utf8ToIso8859x(FLAG_ISO_8859_3);

                return passString<std::string, T>(_iso_8859_3);
            }
            case ISO_8859_4:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_4))
                    m_utf8ToIso8859x(FLAG_ISO_8859_4);

                return passString<std::string, T>(_iso_8859_4);
            }
            case ISO_8859_5:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_5))
                    m_utf8ToIso8859x(FLAG_ISO_8859_5);

                return passString<std::string, T>(_iso_8859_5);
            }
            case ISO_8859_6:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_6))
                    m_utf8ToIso8859x(FLAG_ISO_8859_6);

                return passString<std::string, T>(_iso_8859_6);
            }
            case ISO_8859_7:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_7))
                    m_utf8ToIso8859x(FLAG_ISO_8859_7);

                return passString<std::string, T>(_iso_8859_7);
            }
            case ISO_8859_8:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_8))
                    m_utf8ToIso8859x(FLAG_ISO_8859_8);

                return passString<std::string, T>(_iso_8859_8);
            }
            case ISO_8859_9:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_9))
                    m_utf8ToIso8859x(FLAG_ISO_8859_9);

                return passString<std::string, T>(_iso_8859_9);
            }
            case ISO_8859_10:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_10))
                    m_utf8ToIso8859x(FLAG_ISO_8859_10);

                return passString<std::string, T>(_iso_8859_10);
            }
            case ISO_8859_11:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_11))
                    m_utf8ToIso8859x(FLAG_ISO_8859_11);

                return passString<std::string, T>(_iso_8859_11);
            }
            case ISO_8859_13:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_13))
                    m_utf8ToIso8859x(FLAG_ISO_8859_13);

                return passString<std::string, T>(_iso_8859_13);
            }
            case ISO_8859_14:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_14))
                    m_utf8ToIso8859x(FLAG_ISO_8859_14);

                return passString<std::string, T>(_iso_8859_14);
            }
            case ISO_8859_15:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_15))
                    m_utf8ToIso8859x(FLAG_ISO_8859_15);

                return passString<std::string, T>(_iso_8859_15);
            }
            case ISO_8859_16:
            {
                if (!(_updatedFlags & FLAG_ISO_8859_16))
                    m_utf8ToIso8859x(FLAG_ISO_8859_16);

                return passString<std::string, T>(_iso_8859_16);
            }
            case SHIFTJIS_CP932:
            {
                if (!(_updatedFlags & FLAG_SHIFTJIS_CP932))
                    m_utf8ToShiftJis();

                return passString<std::string, T>(_shiftJis_cp932);
            }
            case JIS_X_0201_FULLWIDTH:
            {
                if (!(_updatedFlags & FLAG_JIS_X_0201_FULLWIDTH))
                    m_utf8ToJisX0201FW();

                return passString<std::string, T>(_jis_x_0201_fullwidth);
            }
            case JIS_X_0201_HALFWIDTH:
            {
                if (!(_updatedFlags & FLAG_JIS_X_0201_HALFWIDTH))
                    m_utf8ToJisX0201HW();

                return passString<std::string, T>(_jis_x_0201_halfwidth);
            }
            case KS_X_1001:
            {
                if (!(_updatedFlags & FLAG_KS_X_1001))
                    m_utf8ToKsX1001();

                return passString<std::string, T>(_ks_x_1001);
            }
            default: //PRIMARY
            {
                if (_primaryEncoding)
                    return GetString<T>(encoding);
                else
                    return GetString<T>(UTF8);
            }
        }
    }

    template <typename T> T GetString(...)
    {
        static_assert(AllowedStringType<T>, "Error: Specified type T of PassString<T>() must be one of the following types: std::string, std::wstring, std::u32string, char*, wchar_t*, char32_t*, const char*, const wchar_t*, or const char32_t*.");
        return T{};
    }

    /// <summary>
    /// Returns the primary encoding identifier.
    /// </summary>
    /// <returns>Primary encoding identifier</returns>
    int GetPrimaryFormat() const;

    /// <summary>
    /// Set current string.
    /// </summary>
    /// <typeparam name="T">String data type.</typeparam>
    /// <param name="input">Input string</param>
    /// <param name="encoding">Encoding identifier</param>
    template<AllowedStdStringType T> void SetString(T& input, const int encoding = PRIMARY)
    {
        SetString(input.c_str(), encoding);
    }

    template<AllowedCStringType T> void SetString(T input, const int encoding = PRIMARY)
    {
        switch (encoding)
        {
            case UTF8:
            {
                _utf8 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_UTF8;
            } break;
            case UTF16LE:
            {
                _utf16LE = reinterpret_cast<const wchar_t*>(input);
                _updatedFlags = FLAG_UTF16LE;
            } break;
            case UTF16BE:
            {
                _utf16BE = reinterpret_cast<const wchar_t*>(input);
                _updatedFlags = FLAG_UTF16BE;
            } break;
            case UTF32LE:
            {
                _utf32LE = reinterpret_cast<const char32_t*>(input);
                _updatedFlags = FLAG_UTF32LE;
            } break;
            case UTF32BE:
            {
                _utf32BE = reinterpret_cast<const char32_t*>(input);
                _updatedFlags = FLAG_UTF32BE;
            } break;
            case ASCII:
            {
                _ascii = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ASCII;
            } break;
            case ISO_8859_1:
            {
                _iso_8859_1 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_1;
            } break;
            case ISO_8859_2:
            {
                _iso_8859_2 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_2;
            } break;
            case ISO_8859_3:
            {
                _iso_8859_3 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_3;
            } break;
            case ISO_8859_4:
            {
                _iso_8859_4 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_4;
            } break;
            case ISO_8859_5:
            {
                _iso_8859_5 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_5;
            } break;
            case ISO_8859_6:
            {
                _iso_8859_6 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_6;
            } break;
            case ISO_8859_7:
            {
                _iso_8859_7 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_7;
            } break;
            case ISO_8859_8:
            {
                _iso_8859_8 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_8;
            } break;
            case ISO_8859_9:
            {
                _iso_8859_9 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_9;
            } break;
            case ISO_8859_10:
            {
                _iso_8859_10 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_10;
            } break;
            case ISO_8859_11:
            {
                _iso_8859_11 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_11;
            } break;
            case ISO_8859_13:
            {
                _iso_8859_13 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_13;
            } break;
            case ISO_8859_14:
            {
                _iso_8859_14 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_14;
            } break;
            case ISO_8859_15:
            {
                _iso_8859_15 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_15;
            } break;
            case ISO_8859_16:
            {
                _iso_8859_16 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_ISO_8859_16;
            } break;
            case SHIFTJIS_CP932:
            {
                _shiftJis_cp932 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_SHIFTJIS_CP932;
            } break;
            case JIS_X_0201_FULLWIDTH:
            {
                _jis_x_0201_fullwidth = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_JIS_X_0201_FULLWIDTH;
            } break;
            case JIS_X_0201_HALFWIDTH:
            {
                _jis_x_0201_halfwidth = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_JIS_X_0201_HALFWIDTH;
            } break;
            case KS_X_1001:
            {
                _ks_x_1001 = reinterpret_cast<const char*>(input);
                _updatedFlags = FLAG_KS_X_1001;
            } break;
            default: //PRIMARY
            {
                if (_primaryEncoding)
                    SetString(input, encoding);
                else
                    SetString(input, UTF8);
            }
        }
    }

    template <typename T> T SetString(...)
    {
        static_assert(AllowedStringType<T>, "Error: Specified type T of SetString<T>() must be one of the following types: std::string, std::wstring, std::u32string, char*, wchar_t*, char32_t*, const char*, const wchar_t*, or const char32_t*.");
        return T{};
    }

    /// <summary>
    /// Sets the primary encoding. This is useful if other parts of your code don't which encoding to output.
    /// <param><c>int encoding</c>: ISO-8859 encoding.</param>
    /// </summary>
    void SetPrimaryEncoding(const int encoding);

    /// <summary>
    /// Sets the left-hand instance to a <b>copie</b> of the right-hand instance
    /// </summary>
    void operator = (const MorphText& other);

#ifndef NDEBUG
    void Print();
    static void Test();
#endif

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
    std::string _shiftJis_cp932;
    std::string _jis_x_0201_halfwidth;
    std::string _jis_x_0201_fullwidth;
    std::string _ks_x_1001;
    int _updatedFlags = 0;
    int _primaryEncoding = UTF8;

    enum Flags
    {
        FLAG_UTF8 = 1 << Encodings::UTF8,
        FLAG_UTF16LE = 1 << Encodings::UTF16LE,
        FLAG_UTF16BE = 1 << Encodings::UTF16BE,
        FLAG_UTF32LE = 1 << Encodings::UTF32LE,
        FLAG_UTF32BE = 1 << Encodings::UTF32BE,
        FLAG_ASCII = 1 << Encodings::ASCII,
        FLAG_ISO_8859_1 = 1 << Encodings::ISO_8859_1,
        FLAG_ISO_8859_2 = 1 << Encodings::ISO_8859_2,
        FLAG_ISO_8859_3 = 1 << Encodings::ISO_8859_3,
        FLAG_ISO_8859_4 = 1 << Encodings::ISO_8859_4,
        FLAG_ISO_8859_5 = 1 << Encodings::ISO_8859_5,
        FLAG_ISO_8859_6 = 1 << Encodings::ISO_8859_6,
        FLAG_ISO_8859_7 = 1 << Encodings::ISO_8859_7,
        FLAG_ISO_8859_8 = 1 << Encodings::ISO_8859_8,
        FLAG_ISO_8859_9 = 1 << Encodings::ISO_8859_9,
        FLAG_ISO_8859_10 = 1 << Encodings::ISO_8859_10,
        FLAG_ISO_8859_11 = 1 << Encodings::ISO_8859_11,
        FLAG_ISO_8859_13 = 1 << Encodings::ISO_8859_13,
        FLAG_ISO_8859_14 = 1 << Encodings::ISO_8859_14,
        FLAG_ISO_8859_15 = 1 << Encodings::ISO_8859_15,
        FLAG_ISO_8859_16 = 1 << Encodings::ISO_8859_16,
        FLAG_SHIFTJIS_CP932 = 1 << Encodings::SHIFTJIS_CP932,
        FLAG_JIS_X_0201_FULLWIDTH = 1 << Encodings::JIS_X_0201_FULLWIDTH,
        FLAG_JIS_X_0201_HALFWIDTH = 1 << Encodings::JIS_X_0201_HALFWIDTH,
        FLAG_KS_X_1001 = 1 << Encodings::KS_X_1001,
        FLAG_Reserved = 1 << Encodings::Reserved
    };

    //Convertion functions
    static std::string utf8ToAscii(const std::string& input);
    static std::string asciiToUtf8(const std::string input, const int32_t maxLength = -1);
    static std::wstring utf8ToUtf16le(const std::string& input);
    static std::string utf16leToUtf8(const std::wstring& input);
    static std::wstring utf8ToUtf16be(const std::string& input);
    static std::string utf16beToUtf8(const std::wstring& input);
    static std::u32string utf8ToUtf32le(const std::string& input);
    static std::string utf32leToUtf8(const std::u32string& input);
    static std::u32string utf8ToUtf32be(const std::string& input);
    static std::string utf32beToUtf8(const std::u32string& input);
    static std::string utf8ToIso8859x(const std::string& input, const int encoding = ISO_8859_1);
    static std::string iso8859xToUtf8(const std::string input, const int encoding = ISO_8859_1);
    static std::string shiftjisToUtf8(const std::string& input);
    static std::string utf8ToShiftjis(const std::string& input);
    static std::string utf8ToJisx0201fullwidth(const std::string& input);
    static std::string jisx0201fullwidthToUtf8(const std::string& input);
    static std::string utf8ToJisx0201halfwidth(const std::string input);
    static std::string jisx0201halfwidthToUtf8(const std::string& input);
    static std::string utf8ToKsx1001(const std::string& input);
    static std::string ksx1001ToUtf8(const std::string& input);
    static std::string convertFromUtf8_singleByte(std::string& input, const int encoding = PRIMARY);
    static std::wstring convertFromUtf8_doubleByte(std::string& input, const int encoding = PRIMARY);
    static std::u32string convertFromUtf8_quatrupleByte(std::string& input, const int encoding = PRIMARY);

    template<typename T> static T convertFromUTF8(std::string input, const int encoding = PRIMARY)
    {
        if constexpr (std::is_same_v<T, std::string>)
            return convertFromUtf8_singleByte(input, encoding);
        if constexpr (std::is_same_v<T, std::wstring>)
            return convertFromUtf8_doubleByte(input, encoding);
        if constexpr (std::is_same_v<T, std::u32string>)
            return convertFromUtf8_quatrupleByte(input, encoding);
    }

    template<AllowedStdStringType T> static std::string convertToUTF8(T input, const int encoding = UTF8)
    {
        switch (encoding)
        {
            case ASCII:
                return asciiToUtf8(std::string(reinterpret_cast<const char*>(input.c_str())));
            case UTF16LE:
                return utf16leToUtf8(std::wstring(reinterpret_cast<const wchar_t*>(input.c_str())));
            case UTF16BE:
                return utf16beToUtf8(std::wstring(reinterpret_cast<const wchar_t*>(input.c_str())));
            case UTF32LE:
                return utf32leToUtf8(std::u32string(reinterpret_cast<const char32_t*>(input.c_str())));
            case UTF32BE:
                return utf32beToUtf8(std::u32string(reinterpret_cast<const char32_t*>(input.c_str())));
            case ISO_8859_1: case ISO_8859_2: case ISO_8859_3: case ISO_8859_4:
            case ISO_8859_5: case ISO_8859_6: case ISO_8859_7: case ISO_8859_8:
            case ISO_8859_9: case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
            case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
                return iso8859xToUtf8(std::string(reinterpret_cast<const char*>(input.c_str())), encoding);
            case SHIFTJIS_CP932:
                return shiftjisToUtf8(reinterpret_cast<const char*>(input.c_str()));
            case JIS_X_0201_FULLWIDTH:
                return jisx0201fullwidthToUtf8(reinterpret_cast<const char*>(input.c_str()));
            case JIS_X_0201_HALFWIDTH:
                return jisx0201halfwidthToUtf8(reinterpret_cast<const char*>(input.c_str()));
            case KS_X_1001:
                return ksx1001ToUtf8(reinterpret_cast<const char*>(input.c_str()));
            default: //UTF8 or invalid format value
            {
                return std::string(reinterpret_cast<const char*>(input.c_str()));
            }
        }
    }

    template<AllowedCStringType T> static std::string convertToUTF8(T input, const int encoding = UTF8)
    {
        if constexpr (std::is_same_v<T, char*> || std::is_same_v<T, const char*>)
            return convertFromUTF8<std::string>(input, encoding);
        if constexpr (std::is_same_v<T, wchar_t*> || std::is_same_v<T, const wchar_t*>)
            return convertFromUTF8<std::wstring>(input, encoding);
        if constexpr (std::is_same_v<T, char32_t*> || std::is_same_v<T, const char32_t*>)
            return convertFromUTF8<std::u32string>(input, encoding);
    }

    //member-modifying conversion functions
    void m_convertToUtf8();
    void m_jisX0201FWToUtf8();
    void m_utf8ToJisX0201FW();
    void m_jisX0201HWToUtf8();
    void m_utf8ToJisX0201HW();
    void m_utf16LeToUtf8();
    void m_utf8ToUtf16le();
    void m_utf16BeToUtf8();
    void m_utf8ToUtf16Be();
    void m_utf32LeToUtf8();
    void m_utf8ToUtf32Le();
    void m_utf32BeToUtf8();
    void m_utf8ToUtf32Be();
    void m_asciiToUtf8();
    void m_utf8ToAscii();
    void m_iso8859xToUtf8(const int encoding);
    void m_utf8ToIso8859x(const int encoding);
    void m_utf8ToShiftJis();
    void m_shiftJis_cp932ToUtf8();
    void m_utf8ToKsX1001();
    void m_ksX1001ToUtf8();

    //helper functions
    static bool compareRaw(const char* lhs, const char* rhs);
    static bool compareRaw(const wchar_t* lhs, const wchar_t* rhs);
    static bool compareRaw(const char32_t* lhs, const char32_t* rhs);
    static void replaceIllegalChars(std::u32string& str, const bool isBE = false);
    static void swapBytes(wchar_t* src);
    static void swapBytes(char32_t* src);
    static bool isLittleEndian();
    static std::string utf16ToUtf8Helper(const std::wstring& str, const bool byteSwap);
    static std::wstring utf8ToUtf16Helper(const std::string& str, const bool byteSwap);
    static std::string utf32ToUtf8Helper(const std::u32string& str, const bool byteSwap);
    static std::u32string utf8ToUtf32Helper(const std::string& str, const bool byteSwap);

    //This is needed because standard C and C++ substring functions are incapable of processing non-UTF strings
    template<AllowedCStringType T> static int findRaw(T superset, T subset, const bool caseSensitive)
    {
        int supersetLength;
        int subsetLength;

        if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*>)
        {
            supersetLength  = strlen(superset);
            subsetLength = strlen(subset);
        }
        else if constexpr (std::is_same_v<T, const wchar_t*> || std::is_same_v<T, wchar_t*>)
        {
            supersetLength = wcslen(superset);
            subsetLength = wcslen(subset);
        }
        else if constexpr (std::is_same_v<T, const char32_t*> || std::is_same_v<T, char32_t*>)
        {
            supersetLength = std::char_traits<char32_t>::length(superset);
            subsetLength = std::char_traits<char32_t>::length(subset);
        }

        if (supersetLength < subsetLength)
            return -1;

        if (caseSensitive)
        {
            for (int i = 0; i < supersetLength - subsetLength + 1; ++i)
            {
                int charMatchCount = 0;
                for (int j = 0; j < subsetLength; ++j)
                {
                    if (superset[i + j] == subset[j])
                        ++charMatchCount;
                }

                if (charMatchCount == subsetLength)
                    return i;
            }
        }
        else
        {
            uint32_t currentSuperset;
            uint32_t currentSubset;

            for (int i = 0; i < supersetLength - subsetLength + 1; ++i)
            {
                int charMatchCount = 0;
                for (int j = 0; j < subsetLength; ++j)
                {
                    currentSuperset = superset[i + j];
                    currentSubset = subset[j];

                    if (currentSuperset >= 'A' && currentSuperset <= 'Z')
                        currentSuperset |= 0x20;

                    if (currentSubset >= 'A' && currentSubset <= 'Z')
                        currentSubset |= 0x20;

                    if (currentSuperset == currentSubset)
                        ++charMatchCount;
                }

                if (charMatchCount == subsetLength)
                    return i;
            }
        }


        return -1;
    }

    template<typename inT, typename outT> static outT passString(inT& str)
    {
        if constexpr (std::is_same_v<outT, std::string>)
            return std::string(reinterpret_cast<const char*>(str.c_str()));
        else if constexpr (std::is_same_v<outT, const char*>)
            return reinterpret_cast<const char*>(str.c_str());
        else if constexpr (std::is_same_v<outT, char*>)
            return reinterpret_cast<char*>(str.data());

        else if constexpr (std::is_same_v<outT, std::wstring>)
            return std::wstring(reinterpret_cast<const wchar_t*>(str.c_str()));
        else if constexpr (std::is_same_v<outT, const wchar_t*>)
            return reinterpret_cast<const wchar_t*>(str.c_str());
        else if constexpr (std::is_same_v<outT, wchar_t*>)
            return reinterpret_cast<wchar_t*>(str.data());

        else if constexpr (std::is_same_v<outT, std::u32string>)
            return std::u32string(reinterpret_cast<const char32_t*>(str.c_str()));
        else if constexpr (std::is_same_v<outT, const char32_t*>)
            return reinterpret_cast<const char32_t*>(str.c_str());
        else if constexpr (std::is_same_v<outT, char32_t*>)
            return reinterpret_cast<char32_t*>(str.data());
    }
};