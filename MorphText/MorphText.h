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
        LATIN10 = ISO_8859_16
    };

private:
    std::string _utf8;
    std::wstring _utf16LE;
    std::wstring _utf16BE;
    std::u32string _utf32LE;
    std::u32string _utf32BE;
    char* _ascii;
    char* _iso_8859_1;
    char* _iso_8859_2;
    char* _iso_8859_3;
    char* _iso_8859_4;
    char* _iso_8859_5;
    char* _iso_8859_6;
    char* _iso_8859_7;
    char* _iso_8859_8;
    char* _iso_8859_9;
    char* _iso_8859_10;
    char* _iso_8859_11;
    char* _iso_8859_13;
    char* _iso_8859_14;
    char* _iso_8859_15;
    char* _iso_8859_16;
    char* _shiftJis;
    int _updatedFlags = 0;
    uint32_t _maxLength = -1;

    static constexpr wchar_t _iso8859_2_map[] = { //Latin-2
        0x00A0, 0x0104, 0x02D8, 0x0141, 0x00A4, 0x013D, 0x015A, 0x00A7, 0x00A8, 0x0160, 0x015E, 0x0164, 0x0179, 0x00AD, 0x017D, 0x017B,
        0x00B0, 0x0105, 0x02DB, 0x0142, 0x00B4, 0x013E, 0x015B, 0x02C7, 0x00B8, 0x0161, 0x015F, 0x0165, 0x017A, 0x02DD, 0x017E, 0x017C,
        0x0154, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0139, 0x0106, 0x00C7, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x011A, 0x00CD, 0x00CE, 0x010E,
        0x0110, 0x0143, 0x0147, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x00D7, 0x0158, 0x016E, 0x00DA, 0x0170, 0x00DC, 0x00DD, 0x0162, 0x00DF,
        0x0155, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x013A, 0x0107, 0x00E7, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x011B, 0x00ED, 0x00EE, 0x010F,
        0x0111, 0x0144, 0x0148, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x00F7, 0x0159, 0x016F, 0x00FA, 0x0171, 0x00FC, 0x00FD, 0x0163, 0x02D9
    };
    static constexpr wchar_t _iso8859_3_map[] = { //Latin-3
        0x00A0, 0x0126, 0x02D8, 0x00A3, 0x00A4, 0x00A5, 0x0124, 0x00A7, 0x00A8, 0x0130, 0x015E, 0x011E, 0x0134, 0x00AD, 0xFFFF, 0x017B,
        0x00B0, 0x0127, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x0125, 0x00B7, 0x00B8, 0x0131, 0x015F, 0x011F, 0x0135, 0x00BD, 0xFFFF, 0x017C,
        0x00C0, 0x00C1, 0x00C2, 0xFFFF, 0x00C4, 0x010A, 0x0108, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0xFFFF, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x0120, 0x00D6, 0x00D7, 0x011C, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x016C, 0x015C, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0xFFFF, 0x00E4, 0x010B, 0x0109, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0xFFFF, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x0121, 0x00F6, 0x00F7, 0x011D, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x016D, 0x015D, 0x02D9
    };
    static constexpr wchar_t _iso8859_4_map[] = { //Latin-4
        0x00A0, 0x0104, 0x0138, 0x0156, 0x00A4, 0x0128, 0x013B, 0x00A7, 0x00A8, 0x0160, 0x0112, 0x0122, 0x0166, 0x00AD, 0x017D, 0x00AF,
        0x00B0, 0x0105, 0x02DB, 0x0157, 0x00B4, 0x0129, 0x013C, 0x02C7, 0x00B8, 0x0161, 0x0113, 0x0123, 0x0167, 0x014A, 0x017E, 0x014B,
        0x0100, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x012A,
        0x0110, 0x0145, 0x014C, 0x0136, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x0172, 0x00DA, 0x00DB, 0x00DC, 0x0168, 0x016A, 0x00DF,
        0x0101, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x012F, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x012B,
        0x0111, 0x0146, 0x014D, 0x0137, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x0173, 0x00FA, 0x00FB, 0x00FC, 0x0169, 0x016B, 0x02D9
    };
    static constexpr wchar_t _iso8859_5_map[] = {//Cyrillic
        0x00A0, 0x0401, 0x0402, 0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x00AD, 0x040E, 0x040F,
        0x0410, 0x0411, 0x0412, 0x0413, 0x0414, 0x0415, 0x0416, 0x0417, 0x0418, 0x0419, 0x041A, 0x041B, 0x041C, 0x041D, 0x041E, 0x041F,
        0x0420, 0x0421, 0x0422, 0x0423, 0x0424, 0x0425, 0x0426, 0x0427, 0x0428, 0x0429, 0x042A, 0x042B, 0x042C, 0x042D, 0x042E, 0x042F,
        0x0430, 0x0431, 0x0432, 0x0433, 0x0434, 0x0435, 0x0436, 0x0437, 0x0438, 0x0439, 0x043A, 0x043B, 0x043C, 0x043D, 0x043E, 0x043F,
        0x0440, 0x0441, 0x0442, 0x0443, 0x0444, 0x0445, 0x0446, 0x0447, 0x0448, 0x0449, 0x044A, 0x044B, 0x044C, 0x044D, 0x044E, 0x044F,
        0x2116, 0x0451, 0x0452, 0x0453, 0x0454, 0x0455, 0x0456, 0x0457, 0x0458, 0x0459, 0x045A, 0x045B, 0x045C, 0x00A7, 0x045E, 0x045F
    };
    static constexpr wchar_t _iso8859_6_map[] = {//Arabic
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x060C, 0x00AD, 0x00AE, 0x00AF,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x061B, 0x00BC, 0x00BD, 0x00BE, 0x061F,
        0x00C0, 0x0621, 0x0622, 0x0623, 0x0624, 0x0625, 0x0626, 0x0627, 0x0628, 0x0629, 0x062A, 0x062B, 0x062C, 0x062D, 0x062E, 0x062F,
        0x0630, 0x0631, 0x0632, 0x0633, 0x0634, 0x0635, 0x0636, 0x0637, 0x0638, 0x0639, 0x063A, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
        0x0640, 0x0641, 0x0642, 0x0643, 0x0644, 0x0645, 0x0646, 0x0647, 0x0648, 0x0649, 0x064A, 0x064B, 0x064C, 0x064D, 0x064E, 0x064F,
        0x0650, 0x0651, 0x0652, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
    };
    static constexpr wchar_t _iso8859_7_map[] = {//Greek
        0x00A0, 0x2018, 0x2019, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x2015,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x0384, 0x0385, 0x0386, 0x00B7, 0x0388, 0x0389, 0x038A, 0x00BB, 0x038C, 0x00BD, 0x038E, 0x038F,
        0x0390, 0x0391, 0x0392, 0x0393, 0x0394, 0x0395, 0x0396, 0x0397, 0x0398, 0x0399, 0x039A, 0x039B, 0x039C, 0x039D, 0x039E, 0x039F,
        0x03A0, 0x03A1, 0x00D2, 0x03A3, 0x03A4, 0x03A5, 0x03A6, 0x03A7, 0x03A8, 0x03A9, 0x03AA, 0x03AB, 0x03AC, 0x03AD, 0x03AE, 0x03AF,
        0x03B0, 0x03B1, 0x03B2, 0x03B3, 0x03B4, 0x03B5, 0x03B6, 0x03B7, 0x03B8, 0x03B9, 0x03BA, 0x03BB, 0x03BC, 0x03BD, 0x03BE, 0x03BF,
        0x03C0, 0x03C1, 0x03C2, 0x03C3, 0x03C4, 0x03C5, 0x03C6, 0x03C7, 0x03C8, 0x03C9, 0x03CA, 0x03CB, 0x03CC, 0x03CD, 0x03CE, 0x00FF
    };
    static constexpr wchar_t _iso8859_8_map[] = {//Hebrew
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00D7, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x203E,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00F7, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x2017,
        0x05D0, 0x05D1, 0x05D2, 0x05D3, 0x05D4, 0x05D5, 0x05D6, 0x05D7, 0x05D8, 0x05D9, 0x05DA, 0x05DB, 0x05DC, 0x05DD, 0x05DE, 0x05DF,
        0x05E0, 0x05E1, 0x05E2, 0x05E3, 0x05E4, 0x05E5, 0x05E6, 0x05E7, 0x05E8, 0x05E9, 0x05EA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
    };
    static constexpr wchar_t _iso8859_9_map[] = {//Turkish, Latin-5
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x00A4, 0x00A5, 0x00A6, 0x00A7, 0x00A8, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x00B4, 0x00B5, 0x00B6, 0x00B7, 0x00B8, 0x00B9, 0x00BA, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00BF,
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x011E, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x0130, 0x015E, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0x011F, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x0131, 0x015F, 0x00FF
    };
    static constexpr wchar_t _iso8859_10_map[] = {//Nordic, Latin-6
        0x00A0, 0x0104, 0x0112, 0x0122, 0x012A, 0x0128, 0x0136, 0x00A7, 0x013B, 0x0110, 0x0160, 0x0166, 0x017D, 0x00AD, 0x016A, 0x014A,
        0x00B0, 0x0105, 0x0113, 0x0123, 0x012B, 0x0129, 0x0137, 0x00B7, 0x013C, 0x0111, 0x0161, 0x0167, 0x017E, 0x2015, 0x016B, 0x014B,
        0x0100, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x012E, 0x010C, 0x00C9, 0x0118, 0x00CB, 0x0116, 0x00CD, 0x00CE, 0x00CF,
        0x00D0, 0x0145, 0x014C, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x0168, 0x00D8, 0x0172, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
        0x0101, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x012F, 0x010D, 0x00E9, 0x0119, 0x00EB, 0x0117, 0x00ED, 0x00EE, 0x00EF,
        0x00F0, 0x0146, 0x014D, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x0169, 0x00F8, 0x0173, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x0138
    };
    static constexpr wchar_t _iso8859_11_map[] = {//Thai
        0x00A0, 0x0E01, 0x0E02, 0x0E03, 0x0E04, 0x0E05, 0x0E06, 0x0E07, 0x0E08, 0x0E09, 0x0E0A, 0x0E0B, 0x0E0C, 0x0E0D, 0x0E0E, 0x0E0F,
        0x0E10, 0x0E11, 0x0E12, 0x0E13, 0x0E14, 0x0E15, 0x0E16, 0x0E17, 0x0E18, 0x0E19, 0x0E1A, 0x0E1B, 0x0E1C, 0x0E1D, 0x0E1E, 0x0E1F,
        0x0E20, 0x0E21, 0x0E22, 0x0E23, 0x0E24, 0x0E25, 0x0E26, 0x0E27, 0x0E28, 0x0E29, 0x0E2A, 0x0E2B, 0x0E2C, 0x0E2D, 0x0E2E, 0x0E2F,
        0x0E30, 0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37, 0x0E38, 0x0E39, 0x0E3A, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0x0E3F,
        0x0E40, 0x0E41, 0x0E42, 0x0E43, 0x0E44, 0x0E45, 0x0E46, 0x0E47, 0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D, 0x0E4E, 0x0E4F,
        0x0E50, 0x0E51, 0x0E52, 0x0E53, 0x0E54, 0x0E55, 0x0E56, 0x0E57, 0x0E58, 0x0E59, 0x0E5A, 0x0E5B, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
    };
    static constexpr wchar_t _iso8859_13_map[] = { //Baltic, Latin-7
        0x00A0, 0x201D, 0x00A2, 0x00A3, 0x00A4, 0x201E, 0x00A6, 0x00A7, 0x00D8, 0x00A9, 0x0156, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00C6,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x201C, 0x00B5, 0x00B6, 0x00B7, 0x00F8, 0x00B9, 0x0157, 0x00BB, 0x00BC, 0x00BD, 0x00BE, 0x00E6,
        0x0104, 0x012E, 0x0100, 0x0106, 0x00C4, 0x00C5, 0x0118, 0x0112, 0x010C, 0x00C9, 0x0179, 0x0116, 0x0122, 0x0136, 0x012A, 0x013B,
        0x0160, 0x0143, 0x0145, 0x00D3, 0x014C, 0x00D5, 0x00D6, 0x00D7, 0x0172, 0x0141, 0x015A, 0x016A, 0x00DC, 0x017B, 0x017D, 0x00DF,
        0x0105, 0x012F, 0x0101, 0x0107, 0x00E4, 0x00E5, 0x0119, 0x0113, 0x010D, 0x00E9, 0x017A, 0x0117, 0x0123, 0x0137, 0x012B, 0x013C,
        0x0161, 0x0144, 0x0146, 0x00F3, 0x014D, 0x00F5, 0x00F6, 0x00F7, 0x0173, 0x0142, 0x015B, 0x016B, 0x00FC, 0x017C, 0x017E, 0x2019
    };
    static constexpr wchar_t _iso8859_14_map[] = { //Celtic, Latin-8
        0x00A0, 0x1E02, 0x1E03, 0x00A3, 0x010A, 0x010B, 0x1E0A, 0x00A7, 0x1E80, 0x00A9, 0x1E82, 0x1E0B, 0x1EF2, 0x00AD, 0x00AE, 0x0178,
        0x1E1E, 0x1E1F, 0x0120, 0x0121, 0x1E40, 0x1E41, 0x00B6, 0x1E56, 0x1E81, 0x1E57, 0x1E83, 0x1E60, 0x1EF3, 0x1E84, 0x1E85, 0x1E61,
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x0174, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x1E6A, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x0176, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0x0175, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x1E6B, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x0177, 0x00FF, 
    };
    static constexpr wchar_t _iso8859_15_map[] = { //West European, Latin-9
        0x00A0, 0x00A1, 0x00A2, 0x00A3, 0x20AC, 0x00A5, 0x0160, 0x00A7, 0x0161, 0x00A9, 0x00AA, 0x00AB, 0x00AC, 0x00AD, 0x00AE, 0x00AF,
        0x00B0, 0x00B1, 0x00B2, 0x00B3, 0x017D, 0x00B5, 0x00B6, 0x00B7, 0x017E, 0x00B9, 0x00BA, 0x00BB, 0x0152, 0x0153, 0x0178, 0x00BF,
        0x00C0, 0x00C1, 0x00C2, 0x00C3, 0x00C4, 0x00C5, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x00D0, 0x00D1, 0x00D2, 0x00D3, 0x00D4, 0x00D5, 0x00D6, 0x00D7, 0x00D8, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x00DD, 0x00DE, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0x00E3, 0x00E4, 0x00E5, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0x00F0, 0x00F1, 0x00F2, 0x00F3, 0x00F4, 0x00F5, 0x00F6, 0x00F7, 0x00F8, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x00FD, 0x00FE, 0x00FF
    };
    static constexpr wchar_t _iso8859_16_map[] = { //Southeast European, Latin-10
        0x00A0, 0x0104, 0x0105, 0x0141, 0x20AC, 0x201E, 0x0160, 0x00A7, 0x0161, 0x00A9, 0x0218, 0x00AB, 0x0179, 0x00AD, 0x017A, 0x017B,
        0x00B0, 0x00B1, 0x010C, 0x0142, 0x017D, 0x201D, 0x00B6, 0x00B7, 0x017E, 0x010D, 0x0219, 0x00BB, 0x0152, 0x0153, 0x0178, 0x017C,
        0x00C0, 0x00C1, 0x00C2, 0x0102, 0x00C4, 0x0106, 0x00C6, 0x00C7, 0x00C8, 0x00C9, 0x00CA, 0x00CB, 0x00CC, 0x00CD, 0x00CE, 0x00CF,
        0x0110, 0x0143, 0x00D2, 0x00D3, 0x00D4, 0x0150, 0x00D6, 0x015A, 0x0170, 0x00D9, 0x00DA, 0x00DB, 0x00DC, 0x0118, 0x021A, 0x00DF,
        0x00E0, 0x00E1, 0x00E2, 0x0103, 0x00E4, 0x0107, 0x00E6, 0x00E7, 0x00E8, 0x00E9, 0x00EA, 0x00EB, 0x00EC, 0x00ED, 0x00EE, 0x00EF,
        0x0111, 0x0144, 0x00F2, 0x00F3, 0x00F4, 0x0151, 0x00F6, 0x015B, 0x0171, 0x00F9, 0x00FA, 0x00FB, 0x00FC, 0x0119, 0x021B, 0x00FF
    };

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
    };

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
        _utf8 = ASCII_To_Utf8(_ascii);
        _updatedFlags |= FLAG_UTF8;
    }

    void utf8ToAscii()
    {
        _ascii = Utf8_To_ASCII(_utf8);
        _updatedFlags |= FLAG_ASCII;
    }

    void iso8859xToUtf8(int format)
    {
        char* txt;

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

    void utf8ToIso8859x(int format)
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

    void initArrays()
    {
        _ascii = nullptr;
        _iso_8859_1 = nullptr;
        _iso_8859_2 = nullptr;
        _iso_8859_3 = nullptr;
        _iso_8859_4 = nullptr;
        _iso_8859_5 = nullptr;
        _iso_8859_6 = nullptr;
        _iso_8859_7 = nullptr;
        _iso_8859_8 = nullptr;
        _iso_8859_9 = nullptr;
        _iso_8859_10 = nullptr;
        _iso_8859_11 = nullptr;
        _iso_8859_13 = nullptr;
        _iso_8859_14 = nullptr;
        _iso_8859_15 = nullptr;
        _iso_8859_16 = nullptr;
        _shiftJis = nullptr;
    }

public:
    MorphText()
    {
        initArrays();
    }

    MorphText(const std::string& utf8)
    {
        initArrays();
        _utf8 = utf8;
        _updatedFlags |= FLAG_UTF8;
    }

    MorphText(const std::wstring& utf16, const bool bigEndian = false)
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

    MorphText(const std::u32string& utf32, const bool bigEndian = false)
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

    MorphText(const char* charStr, const int format = 0)
    {
        initArrays();
        int length = strlen(charStr);

        switch (strType)
        {
        case Formats::UTF8: {
            *this = MorphText(std::string(charStr));
        } break;
        case ISO_8859_1: {
            _iso_8859_1 = new char[length + 1];
            strcpy(_iso_8859_1, charStr);
            _iso_8859_1[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_1;
        } break;
        case ISO_8859_2: {
            _iso_8859_2 = new char[length + 1];
            strcpy(_iso_8859_2, charStr);
            _iso_8859_2[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_2;
        } break;
        case ISO_8859_3: {
            _iso_8859_3 = new char[length + 1];
            strcpy(_iso_8859_3, charStr);
            _iso_8859_3[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_3;
        } break;
        case ISO_8859_4: {
            _iso_8859_4 = new char[length + 1];
            strcpy(_iso_8859_4, charStr);
            _iso_8859_4[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_4;
        } break;
        case ISO_8859_5: {
            _iso_8859_5 = new char[length + 1];
            strcpy(_iso_8859_5, charStr);
            _iso_8859_5[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_5;
        } break;
        case ISO_8859_6: {
            _iso_8859_6 = new char[length + 1];
            strcpy(_iso_8859_6, charStr);
            _iso_8859_6[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_6;
        } break;
        case ISO_8859_7: {
            _iso_8859_7 = new char[length + 1];
            strcpy(_iso_8859_7, charStr);
            _iso_8859_7[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_7;
        } break;
        case ISO_8859_8: {
            _iso_8859_8 = new char[length + 1];
            strcpy(_iso_8859_8, charStr);
            _iso_8859_8[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_8;
        } break;
        case ISO_8859_9: {
            _iso_8859_9 = new char[length + 1];
            strcpy(_iso_8859_9, charStr);
            _iso_8859_9[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_9;
        } break;
        case ISO_8859_10: {
            _iso_8859_10 = new char[length + 1];
            strcpy(_iso_8859_10, charStr);
            _iso_8859_10[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_10;
        } break;
        case ISO_8859_11: {
            _iso_8859_11 = new char[length + 1];
            strcpy(_iso_8859_11, charStr);
            _iso_8859_11[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_11;
        } break;
        case ISO_8859_13: {
            _iso_8859_13 = new char[length + 1];
            strcpy(_iso_8859_13, charStr);
            _iso_8859_13[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_13;
        } break;
        case ISO_8859_14: {
            _iso_8859_14 = new char[length + 1];
            strcpy(_iso_8859_14, charStr);
            _iso_8859_14[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_14;
        } break;
        case ISO_8859_15: {
            _iso_8859_15 = new char[length + 1];
            strcpy(_iso_8859_15, charStr);
            _iso_8859_15[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_15;
        } break;
        case ISO_8859_16: {
            _iso_8859_16 = new char[length + 1];
            strcpy(_iso_8859_16, charStr);
            _iso_8859_16[length] = '/0';
            _updatedFlags |= FLAG_ISO_8859_16;
        } break;
        case Formats::SHIFTJIS: {
            _shiftJis = new char[length + 1];
            strcpy(_shiftJis, charStr);
            _shiftJis[length] = '/0';
            _updatedFlags |= FLAG_SHIFTJIS;
        } break;
        default: // ASCII
        {
            _ascii = new char[length + 1];
            strcpy(_ascii, charStr);
            _ascii[length] = '/0';
            _updatedFlags |= FLAG_ASCII;
        }
        }
    }

    MorphText(const wchar_t* charStr, const bool bigEndian = false)
    {
        initArrays();
        *this = MorphText(std::wstring(charStr), bigEndian);
    }

    MorphText(const MorphText& other)
    {
        initArrays();
        *this = other;
    }

    MorphText(const char32_t* charStr, const bool bigEndian = false)
    {
        initArrays();
        *this = MorphText(std::u32string(charStr), bigEndian);
    }

    ~MorphText()
    {
        if(_ascii) delete[] _ascii;
        if (_iso_8859_1) delete[] _iso_8859_1;
        if (_iso_8859_2) delete[] _iso_8859_2;
        if (_iso_8859_3) delete[] _iso_8859_3;
        if (_iso_8859_4) delete[] _iso_8859_4;
        if (_iso_8859_5) delete[] _iso_8859_5;
        if (_iso_8859_6) delete[] _iso_8859_6;
        if (_iso_8859_7) delete[] _iso_8859_7;
        if (_iso_8859_8) delete[] _iso_8859_8;
        if (_iso_8859_9) delete[] _iso_8859_9;
        if (_iso_8859_10) delete[] _iso_8859_10;
        if (_iso_8859_11) delete[] _iso_8859_11;
        if (_iso_8859_13) delete[] _iso_8859_13;
        if (_iso_8859_14) delete[] _iso_8859_14;
        if (_iso_8859_15) delete[] _iso_8859_15;
        if (_iso_8859_16) delete[] _iso_8859_16;
        if (_shiftJis) delete[] _shiftJis;
    }

    /// <summary>
    /// Converts the passed Shift-Jis char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
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

    /// <summary>
    /// Converts the passed std::string&amp; to a Shift-Jis char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
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
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(input);
    }

    /// <summary>
    /// Converts the passed big endian UTF-16 std::wstring&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::wstring&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf16BE_To_Utf8(const std::wstring& input)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t, 0x10ffff, std::codecvt_mode::consume_header>, wchar_t> converter;
        return converter.to_bytes(input);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-16 big endian std::wstring&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::wstring Utf8_To_Utf16BE(const std::string& input)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<char16_t>, char16_t> converter;
        std::u16string utf16 = converter.from_bytes(input);
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
        return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(input);
    }
    
    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-32 little endian std::u32string&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::u32string Utf8_To_Utf32LE(const std::string& input)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string utf32 = converter.from_bytes(input);
        return utf32.data();
    }

    /// <summary>
    /// Converts the passed big endian UTF-32 std::u32string&amp; to a UTF-8 std::string&amp;.
    /// <param><c>std::u32string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string Utf32BE_To_Utf8(const std::u32string& input)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(input);
    }

    /// <summary>
    /// Converts the passed std::string&amp; to a UTF-32 big endian std::u32string&amp;.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::u32string Utf8_To_Utf32BE(const std::string& input)
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string utf32 = converter.from_bytes(input);
        std::u32string output;
        output.reserve(utf32.size());

        for (char32_t c : utf32)
            output.push_back(static_cast<wchar_t>((c >> 24) | ((c >> 8) & 0xFF00) | ((c << 8) & 0xFF0000) | (c << 24)));

        return output;
    }

    /// <summary>
    /// Converts the passed ASCII char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.</param>
    /// </summary>
    static std::string ASCII_To_Utf8(const char* input) //Converts the ASCII input to UTF-8
    {
        std::string output(input);

        for (int i = 0; i < output.size(); ++i)
            output[i] = input[i] < 0 ? '?' : input[i];

        return output;
    }

    /// <summary>
    /// Converts the passed std::string&amp; to an ASCII char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static char* Utf8_To_ASCII(const std::string& input)
    {
        int size = input.size() + 1;
        char* output = new char[size];

        for (int i = 0; i < size; ++i)
            output[i] = input[i] < 0 ? '?' : input[i];

        return output;
    }

    /// <summary>
    /// Converts the passed ISO-8859-X char&ast; string to a UTF-8 std::string&amp;.
    /// <param><c>char&ast; input: string to be processed.
    /// <c>int format: ISO-8859 format of the passed string.</param>
    /// </summary>
    static std::string ISO8859X_To_Utf8(const char* input, const int format = ISO_8859_1)
    {
        int length = strlen(input);
        wchar_t* temp = new wchar_t[length+1];
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

    /// <summary>
    /// Converts the passed std::string&amp; to an ISO-8859-X char&ast; string.
    /// <param><c>std::string&amp; input: string to be processed.
    /// <c>int format</c>: ISO-8859 format for the string to be returned.</param>
    /// </summary>
    static char* Utf8_To_ISO8859X(const std::string& input, const int format = ISO_8859_1)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring utf16 = converter.from_bytes(input);
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
                    if (_iso8859_2_map[lookupIndex] == ch)
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

    /// <summary>
    /// Checks if the right-hand std::string&amp; parameter appears within the left-hand std::string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::u32string&amp; rhs</c>: std::u32string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    static int Find(const std::string& superset, const std::string& subset, const bool caseSensitive = true)
    {
        std::string sups = caseSensitive ? superset : ToLower(superset);
        std::string subs = caseSensitive ? subset : ToLower(subset);
        return sups.find(subs);
    }

    /// <summary>
    /// Checks if the right-hand std::wstring&amp; parameter appears within the left-hand std::wstring. Returns the position of appearance, otherwise -1.
    /// <param><c>std::wstring&amp; lhs</c>: left-hand std::wstring&amp;. 
    /// <c>std::wstring&amp; rhs</c>: std::wstring&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static int Find(const std::wstring& superset, const std::wstring& subset, const const bool caseSensitive = true, const bool bigEndian = false)
    {
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

    /// <summary>
    /// Checks if the right-hand char&ast; parameter appears within the left-hand string. Returns the position of appearance, otherwise -1.
    /// <param><c>char&ast; lhs</c>: left-hand char&ast;. 
    /// <c>std::u32string&amp; rhs</c>: std::u32string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    static int Find(const char* superset, const char* subset, const int format, const bool caseSensitive = true)
    {
        switch (format)
        {
        case ASCII:
            return Find(ASCII_To_Utf8(superset), ASCII_To_Utf8(subset), caseSensitive);
            break;
        case SHIFTJIS:
            return Find(ShiftJis_To_Utf8(superset), ShiftJis_To_Utf8(subset), caseSensitive);
            break;
        default: //ISO 8859-X
            return Find(ISO8859X_To_Utf8(superset, format), ISO8859X_To_Utf8(subset, format), caseSensitive);
        }
    }

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
    static bool Compare(const std::wstring& lhs, const std::wstring& rhs, const bool caseSensitive = true, const bool isBigEndian = false)
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
        case ASCII:
            return Compare(ASCII_To_Utf8(lhs), ASCII_To_Utf8(rhs), caseSensitive);
        break;
        case SHIFTJIS: 
            return Compare(ShiftJis_To_Utf8(lhs), ShiftJis_To_Utf8(rhs), caseSensitive);
        break;
        default: //ISO 8859-X
            return Compare(ISO8859X_To_Utf8(lhs, format), ISO8859X_To_Utf8(rhs, format), caseSensitive);
        }
    }

    /// <summary>
    /// Returns the passed std::string&amp; in <b>uppercase</b>.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToLower(const std::string& input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), tolower);
        return result;
    }

    /// <summary>
    /// Returns the passed std::string&amp; in <b>uppercase</b>.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToUpper(const std::string& input)
    {
        std::string result = input;
        std::transform(result.begin(), result.end(), result.begin(), toupper);
        return result;
    }

    /// <summary>
    /// Returns the passed std::string&amp; with sarcastic energy.
    /// <param><c>std::string&amp; input: string to be processed.</param>
    /// </summary>
    static std::string ToSarcasm(const std::string& input)
    {
        std::string result = input;

        for (int i = 0; i < result.size(); ++i)
                result[i] = (i & 1) ? std::tolower(input[i]) : std::toupper(input[i]);

        return result;
    }

    /// <summary>
    /// Returns the passed std::u32string&amp; in <b>uppercase</b>.
    /// <param><c>std::u32string&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToLower(const std::wstring& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToLower(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    /// <summary>
    /// Returns the passed std::wstring&amp; in <b>uppercase</b>.
    /// <param><c>std::wstring&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToUpper(const std::wstring& input, const bool isBigEndian = false)
    {
        std::string temp = isBigEndian ? Utf16BE_To_Utf8(input) : Utf16LE_To_Utf8(input);
        temp = ToUpper(temp);
        return isBigEndian ? Utf8_To_Utf16BE(temp) : Utf8_To_Utf16LE(temp);
    }

    /// <summary>
    /// Returns the passed std::wstring&amp; with sarcastic energy.
    /// <param><c>std::wstring&amp; input: string to be processed.
    /// <c>bool isBigEndian</c>: set true if the passed string is big endian.</param>
    /// </summary>
    static std::wstring ToSarcasm(const std::wstring& input, const bool isBigEndian = false)
    {
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

    /// <summary>
    /// Returns the passed char&ast; string in <b>lowercase</b>.
    /// <param><c>char&ast; input: string to be processed.
    /// <c>int format</c>: set format to select char&ast; type.</param>
    /// </summary>
    static char* ToLower(const char* input, const int format)
    {
        std::string temp;
        int length = strlen(input) + 1;
        char* result = new char[length];
        strcpy(result, input);

        switch (format)
        {
        case ASCII: {
            for (char* i = result; *i != '\0'; ++i)
                *i = std::tolower(*i);
        }break;
        case SHIFTJIS: {
            for (size_t i = 0; i < length;)
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
        }break;
        default: { //ISO 8859-X
            temp = ISO8859X_To_Utf8(input, format);
            temp = ToLower(temp);
            result = Utf8_To_ISO8859X(temp);
        }
        }

        return result;
    }

    /// <summary>
    /// Returns the passed char&ast; string in <b>uppercase</b>.
    /// <param><c>char&ast; input: string to be processed.
    /// <c>int format</c>: set format to select char&ast; type.</param>
    /// </summary>
    static char* ToUpper(const char* input, const int format)
    {
        std::string temp;
        int length = strlen(input) + 1;
        char* result = new char[length];
        strcpy(result, input);

        switch (format)
        {
        case ASCII: {
            for (char* i = result; *i != '\0'; ++i)
                *i = std::toupper(*i);
        }break;
        case SHIFTJIS: {
            for (size_t i = 0; i < length;)
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
                    if ((current > 0x83BE && current < 0x83D7) ||
                        (current > 0x846F && current < 0x8492))
                    {
                        current -= 0x20;
                    }
                    else if ((current > 0x8280 && current < 0x829B))
                        current -= 0x21;

                    result[i] = static_cast<char>(current >> 8);
                    result[i + 1] = static_cast<char>(current & 0xFF);
                    i += 2;
                }
            }
        }break;
        default: { //ISO 8859-X
            temp = ISO8859X_To_Utf8(input, format);
            temp = ToUpper(temp);
            result = Utf8_To_ISO8859X(temp);
        }
        }

        return result;
    }

    /// <summary>
    /// Returns the passed char&ast; string with sarcastic energy.
    /// <param><c>char&ast; input: string to be processed.
    /// <c>int format</c>: set format to select char&ast; type.</param>
    /// </summary>
    static char* ToSarcasm(const char* input, const int format)
    {
        std::string temp;
        int length = strlen(input) + 1;
        char* result = new char[length];
        strcpy(result, input);

        switch (format)
        {
        case ASCII: {
            for (char* i = result; *i != '\0'; ++i)
                *i = reinterpret_cast<uint64_t>(i) & 1 ? std::tolower(*i) : std::toupper(*i);
        }break;
        case SHIFTJIS: { //guess it's okay doing it this way here since this function won't be used in performance-critical situations
            temp = ShiftJis_To_Utf8(input);
            temp = ToSarcasm(temp);
            result = Utf8_To_ShiftJis(temp);
        }break;
        default: { //ISO 8859-X
            temp = ISO8859X_To_Utf8(input, format);
            temp = ToSarcasm(temp);
            result = Utf8_To_ISO8859X(temp);
        }
        }

        return result;
    }

    /// <summary>
    /// Returns the <b>lowercase</b> string of type T.
    /// <param><c>int format</c>: set format to select char&ast; type strings or big/little endiand wstring/u32string.</param>
    /// </summary>
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
            case ASCII: {
                utf8ToAscii();
                return ToLower(_ascii, ASCII);
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

    /// <summary>
    /// Returns the string of type T with sarcastic energy.
    /// <param><c>int format</c>: set format to select char&ast; type strings or big/little endiand wstring/u32string.</param>
    /// </summary>
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

    /// <summary>
    /// Checks if the std::string&amp; parameter matches the instance's std::string. Returns true if they match, otherwise false.
    /// <param><c>std::string&amp; lhs</c>: left-hand std::string&amp;. 
    /// <c>std::string&amp; rhs</c>: right-hand std::string&amp; to be compared against. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    bool Compare(const std::string& rhs, const bool caseSensitive = true)
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
    bool Compare(const std::wstring& rhs, const bool caseSensitive = true, const bool bigEndian = false)
    {
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
    bool Compare(const std::u32string& rhs, const bool caseSensitive = true, const bool bigEndian = false)
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
    bool Compare(const char* rhs, const bool caseSensitive = true, const int format = ASCII)
    {
        switch (format)
        {
        case SHIFTJIS:
            return Compare(_shiftJis, rhs, caseSensitive);
        case ISO_8859_1:
            return Compare(_iso_8859_1, rhs, caseSensitive, format);
        case ISO_8859_2:
            return Compare(_iso_8859_2, rhs, caseSensitive, format);
        case ISO_8859_3:
            return Compare(_iso_8859_3, rhs, caseSensitive, format);
        case ISO_8859_4:
            return Compare(_iso_8859_4, rhs, caseSensitive, format);
        case ISO_8859_5:
            return Compare(_iso_8859_5, rhs, caseSensitive, format);
        case ISO_8859_6:
            return Compare(_iso_8859_6, rhs, caseSensitive, format);
        case ISO_8859_7:
            return Compare(_iso_8859_7, rhs, caseSensitive, format);
        case ISO_8859_8:
            return Compare(_iso_8859_8, rhs, caseSensitive, format);
        case ISO_8859_9:
            return Compare(_iso_8859_9, rhs, caseSensitive, format);
        case ISO_8859_10:
            return Compare(_iso_8859_10, rhs, caseSensitive, format);
        case ISO_8859_11:
            return Compare(_iso_8859_11, rhs, caseSensitive, format);
        case ISO_8859_13:
            return Compare(_iso_8859_13, rhs, caseSensitive, format);
        case ISO_8859_14:
            return Compare(_iso_8859_14, rhs, caseSensitive, format);
        case ISO_8859_15:
            return Compare(_iso_8859_15, rhs, caseSensitive, format);
        case ISO_8859_16:
            return Compare(_iso_8859_16, rhs, caseSensitive, format);
        default: //ASCII
            return Compare(_ascii, rhs, caseSensitive);
        }
    }

    /// <summary>
    /// Checks if the std::string&amp; string parameter appears within the instance's std::string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::string&amp; subset</c>: std::string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    int Find(const std::string& subset, const bool caseSensitive = true)
    {
        return Find(_utf8, subset, caseSensitive);
    }

    /// <summary>
    /// Checks if the std::wstring&amp; string parameter appears within the instance's std::wstring. Returns the position of appearance, otherwise -1.
    /// <param><c>std::wstring&amp; subset</c>: std::wstring&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    int Find(const std::wstring& subset, const bool caseSensitive = true, const bool bigEndian = false)
    {
        if(caseSensitive)
            return Find(_utf16BE, subset, caseSensitive, true);

        return Find(_utf16LE, subset, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the std::u32string&amp; string parameter appears within the instance's std::u32string. Returns the position of appearance, otherwise -1.
    /// <param><c>std::u32string&amp; subset</c>: std::u32string&amp; to be found. 
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.
    /// <c>bool isBigEndian</c>: true to return the big endian value, false to return the little endian value.</param>
    /// </summary>
    int Find(const std::u32string& subset, const bool caseSensitive = true, const bool bigEndian = false)
    {
        if (caseSensitive)
            return Find(_utf32BE, subset, caseSensitive, true);

        return Find(_utf32LE, subset, caseSensitive, false);
    }

    /// <summary>
    /// Checks if the char&ast; string parameter appears within the instance's selected (format) string. Returns the position of appearance, otherwise -1.
    /// <param><c>char&ast; subset</c>: char&ast; to be found. 
    /// <c>int format</c>: format value.
    /// <c>bool caseSensitive</c> (optional): Consider case sensitivity (true = case sensitive (default), false = case insensitive.</param>
    /// </summary>
    int Find(const char* subset, const int format, const bool caseSensitive = true)
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
        default: //ASCII
            return Find(ASCII_To_Utf8(_ascii), ASCII_To_Utf8(subset), caseSensitive);
        }
    }

    /// <summary>
    /// Returns the instance's <b>UTF-8</b> value.
    /// </summary>
    std::string GetUTF8()
    {
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
            if (_updatedFlags & FLAG_UTF16BE)
                utf8ToUtf16Be();

            return _utf16BE;
        }

        if (_updatedFlags & FLAG_UTF16LE)
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
            if (_updatedFlags & FLAG_UTF32BE)
                utf8ToUtf32Be();

            return _utf32BE;
        }

        if (_updatedFlags & FLAG_UTF32LE)
            utf8ToUtf32Le();

        return _utf32LE;
    }

    /// <summary>
    /// Returns the instance's <b>ASCII</b> value.
    /// </summary>
    std::string GetASCII()
    {
        if (_updatedFlags & FLAG_ASCII)
            utf8ToAscii();

        return _ascii;
    }

    /// <summary>
    /// Returns the instance's <b>Shift-Jis</b> value as char*.
    /// </summary>
    std::string GetShiftJis()
    {
        if (_updatedFlags & FLAG_SHIFTJIS)
            utf8ToShiftJis();

        return _shiftJis;
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
            if(_updatedFlags & FLAG_ISO_8859_2)
                utf8ToIso8859x(format);
            return _iso_8859_2;
        case ISO_8859_3:
            if (_updatedFlags & FLAG_ISO_8859_3)
                utf8ToIso8859x(format);
            return _iso_8859_3;
        case ISO_8859_4:
            if (_updatedFlags & FLAG_ISO_8859_4)
                utf8ToIso8859x(format);
            return _iso_8859_4;
        case ISO_8859_5:
            if (_updatedFlags & FLAG_ISO_8859_5)
                utf8ToIso8859x(format);
            return _iso_8859_5;
        case ISO_8859_6:
            if (_updatedFlags & FLAG_ISO_8859_6)
                utf8ToIso8859x(format);
            return _iso_8859_6;
        case ISO_8859_7:
            if (_updatedFlags & FLAG_ISO_8859_7)
                utf8ToIso8859x(format);
            return _iso_8859_7;
        case ISO_8859_8:
            if (_updatedFlags & FLAG_ISO_8859_8)
                utf8ToIso8859x(format);
            return _iso_8859_8;
        case ISO_8859_9:
            if (_updatedFlags & FLAG_ISO_8859_9)
                utf8ToIso8859x(format);
            return _iso_8859_9;
        case ISO_8859_10:
            if (_updatedFlags & FLAG_ISO_8859_10)
                utf8ToIso8859x(format);
            return _iso_8859_10;
        case ISO_8859_11:
            if (_updatedFlags & FLAG_ISO_8859_11)
                utf8ToIso8859x(format);
            return _iso_8859_11;
        case ISO_8859_13:
            if (_updatedFlags & FLAG_ISO_8859_13)
                utf8ToIso8859x(format);
            return _iso_8859_13;
        case ISO_8859_14:
            if (_updatedFlags & FLAG_ISO_8859_14)
                utf8ToIso8859x(format);
            return _iso_8859_14;
        case ISO_8859_15:
            if (_updatedFlags & FLAG_ISO_8859_15)
                utf8ToIso8859x(format);
            return _iso_8859_15;
        case ISO_8859_16:
            if (_updatedFlags & FLAG_ISO_8859_16)
                utf8ToIso8859x(format);
            return _iso_8859_16;
        default:
            if (_updatedFlags & FLAG_ISO_8859_1)
                utf8ToIso8859x(format);
            return _iso_8859_1;
        }
    }

    /// <summary>
    /// Sets the instance's <b>ASCII</b> value.
    /// <param><c>char&ast; input</c>: ASCII char* string to be set.</param>
    /// <example> instance.SetASCII(text);</example>
    /// </summary>
    void SetASCII(const char* input)
    {
        if (_updatedFlags & Flags::FLAG_ASCII)
            delete[] _ascii;
        strcpy(_ascii, input);
        _updatedFlags = Flags::FLAG_ASCII;
    }

    /// <summary>
    /// Sets the instance's <b>Shift-Jis</b> value.
    /// <param><c>char&ast; input</c>: Shift-Jis char* string to be set.</param>
    /// <example> instance.SetShiftJis(text);</example>
    /// </summary>
    void SetShiftJis(const char* input)
    {
        if (_updatedFlags & Flags::FLAG_SHIFTJIS)
            delete[] _shiftJis;
        strcpy(_shiftJis, input);
        _updatedFlags = Flags::FLAG_SHIFTJIS;
    }

    /// <summary>
    /// Sets the instance's <b>ISO-8859-X</b> value.
    /// <param><c>char&ast; input</c>: ISO-8859-X char* string to be set. 
    /// <c>int format</c>: ISO-8859 Format.</param>
    /// <example> instance.SetISO8859X(text, MorphText::ISO_8859_3);</example>
    /// </summary>
    void SetISO8859X(const char* input, const int format)
    {
        switch (format)
        {
        case ISO_8859_2:
            if (_updatedFlags & Flags::FLAG_ISO_8859_2)
                delete[] _iso_8859_2;
            strcpy(_iso_8859_2, input);
            _updatedFlags = Flags::FLAG_ISO_8859_2;
            break;
        case ISO_8859_3:
            if (_updatedFlags & Flags::FLAG_ISO_8859_3)
                delete[] _iso_8859_3;
            strcpy(_iso_8859_3, input);
            _updatedFlags = Flags::FLAG_ISO_8859_3;
            break;
        case ISO_8859_4:
            if (_updatedFlags & Flags::FLAG_ISO_8859_4)
                delete[] _iso_8859_4;
            strcpy(_iso_8859_4, input);
            _updatedFlags = Flags::FLAG_ISO_8859_4;
            break;
        case ISO_8859_5:
            if (_updatedFlags & Flags::FLAG_ISO_8859_5)
                delete[] _iso_8859_5;
            strcpy(_iso_8859_5, input);
            _updatedFlags = Flags::FLAG_ISO_8859_5;
            break;
        case ISO_8859_6:
            if (_updatedFlags & Flags::FLAG_ISO_8859_6)
                delete[] _iso_8859_6;
            strcpy(_iso_8859_6, input);
            _updatedFlags = Flags::FLAG_ISO_8859_6;
            break;
        case ISO_8859_7:
            if (_updatedFlags & Flags::FLAG_ISO_8859_7)
                delete[] _iso_8859_7;
            strcpy(_iso_8859_7, input);
            _updatedFlags = Flags::FLAG_ISO_8859_7;
            break;
        case ISO_8859_8:
            if (_updatedFlags & Flags::FLAG_ISO_8859_8)
                delete[] _iso_8859_8;
            strcpy(_iso_8859_8, input);
            _updatedFlags = Flags::FLAG_ISO_8859_8;
            break;
        case ISO_8859_9:
            if (_updatedFlags & Flags::FLAG_ISO_8859_9)
                delete[] _iso_8859_9;
            strcpy(_iso_8859_9, input);
            _updatedFlags = Flags::FLAG_ISO_8859_9;
            break;
        case ISO_8859_10:
            if (_updatedFlags & Flags::FLAG_ISO_8859_10)
                delete[] _iso_8859_10;
            strcpy(_iso_8859_10, input);
            _updatedFlags = Flags::FLAG_ISO_8859_10;
            break;
        case ISO_8859_11:
            if (_updatedFlags & Flags::FLAG_ISO_8859_11)
                delete[] _iso_8859_11;
            strcpy(_iso_8859_11, input);
            _updatedFlags = Flags::FLAG_ISO_8859_11;
            break;
        case ISO_8859_13:
            if (_updatedFlags & Flags::FLAG_ISO_8859_13)
                delete[] _iso_8859_13;
            strcpy(_iso_8859_13, input);
            _updatedFlags = Flags::FLAG_ISO_8859_13;
            break;
        case ISO_8859_14:
            if (_updatedFlags & Flags::FLAG_ISO_8859_14)
                delete[] _iso_8859_14;
            strcpy(_iso_8859_14, input);
            _updatedFlags = Flags::FLAG_ISO_8859_14;
            break;
        case ISO_8859_15:
            if (_updatedFlags & Flags::FLAG_ISO_8859_15)
                delete[] _iso_8859_15;
            strcpy(_iso_8859_15, input);
            _updatedFlags = Flags::FLAG_ISO_8859_15;
            break;
        case ISO_8859_16:
            if (_updatedFlags & Flags::FLAG_ISO_8859_16)
                delete[] _iso_8859_16;
            strcpy(_iso_8859_16, input);
            _updatedFlags = Flags::FLAG_ISO_8859_16;
            break;
        default:// ISO 8859-1
            if (_updatedFlags & Flags::FLAG_ISO_8859_1)
                delete[] _iso_8859_1;
            strcpy(_iso_8859_1, input);
            _updatedFlags = Flags::FLAG_ISO_8859_1;
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
        _updatedFlags = Flags::FLAG_UTF8;
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
            _updatedFlags = Flags::FLAG_UTF16BE;
        }
        else
        {
            _utf16LE = input;
            _updatedFlags = Flags::FLAG_UTF16LE;
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
            _utf32LE = input;
            _updatedFlags = Flags::FLAG_UTF32BE;
        }
        else
        {
            _utf32LE = input;
            _updatedFlags = Flags::FLAG_UTF32LE;
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

    void SetMaxLength(const uint32_t length)
    {
        _maxLength = length;
    }

    /// <summary>
    /// Sets the left-hand instance to a <b>copie</b> of the right-hand instance
    /// </summary>
    void operator = (const MorphText& other)
    {
        this->~MorphText();
        initArrays();
        _utf8 = other._utf8;
        _utf16LE = other._utf16LE;
        _utf16BE = other._utf16BE;
        _utf32LE = other._utf32LE;
        _utf32BE = other._utf32BE;
        if(other._ascii) strcpy(_ascii, other._ascii);
        if (other._iso_8859_1) strcpy(_iso_8859_1, other._iso_8859_1);
        if (other._iso_8859_2) strcpy(_iso_8859_2, other._iso_8859_2);
        if (other._iso_8859_3) strcpy(_iso_8859_3, other._iso_8859_3);
        if (other._iso_8859_4) strcpy(_iso_8859_4, other._iso_8859_4);
        if (other._iso_8859_5) strcpy(_iso_8859_5, other._iso_8859_5);
        if (other._iso_8859_6) strcpy(_iso_8859_6, other._iso_8859_6);
        if (other._iso_8859_7) strcpy(_iso_8859_7, other._iso_8859_7);
        if (other._iso_8859_8) strcpy(_iso_8859_8, other._iso_8859_8);
        if (other._iso_8859_9) strcpy(_iso_8859_9, other._iso_8859_9);
        if (other._iso_8859_10) strcpy(_iso_8859_10, other._iso_8859_10);
        if (other._iso_8859_11) strcpy(_iso_8859_11, other._iso_8859_11);
        if (other._iso_8859_13) strcpy(_iso_8859_13, other._iso_8859_13);
        if (other._iso_8859_14) strcpy(_iso_8859_14, other._iso_8859_14);
        if (other._iso_8859_15) strcpy(_iso_8859_15, other._iso_8859_15);
        if (other._iso_8859_16) strcpy(_iso_8859_16, other._iso_8859_16);
        if (other._shiftJis) strcpy(_shiftJis, other._shiftJis);
        _updatedFlags = other._updatedFlags;
    }

    void Test()
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;

        std::cout << "ASCII: " << _ascii << " --- updated: " << (bool)(_updatedFlags & FLAG_ASCII) << "\n";
        std::cout << "LATIN1: " << _iso_8859_1 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_1) << "\n";
        std::cout << "LATIN2: " << _iso_8859_2 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_2) << "\n";
        std::cout << "LATIN3: " << _iso_8859_3 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_3) << "\n";
        std::cout << "LATIN4: " << _iso_8859_4 << " --- updated: " << (bool)(_updatedFlags & FLAG_ISO_8859_4) << "\n";
        std::cout << "UTF-8: " << _utf8 << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF8) << "\n";
        std::wcout << L"UTF-16LE: " << _utf16LE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16LE) << "\n";
        std::wcout << L"UTF-16BE: " << _utf16BE << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF16BE) << "\n";
        std::cout << "UTF-32LE: " << converter.to_bytes(_utf32LE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32LE) << "\n";
        std::cout << "UTF-32BE: " << converter.to_bytes(_utf32BE) << " --- updated: " << (bool)(_updatedFlags & FLAG_UTF32BE) << "\n";
        std::cout << "\n\n\n\n";
    }
};