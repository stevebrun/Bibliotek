//
//  BibMARCXMLOutputStream.h
//  Bibliotek
//
//  Created by Steve Brunwasser on 5/8/22.
//  Copyright © 2022 Steve Brunwasser. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <Bibliotek/BibRecordOutputStream.h>

NS_ASSUME_NONNULL_BEGIN

/// A write-only stream used to serialize record objects as MARC XML encoded data.
NS_SWIFT_NAME(MARCXMLOutputStream)
@interface BibMARCXMLOutputStream : BibRecordOutputStream

/// Initializes and returns a ``BibMARCXMLOutputStream`` for writing to the given input stream.
/// - parameter outputStream: The `NSOutputStream` object to which record data should be written.
/// - returns: An initialized ``BibMARCOutputStream`` object that writes ``BibRecord`` objects to the given input stream.
- (instancetype)initWithOutputStream:(NSOutputStream *)outputStream NS_DESIGNATED_INITIALIZER;

@end

NS_ASSUME_NONNULL_END
