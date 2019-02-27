//
//  BibClassificationRecordClassificationScheme.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 2/23/19.
//  Copyright © 2019 Steve Brunwasser. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "BibRecordConstants.h"

@class BibRecordSubfield;

NS_ASSUME_NONNULL_BEGIN

/// http://www.loc.gov/marc/classification/cd084.html
NS_SWIFT_NAME(ClassificationRecord.ClassificationScheme)
@interface BibClassificationRecordClassificationScheme : NSObject

@property (nonatomic, copy, readonly) BibClassificationScheme classificationScheme;

@property (nonatomic, assign, readonly) BibEditionKind editionKind;

@property (nonatomic, copy, readonly, nullable) NSString *editionTitle;

@property (nonatomic, copy, readonly, nullable) NSString *editionIdentifier;

@property (nonatomic, copy, readonly, nullable) BibMarcLanguageCode language;

@property (nonatomic, copy, readonly, nullable) NSString *authorization;

@property (nonatomic, copy, readonly, nullable) BibMarcOrganization assigningAgency;

@property (class, nonatomic, strong, readonly) BibRecordFieldTag recordFieldTag;

- (instancetype)initWithIndicators:(NSArray<BibRecordFieldIndicator> *)indicators
                         subfields:(NSArray<BibRecordSubfield *> *)subfields NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
