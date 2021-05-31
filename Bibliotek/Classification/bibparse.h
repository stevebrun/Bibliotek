//
//  bibparse.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 8/22/20.
//  Copyright © 2020 Steve Brunwasser. All rights reserved.
//

#ifndef bibparse_h
#define bibparse_h

#include "bibtype.h"
#include "biblex.h"

__BEGIN_DECLS

#pragma mark - parse lc

/// Read a Library of Congress call number from the given input stream.
/// \param calln Allocated space for a structure representing the parsed call number.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a Library of Congress call number is successfully read from the input stream.
/// \post \c calln is set to a data structure representing the call number when parsing is successful.
extern bool bib_parse_lc_calln(bib_lc_calln_t *calln, bib_strbuf_t *parser);

#pragma mark - parse lc components

/// Read the subject matter for a Library of Congress call number from the given input stream.
/// \param calln Allocated space for a structure representing the parsed call number.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a Library of Congress call number is successfully read from the input stream.
/// \post \c calln is set to a data structure representing the call number when parsing is successful.
extern bool bib_parse_lc_subject(bib_lc_calln_t *calln, bib_strbuf_t *parser);

/// Read the subject class and subclass for a Library of Congress call number from the given input stream.
/// \param calln Allocated space for a structure representing the parsed call number.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a Library of Congress call number is successfully read from the input stream.
/// \post \c calln is set to a data structure representing the call number when parsing is successful.
extern bool bib_parse_lc_subject_base(bib_lc_calln_t *calln, bib_strbuf_t *parser);

/// Read a date or an ordinal value appearing within the caption or a cutter segment in a Library of Congress call
/// number from the given input stream.
/// \param dord Allocated space for a structure representing the parsed date-or-ordinal segment.
/// \param lex_ord_suffix A function defining the lexing strategy used for the suffix of a possible ordinal value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a date or ordinal value is successfully read from the input stream.
/// \post \c num is set to a data structure representing the date or ordinal value when parsing is successful.
extern bool bib_parse_dateord(bib_dateord_t *dord, bib_lex_word_f lex_ord_suffix, bib_strbuf_t *parser);

/// Read a cutter segment for a Library of Congress call number from the given input stream.
/// \param seg Allocated space for a structure representing the parsed cutter segment.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a cutter segment is successfully read from the input stream.
/// \post \c cut is set to a data structure representing the cutter segment when parsing is successful.
extern bool bib_parse_cuttseg(bib_cuttseg_t *seg, bib_strbuf_t *parser);

/// Read up to three cutter segments for a Library of Congress call number from the given input stream.
/// \param segs Allocated space for three structures representing the parsed cutter segments.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a cutter segment is successfully read from the input stream.
/// \post \c segs is set to an array of data structure representing the cutter segments when parsing is successful.
extern bool bib_parse_cuttseg_list(bib_cuttseg_t segs[3], bib_strbuf_t *parser);

/// Read a specification segment for a Library of Congress call number from the given input stream.
/// \param spc Allocated space for a structure representing the parsed specification segment.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a specification segment is successfully read from the input stream.
/// \post \c spc is set to a data structure representing the specification value when parsing is successful.
extern bool bib_parse_lc_specification(bib_lc_specification_t *spc, bib_strbuf_t *parser);

/// Read a list of specification segments for a Library of Congress call number from the given input stream.
/// \param rem Allocated space for a list of specification segments in a call number.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a list of specification segments is successfully read from the input stream.
/// \post \c rem is populated with heap-allocated data structures representing each specification segment
///       when parsing is successful.
extern bool bib_parse_lc_remainder(bib_lc_specification_list_t *rem, bib_strbuf_t *parser);

#pragma mark - parse components

/// Read a year or date span value from the given input stream.
/// \param date Allocated space for a structure representing the parsed date value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a date value is successfully read from the input stream.
/// \post \c date is set to a data structure representing the date value when parsing is successful.
extern bool bib_parse_date(bib_date_t *date, bib_strbuf_t *parser);

/// Read a cutter number from the given input stream.
/// \param cut Allocated space for a structure representing the parsed cutter value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a cutter value is successfully read from the input stream.
/// \post \c cut is set to a data structure representing the cutter value when parsing is successful.
extern bool bib_parse_cutter(bib_cutter_t *cut, bib_strbuf_t *parser);

/// Read an ordinal value for a call number's cutter segment from the given input stream.
/// \param ord Allocated space for a structure representing the parsed ordinal value in a cutter segment.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when an ordinal value is successfully read from the input stream.
/// \post \c ord is set to a data structure representing the ordinal value when parsing is successful.
extern bool bib_parse_cutter_ordinal(bib_ordinal_t *ord, bib_strbuf_t *parser);

/// Read an ordinal value for a call number's caption section from the given input stream.
/// \param ord Allocated space for a structure representing the parsed ordinal value in the caption section.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when an ordinal value is successfully read from the input stream.
/// \post \c ord is set to a data structure representing the ordinal value when parsing is successful.
extern bool bib_parse_caption_ordinal(bib_ordinal_t *ord, bib_strbuf_t *parser);

/// Read an ordinal value for a call number's specification segment from the given input stream.
/// \param ord Allocated space for a structure representing the parsed ordinal value in a specification segment.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when an ordinal value is successfully read from the input stream.
/// \post \c ord is set to a data structure representing the ordinal value when parsing is successful.
extern bool bib_parse_specification_ordinal(bib_ordinal_t *ord, bib_strbuf_t *parser);

/// Read an ordinal value from the given input stream.
/// \param ord Allocated space for a structure representing the parsed ordinal value.
/// \param lex_suffix A function defining the lexing strategy used for the ordinal's suffix value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when an ordinal value is successfully read from the input stream.
/// \post \c ord is set to a data structure representing the ordinal value when parsing is successful.
extern bool bib_parse_ordinal(bib_ordinal_t *ord, bib_lex_word_f lex_suffix, bib_strbuf_t *parser);

/// Read a call number's volume value from the given input stream.
/// \param vol Allocated space for a structure representing the parsed volume value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a volume value is successfully read from the input stream.
/// \post \c vol is set to a data structure representing the volume value when parsing is successful.
extern bool bib_parse_volume(bib_volume_t *vol, bib_strbuf_t *parser);

/// Read a call number's supplementary work value from the given input stream.
/// \param supl Allocated space for a structure representing the parsed supplementary value.
/// \param parser Pointer to a string buffer object to parse from.
/// \returns \c true when a supplementary work value is successfully read from the input stream.
/// \post \c supl is set to a data structure representing the supplementary value when parsing is successful.
extern bool bib_parse_supplement(bib_supplement_t *supl, bib_strbuf_t *parser);

__END_DECLS

#endif /* bibparse_h */
