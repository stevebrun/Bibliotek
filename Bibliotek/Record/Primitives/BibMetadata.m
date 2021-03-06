//
//  BibMetadata.m
//  Bibliotek
//
//  Created by Steve Brunwasser on 6/26/19.
//  Copyright © 2019 Steve Brunwasser. All rights reserved.
//

#import "BibMetadata.h"
#import "BibMetadata+Internal.h"
#import "BibLeader.h"
#import "BibRecordKind.h"

static BibReservedPosition const kAllReservedPositions[] = {
    BibReservedPosition07,
    BibReservedPosition08,
    BibReservedPosition17,
    BibReservedPosition18,
    BibReservedPosition19
};

#pragma mark - Metadata

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-implementations"

@implementation BibMetadata {
    BibLeader *_leader;
}

- (instancetype)init {
    if (self = [super init]) {
        _leader = [BibLeader new];
    }
    return self;
}

- (int8_t)valueForReservedPosition:(BibReservedPosition)index {
    return [[self leader] valueForReservedPosition:index];
}

- (NSString *)description {
    NSMutableArray *const components = [NSMutableArray new];
    NSUInteger const count = sizeof(kAllReservedPositions) / sizeof(BibReservedPosition);
    for (NSUInteger index = 0; index < count; index += 1) {
        BibReservedPosition const position = kAllReservedPositions[index];
        uint8_t const value =  [self valueForReservedPosition:position];
        [components addObject:[NSString stringWithFormat:@"\"%c\"", value]];
    }
    return [NSString stringWithFormat:@"[%@]", [components componentsJoinedByString:@", "]];
}

@end

@implementation BibMetadata (Internal)

- (instancetype)initWithLeader:(BibLeader *)leader {
    if (self = [super init]) {
        _leader = [leader copy];
    }
    return self;
}

- (BibLeader *)leader {
    return _leader;
}

@end

#pragma mark -

@implementation BibMetadata (Copying)

- (id)copyWithZone:(NSZone *)zone {
    return self;
}

- (id)mutableCopyWithZone:(NSZone *)zone {
    return [[BibMutableMetadata allocWithZone:zone] initWithLeader:[self leader]];
}

@end

@implementation BibMetadata (Equality)

- (BOOL)isEqualToMetadata:(BibMetadata *)metadata {
    int const indexCount = sizeof(kAllReservedPositions) / sizeof(BibReservedPosition);
    for (int index = 0; index < indexCount; index += 1) {
        char const myValue = [self valueForReservedPosition:kAllReservedPositions[index]];
        char const theirValue = [metadata valueForReservedPosition:kAllReservedPositions[index]];
        if (myValue != theirValue) {
            return NO;
        }
    }
    return YES;
}

- (BOOL)isEqual:(id)object {
    return self == object
        || ([object isKindOfClass:[BibMetadata class]] && [self isEqualToMetadata:object]);
}

- (NSUInteger)hash {
    NSUInteger hash = 0;
    int const indexCount = sizeof(kAllReservedPositions) / sizeof(BibReservedPosition);
    for (int index = 0; index < indexCount; index += 1) {
        hash |= [self valueForReservedPosition:kAllReservedPositions[index]] << (index % 4 * 8);
    }
    return hash;
}

@end

#pragma mark - Mutable Metadata

@implementation BibMutableMetadata {
    BibMutableLeader *_leader;
}

- (id)copyWithZone:(NSZone *)zone {
    return [[BibMetadata allocWithZone:zone] initWithLeader:[self leader]];
}

- (void)setValue:(int8_t)value forReservedPosition:(BibReservedPosition)index {
    [[self leader] setValue:value forReservedPosition:index];
}

@end

@implementation BibMutableMetadata (Internal)

- (BibMutableLeader *)leader {
    if (_leader == nil) {
        _leader = [[super leader] mutableCopy];
    }
    return _leader;
}

@end

#pragma mark - Encoding

NSString *BibEncodingDescription(BibEncoding const encoding) {
    switch (encoding) {
        case BibMARC8Encoding: return @"MARC8";
        case BibUTF8Encoding:  return @"UTF8";
        default: return [NSString stringWithFormat:@"%c", encoding];
    }
}

#pragma mark - Record Status

NSString *BibRecordStatusDescription(BibRecordStatus const status) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    NSBundle *bundle = [NSBundle bundleForClass:[BibMetadata self]];
#pragma clang diagnostic pop
    switch (status) {
        case BibRecordStatusIncreaseInEncodingLevel:
            return NSLocalizedStringWithDefaultValue(@"a", @"RecordStatus", bundle,
                                                     @"Increase in encoding level", @"Increase in encoding level");
        case BibRecordStatusRevised:
            return NSLocalizedStringWithDefaultValue(@"c", @"RecordStatus", bundle,
                                                     @"Corrected or revised", @"Corrected or revised");
        case BibRecordStatusDeleted:
            return NSLocalizedStringWithDefaultValue(@"d", @"RecordStatus", bundle, @"Deleted", @"Deleted");
        case BibRecordStatusNew:
            return NSLocalizedStringWithDefaultValue(@"n", @"RecordStatus", bundle, @"New", @"New");
        case BibRecordStatusIncreaseInEncodingLevelFromPrePublication:
            return NSLocalizedStringWithDefaultValue(@"p", @"RecordStatus", bundle,
                                                     @"Increase in encoding level from prepublication",
                                                     @"Increase in encoding level from prepublication");
        default: {
            NSString *key = [NSString stringWithFormat:@"%c", status];
            return [bundle localizedStringForKey:key value:nil table:@"RecordStatus"];
        }
    }
}

#pragma mark - Bibliographic Level

NSString *BibBibliographicLevelDescription(BibBibliographicLevel const level) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    NSBundle *bundle = [NSBundle bundleForClass:[BibMetadata self]];
#pragma clang diagnostic pop
    switch (level) {
        case 0: return nil;
        case BibBibliographicLevelMonographicComponentPart:
            return NSLocalizedStringWithDefaultValue(@"a", @"BibliographicLevel", bundle,
                                                     @"Monographic component part", @"Monographic component part");
        case BibBibliographicLevelSerialComponentPart:
            return NSLocalizedStringWithDefaultValue(@"b", @"BibliographicLevel", bundle,
                                                     @"Serial component part", @"Serial component part");
        case BibBibliographicLevelCollection:
            return NSLocalizedStringWithDefaultValue(@"c", @"BibliographicLevel", bundle,
                                                     @"Collection", @"Collection");
        case BibBibliographicLevelSubunit:
            return NSLocalizedStringWithDefaultValue(@"d", @"BibliographicLevel", bundle,
                                                     @"Subunit", @"Subunit");
        case BibBibliographicLevelIntegratingResource:
            return NSLocalizedStringWithDefaultValue(@"i", @"BibliographicLevel", bundle,
                                                     @"Integrating resource", @"Integrating resource");
        case BibBibliographicLevelMonograph:
            return NSLocalizedStringWithDefaultValue(@"m", @"BibliographicLevel", bundle,
                                                     @"Monograph/Item", @"Monograph/Item");
        case BibBibliographicLevelSerial:
            return NSLocalizedStringWithDefaultValue(@"s", @"BibliographicLevel", bundle,
                                                     @"Serial", @"Serial");
        default: {
            NSString *key = [NSString stringWithFormat:@"%c", level];
            return [bundle localizedStringForKey:key value:nil table:@"BibliographicLevel"];
        }
    }
}

#pragma mark - Bibliographic Control Type

NSString *BibBibliographicControlTypeDescription(BibBibliographicControlType const type) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
    NSBundle *bundle = [NSBundle bundleForClass:[BibMetadata self]];
#pragma clang diagnostic pop
    switch (type) {
        case 0: return nil;
        case BibBibliographicControlTypeNone:
            return NSLocalizedStringWithDefaultValue(@" ", @"BibliographicControlType", bundle, @"None", @"None");
        case BibBibliographicControlTypeArchival:
            return NSLocalizedStringWithDefaultValue(@"a", @"BibliographicControlType", bundle, @"Archival", @"Archival");
        default: {
            NSString *key = [NSString stringWithFormat:@"%c", type];
            return [bundle localizedStringForKey:key value:nil table:@"BibliographicLevel"];
        }
    }
}

#pragma mark -

@implementation BibMetadata (DefinedValues)

- (BibEncoding)encoding {
    return [[self leader] recordEncoding];
}

- (BibRecordKind *)recordKind {
    return [[self leader] recordKind];
}

- (BibRecordStatus)recordStatus {
    return [[self leader] recordStatus];
}

- (BibBibliographicLevel)bibliographicLevel {
    if ([[self recordKind] isBibliographicKind]) {
        return [self valueForReservedPosition:BibReservedPosition07];
    }
    return 0;
}

- (BibBibliographicControlType)bibliographicControlType {
    if ([[self recordKind] isBibliographicKind]) {
        return [self valueForReservedPosition:BibReservedPosition08];
    }
    return 0;
}

@end

@implementation BibMutableMetadata (DefinedValues)

- (void)setRecordKind:(BibRecordKind *)recordKind {
    [[self leader] setRecordKind:recordKind];
}

- (void)setRecordStatus:(BibRecordStatus)recordStatus {
    [[self leader] setRecordStatus:recordStatus];
}

- (void)setBibliographicLevel:(BibBibliographicLevel)bibliographicLevel {
    if ([[[self leader] recordKind] isBibliographicKind]) {
        [self setValue:(bibliographicLevel ?: ' ') forReservedPosition:BibReservedPosition07];
    }
}

- (void)setBibliographicControlType:(BibBibliographicControlType)bibliographicControlType {
    if ([[[self leader] recordKind] isBibliographicKind]) {
        bibliographicControlType = (bibliographicControlType ?: BibBibliographicControlTypeNone);
        [self setValue:bibliographicControlType forReservedPosition:BibReservedPosition08];
    }
}

@end

#pragma clang diagnostic pop
