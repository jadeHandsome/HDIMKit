#ifdef __OBJC__
#import <UIKit/UIKit.h>
#else
#ifndef FOUNDATION_EXPORT
#if defined(__cplusplus)
#define FOUNDATION_EXPORT extern "C"
#else
#define FOUNDATION_EXPORT extern
#endif
#endif
#endif

#import "HDIMConversation.h"
#import "HDIMFriendAddApplication.h"
#import "HDIMFriendApplication.h"
#import "HDIMFriendApplicationResult.h"
#import "HDIMFriendCheckResult.h"
#import "HDIMFriendInfo.h"
#import "HDIMFriendInfoResult.h"
#import "HDIMFriendOperationResult.h"
#import "HDIMCreateGroupMemberInfo.h"
#import "HDIMGroupInfo.h"
#import "HDIMGroupInfoResult.h"
#import "HDIMGroupMemberOperationResult.h"
#import "HDIMGroupMemberFullInfo.h"
#import "HDIMGroupMemberInfo.h"
#import "HDIMSDKConfig.h"
#import "HDIMSDKUserFullInfo.h"
#import "HDIMSDKUserInfo.h"
#import "HDIMMessage.h"
#import "HDIMMessageListGetOption.h"
#import "HDIMMessageSearchParam.h"
#import "HDIMMessageSearchResult.h"
#import "HDIMMessageSearchResultItem.h"
#import "V2TIMReceiveMessageOptInfo.h"
#import "HDIMKit.h"
#import "HDIMManager+Conversation.h"
#import "HDIMManager+Friend.h"
#import "HDIMManager+Group.h"
#import "HDIMManager+Message.h"
#import "HDIMManager.h"

FOUNDATION_EXPORT double HDIMKitVersionNumber;
FOUNDATION_EXPORT const unsigned char HDIMKitVersionString[];

