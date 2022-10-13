//
//  HDIMManager+Friend.m
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager+Friend.h"

@implementation HDIMManager (Friend)
/////////////////////////////////////////////////////////////////////////////////
//
//                         关系链和用户资料监听器
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加关系链监听器
 */
- (void)addFriendListener:(id<HDIMFriendshipListener>)listener {
#pragma -- 需要实现
}

/**
 *  移除关系链监听器
 */
- (void)removeFriendListener:(id<HDIMFriendshipListener>)listener {
#pragma -- 需要实现
}


/////////////////////////////////////////////////////////////////////////////////
//
//                       好友添加、删除、列表获取、资料设置相关接口
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取好友列表
 */
- (void)getFriendList:(HDIMFriendInfoListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  获取指定好友资料
 *  @param userIDList 好友 userID 列表
 *                   - ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
 */
- (void)getFriendsInfo:(NSArray<NSString *> *)userIDList succ:(HDIMFriendInfoResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  设置指定好友资料
 */
- (void)setFriendInfo:(HDIMFriendInfo *)info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}



/**
 *  添加好友
 */
- (void)addFriend:(HDIMFriendAddApplication *)application succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  删除好友
 *  @param userIDList 要删除的好友 userID 列表
 *                   - ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
 *  @param deleteType 删除类型（单向好友、双向好友）
 */
- (void)deleteFromFriendList:(NSArray *)userIDList deleteType:(HDIMFriendType)deleteType succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  检查指定用户的好友关系
 *  @param userIDList 要检查的 userID 列表
 *  @param checkType 检查类型 （单向好友检查、双向好友检查）
 *  @param succ 成功后的回调
 *  @param fail 失败后的回调
 *
 *  @note checkType 的使用需要注意：
 *  - checkType 如果传入 V2TIM_FRIEND_TYPE_SINGLE，结果返回：V2TIM_FRIEND_RELATION_TYPE_NONE、V2TIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST 两种情况
 *  - checkType 如果传入 V2TIM_FRIEND_TYPE_BOTH，结果返回：V2TIM_FRIEND_RELATION_TYPE_NONE、V2TIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST、
 *                                                 V2TIM_FRIEND_RELATION_TYPE_IN_OTHER_FRIEND_LIST、V2TIM_FRIEND_RELATION_TYPE_BOTH_WAY 四种情况
 */
- (void)checkFriend:(NSArray<NSString *> *)userIDList checkType:(HDIMFriendType)checkType succ:(HDIMFriendCheckResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/////////////////////////////////////////////////////////////////////////////////
//
//                          好友申请、删除相关逻辑
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取好友申请列表
 *
 *  @note 好友申请列表包括发起的好友申请和收到的好友申请。
*/
- (void)getFriendApplicationList:(HDIMFriendApplicationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  同意好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 *  @param acceptType 建立单向/双向好友关系
 */
- (void)acceptFriendApplication:(HDIMFriendApplication *)application type:(HDIMFriendAcceptType)acceptType succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  拒绝好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 */
- (void)refuseFriendApplication:(HDIMFriendApplication *)application succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  删除好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 */
- (void)deleteFriendApplication:(HDIMFriendApplication *)application succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  设置好友申请已读
 */
- (void)setFriendApplicationRead:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}


/////////////////////////////////////////////////////////////////////////////////
//
//                          黑名单
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加用户到黑名单
 */
- (void)addToBlackList:(NSArray *)userIDList succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  把用户从黑名单中删除
 */
- (void)deleteFromBlackList:(NSArray *)userIDList succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  获取黑名单列表
 */
- (void)getBlackList:(HDIMFriendInfoListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
@end
