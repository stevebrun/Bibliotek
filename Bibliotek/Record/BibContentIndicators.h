//
//  BibContentIndicators.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 6/27/19.
//  Copyright © 2019 Steve Brunwasser. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef char BibContentIndicator NS_TYPED_EXTENSIBLE_ENUM NS_SWIFT_NAME(ContentIndicator);

NS_ASSUME_NONNULL_BEGIN

NS_SWIFT_NAME(ContentIndicators)
@interface BibContentIndicators : NSObject

@property (nonatomic, assign, readonly) NSUInteger count;

- (instancetype)initWithIndicators:(BibContentIndicator const *)indicators
                             count:(NSUInteger)count NS_DESIGNATED_INITIALIZER;

- (BibContentIndicator)indicatorAtIndex:(NSUInteger)index NS_SWIFT_NAME(indicator(at:));

@end

#pragma mark - Copying

@interface BibContentIndicators (Copying) <NSCopying, NSMutableCopying>
@end

#pragma mark - Equality

@interface BibContentIndicators (Equality)

- (BOOL)isEqualToIndicators:(BibContentIndicators *)indicators;

@end

#pragma mark - MARC 21

@interface BibContentIndicators (MARC21)

@property (nonatomic, assign, readonly) BibContentIndicator firstIndicator NS_SWIFT_NAME(first);

@property (nonatomic, assign, readonly) BibContentIndicator secondIndicator NS_SWIFT_NAME(second);

- (instancetype)initWithFirstIndicator:(BibContentIndicator)firstIndicator
                       secondIndicator:(BibContentIndicator)secondIndicator NS_SWIFT_NAME(init(first:second:));

@end

#pragma mark - Mutable

@interface BibMutableContentIndicators : BibContentIndicators

- (void)setIndicator:(BibContentIndicator)indicator atIndex:(NSUInteger)index;

@end

#pragma mark - Mutable MARC 21

@interface BibMutableContentIndicators (MARC21)

@property (nonatomic, assign, readwrite) BibContentIndicator firstIndicator NS_SWIFT_NAME(first);

@property (nonatomic, assign, readwrite) BibContentIndicator secondIndicator NS_SWIFT_NAME(second);

@end

NS_ASSUME_NONNULL_END
