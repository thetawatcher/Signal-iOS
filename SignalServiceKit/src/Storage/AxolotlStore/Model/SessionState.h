//
//  Copyright (c) 2021 Open Whisper Systems. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ChainKey;
@class ECKeyPair;
@class ReceivingChain;

#import <SignalServiceKit/MessageKeys.h>
#import <SignalServiceKit/RootKey.h>

/**
 *  Pending PreKeys
 */

@interface PendingPreKey : NSObject <NSSecureCoding>

@property (readonly) int preKeyId;
@property (readonly) int signedPreKeyId;
@property (readonly) NSData *baseKey;

-(instancetype)initWithBaseKey:(NSData*)baseKey preKeyId:(int)preKeyId signedPreKeyId:(int)signedPrekeyId;

@end

@interface SessionState : NSObject <NSSecureCoding>

/**
 *  AxolotlSessions are either retreived from the database or initiated on new discussions. They are serialized before being stored to make storing abstractions significantly simpler. Because we propose no abstraction for a contact and TextSecure has multi-device (multiple sessions with same identity key) support, the identityKeys need to be added manually.
 */

@property(nonatomic) int  version;
@property(nonatomic, copy) NSData *aliceBaseKey;
@property(nonatomic) NSData *remoteIdentityKey;
@property(nonatomic) NSData *localIdentityKey;
@property(nonatomic) int previousCounter;
@property(nonatomic) RootKey *rootKey;

@property(nonatomic) NSArray<ReceivingChain *> *receivingChains;

@property(nonatomic)int remoteRegistrationId;
@property(nonatomic)int localRegistrationId;

@property (nonatomic, readonly) BOOL isFresh;

- (NSData*)senderRatchetKey;
- (ECKeyPair*)senderRatchetKeyPair;

- (void)setSenderChain:(ECKeyPair*)senderRatcherKeyPair chainKey:(ChainKey*)chainKey;

- (ChainKey*)senderChainKey;

- (void)setUnacknowledgedPreKeyMessage:(int)preKeyId signedPreKey:(int)signedPreKeyId baseKey:(NSData*)baseKey;
- (PendingPreKey*)unacknowledgedPreKeyMessageItems;

@end
