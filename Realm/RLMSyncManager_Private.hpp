////////////////////////////////////////////////////////////////////////////
//
// Copyright 2016 Realm Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
////////////////////////////////////////////////////////////////////////////

#import "RLMSyncManager.h"

#import "sync_config.hpp"
#import "sync_metadata.hpp"

@class RLMSyncUser;

// All private API methods are threadsafe and synchronized, unless denoted otherwise. Since they are expected to be
// called very infrequently, this should pose no issues.

@interface RLMSyncManager () {
    std::unique_ptr<realm::SyncMetadataManager> _metadata_manager;
}

NS_ASSUME_NONNULL_BEGIN

/// Reset the singleton instance, and any saved state. Only for use with Realm Object Store tests.
+ (void)_resetStateForTesting;

- (void)_fireError:(NSError *)error;

- (void)_fireErrorWithCode:(int)errorCode
                   message:(NSString *)message
                   session:(nullable RLMSyncSession *)session
                errorClass:(realm::SyncSessionError)errorClass;

// Note that this method doesn't need to be threadsafe, since all locking is coordinated internally.
- (realm::SyncMetadataManager&)_metadataManager;

- (NSArray<RLMSyncUser *> *)_allUsers;

/**
 Registers a user. If an equivalent user has already been registered, the argument is not added to the store, and the
 existing user is returned. Otherwise, the argument is added to the store and `nil` is returned.
 */
- (nullable RLMSyncUser *)_registerUser:(RLMSyncUser *)user;

- (void)_deregisterUser:(RLMSyncUser *)user;

- (nullable RLMSyncUser *)_userForIdentity:(NSString *)identity;

NS_ASSUME_NONNULL_END

@end
