//
//  bibtype.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 8/22/20.
//  Copyright © 2020 Steve Brunwasser. All rights reserved.
//

#ifndef bibtype_h
#define bibtype_h

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

__BEGIN_DECLS

#pragma mark -

/// A single alphabetic character.
typedef char bib_initial_t;

/// A string of at most three alphabetic characters.
typedef char bib_alpah03_b[4];

/// A string of at most four decimal digits 0 through 9.
typedef char bib_digit04_b[5];

/// A string of at most 16 decimal digits 0 through 9.
typedef char bib_digit16_b[17];

/// A string of at most 16 non-whitespace characters.
typedef char bib_word_b[17];

/// A string of at most 14 non-whitespace characters.
typedef char bib_longword_b[25];

/// A string of either two or four decimal digits 0 through 9.
typedef char bib_year_b[5];

/// A string of at most four alphabetic characters
typedef char bib_mark_b[5];

#pragma mark - date

/// A year or range of years used within a call number.
typedef struct bib_date {
    /// The initial year of the date range, or the exact year for single year values.
    bib_year_b year;

    /// The character used to separate the year from the end of the range.
    ///
    /// This is the null character for single year values.
    char separator;

    /// The last year in the range.
    bib_year_b span;

    /// Some short optional alhpabetic suffix attached to the date.
    bib_mark_b mark;
} bib_date_t;

extern bool bib_date_init(bib_date_t *date, char const *str);
extern bool bib_date_is_empty(bib_date_t const *date);
extern bool bib_date_has_span(bib_date_t const *date);

#pragma mark - cutter

/// A cutter number.
typedef struct bib_cutter {
    /// The initial alphabetic character for the number.
    bib_initial_t letter;

    /// The decimal digits following the initial letter in the number.
    bib_digit16_b number;

    /// Some short optional alphabetic suffix attached to the cutter number.
    bib_mark_b mark;
} bib_cutter_t;

extern bool bib_cutter_init(bib_cutter_t *cut, char const *str);
extern bool bib_cutter_is_empty(bib_cutter_t const *cut);

#pragma mark - ordinal

/// An integer value followed by an alphabetic suffix. i.e. "15th"
typedef struct bib_ordinal {
    /// The integer value of the ordinal.
    bib_digit16_b number;

    /// The alphabetic suffix following the number.
    bib_word_b    suffix;
} bib_ordinal_t;

extern bool bib_ordinal_is_empty(bib_ordinal_t const *ord);

#pragma mark - volume

/// An integer value preceeded by some alphabetic marker. i.e. "vol. 1"
typedef struct bib_volume {
    /// The alphabetic prefix denoting the type of "volume".
    bib_word_b    prefix;

    /// The integer value following the "volume" type.
    bib_digit16_b number;
} bib_volume_t;

bool bib_volume_init(bib_volume_t *vol, char const *str);
extern bool bib_volume_is_empty(bib_volume_t const *vol);

#pragma mark - lc specification

/// A flag indicating the type of data within a specification segment.
typedef enum bib_lc_specification_kind {
    bib_lc_specification_kind_date = 1,
    bib_lc_specification_kind_ordinal,
    bib_lc_specification_kind_volume,
    bib_lc_specification_kind_word
} bib_lc_specification_kind_t;

/// A value within the specification section of a Library of Congress call number.
typedef struct bib_lc_specification {
    /// The type of data within the specification segment.
    bib_lc_specification_kind_t kind;

    union {
        /// A date value, marked by \c bib_lc_specification_kind_date
        bib_date_t     date;

        /// An ordinal value, marked by \c bib_lc_specification_kind_ordinal
        bib_ordinal_t  ordinal;

        /// A volume value, marked by \c bib_lc_specification_kind_volume
        bib_volume_t   volume;

        /// A long word value, marked by \c bib_lc_specification_kind_word
        bib_longword_b word;
    };
} bib_lc_specification_t;

extern void bib_lc_specification_init(bib_lc_specification_t *spc, bib_lc_specification_kind_t spec);
extern void bib_lc_specification_deinit(bib_lc_specification_t *spc);
extern bool bib_lc_specification_is_empty(bib_lc_specification_t const *spc);

/// A list of specification segment values.
typedef struct bib_lc_specification_list {
    /// The raw heap-allocated buffer contianing the heap-allocated segments.
    bib_lc_specification_t *buffer;

    /// The amount of specification segments within this list.
    size_t            length;
} bib_lc_specification_list_t;

extern void bib_lc_specification_list_init  (bib_lc_specification_list_t *list);
extern void bib_lc_specification_list_append(bib_lc_specification_list_t *list, bib_lc_specification_t *spc);
extern void bib_lc_specification_list_deinit(bib_lc_specification_list_t *list);
extern bool bib_lc_specification_list_is_empty(bib_lc_specification_list_t const *list);

#pragma mark - dateord

/// A flag indicating the type of data within a date-or-other value.
typedef enum bib_lc_dateord_kind {
    bib_lc_dateord_kind_date = 1,
    bib_lc_dateord_kind_ordinal
} bib_lc_dateord_kind_t;

/// A date or ordinal value within the caption section or a cutter segment in a Library of Congress call number.
typedef struct bib_lc_dateord {
    /// The type of data within the date-or-ordinal value.
    bib_lc_dateord_kind_t kind;

    union {
        /// A date value, marked by \c bib_lc_dateord_kind_date
        bib_date_t date;

        /// An ordinal value, marked by \c bib_lc_dateord_kind_ordinal
        bib_ordinal_t ordinal;
    };
} bib_lc_dateord_t;


extern bool bib_lc_dateord_init_date(bib_lc_dateord_t *dord, bib_date_t const *date);
extern bool bib_lc_dateord_init_ordinal(bib_lc_dateord_t *dord, bib_ordinal_t const *ord);

extern bib_date_t const *bib_lc_dateord_get_date(bib_lc_dateord_t *const dord);
extern bib_ordinal_t const *bib_lc_dateord_get_ordinal(bib_lc_dateord_t *const dord);

extern bool bib_lc_dateord_is_empty(bib_lc_dateord_t const *dord);


#pragma mark - lc cutter

/// A cutter segment within a Library of Congress call number.
typedef struct bib_lc_cutter {
    /// The cutter number.
    bib_cutter_t    cuttnum;

    /// The date or ordinal value trailing the cutter number.
    bib_lc_dateord_t dateord;
} bib_lc_cutter_t;

extern bool bib_lc_cutter_init(bib_lc_cutter_t *cut, bib_cutter_t const *num, bib_lc_dateord_t const *dord);
extern bool bib_lc_cutter_is_empty(bib_lc_cutter_t const *cut);

#pragma mark -

/// A Library of Congress call number.
typedef struct bib_lc_calln {
    /// The at most three letter initial of the subject matter.
    bib_alpah03_b letters;

    /// The integer value of the subject matter.
    bib_digit04_b integer;

    /// The decimal portion of the subject matter.
    bib_digit16_b decimal;

    /// The date or ordinal value within the caption.
    bib_lc_dateord_t dateord;

    /// The three cutter number segments.
    bib_lc_cutter_t cutters[3];

    /// The first two specification segments.
    bib_lc_specification_t specifications[2];

    /// The remaining sepcifiation segments.
    bib_lc_specification_list_t remainder;
} bib_lc_calln_t;

extern bool bib_lc_calln_init  (bib_lc_calln_t *num, char const *str);
extern void bib_lc_calln_deinit(bib_lc_calln_t *num);

#pragma mark -

typedef enum bib_calln_comparison {
    /// The leading value is ordered before the trailing value, and therefore does not specialize it.
    bib_calln_ordered_descending = -1,

    /// The leading value is the same as the trailing value.
    bib_calln_ordered_same       =  0,

    /// The leading value is ordered after the trailing value in a way that does not specialize it.
    bib_calln_ordered_ascending  =  1,

    /// The leading value is a superset of the trailing value, but they are not equal.
    bib_calln_ordered_specifying =  2

} bib_calln_comparison_t;

extern bib_calln_comparison_t bib_lc_calln_compare(bib_calln_comparison_t status, bib_lc_calln_t const *left, bib_lc_calln_t const *right, bool specify);
extern bib_calln_comparison_t bib_lc_cutter_compare(bib_calln_comparison_t status, bib_lc_cutter_t const *left, bib_lc_cutter_t const *right, bool specify);
extern bib_calln_comparison_t bib_lc_dateord_compare(bib_calln_comparison_t status, bib_lc_dateord_t const *left, bib_lc_dateord_t const *right, bool specify);
extern bib_calln_comparison_t bib_lc_special_compare(bib_calln_comparison_t status, bib_lc_specification_t const *left, bib_lc_specification_t const *right, bool specify);

extern bib_calln_comparison_t bib_date_compare(bib_calln_comparison_t status, bib_date_t const *left, bib_date_t const *right, bool specify);
extern bib_calln_comparison_t bib_cutter_compare(bib_calln_comparison_t status, bib_cutter_t const *left, bib_cutter_t const *right, bool specify);
extern bib_calln_comparison_t bib_volume_compare(bib_calln_comparison_t status, bib_volume_t const *left, bib_volume_t const *right, bool specify);
extern bib_calln_comparison_t bib_ordinal_compare(bib_calln_comparison_t status, bib_ordinal_t const *left, bib_ordinal_t const *right, bool specify);

#pragma mark -

typedef enum string_specialized_comparison_result {
    /// The \c string is lexically ordered before the \c prefix and therefore does not specialize it.
    string_specialized_ordered_descending = -1,

    /// The \c string does begin with \c prefix and they are equal.
    string_specialized_ordered_same       =  0,

    /// The \c string is lexically ordered after the \c prefix in a way that does not specialize it.
    string_specialized_ordered_ascending  =  1,

    /// The \c string does begin with \c prefix but they are not equal.
    string_specialized_ordered_specifying =  2
} string_specialized_comparison_result_t;

/// Determine if the given \c string begins with the given \c prefix and whether or not they are equal.
/// \param status The result of previous specialization comparisons. This is used to continue matching
///               prefixes for subsequent segments that have been completly equivalend thus far.
/// \param prefix A prefix string search for.
/// \param string A string that may or may not begin with or euqal to the given prefix
/// \returns \c string_specialization_none when the string does begin with the given prefix
/// \returns \c string_specialization_none when the status is set to \c string_specialization_none
/// \returns \c string_specialization_none when the status is \c string_specialization_found
///          and the given prefix is not the empty string.
/// \returns \c string_specialization_maybe when the status is set to \c string_specialization_maybe
///          and the string and prefix are equivalent.
/// \returns \c string_specialization_found when the string begins with, but is not equal to, the given prefix.
/// \returns \c string_specialization_found when the status is set to \c string_specialization_found
///          and the given prefix is empty the empty string.
extern bib_calln_comparison_t string_specialized_compare(bib_calln_comparison_t status,
                                                                         char const *prefix,
                                                                         char const *string);

extern bib_calln_comparison_t bib_string_specify_compare(bib_calln_comparison_t status,
                                                         char const *prefix, char const *string, bool specify);

__END_DECLS

#endif /* bibtype_h */
