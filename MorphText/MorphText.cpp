#include "MorphText.hpp"
#include <bit>
#include <unordered_map>

MorphText::MorphText(const std::string& str, const int encoding)
{
    switch (encoding)
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
        case SHIFTJIS_CP932: {
            _shiftJis_cp932 = str;
            _updatedFlags |= FLAG_SHIFTJIS_CP932;
        } break;
        case JIS_X_0201_FULLWIDTH: {
            _jis_x_0201_fullwidth = str;
            _updatedFlags |= FLAG_JIS_X_0201_FULLWIDTH;
        } break;
        case JIS_X_0201_HALFWIDTH: {
            _jis_x_0201_halfwidth = str;
            _updatedFlags |= FLAG_JIS_X_0201_HALFWIDTH;
        } break;
        case KS_X_1001: {
            _ks_x_1001 = str;
            _updatedFlags |= FLAG_KS_X_1001;
        } break;
        case POKEMON_GEN1_ENGLISH: {
            _pokemon_gen1_english = str;
            _updatedFlags |= FLAG_POKEMON_GEN1_ENGLISH;
        } break;
        case POKEMON_GEN1_FRENCH_GERMAN: {
            _pokemon_gen1_french_german = str;
            _updatedFlags |= FLAG_POKEMON_GEN1_FRENCH_GERMAN;
        } break;
        case POKEMON_GEN1_ITALIAN_SPANISH: {
            _pokemon_gen1_italian_spanish = str;
            _updatedFlags |= FLAG_POKEMON_GEN1_ITALIAN_SPANISH;
        } break;
        case POKEMON_GEN1_JAPANESE: {
            _pokemon_gen1_japanese = str;
            _updatedFlags |= FLAG_POKEMON_GEN1_JAPANESE;
        } break;
        case POKEMON_GEN2_ENGLISH: {
            _pokemon_gen2_english = str;
            _updatedFlags |= FLAG_POKEMON_GEN2_ENGLISH;
        } break;
        default: // UTF8
        {
            _utf8 = str;
            _updatedFlags |= FLAG_UTF8;
            _primaryEncoding = UTF8;
            return;
        }
    }

    _primaryEncoding = encoding;
}

MorphText::MorphText(const std::wstring& str, const int encoding)
{
    switch(encoding)
    {
        case UTF16BE:
            _utf16BE = str;
            _updatedFlags |= FLAG_UTF16BE;
            _primaryEncoding = UTF16BE;
            break;
        default://UTF16LE or invalid
            _utf16LE = str;
            _updatedFlags |= FLAG_UTF16LE;
            _primaryEncoding = UTF16LE;
    }
}

MorphText::MorphText(const std::u32string& str, const int encoding)
{
    switch (encoding)
    {
    case UTF32BE:
        _utf32BE = str;
        _updatedFlags |= FLAG_UTF32BE;
        _primaryEncoding = UTF32BE;
        break;
    default://UTF32LE or invalid
        _utf32LE = str;
        _updatedFlags |= FLAG_UTF32LE;
        _primaryEncoding = UTF32LE;
    }
}

MorphText::MorphText(const char* charStr, const int encoding)
{
    *this = MorphText(std::string(charStr), encoding);
}

MorphText::MorphText(const wchar_t* charStr, const int encoding)
{
    *this = MorphText(std::wstring(charStr), encoding);
}

MorphText::MorphText(const char32_t* charStr, const int encoding)
{
    *this = MorphText(std::u32string(charStr), encoding);
}

MorphText::MorphText(char* charStr, const int encoding)
{
    *this = MorphText(std::string(charStr), encoding);
}

MorphText::MorphText(wchar_t* charStr, const int encoding)
{
    *this = MorphText(std::wstring(charStr), encoding);
}

MorphText::MorphText(char32_t* charStr, const int encoding)
{
    *this = MorphText(std::u32string(charStr), encoding);
}

MorphText::MorphText(const MorphText& other)
{
    *this = other;
}

std::string MorphText::utf8ToAscii(const std::string& input)
{
    std::wstring temp = utf8ToUtf16le(input);

    for (wchar_t& ch : temp)
    {
        if (ch > 0x7f)
            ch = '?';
    }

    return utf16leToUtf8(temp);
}

std::string MorphText::asciiToUtf8(const std::string input)
{
    std::string output = input.c_str();

    for (char& c : output)
        if (c < 0)
            c = '?';

    return output;
}

std::wstring MorphText::utf8ToUtf16le(const std::string& input)
{
    return utf8ToUtf16Helper(input, !isLittleEndian());
}

std::string MorphText::utf16leToUtf8(const std::wstring& input)
{
    return utf16ToUtf8Helper(input, !isLittleEndian());
}

std::wstring MorphText::utf8ToUtf16be(const std::string& input)
{
    return utf8ToUtf16Helper(input, isLittleEndian());
}

std::string MorphText::utf16beToUtf8(const std::wstring& input)
{
    return utf16ToUtf8Helper(input, isLittleEndian());
}

std::u32string MorphText::utf8ToUtf32le(const std::string& input)
{
    return utf8ToUtf32Helper(input, !isLittleEndian());
}


std::string MorphText::utf32leToUtf8(const std::u32string& input)
{
    return utf32ToUtf8Helper(input, !isLittleEndian());
}

std::u32string MorphText::utf8ToUtf32be(const std::string& input)
{
    return utf8ToUtf32Helper(input, isLittleEndian());
}

std::string MorphText::utf32beToUtf8(const std::u32string& input)
{
    return utf32ToUtf8Helper(input, isLittleEndian());
}

std::string MorphText::utf8ToIso8859x(const std::string& input, const int encoding)
{
    const std::wstring utf16 = utf8ToUtf16le(input);
    wchar_t* lookup;

    switch (encoding)
    {
        case ISO_8859_1:
            lookup = (wchar_t*)_iso8859_1_map;
            break;
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
        default: //invalid
            throw("Invalid ISO 8859 identifier");
            return input;
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

std::string MorphText::iso8859xToUtf8(const std::string input, const int encoding)
{
    std::wstring temp(input.size(), '\0');
    wchar_t* lookup;

    switch (encoding)
    {
        case ISO_8859_1:
            lookup = (wchar_t*)_iso8859_1_map;
            break;
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
        default: //invalid
            throw("Invalid ISO 8859 identifier");
            return input;
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

std::string MorphText::shiftjisToUtf8(const std::string& input)
{
    int inputIndex = -1;
    std::string output(input.size(), 0);
    std::wstring temp(input.size(), 0);

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
        /*else if (input[inputIndex] > 0xFD)
            temp[i] = L'©';
        else if (input[inputIndex] > 0xFE)
            temp[i] = L'™';
        else if (input[inputIndex] > 0xFF)
            temp[i] = L'…';*/
        else if ((input[inputIndex] > 0x7f && input[inputIndex + 1] < 0x40) && (input[inputIndex] <= 0xA0 && input[inputIndex + 1] > 0x4F))
            temp[i] = L'?';
        else if (ch > 0xA0 && ch < 0xE0) //Half Width Katakana and such
            temp[i] = 0xFEC0 + ch;
        else if (ch >= 0x81 && ch <= 0xFF)
        {
            uint16_t sjIndex = ch << 8;
            ++inputIndex;
            sjIndex |= input[inputIndex] & 0xFF;
            temp[i] = _shift_jis_CP932_map[sjIndex - 0x8140];
        }
        else if (input[inputIndex] < 0x80)
            temp[i] = input[inputIndex];
        else
            temp[i] = 0x8148;
    }

    temp = temp.c_str();
    return utf16leToUtf8(temp);
}

std::string MorphText::utf8ToShiftjis(const std::string& input)
{
    int outputIndex = -1;
    std::wstring utf16 = utf8ToUtf16le(input);
    int length = utf16.size();
    std::string output(length * 2 + 1, '\0');

    for (int i = 0; i < utf16.size(); ++i)
    {
        ++outputIndex;
        wchar_t ch = utf16[i];

        if (utf16[i] == L'¥')
            output[outputIndex] = 0x5C;
        else if (utf16[i] == L'‾')
            output[outputIndex] = 0x7E;
        /*else if (utf16[i] == L'©')
            output[outputIndex] = 0xFD;
        else if (utf16[i] == L'™')
            output[outputIndex] = 0xFE;
        else if (utf16[i] == L'…')
            output[outputIndex] = 0xFF;*/
        else if (utf16[i] < 0x80)
            output[outputIndex] = static_cast<char>(utf16[i]);
        else if (utf16[i] > 0xFF60 && utf16[i] < 0xFFA0) //Half Width Katakana and such
            output[outputIndex] = utf16[i] - 0xFEC0;
        else if (utf16[i] >= 0xF0 && utf16[i] <= 0xFF)
            output[outputIndex] = '\?';
        else if (utf16[i] == L'\0')
            break;
        else
            for (uint16_t lookupIndex = 0; lookupIndex < 0x7B10; ++lookupIndex)
            {
                if (_shift_jis_CP932_map[lookupIndex] == ch)
                {
                    output[outputIndex] = static_cast<char>((lookupIndex + 0x8140) >> 8); //mind endianness
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

std::string MorphText::utf8ToJisx0201fullwidth(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
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
        else if (utf16[i] < 0xA1)
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
                else if (lookupIndex == 0x5F)
                    output[i] = L'?';
            }
    }

    return output;
}

std::string MorphText::jisx0201fullwidthToUtf8(const std::string& input)
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
            temp[i] = L'?';
        else if (input[i] > 0x7f && input[i] < 0xA1)
            temp[i] = L'?';
        else
            temp[i] = input[i];
    }

    return utf16leToUtf8(temp);
}

std::string MorphText::utf8ToJisx0201halfwidth(const std::string input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
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

std::string MorphText::jisx0201halfwidthToUtf8(const std::string& input)
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
            temp[i] = L'?';
        else if (input[i] > 0x7f && input[i] < 0xA1)
            temp[i] = L'?';
        else
            temp[i] = input[i];
    }

    return utf16leToUtf8(temp);
}

std::string MorphText::utf8ToKsx1001(const std::string& input)
{
    int outputIndex = -1;
    std::wstring utf16 = utf8ToUtf16le(input);
    int length = utf16.size();
    std::string output(length * 2 + 1, '\0');
    const uint16_t charOffset = 0xA1A0;

    for (int i = 0; i < utf16.size(); ++i)
    {
        ++outputIndex;
        wchar_t ch = utf16[i];

        if(ch == L'₩')
            output[outputIndex] = 0x5C;
        else if (utf16[i] < 0x80)
            output[outputIndex] = static_cast<char>(utf16[i]);
        else if (utf16[i] == L'\0')
            break;
        else
            for (uint16_t lookupIndex = 0; lookupIndex < 0x5C80; ++lookupIndex)
            {
                if (_ks_x_1001_map[lookupIndex] == ch)
                {
                    output[outputIndex] = static_cast<char>((lookupIndex + charOffset) >> 8); //mind endianness
                    ++outputIndex;
                    output[outputIndex] = static_cast<char>(lookupIndex + charOffset);
                    break;
                }
                else if (lookupIndex > 0x5C8E)
                {
                    output[outputIndex] = charOffset + 0x2330; //ideographic ？
                }
            }
    }

    return output.c_str();
}

std::string MorphText::ksx1001ToUtf8(const std::string& input)
{
    int inputIndex = -1;
    std::string output(input.size(), '\0');
    std::wstring temp(input.size(), L'\0');
    const uint16_t charOffset = 0xA1A0;
    int32_t currentCharOffset;

    for (int i = 0; i < input.size(); ++i)
    {
        ++inputIndex;

        if (inputIndex >= input.size())
            break;

        uint8_t ch = (uint8_t)input[inputIndex];
        //currentCharOffset = charOffset - input[i];

        if (input[inputIndex] == 0x5C)
            temp[i] = L'₩';
        else if (ch >= 0xA1 && ch <= 0xFD)
        {
            uint16_t ksIndex = ch << 8;
            ++inputIndex;
            ksIndex |= input[inputIndex] & 0xFF;
            ksIndex -= 0xA1A0;
            temp[i] = _ks_x_1001_map[ksIndex] == 0x0000 ? L'？' : _ks_x_1001_map[ksIndex];
        }
        else if (input[inputIndex] < 0x80)
            temp[i] = input[inputIndex];
        else
            temp[i] = L'?';
    }

    temp = temp.c_str();
    return utf16leToUtf8(temp);
}

std::string MorphText::utf8ToPokemonGen1English(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
    std::string output(utf16.size(), '\0');
    int stepBack = 0; //needed if '-esc found

    for (int i = 0; i < output.size(); ++i)
    {
        output[i - stepBack] = utf16charToPokemonGen1and2AlphaNumeric(utf16[i]);

        if (output[i - stepBack])
        {
            continue;
        }
        else if (utf16[i] == L'‥')
        {
            output[i - stepBack] = 0x75;
        }
        else if (utf16[i] == L'\'')
        {
            switch (utf16[i + 1])
            {
                case L'd':
                    output[i-stepBack] = 0xBB;
                    break;
                case L'l':
                    output[i-stepBack] = 0xBC;
                    break;
                case L's':
                    output[i-stepBack] = 0xBD;
                    break;
                case L't':
                    output[i-stepBack] = 0xBE;
                    break;
                case L'v':
                    output[i-stepBack] = 0xBF;
                    break;
                case L'r':
                    output[i-stepBack] = 0xE4;
                    break;
                case L'm':
                    output[i-stepBack] = 0xE5;
                    break;
                default:
                    output[i-stepBack] = 0xE0;
                    --i;
                    --stepBack;
            }
            ++i;
            ++stepBack;
        }
        else
        {
            for (int j = 0; j < 0x100 - 0x60; ++j)
            {
                if (_pokemon_gen1_english_map[j] == utf16[i])
                {
                    output[i-stepBack] = j + 0x60;
                    break;
                }

                if (j == 0x100 - 0x60 - 1)
                    output[i-stepBack] = 0xE6;
            }
        }
    }

    return output.c_str();
}

std::string MorphText::pokemonGen1EnglishToUtf8(const std::string& input)
{
    std::wstring utf16(input.size()*2, '\0'); //mind double-chars like 's
    int stepForward = 0; //needed if '-esc found

    for (int i = 0; i < input.size(); ++i)
    {
        uint8_t ch = input[i];
        
        if ((ch >= 0xBB && ch <= 0xBF) || ch == 0xE4 || ch == 0xE5)
        {
            utf16[i + stepForward] = L'\'';
            ++stepForward;

            switch (ch)
            {
                case 0xBB:
                    utf16[i + stepForward] = L'd';
                    break;
                case 0xBC:
                    utf16[i + stepForward] = L'l';
                    break;
                case 0xBD:
                    utf16[i + stepForward] = L's';
                    break;
                case 0xBE:
                    utf16[i + stepForward] = L't';
                    break;
                case 0xBF:
                    utf16[i + stepForward] = L'v';
                    break;
                case 0xE4:
                    utf16[i + stepForward] = L'r';
                    break;
                case 0xE5:
                    utf16[i + stepForward] = L'm';
                    break;
            }
        }
        else if (ch >= 0x60 && ch <= 0xFF)
            utf16[i + stepForward] = _pokemon_gen1_english_map[ch - 0x60];
        else
            utf16[i + stepForward] = L'?';
    }

    return utf16leToUtf8(utf16.c_str());
}

std::string MorphText::utf8ToPokemonGen1FrenchGerman(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
    std::string output(utf16.size(), '\0');
    int stepBack = 0; //needed if '-esc found
    
    static const std::unordered_map<wchar_t, std::pair<uint8_t, uint8_t>> charMap =
    {
        {L'c', {0xD4, 0xA2}},
        {L'd', {0xD5, 0xA3}},
        {L'j', {0xD6, 0xA9}},
        {L'l', {0xD7, 0xAB}},
        {L'm', {0xD8, 0xAC}},
        {L'n', {0xD9, 0xAD}},
        {L'p', {0xDA, 0xAF}},
        {L's', {0xDB, 0xB2}},
        {L't', {0xDD, 0xB3}},
        {L'u', {0xDE, 0xB4}},
        {L'y', {0xDF, 0xB8}},
    };

    for (int i = 0; i < output.size(); ++i)
    {
        if (charMap.find(utf16[i]) != charMap.end())
        {
            auto [accentedChar, normalChar] = charMap.at(utf16[i]);

            if (utf16[i + 1] == L'\'') 
            {
                output[i - stepBack] = accentedChar;
                ++i;
                ++stepBack;
            }
            else 
            {
                output[i - stepBack] = normalChar;
            }
        }
        else if (utf16[i] == L'\'')
        {
            if (utf16[i + 1] == L's')
            {
                output[i - stepBack] = 0xBC;
                ++i;
                ++stepBack;
            }
            else
                output[i - stepBack] = 0xE0;
        }
        else if (output[i - stepBack] =  utf16charToPokemonGen1and2AlphaNumeric(utf16[i]))
        {                           //^this is meant to be an assignment
            continue;
        }
        else if (utf16[i] == L'‥')
        {
            output[i - stepBack] = 0x75;
        }
        else
        {
            for (int j = 0; j < 0x100 - 0x60; ++j)
            {
                if (_pokemon_gen1_french_german_map[j] == utf16[i])
                {
                    output[i - stepBack] = j + 0x60;
                    break;
                }

                if (j == 0x100 - 0x60 - 1)
                    output[i - stepBack] = 0xE6;
            }
        }
    }

    return output.c_str();
}

std::string MorphText::pokemonGen1FrenchGermanToUtf8(const std::string& input)
{
    std::wstring utf16(input.size() * 2, '\0'); //mind double-chars like 's
    int stepForward = 0; //needed if '-esc found

    for (int i = 0; i < input.size(); ++i)
    {
        uint8_t ch = input[i];

        if (ch == 0xDC)
        {
            utf16[i + stepForward] = L'\'';
            ++stepForward;
            utf16[i + stepForward] = L's';
        }
        else if (ch >= 0xD4 && ch <= 0xDF)
        {
            switch (ch)
            {
            case 0xD4:
                utf16[i + stepForward] = L'c';
                break;
            case 0xD5:
                utf16[i + stepForward] = L'd';
                break;
            case 0xD6:
                utf16[i + stepForward] = L'j';
                break;
            case 0xD7:
                utf16[i + stepForward] = L'l';
                break;
            case 0xD8:
                utf16[i + stepForward] = L'm';
                break;
            case 0xD9:
                utf16[i + stepForward] = L'n';
                break;
            case 0xDA:
                utf16[i + stepForward] = L'p';
                break;
            case 0xDB:
                utf16[i + stepForward] = L's';
                break;
            case 0xDD:
                utf16[i + stepForward] = L't';
                break;
            case 0xDE:
                utf16[i + stepForward] = L'u';
                break;
            case 0xDF:
                utf16[i + stepForward] = L'y';
                break;
            }

            ++stepForward;
            utf16[i + stepForward] = L'\'';
        }
        else if (ch >= 0x60 && ch <= 0xFF)
            utf16[i + stepForward] = _pokemon_gen1_french_german_map[ch - 0x60];
        else
            utf16[i + stepForward] = L'?';
    }

    return utf16leToUtf8(utf16.c_str());
}


std::string MorphText::utf8ToPokemonGen1ItalianSpanish(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
    std::string output(utf16.size(), '\0');
    int stepBack = 0; //needed if '-esc found

    for (int i = 0; i < output.size(); ++i)
    {
        output[i - stepBack] = utf16charToPokemonGen1and2AlphaNumeric(utf16[i]);

        if (output[i - stepBack])
        {
            continue;
        }
        else if (utf16[i] == L'‥')
        {
            output[i - stepBack] = 0x75;
        }
        else if (utf16[i] == L'\'')
        {
            switch (utf16[i + 1])
            {
            case L'd':
                output[i - stepBack] = 0xD8;
                break;
            case L'l':
                output[i - stepBack] = 0xD9;
                break;
            case L'm':
                output[i - stepBack] = 0xDA;
                break;
            case L'r':
                output[i - stepBack] = 0xDB;
                break;
            case L's':
                output[i - stepBack] = 0xDC;
                break;
            case L't':
                output[i - stepBack] = 0xDD;
                break;
            case L'v':
                output[i - stepBack] = 0xDE;
                break;
            default:
                output[i - stepBack] = 0xE0;
                --i;
                --stepBack;
            }
            ++i;
            ++stepBack;
        }
        else
        {
            for (int j = 0; j < 0x100 - 0x60; ++j)
            {
                if (_pokemon_gen1_italian_spanish_map[j] == utf16[i])
                {
                    output[i - stepBack] = j + 0x60;
                    break;
                }

                if (j == 0x100 - 0x60 - 1)
                    output[i - stepBack] = 0xE6;
            }
        }
    }

    return output.c_str();
}

std::string MorphText::pokemonGen1ItalianSpanishToUtf8(const std::string& input)
{
    std::wstring utf16(input.size() * 2, '\0'); //mind double-chars like 's
    int stepForward = 0; //needed if '-esc found

    for (int i = 0; i < input.size(); ++i)
    {
        uint8_t ch = input[i];

        if (ch >= 0xD8 && ch <= 0xDE)
        {
            utf16[i + stepForward] = L'\'';
            ++stepForward;

            switch (ch)
            {
            case 0xD8:
                utf16[i + stepForward] = L'd';
                break;
            case 0xD9:
                utf16[i + stepForward] = L'l';
                break;
            case 0xDA:
                utf16[i + stepForward] = L'm';
                break;
            case 0xDB:
                utf16[i + stepForward] = L'r';
                break;
            case 0xDC:
                utf16[i + stepForward] = L's';
                break;
            case 0xDD:
                utf16[i + stepForward] = L't';
                break;
            case 0xDE:
                utf16[i + stepForward] = L'v';
                break;
            }
        }
        else if (ch >= 0x60 && ch <= 0xFF)
            utf16[i + stepForward] = _pokemon_gen1_italian_spanish_map[ch - 0x60];
        else
            utf16[i + stepForward] = L'?';
    }

    return utf16leToUtf8(utf16.c_str());
}


std::string MorphText::utf8ToPokemonGen1Japanese(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
    std::string output(input.size(), '\0');
    int stepBackwards = 0; //needed if esc chars

    static const std::unordered_map<wchar_t, std::pair<uint8_t, uint8_t>> charMap =
    {
        {L'イ', {0x02, 0x81}},
        {L'エ', {0x04, 0x83}},
        {L'オ', {0x05, 0x84}},
        {L'ナ', {0x14, 0x94}},
        {L'ニ', {0x15, 0x85}},
        {L'ヌ', {0x16, 0x96}},
        {L'ネ', {0x17, 0x97}},
        {L'ノ', {0x18, 0x98}},
        {L'マ', {0x1D, 0x9D}},
        {L'ミ', {0x1E, 0x9E}},
        {L'ム', {0x1F, 0x9F}},
        {L'ィ', {0x20, 0xB0}},
        {L'あ', {0x21, 0xB1}},
        {L'い', {0x22, 0xB2}},
        {L'え', {0x24, 0xB4}},
        {L'お', {0x25, 0xB5}},
        {L'な', {0x35, 0xC5}},
        {L'に', {0x36, 0xC6}},
        {L'ぬ', {0x37, 0xC8}},
        {L'ね', {0x38, 0xC9}},
        {L'の', {0x39, 0xCA}}
    };

    for (int i = 0; i < utf16.size(); ++i)
    {
        wchar_t inputChar = utf16[i];
        wchar_t inputCharAhead = (i + 1) < utf16.size() ? utf16[i + 1] : 0;

        if (inputCharAhead == L'ま')
        {
            if (inputCharAhead == 0x3099 || inputCharAhead == 0xFF9E || inputCharAhead == 0x309B)
            {
                output[i - stepBackwards] = 0x3F;
                ++i;
                ++stepBackwards;
            }
            else if (inputCharAhead == 0x309A || inputCharAhead == 0x309C || inputCharAhead == 0xFF9F)
            {
                output[i - stepBackwards] = 0x49;
                ++i;
                ++stepBackwards;
            }
            else
                output[i - stepBackwards] = 0xCF;
        }
        else if (charMap.find(inputChar) != charMap.end())
        {
            auto [marked, normal] = charMap.at(inputChar);

            if (inputCharAhead == 0x3099 || inputCharAhead == 0xFF9E || inputCharAhead == 0x309B)
            {
                output[i - stepBackwards] = marked;
                ++i;
                ++stepBackwards;
            }
            else
                output[i - stepBackwards] = normal;
        }
        else if (inputChar == L'も')
        {
            if (inputCharAhead == 0x309A || inputCharAhead == 0x309C || inputCharAhead == 0xFF9F)
            {
                output[i - stepBackwards] = 0x4D;
                ++i;
                ++stepBackwards;
            }
            else
                output[i - stepBackwards] = 0xD3;
        }
        else if (utf16[i] == L'‥')
        {
            output[i - stepBackwards] = 0x75;
        }
        else if (utf16[i] == L' ')
        {
            output[i - stepBackwards] = 0x7F;
        }
        else if (utf16[i] == L'?')
        {
            output[i - stepBackwards] = 0xE6;
        }
        else if (utf16[i] == L'!')
        {
            output[i - stepBackwards] = 0xE7;
        }
        else
        {
            for (int j = 0; j < 0x100; ++j)
            {
                if (_pokemon_gen1_japanese_map[j] == inputChar)
                {
                    output[i - stepBackwards] = j;
                    break;
                }

                if(j == 0xFF)
                    output[i - stepBackwards] = 0xE6;
            }
        }
    }

    return output.c_str();
}

std::string MorphText::pokemonGen1JapaneseToUtf8(const std::string& input)
{
    std::wstring output(input.size() * 2, '\0'); //mind double-chars like 's
    int stepForward = 0; //needed if '-esc found

    static const std::unordered_map<uint8_t, wchar_t> charMap =
    {
        {0x02, L'イ' },
        {0x04, L'エ' },
        {0x05, L'オ' },
        {0x14, L'ナ' },
        {0x15, L'ニ' },
        {0x16, L'ヌ' },
        {0x17, L'ネ' },
        {0x18, L'ノ' },
        {0x1D, L'マ' },
        {0x1E, L'ミ' },
        {0x1F, L'ム' },
        {0x20, L'ィ' },
        {0x21, L'あ' },
        {0x22, L'い' },
        {0x24, L'え' },
        {0x25, L'お' },
        {0x35, L'な' },
        {0x36, L'に' },
        {0x37, L'ぬ' },
        {0x38, L'ね' },
        {0x39, L'の' },
        {0x3F, L'ま' }
    };

    for (int i = 0; i < input.size(); ++i)
    {
        uint8_t ch = input[i];

        if (ch == 0x4D || ch == 0x49)
        {
            output[i + stepForward] = ch == 0x4D ? L'も' : L'ま';
            ++stepForward;
            output[i + stepForward] = 0x309A;
        }
        else if (charMap.find(ch) != charMap.end())
        {
            output[i + stepForward] = charMap.at(ch);
            ++stepForward;
            output[i + stepForward] = 0x3099;
        }
        else
            output[i + stepForward] = _pokemon_gen1_japanese_map[ch];
    }

    return utf16leToUtf8(output.c_str());
}


std::string MorphText::utf8ToPokemonGen2English(const std::string& input)
{
    std::wstring utf16 = utf8ToUtf16le(input);
    std::string output(utf16.size(), '\0');
    int stepBack = 0; //needed if '-esc found

    for (int i = 0; i < output.size(); ++i)
    {
        output[i - stepBack] = utf16charToPokemonGen1and2AlphaNumeric(utf16[i]);

        if (output[i - stepBack])
        {
            continue;
        }
        else if (utf16[i] == L'‥')
        {
            output[i - stepBack] = 0x75;
        }
        else if (utf16[i] == L'\'')
        {
            switch (utf16[i + 1])
            {
            case L'd':
                output[i - stepBack] = 0xD0;
                break;
            case L'l':
                output[i - stepBack] = 0xD1;
                break;
            case L'm':
                output[i - stepBack] = 0xD2;
                break;
            case L'r':
                output[i - stepBack] = 0xD3;
                break;
            case L's':
                output[i - stepBack] = 0xD4;
                break;
            case L't':
                output[i - stepBack] = 0xD5;
                break;
            case L'v':
                output[i - stepBack] = 0xD6;
                break;
            default:
                output[i - stepBack] = 0xE0;
                --i;
                --stepBack;
            }
            ++i;
            ++stepBack;
        }
        else if (utf16[i] == L'“' || utf16[i] == L'『')
        {
            output[i - stepBack] = 0x72;
        }
        else if (utf16[i] == L'”' || utf16[i] == L'』')
        {
            output[i - stepBack] = 0x73;
        }
        else
        {
            for (int j = 0; j < 0x100 - 0x60; ++j)
            {
                if (_pokemon_gen2_english_map[j] == utf16[i])
                {
                    output[i - stepBack] = j + 0x60;
                    break;
                }

                if (j == 0x100 - 0x60 - 1)
                    output[i - stepBack] = 0xE6;
            }
        }
    }

    return output.c_str();
}

std::string MorphText::pokemonGen2EnglishToUtf8(const std::string& input)
{
    std::wstring utf16(input.size() * 2, '\0'); //mind double-chars like 's
    int stepForward = 0; //needed if '-esc found

    for (int i = 0; i < input.size(); ++i)
    {
        uint8_t ch = input[i];

        if (ch >= 0xD0 && ch <= 0xD6)
        {
            utf16[i + stepForward] = L'\'';
            ++stepForward;

            switch (ch)
            {
            case 0xD0:
                utf16[i + stepForward] = L'd';
                break;
            case 0xD1:
                utf16[i + stepForward] = L'l';
                break;
            case 0xD2:
                utf16[i + stepForward] = L'm';
                break;
            case 0xD3:
                utf16[i + stepForward] = L'r';
                break;
            case 0xD4:
                utf16[i + stepForward] = L's';
                break;
            case 0xD5:
                utf16[i + stepForward] = L't';
                break;
            case 0xD6:
                utf16[i + stepForward] = L'v';
                break;
            }
        }
        else if (ch >= 0x60 && ch <= 0xFF)
            utf16[i + stepForward] = _pokemon_gen2_english_map[ch - 0x60];
        else
            utf16[i + stepForward] = L'?';
    }

    return utf16leToUtf8(utf16.c_str());
}

bool MorphText::compareRaw(const char* lhs, const char* rhs)
{
    const int len = strlen(lhs);

    for (int i = 0; i < len; ++i)
        if (lhs[i] != rhs[i])
            return false;

    return true;
}

bool MorphText::compareRaw(const wchar_t* lhs, const wchar_t* rhs)
{
    const int len = wcslen(lhs);

    for (int i = 0; i < len; ++i)
        if (lhs[i] != rhs[i])
            return false;

    return true;
}

bool MorphText::compareRaw(const char32_t* lhs, const char32_t* rhs)
{
    const int len = std::char_traits<char32_t>::length(lhs);

    for (int i = 0; i < len; ++i)
        if (lhs[i] != rhs[i])
            return false;

    return true;
}

void MorphText::replaceIllegalChars(std::u32string& str, const bool isBE)
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

std::string MorphText::convertFromUtf8_singleByte(std::string& input, const int encoding)
{
    switch (encoding)
    {
        case ASCII:
            return utf8ToAscii(input);
        case ISO_8859_1: case ISO_8859_2: case ISO_8859_3: case ISO_8859_4:
        case ISO_8859_5: case ISO_8859_6: case ISO_8859_7: case ISO_8859_8:
        case ISO_8859_9: case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
        case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
            return utf8ToIso8859x(input, encoding);
        case SHIFTJIS_CP932:
            return utf8ToShiftjis(input);
        case JIS_X_0201_FULLWIDTH:
            return utf8ToJisx0201fullwidth(input);
        case JIS_X_0201_HALFWIDTH:
            return utf8ToJisx0201halfwidth(input);
        case KS_X_1001:
            return utf8ToKsx1001(input);
        case POKEMON_GEN1_ENGLISH:
            return utf8ToPokemonGen1English(input);
        case POKEMON_GEN1_FRENCH_GERMAN:
            return utf8ToPokemonGen1FrenchGerman(input);
        case POKEMON_GEN1_ITALIAN_SPANISH:
            return utf8ToPokemonGen1ItalianSpanish(input);
        case POKEMON_GEN1_JAPANESE:
            return utf8ToPokemonGen1Japanese(input);
        case POKEMON_GEN2_ENGLISH:
            return utf8ToPokemonGen2English(input);
        default: //invalid format value
        {
            return input;
        }
    }
}

std::wstring MorphText::convertFromUtf8_doubleByte(std::string& input, const int encoding)
{
    switch (encoding)
    {
        case UTF16LE:
            return utf8ToUtf16le(input);
        case UTF16BE:
            return utf8ToUtf16be(input);
        default: //invalid format value
        {
            return std::wstring(reinterpret_cast<const wchar_t*>(input.c_str()));
        }
    }
}

std::u32string MorphText::convertFromUtf8_quatrupleByte(std::string& input, const int encoding)
{
    switch (encoding)
        {
        case UTF32LE:
            return utf8ToUtf32le(input);
        case UTF32BE:
            return utf8ToUtf32be(input);
        default: //invalid format value
        {
            return std::u32string(reinterpret_cast<const char32_t*>(input.c_str()));
        }
    }
}

void MorphText::m_convertToUtf8()
{
    if (_updatedFlags & FLAG_UTF8)
        return;

    if (_updatedFlags & FLAG_ISO_8859_1)
        m_iso8859xToUtf8(ISO_8859_1);
    else if (_updatedFlags & FLAG_ISO_8859_2)
        m_iso8859xToUtf8(ISO_8859_2);
    else if (_updatedFlags & FLAG_ISO_8859_3)
        m_iso8859xToUtf8(ISO_8859_3);
    else if (_updatedFlags & FLAG_ISO_8859_4)
        m_iso8859xToUtf8(ISO_8859_4);
    else if (_updatedFlags & FLAG_ISO_8859_5)
        m_iso8859xToUtf8(ISO_8859_5);
    else if (_updatedFlags & FLAG_ISO_8859_6)
        m_iso8859xToUtf8(ISO_8859_6);
    else if (_updatedFlags & FLAG_ISO_8859_7)
        m_iso8859xToUtf8(ISO_8859_7);
    else if (_updatedFlags & FLAG_ISO_8859_8)
        m_iso8859xToUtf8(ISO_8859_8);
    else if (_updatedFlags & FLAG_ISO_8859_9)
        m_iso8859xToUtf8(ISO_8859_9);
    else if (_updatedFlags & FLAG_ISO_8859_10)
        m_iso8859xToUtf8(ISO_8859_10);
    else if (_updatedFlags & FLAG_ISO_8859_11)
        m_iso8859xToUtf8(ISO_8859_11);
    else if (_updatedFlags & FLAG_ISO_8859_13)
        m_iso8859xToUtf8(ISO_8859_13);
    else if (_updatedFlags & FLAG_ISO_8859_14)
        m_iso8859xToUtf8(ISO_8859_14);
    else if (_updatedFlags & FLAG_ISO_8859_15)
        m_iso8859xToUtf8(ISO_8859_15);
    else if (_updatedFlags & FLAG_ISO_8859_16)
        m_iso8859xToUtf8(ISO_8859_16);
    else if (_updatedFlags & FLAG_UTF16LE)
        m_utf16LeToUtf8();
    else if (_updatedFlags & FLAG_UTF16BE)
        m_utf16BeToUtf8();
    else if (_updatedFlags & FLAG_UTF32LE)
        m_utf32LeToUtf8();
    else if (_updatedFlags & FLAG_UTF32BE)
        m_utf32BeToUtf8();
    else if (_updatedFlags & FLAG_JIS_X_0201_FULLWIDTH)
        m_jisX0201FWToUtf8();
    else if (_updatedFlags & FLAG_JIS_X_0201_HALFWIDTH)
        m_jisX0201HWToUtf8();
    else if (_updatedFlags & FLAG_KS_X_1001)
        m_ksX1001ToUtf8();
    else if (_updatedFlags & FLAG_SHIFTJIS_CP932)
        m_shiftJis_cp932ToUtf8();
    else if (_updatedFlags & FLAG_POKEMON_GEN1_ENGLISH)
        m_pokemonGen1EnglishToUtf8();
    else if (_updatedFlags & FLAG_POKEMON_GEN1_FRENCH_GERMAN)
        m_pokemonGen1FrenchGermanToUtf8();
    else if (_updatedFlags & FLAG_POKEMON_GEN1_ITALIAN_SPANISH)
        m_pokemonGen1ItalianSpanishToUtf8();
    else if (_updatedFlags & FLAG_POKEMON_GEN1_JAPANESE)
        m_pokemonGen1JapaneseToUtf8();    
    else if (_updatedFlags & FLAG_POKEMON_GEN2_ENGLISH)
        m_pokemonGen2EnglishToUtf8();
    else
        m_asciiToUtf8();
}

void MorphText::m_jisX0201FWToUtf8()
{
    _utf8 = jisx0201fullwidthToUtf8(_jis_x_0201_fullwidth);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToJisX0201FW()
{
    _jis_x_0201_fullwidth = utf8ToJisx0201fullwidth(_utf8);
    _updatedFlags |= FLAG_JIS_X_0201_FULLWIDTH;
}

void MorphText::m_jisX0201HWToUtf8()
{
    _utf8 = jisx0201halfwidthToUtf8(_jis_x_0201_halfwidth);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToJisX0201HW()
{
    _jis_x_0201_halfwidth = utf8ToJisx0201halfwidth(_utf8);
    _updatedFlags |= FLAG_JIS_X_0201_HALFWIDTH;
}

void MorphText::m_utf16LeToUtf8()
{
    _utf8 = utf16leToUtf8(_utf16LE);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToUtf16le()
{
    _utf16LE = utf8ToUtf16le(_utf8);
    _updatedFlags |= FLAG_UTF16LE;
}

void MorphText::m_utf16BeToUtf8()
{
    _utf8 = utf16beToUtf8(_utf16BE);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToUtf16Be()
{
    _utf16BE = utf8ToUtf16be(_utf8);
    _updatedFlags |= FLAG_UTF16BE;
}

void MorphText::m_utf32LeToUtf8()
{
    _utf8 = utf32leToUtf8(_utf32LE);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToUtf32Le()
{
    _utf32LE = utf8ToUtf32le(_utf8);
    _updatedFlags |= FLAG_UTF32LE;
}

void MorphText::m_utf32BeToUtf8()
{
    _utf8 = utf32beToUtf8(_utf32BE);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToUtf32Be()
{
    _utf32BE = utf8ToUtf32be(_utf8);
    _updatedFlags |= FLAG_UTF32BE;
}

void MorphText::m_asciiToUtf8()
{
    _utf8 = asciiToUtf8(_ascii);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToAscii()
{
    _ascii = convertFromUTF8<std::string>(_utf8, ASCII);
    _updatedFlags |= FLAG_ASCII;
}

void MorphText::m_iso8859xToUtf8(const int encoding)
{
    std::string txt;

    switch (encoding)
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

    _utf8 = iso8859xToUtf8(txt, encoding);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToIso8859x(const int encoding)
{
    switch (encoding)
    {
    case ISO_8859_2:
        _iso_8859_2 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_3:
        _iso_8859_3 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_4:
        _iso_8859_4 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_5:
        _iso_8859_5 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_6:
        _iso_8859_6 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_7:
        _iso_8859_7 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_8:
        _iso_8859_8 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_9:
        _iso_8859_9 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_10:
        _iso_8859_10 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_11:
        _iso_8859_11 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_13:
        _iso_8859_13 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_14:
        _iso_8859_14 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_15:
        _iso_8859_15 = utf8ToIso8859x(_utf8, encoding);
        break;
    case ISO_8859_16:
        _iso_8859_16 = utf8ToIso8859x(_utf8, encoding);
        break;
    default:// ISO 8859-1
        _iso_8859_1 = utf8ToIso8859x(_utf8, encoding);
        break;
    }

    _updatedFlags |= (encoding >= ISO_8859_1 && encoding <= ISO_8859_16) ? (1 << encoding) : ISO_8859_1;
}

void MorphText::m_utf8ToShiftJis()
{
    _shiftJis_cp932 = utf8ToShiftjis(_utf8);
    _updatedFlags |= FLAG_SHIFTJIS_CP932;
}

void MorphText::m_shiftJis_cp932ToUtf8()
{
    _utf8 = shiftjisToUtf8(_shiftJis_cp932);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToKsX1001()
{
    _ks_x_1001 = utf8ToKsx1001(_utf8);
    _updatedFlags |= FLAG_KS_X_1001;
}

void MorphText::m_ksX1001ToUtf8()
{
    _utf8 = ksx1001ToUtf8(_ks_x_1001);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_pokemonGen1EnglishToUtf8()
{
    _utf8 = pokemonGen1EnglishToUtf8(_pokemon_gen1_english);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToPokemonGen1English()
{
    _pokemon_gen1_english = utf8ToPokemonGen1English(_utf8);
    _updatedFlags |= FLAG_POKEMON_GEN1_ENGLISH;
}

void MorphText::m_pokemonGen1FrenchGermanToUtf8()
{
    _utf8 = pokemonGen1FrenchGermanToUtf8(_pokemon_gen1_french_german);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToPokemonGen1FrenchGerman()
{
    _pokemon_gen1_french_german = utf8ToPokemonGen1FrenchGerman(_utf8);
    _updatedFlags |= FLAG_POKEMON_GEN1_FRENCH_GERMAN;
}

void MorphText::m_pokemonGen1ItalianSpanishToUtf8()
{
    _utf8 = pokemonGen1ItalianSpanishToUtf8(_pokemon_gen1_italian_spanish);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToPokemonGen1ItalianSpanish()
{
    _pokemon_gen1_italian_spanish = utf8ToPokemonGen1ItalianSpanish(_utf8);
    _updatedFlags |= FLAG_POKEMON_GEN1_ITALIAN_SPANISH;
}

void MorphText::m_pokemonGen1JapaneseToUtf8()
{
    _utf8 = pokemonGen1JapaneseToUtf8(_pokemon_gen1_japanese);
    _updatedFlags |= FLAG_UTF8;
}

void MorphText::m_utf8ToPokemonGen1Japanese()
{
    _pokemon_gen1_japanese = utf8ToPokemonGen1Japanese(_utf8);
    _updatedFlags |= FLAG_POKEMON_GEN1_JAPANESE;
}

void MorphText::m_utf8ToPokemonGen2English()
{
    _pokemon_gen2_english = utf8ToPokemonGen2English(_utf8);
    _updatedFlags |= FLAG_POKEMON_GEN2_ENGLISH;
}

void MorphText::m_pokemonGen2EnglishToUtf8()
{
    _utf8 = pokemonGen2EnglishToUtf8(_pokemon_gen2_english);
    _updatedFlags |= FLAG_UTF8;
}

bool MorphText::isLittleEndian()
{
    const uint16_t flag = 0x0001;
    return *reinterpret_cast<const bool*>(&flag);
}

/*

int MorphText::findRaw(const wchar_t* superset, const wchar_t* subset, const bool caseSensitive)
{
    const int supersetLength = wcslen(superset);
    const int subsetLength = wcslen(subset);

    if (supersetLength < subsetLength)
        return -1;

    if (caseSensitive)
    {
        for (int i = 0; i < supersetLength - subsetLength; ++i)
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
        wchar_t currentSuperset;
        wchar_t currentSubset;

        for (int i = 0; i < supersetLength - subsetLength; ++i)
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

int MorphText::findRaw(const char32_t* superset, const char32_t* subset, const bool caseSensitive)
{
    const int supersetLength = std::char_traits<char32_t>::length(superset);
    const int subsetLength = std::char_traits<char32_t>::length(subset);

    if (supersetLength < subsetLength)
        return -1;

    if (caseSensitive)
    {
        for (int i = 0; i < supersetLength - subsetLength; ++i)
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
        char currentSuperset;
        char currentSubset;

        for (int i = 0; i < supersetLength - subsetLength; ++i)
        {
            int charMatchCount = 0;
            for (int j = 0; j < strlen(subset); ++j)
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
}*/

std::wstring MorphText::utf8ToUtf16Helper(const std::string& str, const bool byteSwap)
{
    if (byteSwap)
    {
        std::wstring output = utf8ToUtf16Helper(str, false);

        for (wchar_t& ch : output)
            ch = std::byteswap(ch);

        return output;
    }
    else
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        return converter.from_bytes(str.c_str());
    }
}

std::string MorphText::sanitizeUtf8(const std::string& input)
{
    std::string output;
    for (size_t i = 0; i < input.size(); )
    {
        unsigned char c = input[i];
        if (c <= 0x7F) {
            // Valid single-byte character
            output += c;
            ++i;
        }
        else if ((c >= 0xC2 && c <= 0xDF) && (i + 1 < input.size()) &&
            (input[i + 1] >= 0x80 && input[i + 1] <= 0xBF)) 
        {
            // Valid two-byte sequence
            output += c;
            output += input[i + 1];
            i += 2;
        }
        else if ((c >= 0xE0 && c <= 0xEF) && (i + 2 < input.size()) &&
            (input[i + 1] >= 0x80 && input[i + 1] <= 0xBF) &&
            (input[i + 2] >= 0x80 && input[i + 2] <= 0xBF))
        {
            // Valid three-byte sequence
            output += c;
            output += input[i + 1];
            output += input[i + 2];
            i += 3;
        }
        else if ((c >= 0xF0 && c <= 0xF4) && (i + 3 < input.size()) &&
            (input[i + 1] >= 0x80 && input[i + 1] <= 0xBF) &&
            (input[i + 2] >= 0x80 && input[i + 2] <= 0xBF) &&
            (input[i + 3] >= 0x80 && input[i + 3] <= 0xBF))
        {
            // Valid four-byte sequence
            output += c;
            output += input[i + 1];
            output += input[i + 2];
            output += input[i + 3];
            i += 4;
        }
        else
        {
            // Invalid sequence, replace with '?'
            output += '?';
            ++i;
        }
    }
    return output;
}

std::string MorphText::utf16ToUtf8Helper(const std::wstring& str, const bool byteSwap)
{
    if (byteSwap)
    {
        std::wstring temp = str;

        for (wchar_t& ch : temp)
            ch = std::byteswap(ch);

        return utf16ToUtf8Helper(temp, false);
    }
    else
        return std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>>().to_bytes(str.c_str());
}

std::u32string MorphText::utf8ToUtf32Helper(const std::string& str, const bool byteSwap)
{
    if (byteSwap)
    {
        std::u32string output = utf8ToUtf32Helper(str, false);

        for (char32_t& ch : output)
            ch = std::byteswap(ch);

        return output;
    }
    else
    {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.from_bytes(str.c_str());
    }
}

std::string MorphText::utf32ToUtf8Helper(const std::u32string& str, const bool byteSwap)
{
    if (byteSwap)
    {
        std::u32string temp = str;

        for (char32_t& ch : temp)
            ch = std::byteswap(ch);//swapBytes(&ch);

        return utf32ToUtf8Helper(temp, false);
    }
    else
    {
        std::u32string unchecked = str.c_str();
        replaceIllegalChars(unchecked);
        return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(unchecked);
    }
}

uint8_t MorphText::utf16charToPokemonGen1and2AlphaNumeric(const wchar_t ch)
{
    if (ch >= L'A' && ch <= L'Z')
        return ch + 0x80 - L'A';
    else if (ch >= L'a' && ch <= L'z')
        return ch + 0xA0 - L'a';
    else if (ch >= L'0' && ch <= L'9')
        return ch + 0xF6 - L'0';
    
    return 0;
}

uint8_t MorphText::pokemonGen1and2EsItSwapCaseSpecial(const uint8_t key, const bool upperToLower)
{
    static const std::unordered_map<uint8_t, uint8_t> charMapUpperToLower =
    {
        {0xBE, 0xBA},
        {0xBF, 0xCF},
        {0xC0, 0xC3},
        {0xC1, 0xC4},
        {0xC2, 0xC5},
        {0xC6, 0xBB},
        {0xC7, 0xBC},
        {0xC8, 0xD0},
        {0xC9, 0xD1},
        {0xCA, 0xD2},
        {0xCB, 0xD3},
        {0xCC, 0xD4},
        {0xCD, 0xBD},
        {0xCE, 0xD5}
    };

    static const std::unordered_map<uint8_t, uint8_t> charMapLowerToUpper =
    {
        {0xBA, 0xBE},
        {0xCF, 0xBF},
        {0xC3, 0xC0},
        {0xC4, 0xC1},
        {0xC5, 0xC2},
        {0xBB, 0xC6},
        {0xBC, 0xC7},
        {0xD0, 0xC8},
        {0xD1, 0xC9},
        {0xD2, 0xCA},
        {0xD3, 0xCB},
        {0xD4, 0xCC},
        {0xBD, 0xCD},
        {0xD5, 0xCE}
    };

    if (upperToLower)
    {
        if (charMapUpperToLower.find(key) != charMapUpperToLower.end())
            return charMapUpperToLower.at(key);
    }
    else
    {
        if (charMapLowerToUpper.find(key) != charMapLowerToUpper.end())
            return charMapLowerToUpper.at(key);
    }

    return key;
}

int MorphText::GetPrimaryFormat() const
{
    return _primaryEncoding;
}

std::string MorphText::ToLower(const std::string& input, const int encoding)
{
    std::string result = input;

    switch (encoding)
    {
        case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
        case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
        case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
        case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
        case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
        case SHIFTJIS_CP932: case KS_X_1001:
        {
            result = convertToUTF8<std::string>(input, encoding);
            result = ToLower(result, UTF8);
            return convertFromUTF8<std::string>(result, encoding);
        }
        case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH: {
            for (int i = 0; i < result.size(); ++i)
                if (result[i] < 0x7F)
                    result[i] = std::tolower(result[i]);

            return result;
        }
        case POKEMON_GEN1_ENGLISH: case POKEMON_GEN2_ENGLISH: {
            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = ch + 0x20;
            }
            return result;
        }
        case POKEMON_GEN1_FRENCH_GERMAN: {
            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = ch + 0x20;
                else if(ch >= 0xC0 && ch <= 0xC2)
                    result[i] = ch + 3;
            }
            return result;
        }
        case POKEMON_GEN1_ITALIAN_SPANISH: {


            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = ch + 0x20;
                else
                    result[i] = pokemonGen1and2EsItSwapCaseSpecial(ch, true);
            }
            return result;
        }
        case POKEMON_GEN1_JAPANESE:
            return result;
        default: { //UTF8, ASCII
            std::transform(result.begin(), result.end(), result.begin(), tolower);
            return result;
        }
    }
}

std::wstring MorphText::ToLower(const std::wstring& input, const int encoding)
{
    std::string temp = convertToUTF8<std::wstring>(input, encoding);
    temp = ToLower(temp);
    return convertFromUTF8<std::wstring>(temp, encoding);
}

std::u32string MorphText::ToLower(const std::u32string& input, const int encoding)
{
    std::string temp = convertToUTF8<std::u32string>(input, encoding);
    temp = ToLower(temp);
    return convertFromUTF8<std::u32string>(temp, encoding);
}

wchar_t* MorphText::ToLower(const wchar_t* input, const int encoding)
{
    const int length = wcslen(input) + 1;
    wchar_t* result = new wchar_t[length];
    wcscpy_s(result, length, input);

    switch (encoding)
    {
        case UTF16BE:
            for (wchar_t* i = result; i < result + length; ++i)
            {
                *i = std::byteswap(*i);

                if (*i != '\0')
                    break;

                *i = std::towlower(*i);
                *i = std::byteswap(*i);
            }
            break;
        default: //UTF16LE or invalid encoding
        {
            for (wchar_t* i = result; *i != '\0'; ++i)
                *i = std::towlower(*i);
        }
    }

    return result;
}

char32_t* MorphText::ToLower(const char32_t* input, const int encoding)
{
    const int length = std::char_traits<char32_t>::length(input) + 1;
    char32_t* result = new char32_t[length];
    std::char_traits<char32_t>::copy(result, input, length);

    switch (encoding)
    {
        case UTF32BE:
            for (char32_t* i = result; i < result + length; ++i)
            {
                *i = std::byteswap(*i);

                if (*i != '\0')
                    break;

                *i = std::towlower(*i);
                *i = std::byteswap(*i);
            }
        break;
        default: //UTF32LE, invalid encoding
            for (char32_t* i = result; *i != '\0'; ++i)
                *i = std::towlower(*i);
    }

    return result;
}

std::string MorphText::ToUpper(const std::string& input, const int encoding)
{
    std::string result = input;

    switch (encoding)
    {
        case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
        case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
        case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
        case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
        case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
        case SHIFTJIS_CP932: case KS_X_1001:
        {
            result = convertToUTF8<std::string>(input, encoding);
            result = ToUpper(result, UTF8);
            return convertFromUTF8<std::string>(result, encoding);
        }
        case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH: {
            for (int i = 0; i < result.size(); ++i)
                if (result[i] < 0x7F)
                    result[i] = std::toupper(result[i]);

            return result;
        }
        case POKEMON_GEN1_ENGLISH: case POKEMON_GEN2_ENGLISH: {
            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = ch - 0x20;
            }
            return result;
        }
        case POKEMON_GEN1_FRENCH_GERMAN: {
            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = ch - 0x20;
                else if (ch >= 0xC3 && ch <= 0xC5)
                    result[i] = ch - 3;
            }
            return result;
        }
        case POKEMON_GEN1_ITALIAN_SPANISH:
        {
            uint8_t ch;
            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = ch - 0x20;
                else
                    result[i] = pokemonGen1and2EsItSwapCaseSpecial(ch, false);
            }
            return result;
        }
        case POKEMON_GEN1_JAPANESE:
            return result;
        default: { //UTF8, ASCII
            std::transform(result.begin(), result.end(), result.begin(), toupper);
            return result;
        }
    }
}

std::wstring MorphText::ToUpper(const std::wstring& input, const int encoding)
{
    std::string temp = convertToUTF8<std::wstring>(input, encoding);
    temp = ToUpper(temp);
    return convertFromUTF8<std::wstring>(temp, encoding);
}

std::u32string MorphText::ToUpper(const std::u32string& input, const int encoding)
{
    std::string temp = convertToUTF8<std::u32string>(input, encoding);
    temp = ToUpper(temp);
    return convertFromUTF8<std::u32string>(temp, encoding);
}

wchar_t* MorphText::ToUpper(const wchar_t* input, const int encoding)
{
    const int length = wcslen(input) + 1;
    wchar_t* result = new wchar_t[length];
    wcscpy_s(result, length, input);

    switch (encoding)
    {
        case UTF16BE:
            for (wchar_t* i = result; i < result + length; ++i)
            {
                *i = std::byteswap(*i);

                if (*i != '\0')
                    break;

                *i = std::towupper(*i);
                *i = std::byteswap(*i);
            }
            break;
        default: //UTF16LE, invalid encoding
            for (wchar_t* i = result; *i != '\0'; ++i)
              *i = std::towupper(*i);
    }

    return result;
}

char32_t* MorphText::ToUpper(const char32_t* input, const int encoding)
{
    int length = std::char_traits<char32_t>::length(input) + 1;
    char32_t* result = new char32_t[length];
    std::char_traits<char32_t>::copy(result, input, length);

    switch (encoding)
    {
        case UTF32BE:
            for (char32_t* i = result; i < result + length; ++i)
            {
                *i = std::byteswap(*i);

                if (*i != '\0')
                    break;

                *i = std::towupper(*i);
                *i = std::byteswap(*i);
            }
        break;
        default: //UTF32LE, invalid encoding
            for (char32_t* i = result; *i != '\0'; ++i)
                *i = std::towupper(*i);
    }

    return result;
}

std::string MorphText::ToSarcasm(const std::string& input, const int encoding)
{
    std::string result = input;

    switch (encoding)
    {
        case ISO_8859_1:  case ISO_8859_2:  case ISO_8859_3:
        case ISO_8859_4:  case ISO_8859_5:  case ISO_8859_6:
        case ISO_8859_7:  case ISO_8859_8:  case ISO_8859_9:
        case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
        case ISO_8859_14: case ISO_8859_15: case ISO_8859_16:
        case SHIFTJIS_CP932: case KS_X_1001:
        {
            result = convertToUTF8<std::string>(input, encoding);
            result = ToSarcasm(result, UTF8);
            return convertFromUTF8<std::string>(result, encoding);
        }
        case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH:
        {
            for (int i = 0; i < result.size(); ++i)
                if (result[i] < 0x7F)
                    result[i] = i & 1 ? std::tolower(result[i]) : std::toupper(result[i]);

            return result;
        }
        case POKEMON_GEN1_ENGLISH: case POKEMON_GEN2_ENGLISH:
        {
            uint8_t ch;

            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = (i & 1) ? ch + 0x20 : ch;
                else if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = (i & 1) == 0 ? ch - 0x20 : ch;
            }
            return result;
        }
        case POKEMON_GEN1_FRENCH_GERMAN:
        {
            uint8_t ch;

            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = (i & 1) ? ch + 0x20 : ch;
                else if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = (i & 1) == 0 ? ch - 0x20 : ch;
                else if (ch >= 0xC0 && ch <= 0xC2)
                    result[i] = (i & 1) ? ch + 3 : ch;
                else if (ch >= 0xC3 && ch <= 0xC5)
                    result[i] = (i & 1) == 0 ? ch - 3 : ch;
            }
            return result;
        }
        case POKEMON_GEN1_ITALIAN_SPANISH:
        {
            uint8_t ch;

            for (int i = 0; i < result.size(); ++i)
            {
                ch = result[i];

                if (ch >= 0x80 && ch <= 0x99)
                    result[i] = (i & 1) ? ch + 0x20 : ch;
                else if (ch >= 0xA0 && ch <= 0xB9)
                    result[i] = (i & 1) == 0 ? ch - 0x20 : ch;
                else
                    result[i] = pokemonGen1and2EsItSwapCaseSpecial(ch, i & 1);
            }
            return result;
        }
        case POKEMON_GEN1_JAPANESE:
            return result;
        default: //UTF8, ASCII
        {
            for (int i = 0; i < result.size(); ++i)
                result[i] = (i & 1) ? std::tolower(input[i]) : std::toupper(input[i]);

            return result;
        }
    }
}

std::wstring MorphText::ToSarcasm(const std::wstring& input, const int encoding)
{
    std::string temp = convertToUTF8<std::wstring>(input, encoding);
    temp = ToSarcasm(temp);
    return convertFromUTF8<std::wstring>(temp, encoding);
}

std::u32string MorphText::ToSarcasm(const std::u32string& input, const int encoding)
{
    std::string temp = convertToUTF8<std::u32string>(input, encoding);
    temp = ToSarcasm(temp);
    return convertFromUTF8<std::u32string>(temp, encoding);
}

wchar_t* MorphText::ToSarcasm(const wchar_t* input, const int encoding)
{
    const int length = wcslen(input) + 1;
    wchar_t* result = new wchar_t[length];
    wcscpy_s(result, length, ToSarcasm(std::wstring(input), encoding).c_str());
    return result;
}

char32_t* MorphText::ToSarcasm(const char32_t* input, const int encoding)
{
    const int length = std::char_traits<char32_t>::length(input) + 1;
    char32_t* result = new char32_t[length];
    std::char_traits<char32_t>::copy(result, ToSarcasm(std::u32string(input), encoding).c_str(), length);
    return result;
}

bool MorphText::Compare(const std::string& lhs, const std::string& rhs, const bool caseSensitive, const int encoding)
{
    std::string lhsOperand = caseSensitive ? lhs : ToLower(lhs, encoding);
    std::string rhsOperand = caseSensitive ? rhs : ToLower(rhs, encoding);

    return lhsOperand.compare(rhsOperand) == 0;
}

bool MorphText::Compare(const std::wstring& lhs, const std::wstring& rhs, const bool caseSensitive, const int encoding)
{
    std::string lhsOperand;
    std::string rhsOperand;

    switch (encoding)
    {
        case UTF16BE:
        {
            lhsOperand = caseSensitive ? utf16beToUtf8(lhs) : ToLower(utf16beToUtf8(lhs), encoding);
            rhsOperand = caseSensitive ? utf16beToUtf8(rhs) : ToLower(utf16beToUtf8(rhs), encoding);
        } break;
        default: //UTF16LE, invalid encoding
        {
            lhsOperand = caseSensitive ? utf16leToUtf8(lhs) : ToLower(utf16leToUtf8(lhs), encoding);
            rhsOperand = caseSensitive ? utf16leToUtf8(rhs) : ToLower(utf16leToUtf8(rhs), encoding);
        }
    }

    return lhsOperand.compare(rhsOperand) == 0;
}

bool MorphText::Compare(const std::u32string& lhs, const std::u32string& rhs, const bool caseSensitive, const int encoding)
{
    std::string lhsOperand;
    std::string rhsOperand;

    switch (encoding)
    {
    case UTF32BE:
        lhsOperand = caseSensitive ? utf32beToUtf8(lhs) : ToLower(utf32beToUtf8(lhs), encoding);
        rhsOperand = caseSensitive ? utf32beToUtf8(rhs) : ToLower(utf32beToUtf8(rhs), encoding);
        break;
    default://UTF32LE, invalid encoding
        lhsOperand = caseSensitive ? utf32leToUtf8(lhs) : ToLower(utf32leToUtf8(lhs), encoding);
        rhsOperand = caseSensitive ? utf32leToUtf8(rhs) : ToLower(utf32leToUtf8(rhs), encoding);
    }

    return lhsOperand.compare(rhsOperand) == 0;
}

bool MorphText::Compare(const char* lhs, const char* rhs, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case SHIFTJIS_CP932: case KS_X_1001: case JIS_X_0201_FULLWIDTH: case JIS_X_0201_HALFWIDTH:
        case ISO_8859_1: case ISO_8859_2: case ISO_8859_3: case ISO_8859_4:
        case ISO_8859_5: case ISO_8859_6: case ISO_8859_7: case ISO_8859_8:
        case ISO_8859_9: case ISO_8859_10: case ISO_8859_11: case ISO_8859_13:
        case ISO_8859_14: case ISO_8859_15: case ISO_8859_16: case POKEMON_GEN1_ENGLISH:
        case POKEMON_GEN1_FRENCH_GERMAN: case POKEMON_GEN1_ITALIAN_SPANISH: case POKEMON_GEN1_JAPANESE:
        case POKEMON_GEN2_ENGLISH:
        {
            if (!caseSensitive)
            {
                const std::string lowerLhs = ToLower(lhs, encoding);
                const std::string lowerRhs = ToLower(rhs, encoding);
                return compareRaw(lowerLhs.c_str(), lowerRhs.c_str());
            }

            return compareRaw(lhs, rhs);
        }
        default: //UTF8, ASCII
        {
            if (!caseSensitive)
            {
                const std::string lowerLhs = ToLower(lhs, encoding);
                const std::string lowerRhs = ToLower(rhs, encoding);
                return strcmp(lowerLhs.c_str(), lowerRhs.c_str()) == 0;
            }
            return strcmp(lhs, rhs) == 0;
        }
    }
}

bool MorphText::Compare(const wchar_t* lhs, const wchar_t* rhs, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case UTF16BE:
        {
            if (caseSensitive)
                return compareRaw(lhs, rhs);
            else
            {
                const std::wstring lowerLhs = ToLower(std::wstring(lhs), encoding);
                const std::wstring lowerRhs = ToLower(std::wstring(rhs), encoding);
                return Compare(lowerLhs, lowerRhs, true, UTF16LE);
            }
        }
        default: //UTF16LE, invaliid encoding
        {
            if (caseSensitive)
                return wcscmp(lhs, rhs) == 0;
            else
            {
                const std::wstring lowerLhs = ToLower(std::wstring(lhs), encoding);
                const std::wstring lowerRhs = ToLower(std::wstring(rhs), encoding);
                return Compare(lowerLhs, lowerRhs, true, UTF16LE);
            }
        }
    }
}

bool MorphText::Compare(const char32_t* lhs, const char32_t* rhs, const bool caseSensitive, const int encoding)
{
    const int lhsLength = std::char_traits<char32_t>::length(lhs) + 1;
    const int lhrLength = std::char_traits<char32_t>::length(rhs) + 1;

    if (!caseSensitive)
    {
        const char32_t* lowerLhs = ToLower(lhs, encoding);
        const char32_t* lowerRhs = ToLower(rhs, encoding);
        const int result = std::char_traits<char32_t>::compare(lowerLhs, lowerRhs, lhsLength);
        delete[] lowerLhs;
        delete[] lowerRhs;
        return result == 0;
    }

    return std::char_traits<char32_t>::compare(lhs, rhs, lhsLength) == 0;
}

bool MorphText::Compare(const std::string& rhs, const bool caseSensitive, const int encoding)
{
    return Compare(GetString<std::string>(encoding), rhs, caseSensitive, encoding);
}

bool MorphText::Compare(const std::wstring& rhs, const bool caseSensitive, const int encoding)
{
    return Compare(GetString<std::wstring>(encoding), rhs, caseSensitive, encoding);
}

bool MorphText::Compare(const std::u32string& rhs, const bool caseSensitive, const int encoding)
{
    return Compare(GetString<std::u32string>(encoding), rhs, caseSensitive, encoding);
}

bool MorphText::Compare(const char* rhs, const bool caseSensitive, const int encoding)
{
    return Compare(GetString<std::string>(encoding).c_str(), rhs, caseSensitive, encoding);
    /*switch (encoding)
    {
    case ASCII:
        return Compare(_ascii.c_str(), rhs, caseSensitive, encoding);
    case SHIFTJIS_CP932:
        return Compare(_shiftJis_cp932.c_str(), rhs, caseSensitive, encoding);
    case JIS_X_0201_FULLWIDTH:
        return Compare(_jis_x_0201_fullwidth.c_str(), rhs, caseSensitive, encoding);
    case JIS_X_0201_HALFWIDTH:
        return Compare(_jis_x_0201_halfwidth.c_str(), rhs, caseSensitive, encoding);
    case KS_X_1001:
        return Compare(_ks_x_1001.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_1:
        return Compare(_iso_8859_1.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_2:
        return Compare(_iso_8859_2.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_3:
        return Compare(_iso_8859_3.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_4:
        return Compare(_iso_8859_4.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_5:
        return Compare(_iso_8859_5.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_6:
        return Compare(_iso_8859_6.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_7:
        return Compare(_iso_8859_7.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_8:
        return Compare(_iso_8859_8.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_9:
        return Compare(_iso_8859_9.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_10:
        return Compare(_iso_8859_10.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_11:
        return Compare(_iso_8859_11.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_13:
        return Compare(_iso_8859_13.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_14:
        return Compare(_iso_8859_14.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_15:
        return Compare(_iso_8859_15.c_str(), rhs, caseSensitive, encoding);
    case ISO_8859_16:
        return Compare(_iso_8859_16.c_str(), rhs, caseSensitive, encoding);
    default: //UTF8
        return Compare(_utf8.c_str(), rhs, caseSensitive, encoding);
    }*/
}

bool MorphText::Compare(const wchar_t* rhs, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
    case UTF16BE:
        return Compare(_utf16BE.c_str(), rhs, caseSensitive, encoding);
    default: //UTF16LE, invalid format
        return Compare(_utf16LE.c_str(), rhs, caseSensitive, encoding);
    }
}

bool MorphText::Compare(const char32_t* rhs, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
    case UTF32BE:
        return Compare(_utf32BE.c_str(), rhs, caseSensitive, encoding);
    default: //UTF32LE, invalid format
        return Compare(_utf32LE.c_str(), rhs, caseSensitive, encoding);
    }
}

int MorphText::Find(const std::string& superset, const std::string& subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
    case UTF8: case ASCII:
    {
        const std::string sups = caseSensitive ? superset : ToLower(superset, encoding);
        const std::string subs = caseSensitive ? subset : ToLower(subset, encoding);
        return sups.find(subs);
    }
    case POKEMON_GEN1_ENGLISH: case POKEMON_GEN1_FRENCH_GERMAN:
    case POKEMON_GEN1_ITALIAN_SPANISH: case POKEMON_GEN1_JAPANESE:
    case POKEMON_GEN2_ENGLISH:
        return findPokemonGen1(superset.c_str(), subset.c_str(), caseSensitive);
    default: //invalid format
        return findRaw<const char*>(superset.c_str(), subset.c_str(), caseSensitive);
    }
}

int MorphText::Find(const std::wstring& superset, const std::wstring& subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case UTF16LE:
        {
            const std::wstring sups = caseSensitive ? superset : ToLower(superset, encoding);
            const std::wstring subs = caseSensitive ? subset : ToLower(subset, encoding);
            return sups.find(subs);
        }
        default: //UTF16LE, invalid encoding
            return findRaw<const wchar_t*>(superset.c_str(), subset.c_str(), caseSensitive);
    }
}

int MorphText::Find(const std::u32string& superset, const std::u32string& subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case UTF32LE:
        {
            const std::u32string sups = caseSensitive ? superset : ToLower(superset, encoding);
            const std::u32string subs = caseSensitive ? subset : ToLower(subset, encoding);
            return sups.find(subs);
        }
        default: //UTF32LE, invalid encoding
            return findRaw<const char32_t*>(superset.c_str(), subset.c_str(), caseSensitive);
    }
}

int MorphText::Find(const char* superset, const char* subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case UTF8: case ASCII:
        {
            if (caseSensitive)
            {
                const char* position = strstr(superset, subset);

                if (position != nullptr)
                    return position - superset;

                return -1;
            }
            
            const std::string sups = caseSensitive ? superset : ToLower(superset, encoding);
            const std::string subs = caseSensitive ? subset : ToLower(subset, encoding);
            return sups.find(subs);
        }
        case POKEMON_GEN1_ENGLISH: case POKEMON_GEN1_FRENCH_GERMAN:
        case POKEMON_GEN1_ITALIAN_SPANISH: case POKEMON_GEN1_JAPANESE:
        case POKEMON_GEN2_ENGLISH:
            return findPokemonGen1(superset, subset, caseSensitive);
        default: //invalid format
            return findRaw<const char*>(superset, subset, caseSensitive);
    }
}


int MorphText::Find(const wchar_t* superset, const wchar_t* subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
        case UTF16LE:
        {
            if (caseSensitive)
            {
                const wchar_t* position = wcsstr(superset, subset);

                if (position != nullptr)
                    return position - superset;

                return -1;
            }

            const std::wstring sups = caseSensitive ? superset : ToLower(superset, encoding);
            const std::wstring subs = caseSensitive ? subset : ToLower(subset, encoding);
            return sups.find(subs);
        }
        default: //UTF16LE, invalid encoding
            return findRaw<const wchar_t*>(superset, subset, caseSensitive);
    }
}

int MorphText::Find(const char32_t* superset, const char32_t* subset, const bool caseSensitive, const int encoding)
{
    switch (encoding)
    {
    case UTF32LE:
    {
        if (caseSensitive)
            return findRaw(superset, subset, true);

        const std::u32string sups = caseSensitive ? superset : ToLower(superset, encoding);
        const std::u32string subs = caseSensitive ? subset : ToLower(subset, encoding);
        return sups.find(subs);
    }
    default: //UTF32LE, invalid encoding
        return findRaw<const char32_t*>(superset, subset, caseSensitive);
    }
}

int MorphText::Find(const std::string& subset, const bool caseSensitive, const int encoding)
{
    return Find(GetString<std::string>(encoding), subset, caseSensitive, encoding);
}

int MorphText::Find(const std::wstring& subset, const bool caseSensitive, const int encoding)
{
    return Find(GetString<std::wstring>(encoding), subset, caseSensitive, encoding);
}

int MorphText::Find(const std::u32string& subset, const bool caseSensitive, const int encoding)
{
    return Find(GetString<std::u32string>(encoding), subset, caseSensitive, encoding);
}

int MorphText::Find(const char* subset, const bool caseSensitive, const int encoding) const
{
    switch (encoding)
    {
    case ISO_8859_1:
        return Find(iso8859xToUtf8(_iso_8859_1, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_2:
        return Find(iso8859xToUtf8(_iso_8859_2, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_3:
        return Find(iso8859xToUtf8(_iso_8859_3, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_4:
        return Find(iso8859xToUtf8(_iso_8859_4, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_5:
        return Find(iso8859xToUtf8(_iso_8859_5, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_6:
        return Find(iso8859xToUtf8(_iso_8859_6, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_7:
        return Find(iso8859xToUtf8(_iso_8859_7, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_8:
        return Find(iso8859xToUtf8(_iso_8859_8, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_9:
        return Find(iso8859xToUtf8(_iso_8859_9, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_10:
        return Find(iso8859xToUtf8(_iso_8859_10, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_11:
        return Find(iso8859xToUtf8(_iso_8859_11, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_13:
        return Find(iso8859xToUtf8(_iso_8859_13, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_14:
        return Find(iso8859xToUtf8(_iso_8859_14, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_15:
        return Find(iso8859xToUtf8(_iso_8859_15, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case ISO_8859_16:
        return Find(iso8859xToUtf8(_iso_8859_16, encoding), iso8859xToUtf8(subset, encoding), caseSensitive);
    case SHIFTJIS_CP932:
        return Find(shiftjisToUtf8(_shiftJis_cp932), shiftjisToUtf8(subset), caseSensitive);
    case KS_X_1001:
        return Find(ksx1001ToUtf8(_ks_x_1001), ksx1001ToUtf8(subset), caseSensitive);
    case JIS_X_0201_FULLWIDTH:
        return Find(jisx0201fullwidthToUtf8(_jis_x_0201_fullwidth), jisx0201fullwidthToUtf8(subset), caseSensitive);
    case JIS_X_0201_HALFWIDTH:
        return Find(jisx0201halfwidthToUtf8(_jis_x_0201_halfwidth), jisx0201halfwidthToUtf8(subset), caseSensitive);
    case POKEMON_GEN1_ENGLISH:
        return Find(pokemonGen1EnglishToUtf8(_pokemon_gen1_english), pokemonGen1EnglishToUtf8(subset), caseSensitive);
    case POKEMON_GEN1_FRENCH_GERMAN:
        return Find(pokemonGen1FrenchGermanToUtf8(_pokemon_gen1_french_german), pokemonGen1FrenchGermanToUtf8(subset), caseSensitive);
    case POKEMON_GEN1_ITALIAN_SPANISH:
        return Find(pokemonGen1ItalianSpanishToUtf8(_pokemon_gen1_italian_spanish), pokemonGen1ItalianSpanishToUtf8(subset), caseSensitive);
    case POKEMON_GEN1_JAPANESE:
        return Find(pokemonGen1JapaneseToUtf8(_pokemon_gen1_japanese), pokemonGen1JapaneseToUtf8(subset), caseSensitive);
    case POKEMON_GEN2_ENGLISH:
        return Find(pokemonGen2EnglishToUtf8(_pokemon_gen2_english), pokemonGen2EnglishToUtf8(subset), caseSensitive);
    default: //ASCII
        return Find(asciiToUtf8(_ascii), asciiToUtf8(subset), caseSensitive);
    }
}

int MorphText::findPokemonGen1(const char* superset, const char* subset, const bool caseSensitive)
{
    if (caseSensitive)
        return findRaw(superset, subset, caseSensitive);

    int supersetLength = strlen(superset);
    int subsetLength = strlen(subset);

    if (supersetLength < subsetLength)
        return -1;

    uint8_t currentSuperset;
    uint8_t currentSubset;

    for (int i = 0; i < supersetLength - subsetLength + 1; ++i)
    {
        int charMatchCount = 0;
        for (int j = 0; j < subsetLength; ++j)
        {
            currentSuperset = superset[i + j];
            currentSubset = subset[j];

            if (currentSuperset >= 0x80 && currentSuperset <= 0x99)
                currentSuperset += 0x20;

            if (currentSubset >= 0x80 && currentSubset <= 0x99)
                currentSubset += 0x20;

            if (currentSuperset == currentSubset)
                ++charMatchCount;
        }

        if (charMatchCount == subsetLength)
            return i;
    }
}

void MorphText::SetPrimaryEncoding(const int encoding)
{
    m_convertToUtf8();
    _primaryEncoding = encoding;

    switch (encoding)
    {
        case UTF8:
            return;
        case ASCII:
            m_utf8ToAscii();
            break;
        case SHIFTJIS_CP932:
            m_utf8ToShiftJis();
            break;
        case KS_X_1001:
            m_utf8ToKsX1001();
            break;
        case JIS_X_0201_FULLWIDTH:
            m_utf8ToJisX0201FW();
            break;
        case JIS_X_0201_HALFWIDTH:
            m_utf8ToJisX0201HW();
            break;
        case POKEMON_GEN1_ENGLISH:
            m_pokemonGen1EnglishToUtf8();
            break;
        case POKEMON_GEN1_FRENCH_GERMAN:
            m_pokemonGen1FrenchGermanToUtf8();
            break;
        case POKEMON_GEN1_ITALIAN_SPANISH:
            m_pokemonGen1ItalianSpanishToUtf8();
            break;
        case POKEMON_GEN1_JAPANESE:
            m_pokemonGen1JapaneseToUtf8();
            break;
        case POKEMON_GEN2_ENGLISH:
            m_pokemonGen2EnglishToUtf8();
            break;
        case UTF16LE:
            m_utf8ToUtf16le();
            break;
        case UTF16BE:
            m_utf8ToUtf16Be();
            break;
        case UTF32LE:
            m_utf8ToUtf32Le();
            break;
        case UTF32BE:
            m_utf8ToUtf32Be();
            break;
        default: //ISO-8859-X
            m_utf8ToIso8859x(encoding);
    }
}

void MorphText::operator = (const MorphText& other)
{
    _utf8 = other._utf8;
    _utf16LE = other._utf16LE;
    _utf16BE = other._utf16BE;
    _utf32LE = other._utf32LE;
    _utf32BE = other._utf32BE;
    _ascii = other._ascii;
    _jis_x_0201_fullwidth = other._jis_x_0201_fullwidth;
    _jis_x_0201_halfwidth = other._jis_x_0201_halfwidth;
    _shiftJis_cp932 = other._shiftJis_cp932;
    _ks_x_1001 = other._ks_x_1001;
    _pokemon_gen1_english = other._pokemon_gen1_english;
    _pokemon_gen1_french_german = other._pokemon_gen1_french_german;
    _pokemon_gen1_italian_spanish = other._pokemon_gen1_italian_spanish;
    _pokemon_gen1_japanese = other._pokemon_gen1_japanese;
    _pokemon_gen2_english = other._pokemon_gen2_english;
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
    _primaryEncoding = other._primaryEncoding;
}

#ifndef NDEBUG

void MorphText::testSubRoutine(const std::string& str, const std::string& utf8, const char* hex, const int encoding)
{
    if (encoding != ISO_8859_3) //consider that ISO-8859-3 has undefined characters
        assert(Compare(str.c_str(), hex, CASE_SENSITIVE, encoding));

    std::string utf8c = Convert<std::string, std::string>(str, encoding, UTF8);
    assert(Compare(utf8c, utf8, CASE_SENSITIVE, UTF8));

    std::string testStr = Convert<const char*, std::string>("Abcd123", UTF8, encoding);
    std::string hexBin = { 0x41, 0x62, 0x63, 0x64, 0x31, 0x32, 0x33, 0x00 };

    assert(Compare(testStr.c_str(), (char*)hexBin.data(), CASE_SENSITIVE, encoding));
    assert(Compare(testStr.c_str(), "aBcD123", CASE_INSENSITIVE, encoding));
    assert(Compare(ToLower(testStr, encoding), "abcd123", CASE_SENSITIVE, encoding));
    assert(Compare(ToUpper(testStr, encoding), "ABCD123", CASE_SENSITIVE, encoding));
    assert(Compare(ToSarcasm(testStr, encoding), "AbCd123", CASE_SENSITIVE, encoding));
    assert(Find(testStr, "d1", CASE_SENSITIVE, encoding) == 3);
    assert(Find(testStr, "D1", CASE_INSENSITIVE, encoding) == 3);

    MorphText test(testStr, encoding);
    assert(test.Compare("Abcd123", CASE_SENSITIVE, encoding));
    assert(Compare(test.ToLower<std::string>(encoding), "abcd123", CASE_SENSITIVE, encoding));
    assert(Compare(test.ToUpper<std::string>(encoding), "ABCD123", CASE_SENSITIVE, encoding));
    assert(Compare(test.ToSarcasm<std::string>(encoding), "AbCd123", CASE_SENSITIVE, encoding));
    assert(test.Find(std::string("d1"), CASE_SENSITIVE, encoding) == 3);
    assert(test.Find(std::string("D1"), CASE_INSENSITIVE, encoding) == 3);
}

void MorphText::testUTF8()
{
    std::vector<uint8_t> hexBin = { 0x41, 0x62, 0x63, 0x64, 0x31, 0x32, 0x33, 0x00 };
    testSubRoutine("Abcd123", "Abcd123", (char*)hexBin.data(), UTF8);
}

void MorphText::testASCII()
{
    std::vector<uint8_t> hexBin = { 0x41, 0x62, 0x63, 0x64, 0x31, 0x32, 0x33, 0x00 };
    testSubRoutine("Abcd123", "Abcd123", (char*)hexBin.data(), ASCII);
}

void MorphText::testUTF16LE()
{
    std::string testStr = "ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니"; 
    std::wstring utf16L = Convert<std::string, std::wstring>(testStr, UTF8, UTF16LE);
    std::wstring utf16R = L"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    assert(Compare(utf16L, utf16R, CASE_SENSITIVE, UTF16LE));
    
    std::string utf8 = Convert<std::wstring, std::string>(utf16L, UTF16LE, UTF8);
    assert(Compare(utf8, testStr, CASE_SENSITIVE, UTF8));

    utf16L = L"Abcd123";
    assert(Compare(utf16L, L"abCd123", CASE_INSENSITIVE, UTF16LE));
    assert(Compare(ToLower(utf16L, UTF16LE), L"abcd123", CASE_SENSITIVE, UTF16LE));
    assert(Compare(ToUpper(utf16L, UTF16LE), L"ABCD123", CASE_SENSITIVE, UTF16LE));
    assert(Compare(ToSarcasm(utf16L, UTF16LE), L"AbCd123", CASE_SENSITIVE, UTF16LE));
    assert(Find(utf16L, L"d1", CASE_SENSITIVE, UTF16LE) == 3);
    assert(Find(utf16L, L"D1", CASE_INSENSITIVE, UTF16LE) == 3);

    MorphText test(utf16L, UTF16LE);
    assert(test.Compare(L"Abcd123", CASE_SENSITIVE, UTF16LE));
    assert(Compare(test.ToLower<std::wstring>(UTF16LE), L"abcd123", CASE_SENSITIVE, UTF16LE));
    assert(Compare(test.ToUpper<std::wstring>(UTF16LE), L"ABCD123", CASE_SENSITIVE, UTF16LE));
    assert(Compare(test.ToSarcasm<std::wstring>(UTF16LE), L"AbCd123", CASE_SENSITIVE, UTF16LE));
    assert(test.Find(L"d1", CASE_SENSITIVE, UTF16LE) == 3);
    assert(test.Find(L"D1", CASE_INSENSITIVE, UTF16LE) == 3);
}

void MorphText::testUTF16BE()
{
    std::string testStr = "ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    std::wstring utf16L = Convert<std::string, std::wstring>(testStr, UTF8, UTF16BE);
    std::wstring utf16R = L"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    for (wchar_t& ch : utf16R)
        ch = std::byteswap(ch);

    assert(Compare(utf16L, utf16R, CASE_SENSITIVE, UTF16BE));

    std::string utf8 = Convert<std::wstring, std::string>(utf16L, UTF16BE, UTF8);
    assert(Compare(utf8, testStr, CASE_SENSITIVE, UTF8));

    utf16L = L"Abc";
    for (wchar_t& ch : utf16L)
        ch = std::byteswap(ch);

    MorphText test(utf16L, UTF16BE);

    std::vector<wchar_t> bin = { 0x4100, 0x6200, 0x6300, 0x0000 };
    assert(Compare(utf16L, bin.data(), CASE_INSENSITIVE, UTF16BE)); 
    assert(test.Compare(bin.data(), CASE_SENSITIVE, UTF16BE));
    bin[0] = 0x6100;
    assert(Compare(ToLower(utf16L, UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    assert(Compare(test.ToLower<std::wstring>(UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    bin = { 0x4100, 0x4200, 0x4300, 0x0000  };
    assert(Compare(ToUpper(utf16L, UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    assert(Compare(test.ToUpper<std::wstring>(UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    bin = { 0x4100, 0x6200, 0x4300, 0x0000 };
    assert(Compare(ToSarcasm(utf16L, UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    assert(Compare(test.ToSarcasm<std::wstring>(UTF16BE), bin.data(), CASE_SENSITIVE, UTF16BE));
    bin = { 0x6300, 0x0000 };
    assert(Find(utf16L, bin.data(), CASE_SENSITIVE, UTF16BE) == 2);
    assert(test.Find(bin.data(), CASE_SENSITIVE, UTF16BE) == 2);
    bin = { 0x4300, 0x0000 };
    assert(Find(utf16L, bin.data(), CASE_INSENSITIVE, UTF16BE) == 2);
    assert(test.Find(bin.data(), CASE_INSENSITIVE, UTF16BE) == 2);
}

void MorphText::testUTF32LE()
{
    std::string testStr = "ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    std::u32string UTF32L = Convert<std::string, std::u32string>(testStr, UTF8, UTF32LE);
    std::u32string UTF32R = U"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    assert(Compare(UTF32L, UTF32R, CASE_SENSITIVE, UTF32LE));

    std::string utf8 = Convert<std::u32string, std::string>(UTF32L, UTF32LE, UTF8);
    assert(Compare(utf8, testStr, CASE_SENSITIVE, UTF8));

    UTF32L = U"Abcd123";
    assert(Compare(UTF32L, U"abCd123", CASE_INSENSITIVE, UTF32LE));
    assert(Compare(ToLower(UTF32L, UTF32LE), U"abcd123", CASE_SENSITIVE, UTF32LE));
    assert(Compare(ToUpper(UTF32L, UTF32LE), U"ABCD123", CASE_SENSITIVE, UTF32LE));
    assert(Compare(ToSarcasm(UTF32L, UTF32LE), U"AbCd123", CASE_SENSITIVE, UTF32LE));
    assert(Find(UTF32L, U"d1", CASE_SENSITIVE, UTF32LE) == 3);
    assert(Find(UTF32L, U"D1", CASE_INSENSITIVE, UTF32LE) == 3);

    MorphText test(UTF32L, UTF32LE);
    assert(test.Compare(U"Abcd123", CASE_SENSITIVE, UTF32LE));
    assert(Compare(test.ToLower<std::u32string>(UTF32LE), U"abcd123", CASE_SENSITIVE, UTF32LE));
    assert(Compare(test.ToUpper<std::u32string>(UTF32LE), U"ABCD123", CASE_SENSITIVE, UTF32LE));
    assert(Compare(test.ToSarcasm<std::u32string>(UTF32LE), U"AbCd123", CASE_SENSITIVE, UTF32LE));
    assert(test.Find(U"d1", CASE_SENSITIVE, UTF32LE) == 3);
    assert(test.Find(U"D1", CASE_INSENSITIVE, UTF32LE) == 3);
}

void MorphText::testUTF32BE()
{
    std::string testStr = "ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    std::u32string UTF32L = Convert<std::string, std::u32string>(testStr, UTF8, UTF32BE);
    std::u32string UTF32R = U"ABCabc ÄÖÜẞäöüß Ññ オオヤマネコ　おおやまねこ　大山猫　스라소니";
    for (char32_t& ch : UTF32R)
        ch = std::byteswap(ch);

    assert(Compare(UTF32L, UTF32R, CASE_SENSITIVE, UTF32BE));

    std::string utf8 = Convert<std::u32string, std::string>(UTF32L, UTF32BE, UTF8);
    assert(Compare(utf8, testStr, CASE_SENSITIVE, UTF8));

    UTF32L = U"Abc";
    for (char32_t& ch : UTF32L)
        ch = std::byteswap(ch);

    MorphText test(UTF32L, UTF32BE);

    std::vector<char32_t> bin = { 0x41000000, 0x62000000, 0x63000000, 0x00000000 };
    assert(Compare(UTF32L, bin.data(), CASE_INSENSITIVE, UTF32BE));
    assert(test.Compare(bin.data(), CASE_SENSITIVE, UTF32BE));
    bin[0] = 0x61000000;
    assert(Compare(ToLower(UTF32L, UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    assert(Compare(test.ToLower<std::u32string>(UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    bin = { 0x41000000, 0x42000000, 0x43000000, 0x00000000 };
    assert(Compare(ToUpper(UTF32L, UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    assert(Compare(test.ToUpper<std::u32string>(UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    bin = { 0x41000000, 0x62000000, 0x43000000, 0x00000000 };
    assert(Compare(ToSarcasm(UTF32L, UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    assert(Compare(test.ToSarcasm<std::u32string>(UTF32BE), bin.data(), CASE_SENSITIVE, UTF32BE));
    bin = { 0x63000000, 0x00000000 };
    assert(Find(UTF32L, bin.data(), CASE_SENSITIVE, UTF32BE) == 2);
    assert(test.Find(bin.data(), CASE_SENSITIVE, UTF32BE) == 2);
    bin = { 0x43000000, 0x00000000 };
    assert(Find(UTF32L, bin.data(), CASE_INSENSITIVE, UTF32BE) == 2);
    assert(test.Find(bin.data(), CASE_INSENSITIVE, UTF32BE) == 2);
}

void MorphText::testISO_8859_X()
{
    std::vector<std::string> utf8Strings
    {
        " ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ",
        " Ą˘Ł¤ĽŚ§¨ŠŞŤŹ­ŽŻ°ą˛ł´ľśˇ¸šşťź˝žżŔÁÂĂÄĹĆÇČÉĘËĚÍÎĎĐŃŇÓÔŐÖ×ŘŮÚŰÜÝŢßŕáâăäĺćçčéęëěíîďđńňóôőö÷řůúűüýţ˙",
        " Ħ˘£¤?Ĥ§¨İŞĞĴ­?Ż°ħ²³´µĥ·¸ışğĵ½?żÀÁÂ?ÄĊĈÇÈÉÊËÌÍÎÏ?ÑÒÓÔĠÖ×ĜÙÚÛÜŬŜßàáâ?äċĉçèéêëìíîï?ñòóôġö÷ĝùúûüŭŝ˙",
        " ĄĸŖ¤ĨĻ§¨ŠĒĢŦ­Ž¯°ą˛ŗ´ĩļˇ¸šēģŧŊžŋĀÁÂÃÄÅÆĮČÉĘËĖÍÎĪĐŅŌĶÔÕÖ×ØŲÚÛÜŨŪßāáâãäåæįčéęëėíîīđņōķôõö÷øųúûüũū˙",
        " ЁЂЃЄЅІЇЈЉЊЋЌ­ЎЏАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюя№ёђѓєѕіїјљњћќ§ўџ",
        "",
        "",
        "",
        " ¡¢£¤¥¦§¨©ª«¬­®¯°±²³´µ¶·¸¹º»¼½¾¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏĞÑÒÓÔÕÖ×ØÙÚÛÜİŞßàáâãäåæçèéêëìíîïğñòóôõö÷øùúûüışÿ",
        " ĄĒĢĪĨĶ§ĻĐŠŦŽ­ŪŊ°ąēģīĩķ·ļđšŧž―ūŋĀÁÂÃÄÅÆĮČÉĘËĖÍÎÏÐŅŌÓÔÕÖŨØŲÚÛÜÝÞßāáâãäåæįčéęëėíîïðņōóôõöũøųúûüýþĸ",
        "",
        " ”¢£¤„¦§Ø©Ŗ«¬­®Æ°±²³“µ¶·ø¹ŗ»¼½¾æĄĮĀĆÄÅĘĒČÉŹĖĢĶĪĻŠŃŅÓŌÕÖ×ŲŁŚŪÜŻŽßąįāćäåęēčéźėģķīļšńņóōõö÷ųłśūüżž’",
        " Ḃḃ£ĊċḊ§Ẁ©ẂḋỲ­®ŸḞḟĠġṀṁ¶ṖẁṗẃṠỳẄẅṡÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏŴÑÒÓÔÕÖṪØÙÚÛÜÝŶßàáâãäåæçèéêëìíîïŵñòóôõöṫøùúûüýŷÿ",
        " ¡¢£€¥Š§š©ª«¬­®¯°±²³Žµ¶·ž¹º»ŒœŸ¿ÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõö÷øùúûüýþÿ",
        " ĄąŁ€„Š§š©Ș«Ź­źŻ°±ČłŽ”¶·žčș»ŒœŸżÀÁÂĂÄĆÆÇÈÉÊËÌÍÎÏĐŃÒÓÔŐÖŚŰÙÚÛÜĘȚßàáâăäćæçèéêëìíîïđńòóôőöśűùúûüęțÿ"
    };
    
    for (int i = 0; i < utf8Strings.size(); ++i)
    {
        std::vector<uint8_t> hexBin(0x61);
        for (int hi = 0; hi < hexBin.size() - 1; ++hi)
            hexBin[hi] = hi + 0xA0;
        hexBin.back() = 0;

        int encoding = ISO_8859_1 + i;
        std::string testStr = Convert<std::string, std::string>(utf8Strings[i], UTF8, encoding);

        if (i == 5)
        {
            testStr = Convert<const char*, std::string>("test سشصض", UTF8, ISO_8859_6);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD3, 0xD4, 0xD5, 0xD6, 0xD7, 0x00 };
            assert(Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_6));
            std::string utf8Comp = "test سشصض";
            std::string utf8 = Convert<std::string, std::string>(testStr, ISO_8859_6, UTF8);
            assert(Compare(utf8Comp, utf8));
            continue;
        }
        else if (i == 6)
        {
            testStr = Convert<const char*, std::string>("test ΦΧΨΩΪ", UTF8, ISO_8859_7);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0x00 };
            assert(Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_7));
            std::string utf8Comp = "test ΦΧΨΩΪ";
            std::string utf8 = Convert<std::string, std::string>(testStr, ISO_8859_7, UTF8);
            assert(Compare(utf8Comp, utf8));
            continue;
        }
        else if (i == 7)
        {
            testStr = Convert<const char*, std::string>("test דהוזחטי", UTF8, ISO_8859_8);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9, 0x00 };
            assert(Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_8));
            std::string utf8Comp = "test דהוזחטי";
            std::string utf8 = Convert<std::string, std::string>(testStr, ISO_8859_8, UTF8);
            assert(Compare(utf8Comp, utf8));
            continue;
        }
        else if (i == 10)
        {
            testStr = Convert<const char*, std::string>("test ฃคฅฆ", UTF8, ISO_8859_11);
            hexBin = { 0x74, 0x65, 0x73, 0x74, 0x20, 0xA3, 0xA4, 0xA5, 0xA6, 0x00 };
            assert(Compare(testStr.c_str(), (char*)hexBin.data(), true, ISO_8859_11));
            std::string utf8Comp = "test ฃคฅฆ";
            std::string utf8 = Convert<std::string, std::string>(testStr, ISO_8859_11, UTF8);
            assert(Compare(utf8Comp, utf8));
            continue;
        }

        testSubRoutine(testStr, utf8Strings[i], (char*)hexBin.data(), encoding);
    }
}

void MorphText::testShiftJis931()
{
    std::string utf8String = "ooyamaneko ｵｵﾔﾏﾈｺ　オオヤマネコ　おおやまねこ　大山猫";
    std::string testStr = Convert<std::string, std::string>(utf8String, UTF8, SHIFTJIS_CP932);
    std::vector<uint8_t> hexBin = { 0x6F, 0x6F, 0x79, 0x61, 0x6D, 0x61, 0x6E, 0x65, 0x6B, 0x6F, 0x20, 0xB5, 0xB5, 0xD4, 0xCF, 0xC8, 0xBA, 0x81, 0x40, 0x83,
               0x49, 0x83, 0x49, 0x83, 0x84, 0x83, 0x7D, 0x83, 0x6C, 0x83, 0x52, 0x81, 0x40, 0x82, 0xA8, 0x82, 0xA8, 0x82, 0xE2, 0x82,
               0xDC, 0x82, 0xCB, 0x82, 0xB1, 0x81, 0x40, 0x91, 0xE5, 0x8E, 0x52, 0x94, 0x4C, 0x00 };
    testSubRoutine(testStr, utf8String, (char*)hexBin.data(), SHIFTJIS_CP932);
}

void MorphText::testKSX1001()
{
    std::string utf8String = "스라소니";
    std::string testStr = Convert<std::string, std::string>(utf8String, UTF8, KS_X_1001);
    std::vector<uint8_t> hexBin = { 0xBD, 0xBA, 0xB6, 0xF3, 0xBC, 0xD2, 0xB4, 0xCF, 0x00 };
    testSubRoutine(testStr, utf8String, (char*)hexBin.data(), KS_X_1001);
}

void MorphText::testJis0201FW()
{
    std::string utf8String = "オオヤマネコ ABCD abcd";
    std::string testStr = Convert<std::string, std::string>(utf8String, UTF8, JIS_X_0201_FULLWIDTH);
    std::vector<uint8_t> hexBin = { 0xB5, 0xB5, 0xD4, 0xCF, 0xC8, 0xBA, 0x20, 0x41, 0x42, 0x43, 0x44, 0x20, 0x61, 0x62, 0x63, 0x64 };
    testSubRoutine(testStr, utf8String, (char*)hexBin.data(), JIS_X_0201_FULLWIDTH);
}

void MorphText::testJis0201HW()
{
    std::string utf8String = "ｵｵﾔﾏﾈｺ ABCD abcd";
    std::string testStr = Convert<std::string, std::string>(utf8String, UTF8, JIS_X_0201_HALFWIDTH);
    std::vector<uint8_t> hexBin = { 0xB5, 0xB5, 0xD4, 0xCF, 0xC8, 0xBA, 0x20, 0x41, 0x42, 0x43, 0x44, 0x20, 0x61, 0x62, 0x63, 0x64 };
    testSubRoutine(testStr, utf8String, (char*)hexBin.data(), JIS_X_0201_HALFWIDTH);
}

void MorphText::testPokemonGen1()
{
    std::string utf8 = "";
    std::string utf8Comp = "";
    std::string testStr;
    std::vector<std::vector<uint8_t>> hexBin
    {
        { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x70, 0x71, 0xE1, 0xE8, 0xF5, 0x7F, 0xE4, 0xA3, 0xA5, 0xBB, 0xA6, 0xB1, 0xE0, 0xB6, 0xF0, 0x00 },
        { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x70, 0x71, 0xE1, 0xE8, 0xF5, 0x7F, 0xE0, 0xB1, 0xA3, 0xA5, 0xD5, 0xA6, 0xB1,0xB6, 0xE0, 0xF0, 0xC3, 0xC4, 0xC5, 0xD5, 0xBE, 0xA6, 0xD9, 0xC0, 0xC1, 0xC2, 0xE8, 0x00 },
        { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x70, 0x71, 0xE1, 0xE8, 0xF5, 0x7F, 0xDB, 0xA3, 0xA5, 0xA3, 0xE0, 0xA6, 0xB1, 0xB6, 0xE0, 0xF0, 0xC3, 0xC4, 0xC5, 0xA3, 0xE0, 0xCA, 0xA6, 0xAD, 0xE0, 0xC0, 0xC1, 0xC2, 0xE8, 0x00 },
        { 0x83, 0xE3, 0x8C, 0x19, 0xE3, 0xAB, 0x7F, 0x21, 0x61, 0x60, 0x00 }
    };

    std::vector<std::string> utf8Strings
    {
        "azAZ09‘’Ⓟ.♀ 'rdf'dgr'w$",
        "azAZ09‘’Ⓟ.♀ 'rdfd'grw'$äöüd'ßgn'ÄÖÜ.",
        "azAZ09‘’Ⓟ.♀ 'rdfd'grw'$äöüd'Ñgn'ÄÖÜ.",
        "エースバーン　あ゙"
    };

    for (int i = 0; i < utf8Strings.size(); ++i)
    {
        int encoding = POKEMON_GEN1_ENGLISH + i;
        std::string testStr = Convert<std::string, std::string>(utf8Strings[i], UTF8, encoding);
        assert(Compare(testStr.c_str(), (char*)hexBin[i].data(), CASE_SENSITIVE, encoding));
        std::string utf8C = Convert<std::string, std::string>(testStr, encoding, UTF8);
        assert(Compare(utf8C, utf8Strings[i]));

        if (encoding == POKEMON_GEN1_JAPANESE)
        {
            std::vector<uint8_t> subHex = { 0x19, 0xE3, 0xAB, 0x00 };
            assert(Find(testStr, (char*)subHex.data(), CASE_SENSITIVE, encoding) == 3);

            MorphText test(testStr, encoding);
            assert(test.Compare((char*)hexBin[i].data(), CASE_SENSITIVE, encoding));
            assert(test.Find(std::string((char*)subHex.data()), CASE_SENSITIVE, encoding) == 3);
            continue;
        }

        testStr = Convert<const char*, std::string>("AbcD123", UTF8, encoding);
        std::vector<uint8_t> hex = { 0x80, 0xA1, 0xA2, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };

        assert(Compare(testStr.c_str(), (char*)hex.data(), CASE_SENSITIVE, encoding));
        hex[0] = 0xA0;
        assert(Compare(testStr.c_str(), (char*)hex.data(), CASE_INSENSITIVE, encoding));
        std::vector<uint8_t> hexLower = { 0xA0, 0xA1, 0xA2, 0xA3, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToLower(testStr, encoding), (char*)hexLower.data(), CASE_SENSITIVE, encoding));
        std::vector<uint8_t> hexUpper = { 0x80, 0x81, 0x82, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToUpper(testStr, encoding), (char*)hexUpper.data(), CASE_SENSITIVE, encoding));
        std::vector<uint8_t> hexSarcasm = { 0x80, 0xA1, 0x82, 0xA3, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToSarcasm(testStr, encoding), (char*)hexSarcasm.data(), CASE_SENSITIVE, encoding));

        std::vector<uint8_t> subHexSensitive = { 0x83, 0xF7, 0x00 };
        assert(Find(testStr, (char*)subHexSensitive.data(), CASE_SENSITIVE, encoding) == 3);
        std::vector<uint8_t> subHexInsensitive = { 0xA3, 0xF7, 0x00 };
        assert(Find(testStr, (char*)subHexInsensitive.data(), CASE_INSENSITIVE, encoding) == 3);

        MorphText test(testStr, encoding);
        hex = { 0x80, 0xA1, 0xA2, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(test.Compare((char*)hex.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToLower<std::string>(encoding), (char*)hexLower.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToUpper<std::string>(encoding), (char*)hexUpper.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToSarcasm<std::string>(encoding), (char*)hexSarcasm.data(), CASE_SENSITIVE, encoding));
        assert(test.Find(std::string((char*)subHexSensitive.data()), CASE_SENSITIVE, encoding) == 3);
        assert(test.Find(std::string((char*)subHexInsensitive.data()), CASE_INSENSITIVE, encoding) == 3);
    }
}

void MorphText::testPokemonGen2()
{
    std::string utf8 = "";
    std::string utf8Comp = "";
    std::string testStr;
    std::vector<std::vector<uint8_t>> hexBin
    {
        { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x72, 0x73, 0xE1, 0xE8, 0xF5, 0x7F, 0xD3, 0xA3, 0xA5, 0xD0, 0xA6, 0xB1, 0xE0, 0xB6, 0xF0, 0x00 },
  //      { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x72, 0x73, 0xE1, 0xE8, 0xF5, 0x7F, 0xE0, 0xB1, 0xA3, 0xA5, 0xD5, 0xA6, 0xB1,0xB6, 0xE0, 0xF0, 0xC3, 0xC4, 0xC5, 0xD5, 0xBE, 0xA6, 0xD9, 0xC0, 0xC1, 0xC2, 0xE8, 0x00 },
  //      { 0xA0, 0xB9, 0x80, 0x99, 0xF6, 0xFF, 0x72, 0x73, 0xE1, 0xE8, 0xF5, 0x7F, 0xDB, 0xA3, 0xA5, 0xA3, 0xE0, 0xA6, 0xB1, 0xB6, 0xE0, 0xF0, 0xC3, 0xC4, 0xC5, 0xA3, 0xE0, 0xCA, 0xA6, 0xAD, 0xE0, 0xC0, 0xC1, 0xC2, 0xE8, 0x00 },
  //      { 0x83, 0xE3, 0x8C, 0x19, 0xE3, 0xAB, 0x7F, 0x21, 0x61, 0x60, 0x00 }
    };

    std::vector<std::string> utf8Strings
    {
        "azAZ09“”Ⓟ.♀ 'rdf'dgr'w$",
       // "azAZ09“”Ⓟ.♀ 'rdfd'grw'$äöüd'ßgn'ÄÖÜ.",
       // "azAZ09“”Ⓟ.♀ 'rdfd'grw'$äöüd'Ñgn'ÄÖÜ.",
       // "エースバーン　あ゙"
    };

    for (int i = 0; i < utf8Strings.size(); ++i)
    {
        int encoding = POKEMON_GEN2_ENGLISH + i;
        std::string testStr = Convert<std::string, std::string>(utf8Strings[i], UTF8, encoding);
        assert(Compare(testStr.c_str(), (char*)hexBin[i].data(), CASE_SENSITIVE, encoding));
        std::string utf8C = Convert<std::string, std::string>(testStr, encoding, UTF8);
        assert(Compare(utf8C, utf8Strings[i]));

        /*if (encoding == POKEMON_GEN2_JAPANESE)
        {
            std::vector<uint8_t> subHex = { 0x19, 0xE3, 0xAB, 0x00 };
            assert(Find(testStr, (char*)subHex.data(), CASE_SENSITIVE, encoding) == 3);

            MorphText test(testStr, encoding);
            assert(test.Compare((char*)hexBin[i].data(), CASE_SENSITIVE, encoding));
            assert(test.Find(std::string((char*)subHex.data()), CASE_SENSITIVE, encoding) == 3);
            continue;
        }*/

        testStr = Convert<const char*, std::string>("AbcD123", UTF8, encoding);
        std::vector<uint8_t> hex = { 0x80, 0xA1, 0xA2, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };

        assert(Compare(testStr.c_str(), (char*)hex.data(), CASE_SENSITIVE, encoding));
        hex[0] = 0xA0;
        assert(Compare(testStr.c_str(), (char*)hex.data(), CASE_INSENSITIVE, encoding));
        std::vector<uint8_t> hexLower = { 0xA0, 0xA1, 0xA2, 0xA3, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToLower(testStr, encoding), (char*)hexLower.data(), CASE_SENSITIVE, encoding));
        std::vector<uint8_t> hexUpper = { 0x80, 0x81, 0x82, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToUpper(testStr, encoding), (char*)hexUpper.data(), CASE_SENSITIVE, encoding));
        std::vector<uint8_t> hexSarcasm = { 0x80, 0xA1, 0x82, 0xA3, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(Compare(ToSarcasm(testStr, encoding), (char*)hexSarcasm.data(), CASE_SENSITIVE, encoding));

        std::vector<uint8_t> subHexSensitive = { 0x83, 0xF7, 0x00 };
        assert(Find(testStr, (char*)subHexSensitive.data(), CASE_SENSITIVE, encoding) == 3);
        std::vector<uint8_t> subHexInsensitive = { 0xA3, 0xF7, 0x00 };
        assert(Find(testStr, (char*)subHexInsensitive.data(), CASE_INSENSITIVE, encoding) == 3);

        MorphText test(testStr, encoding);
        hex = { 0x80, 0xA1, 0xA2, 0x83, 0xF7, 0xF8, 0xF9, 0x00 };
        assert(test.Compare((char*)hex.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToLower<std::string>(encoding), (char*)hexLower.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToUpper<std::string>(encoding), (char*)hexUpper.data(), CASE_SENSITIVE, encoding));
        assert(Compare(test.ToSarcasm<std::string>(encoding), (char*)hexSarcasm.data(), CASE_SENSITIVE, encoding));
        assert(test.Find(std::string((char*)subHexSensitive.data()), CASE_SENSITIVE, encoding) == 3);
        assert(test.Find(std::string((char*)subHexInsensitive.data()), CASE_INSENSITIVE, encoding) == 3);
    }
}

void MorphText::Print()
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
    std::cout << "Jis x 0201 Full Width: " << _jis_x_0201_fullwidth << " --- updated: " << (bool)(_updatedFlags & FLAG_JIS_X_0201_FULLWIDTH) << "\n";
    std::cout << "Jis x 0201 Half Width: " << _jis_x_0201_halfwidth << " --- updated: " << (bool)(_updatedFlags & FLAG_JIS_X_0201_HALFWIDTH) << "\n";
    std::cout << "Shift Jis CP932: " << _shiftJis_cp932 << " --- updated: " << (bool)(_updatedFlags & FLAG_SHIFTJIS_CP932) << "\n";
    std::cout << "KS X 1001: " << _ks_x_1001 << " --- updated: " << (bool)(_updatedFlags & FLAG_KS_X_1001) << "\n";
    std::cout << "Pokemon Gen1 English: " << _pokemon_gen1_english << " --- updated: " << (bool)(_updatedFlags & FLAG_POKEMON_GEN1_ENGLISH) << "\n";
    std::cout << "Pokemon Gen1 French, German: " << _pokemon_gen1_french_german << " --- updated: " << (bool)(_updatedFlags & FLAG_POKEMON_GEN1_FRENCH_GERMAN) << "\n";
    std::cout << "Pokemon Gen1 Italian, Spanish: " << _pokemon_gen1_italian_spanish << " --- updated: " << (bool)(_updatedFlags & FLAG_POKEMON_GEN1_ITALIAN_SPANISH) << "\n";
    std::cout << "Pokemon Gen1 Japanese: " << _pokemon_gen1_japanese << " --- updated: " << (bool)(_updatedFlags & FLAG_POKEMON_GEN1_JAPANESE) << "\n";
    std::cout << "Pokemon Gen2 English: " << _pokemon_gen2_english << " --- updated: " << (bool)(_updatedFlags & FLAG_POKEMON_GEN2_ENGLISH) << "\n";
    std::cout << "Primary Format: " << _primaryEncoding << "\n";
    std::cout << "Endianness: " << (isLittleEndian() ? "little" : "big") << "\n";
    std::cout << "\n";
}
void MorphText::Test()
{
    std::cout << "Running Tests... ";
    testUTF8();
    testASCII();
    testUTF16LE();
    testUTF16BE();
    testUTF32LE();
    testUTF32BE();
    testISO_8859_X();
    testShiftJis931();
    testKSX1001();
    testJis0201FW();
    testJis0201HW();
    testPokemonGen1();
    testPokemonGen2();
    std::cout << "PASS\n";
}
#endif