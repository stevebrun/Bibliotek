//
//  biblex.c
//  Bibliotek
//
//  Created by Steve Brunwasser on 8/22/20.
//  Copyright © 2020 Steve Brunwasser. All rights reserved.
//

#include "biblex.h"
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

static bool bib_isnumber(char c) { return isnumber(c); }
static bool bib_isletter(char c) { return isalpha(c); }

#pragma mark - lex

bool bib_lex_integer(bib_digit04_t buffer, char const **const str, size_t *const len)
{
    size_t length = bib_lex_digit_n(buffer, bib_integer_size, str, len);
    buffer[length] = '\0';
    return (length > 0);
}

bool bib_lex_digit16(bib_digit16_t buffer, char const **const str, size_t *const len)
{
    size_t length = bib_lex_digit_n(buffer, bib_digit16_size, str, len);
    buffer[length] = '\0';
    return (length > 0);
}

bool bib_lex_decimal(bib_digit16_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *string = *str;
    size_t string_length = *len;
    bool success = bib_read_point(&string, &string_length)
                && bib_lex_digit16(buffer, &string, &string_length)
                && bib_advance_step(*len - string_length, str, len);
    if (!success) {
        memset(buffer, 0, sizeof(char) * (bib_digit16_size + 1));
    }
    return success;
}

bool bib_lex_year(bib_year_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *str_0 = *str;
    size_t      len_0 = *len;
    size_t length = bib_lex_digit_n(buffer, bib_datenum_size, &str_0, &len_0);
    return (length == 4) && bib_advance_step(*len - len_0, str, len);
}

bool bib_lex_year_abv(bib_year_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *str_0 = *str;
    size_t      len_0 = *len;
    size_t length = bib_lex_digit_n(buffer, 3, &str_0, &len_0);
    return (length == 2) && bib_advance_step(*len - len_0, str, len);
}

bool bib_lex_mark(bib_mark_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *str_0 = *str;
    size_t      len_0 = *len;
    bool alpha_success = bib_lex_alpha_n(buffer, sizeof(bib_mark_t), &str_0, &len_0);

    char const *str_1 = str_0;
    size_t      len_1 = len_0;
    bool break_success = alpha_success && (bib_read_space(&str_1, &len_1) || bib_peek_break(str_1, len_1));

    bool success = alpha_success && break_success && bib_advance_step(*len - len_0, str, len);
    if (!success) {
        memset(buffer, 0, sizeof(bib_mark_t));
    }
    return success;
}

//bool bib_lex_cutter(char buffer[bib_cuttern_size + 1], char const **const str, size_t *const len)
//{
//    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
//        return false;
//    }
//    char const *string = *str;
//    size_t string_length = *len;
//
//    if (isupper(string[0])) {
//        buffer[0] = string[0];
//        string = &(string[1]);
//        string_length -= 1;
//        buffer[1] = '\0';
//    } else {
//        return false;
//    }
//
//    size_t digit_length = bib_lex_digit_n(&(buffer[1]), bib_cuttern_size - 1, &string, &string_length);
//    buffer[digit_length + 1] = '\0';
//    bool success = bib_advance_step(*len - string_length, str, len);
//    if (!success) {
//        memset(buffer, 0, sizeof(char) * (bib_cuttern_size + 1));
//    }
//    return success;
//}

bool bib_lex_subclass(bib_alpah03_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *string = *str;
    size_t string_length = *len;

    size_t string_index = 0;
    size_t buffer_index = 0;
    while ((buffer_index < bib_lcalpha_size) && (string_index < string_length)) {
        const char current_char = string[string_index];
        if (isupper(current_char)) {
            buffer[buffer_index] = current_char;
            buffer_index += 1;
            string_index += 1;
        } else {
            break;
        }
    }
    buffer[buffer_index] = '\0';
    bool success = bib_advance_step(buffer_index, str, len);
    if (!success) {
        memset(buffer, 0, sizeof(char) * (bib_lcalpha_size + 1));
    }
    return success;
}

bool bib_lex_caption_ordinal_suffix(bib_word_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }

    char const *str0 = *str;
    size_t      len0 = *len;

    char  *outbuf0 = buffer;
    size_t outlen0 = sizeof(bib_word_t);

    size_t alphalen = bib_lex_alpha_n(outbuf0, outlen0, &str0, &len0);
    bool alpha_success = (alphalen > 0);

    char const *str1 = str0;
    size_t      len1 = len0;
    bool space_success = alpha_success && bib_read_space(&str1, &len1);
    bool point_success = alpha_success && bib_read_point(&str1, &len1);

    bool success = (space_success || point_success) && bib_advance_step(*len - len0, str, len);
    if (!success) {
        memset(buffer, 0, outlen0);
    }
    return success;
}

bool bib_lex_special_ordinal_suffix(bib_word_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }

    char const *str0 = *str;
    size_t      len0 = *len;

    char  *outbuf0 = buffer;
    size_t outlen0 = sizeof(bib_word_t);
    memset(buffer, 0, sizeof(bib_word_t));

    size_t alphalen = bib_lex_alpha_n(outbuf0, outlen0, &str0, &len0);
    bool alpha_success = (alphalen > 0) && bib_advance_step(alphalen, (char const **)&outbuf0, &outlen0);

    bool stop = false;
    bool needs_point = false;
    bool success = alpha_success;
    while ((len0 > 0) && (outlen0 > 1) && success && !stop) {
        char const *str1 = str0;
        size_t      len1 = len0;
        char  *outbuf1 = outbuf0;
        size_t outlen1 = outlen0;

        if (!needs_point && bib_read_space(&str1, &len1)) {
            success = true;
            stop = true;
            str0 = str1;
            len0 = len1;
            break;
        }
        bool point_success = bib_read_point(&str1, &len1);
        if (needs_point && !point_success) {
            success = false;
            stop = true;
            break;
        }
        if (point_success) {
            outbuf1[0] = '.';
            bib_advance_step(1, (char const **)&outlen1, &outlen1);
        }

        char const *str2 = str1;
        size_t      len2 = len1;
        char  *outbuf2 = outbuf1;
        size_t outlen2 = outlen1;
        size_t alphalen = bib_lex_alpha_n(outbuf2, outlen2, &str2, &len2);
        bool alpha_success = (alphalen > 0) && bib_advance_step(alphalen, (char const **)&outbuf2, &outlen2);

        char const *str3 = (alpha_success) ? str2 : str1;
        size_t      len3 = (alpha_success) ? len2 : len1;
        if (alpha_success) {
            needs_point = true;
            outbuf0 = outbuf2;
            outlen0 = outlen2;
            str0 = str3;
            len0 = len3;
            continue;
        } else if (point_success) {
            needs_point = false;
            if (bib_peek_break(str2, len2)) {
                success = true;
                stop = true;
            } else {
                // trailing word-break required
                success = false;
                stop = true;
                break;
            }
            if (success && !stop) {
                outbuf0 = outbuf2;
                outlen0 = outlen2;
                str0 = str3;
                len0 = len3;
            }
            continue;
        } else {
            stop = true;
            success = false;
            break;
        }
    }

    bool final_success = success && bib_advance_step(*len - len0, str, len);
    if (!final_success) {
        memset(buffer, 0, sizeof(bib_word_t));
    }
    return final_success;
}

bool bib_lex_ordinal_suffix_(bib_word_t buffer, bool *const take_point, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    if (take_point != NULL) {
        *take_point = false;
    }

    char const *str_0 = *str;
    size_t      len_0 = *len;

    char  *out_buf_0 = buffer;
    size_t out_len_0 = sizeof(bib_word_t);

    bool stop = false;
    while ((len_0 > 0) && (out_len_0 > 1) && !stop) {
        char  *out_buf_1 = out_buf_0;
        size_t out_len_1 = out_len_0;

        char const *str_1 = str_0;
        size_t      len_1 = len_0;
        bool __unused _ = bib_read_space(&str_1, &len_1);
        size_t alpha_len = bib_read_buff(out_buf_1, out_len_1 - 1, bib_isletter, &str_1, &len_1);
        bool alpha_success = (alpha_len > 0);
        if (alpha_success) {
            assert(alpha_len < out_len_1);
            out_buf_1 = &(out_buf_1[alpha_len]);
            out_len_1 -= alpha_len;
        }

        char const *str_2 = str_1;
        size_t      len_2 = len_1;
        bool point_success = alpha_success && bib_read_point(&str_2, &len_2);

        char const *str_3 = str_2;
        size_t      len_3 = len_2;
        bool space_success = alpha_success && bib_read_space(&str_3, &len_3);

        if (point_success) {
            char const *str_4 = str_3;
            size_t      len_4 = len_3;
            if (bib_read_point(&str_4, &len_4)) {
                assert(out_len_1 > 1);
                out_buf_1[0] = '.';
                out_len_1 -= 1;
                out_buf_0 = out_buf_1;
                out_len_0 = out_len_1;
                str_0 = str_2;
                len_0 = len_2;
            } else {
                char c0 = '\0', c1 = '\0';
                bool s0 = bib_read_char(&c0, &str_4, &len_4);
                bool s1 = bib_read_char(&c1, &str_4, &len_4);
                bool cutter_tail = (s0 && isalpha(c0) && s1 && isnumber(c1));
                if (cutter_tail) {
                    stop = true;
                } else {
                    assert(out_len_1 > 1);
                    out_buf_1[0] = '.';
                    out_len_1 -= 1;
                }
                if (space_success) {
                    str_0 = str_2;
                    len_0 = len_2;
                    if (cutter_tail) {
                        if (take_point != NULL) {
                            *take_point = true;
                        }
                    }
                } else {
                    str_0 = str_1;
                    len_0 = len_1;
                }
                out_buf_0 = out_buf_1;
                out_len_0 = out_len_1;
            }
        } else if (space_success) {
            out_buf_0 = out_buf_1;
            out_len_0 = out_len_1;
            str_0 = str_1;
            len_0 = len_1;
            stop = true;
        } else {
            stop = true;
        }
    }

    bool success = (out_buf_0 != buffer) && bib_advance_step(*len - len_0, str, len);
    if (success) {
        assert(out_len_0 > 0);
        out_buf_0[0] = '\0';
    } else {
        memset(buffer, 0, sizeof(bib_word_t));
    }
    return success;
}

bool bib_lex_volume_prefix(bib_word_t buffer, char const **const str, size_t *const len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }

    char const *str0 = *str;
    size_t      len0 = *len;

    char  *outbuf0 = buffer;
    size_t outlen0 = sizeof(bib_word_t);

    size_t alphalen = bib_lex_alpha_n(outbuf0, outlen0, &str0, &len0);
    bool alpha_success = (alphalen > 0);

    char const *str1 = str0;
    size_t      len1 = len0;
    bool point_success = alpha_success && bib_read_point(&str1, &len1);

    bool success = point_success && bib_advance_step(*len - len1, str, len);
    if (!success) {
        memset(buffer, 0, outlen0);
    }
    return success;
}


static bool bib_lex_word_pred(char const c) { return !isspace(c); }

bool bib_lex_longword(bib_longword_t buffer, char const **str, size_t *len)
{
    if (buffer == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }

    char const *str0 = *str;
    size_t      len0 = *len;

    char  *outbuf0 = buffer;
    size_t outlen0 = sizeof(bib_longword_t);

    size_t wordlen = bib_lex_char_n(outbuf0, outlen0, bib_lex_word_pred, &str0, &len0);
    bool word_success = (wordlen > 0);

    bool success = word_success && bib_advance_step(*len - len0, str, len);
    if (!success) {
        memset(buffer, 0, outlen0);
    }
    return success;
}

size_t bib_lex_digit_n(char *const buffer, size_t const buffer_len, char const **const str, size_t *const len)
{
    return bib_lex_char_n(buffer, buffer_len, bib_isnumber, str, len);
}

size_t bib_lex_alpha_n(char *const buffer, size_t const buffer_len, char const **const str, size_t *const len)
{
    return bib_lex_char_n(buffer, buffer_len, bib_isletter, str, len);
}

size_t bib_lex_char_n  (char *const buffer, size_t const buffer_len, bool (*const pred)(char),
                        char const **const str, size_t *const len)
{
    if (buffer == NULL || buffer_len < 1 || pred == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *const string = *str;
    size_t const string_length = *len;

    size_t string_index = 0;
    size_t buffer_index = 0;
    while ((buffer_index < buffer_len) && (string_index < string_length)) {
        const char current_char = string[string_index];
        if (pred(current_char)) {
            buffer[buffer_index] = current_char;
            buffer_index += 1;
            string_index += 1;
        } else {
            break;
        }
    }
    bool success = bib_advance_step(buffer_index, str, len);
    if (!success) {
        memset(buffer, 0, sizeof(char) * buffer_len);
    }
    return (success) ? buffer_index : 0;
}

#pragma mark - read

bool bib_read_space(char const **const str, size_t *const len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *const string = *str;
    size_t const string_length = *len;

    bool stop = false;
    size_t string_index = 0;
    while ((string_index < string_length) && !stop) {
        char current_char = string[string_index];
        if (isspace(current_char)) {
            string_index += 1;
        } else {
            stop = true;
        }
    }
    return bib_advance_step(string_index, str, len);
}

bool bib_read_point(char const **const str, size_t *const len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    return ((*str)[0] == '.') ? bib_advance_step(1, str, len) : false;
}

bool bib_read_dash(char const **str, size_t *len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    return ((*str)[0] == '-') ? bib_advance_step(1, str, len) : false;
}

bool bib_read_slash(char const **str, size_t *len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    return ((*str)[0] == '/') ? bib_advance_step(1, str, len) : false;
}

bool bib_read_char(char *const c, char const **const str, size_t *const len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char v = (*str)[0];
    bool success = bib_advance_step(1, str, len);
    if (success && c != NULL) {
        *c = v;
    }
    return success;
}

size_t bib_read_buff(char *const buffer, size_t const buflen, bool (*const pred)(char),
                     char const **const str, size_t *const len)
{
    if (buffer == NULL || buflen <= 0 || pred == NULL || str == NULL || *str == NULL || len == NULL || *len == 0) {
        return false;
    }
    char const *const input = *str;
    size_t const      inlen = *len;
    size_t index = 0;
    char current = input[index];
    while ((index < inlen) && (index < buflen) && pred(current)) {
        buffer[index] = current;
        index += 1;
    }
    bool success = (index > 0) && bib_advance_step(index, str, len);
    if (!success) {
        memset(buffer, 0, buflen);
    }
    return success;
}

bool bib_peek_break(char const *const str, size_t const len)
{
    if (str == NULL) { return false; }
    if (len == 0) { return true; }

    char const *str_0 = str;
    size_t      len_0 = len;
    if (bib_read_space(&str_0, &len_0)) {
        return true;
    }
    char c = '\0';
    if (!bib_read_char(&c, &str_0, &len_0)) {
        return false;
    }
    switch (c) {
    case '\0': // null terminator
    case  EOF: // end of file
    case 0x03: // end of text
    case 0x1C: // file separator
    case 0x1D: // group separator
    case 0x1E: // record separator
    case 0x1F: // unit separator
        return true;
    default:
        return false;
    }
}

#pragma mark - advance

bool bib_advance_step(size_t const step, char const **const str, size_t *const len)
{
    if (str == NULL || *str == NULL || len == NULL || *len == 0 || step <= 0) {
        return false;
    }
    if (step < *len) {
        *str = &((*str)[step]);
        *len -= step;
    }
    return true;
}
