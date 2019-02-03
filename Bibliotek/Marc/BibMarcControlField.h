//
//  BibMarcRecordControlField.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 1/22/19.
//  Copyright © 2019 Steve Brunwasser. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BibMarcTag;

NS_ASSUME_NONNULL_BEGIN

/// \brief A control field contains information and metadata pertaining to the processing of a record's data.
///
/// More information about MARC 21 records can be found in the Library of Congress's documentation on
/// MARC 21 Record Structure: https://www.loc.gov/marc/specifications/specrecstruc.html.
NS_SWIFT_NAME(MarcControlField)
@interface BibMarcControlField : NSObject <NSCopying, NSMutableCopying, NSSecureCoding>

/// A three-digit code used to identify this control field's semantic purpose.
@property (nonatomic, strong, readonly) BibMarcTag *tag;

/// The stored data within this control field.
@property (nonatomic, copy, readonly) NSString *content;

- (nullable instancetype)initWithTag:(BibMarcTag *)tag content:(NSString *)content NS_DESIGNATED_INITIALIZER;

+ (nullable instancetype)controlFieldWithTag:(BibMarcTag *)tag
                                     content:(NSString *)content NS_SWIFT_UNAVAILABLE("Use init(tag:content:)");

/// Determine whether or not the given control field represents the same data as the receiver.
/// \param controlField The control field with which the receiver should be compared.
/// \returns Returns \c YES if the given control field and the receiver have the same tag and content data.
- (BOOL)isEqualToControlField:(BibMarcControlField *)controlField;

@end

NS_SWIFT_NAME(MarcMutableControlField)
@interface BibMarcMutableControlField : BibMarcControlField

/// A three-digit code used to identify this control field's semantic purpose.
@property (nonatomic, strong, readwrite) BibMarcTag *tag;

/// The stored data within this control field.
@property (nonatomic, copy, readwrite) NSString *content;

@end

NS_ASSUME_NONNULL_END