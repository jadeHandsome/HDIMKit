//
//  HDIMManager+Friend.h
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager.h"


@protocol HDIMFriendshipListener;
@class HDIMFriendInfo;
@class HDIMFriendInfoResult;
@class HDIMFriendApplicationResult;
@class HDIMFriendApplication;
@class HDIMFriendOperationResult;
@class HDIMFriendCheckResult;
@class HDIMFriendAddApplication;

@interface HDIMManager (Friend)
/// 好友申请类型
typedef NS_ENUM(NSInteger, HDIMFriendApplicationType) {
    HDIM_FRIEND_APPLICATION_COME_IN        = 1,  ///< 别人发给我的
    HDIM_FRIEND_APPLICATION_SEND_OUT       = 2,  ///< 我发给别人的
    HDIM_FRIEND_APPLICATION_BOTH           = 3,  ///< 别人发给我的 和 我发给别人的。仅拉取时有效
};
/// 好友类型
typedef NS_ENUM(NSInteger, HDIMFriendType) {
    HDIM_FRIEND_TYPE_SINGLE                = 1,  ///< 单向好友
    HDIM_FRIEND_TYPE_BOTH                  = 2,  ///< 双向好友
};

/// 好友关系类型
typedef NS_ENUM(NSInteger, HDIMFriendRelationType) {
    HDIM_FRIEND_RELATION_TYPE_NONE                   = 0x0,  ///< 不是好友
    HDIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST      = 0x1,  ///< 对方在我的好友列表中
    HDIM_FRIEND_RELATION_TYPE_IN_OTHER_FRIEND_LIST   = 0x2,  ///< 我在对方的好友列表中
    HDIM_FRIEND_RELATION_TYPE_BOTH_WAY               = 0x3,  ///< 互为好友
};

/// 好友申请接受类型
typedef NS_ENUM(NSInteger, HDIMFriendAcceptType) {
    HDIM_FRIEND_ACCEPT_AGREE             = 0,  ///< 接受加好友（建立单向好友）
    HDIM_FRIEND_ACCEPT_AGREE_AND_ADD     = 1,  ///< 接受加好友并加对方为好友（建立双向好友）
};

/// 获取好友列表成功回调
typedef void (^HDIMFriendInfoListSucc)(NSArray<HDIMFriendInfo *> *infoList);

/// 获取指定好友信息成功回调
typedef void (^HDIMFriendInfoResultListSucc)(NSArray<HDIMFriendInfoResult *> *resultList);

/// 好友操作成功回调
typedef void (^HDIMFriendOperationResultSucc)(HDIMFriendOperationResult *result);

/// 好友列表操作成功回调
typedef void (^HDIMFriendOperationResultListSucc)(NSArray<HDIMFriendOperationResult *> *resultList);

/// 好友检查成功回调
typedef void (^HDIMFriendCheckResultListSucc)(NSArray<HDIMFriendCheckResult *> *resultList);

/// 获取好友申请列表成功回调
typedef void (^HDIMFriendApplicationResultSucc)(HDIMFriendApplicationResult *result);


/////////////////////////////////////////////////////////////////////////////////
//
//                         关系链和用户资料监听器
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加关系链监听器
 */
- (void)addFriendListener:(id<HDIMFriendshipListener>)listener;

/**
 *  移除关系链监听器
 */
- (void)removeFriendListener:(id<HDIMFriendshipListener>)listener;


/////////////////////////////////////////////////////////////////////////////////
//
//                       好友添加、删除、列表获取、资料设置相关接口
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取好友列表
 */
- (void)getFriendList:(HDIMFriendInfoListSucc)succ fail:(IMSDKFail)fail;

/**
 *  获取指定好友资料
 *  @param userIDList 好友 userID 列表
 *                   - ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
 */
- (void)getFriendsInfo:(NSArray<NSString *> *)userIDList succ:(HDIMFriendInfoResultListSucc)succ fail:(IMSDKFail)fail;

/**
 *  设置指定好友资料
 */
- (void)setFriendInfo:(HDIMFriendInfo *)info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;



/**
 *  添加好友
 */
- (void)addFriend:(HDIMFriendAddApplication *)application succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  删除好友
 *  @param userIDList 要删除的好友 userID 列表
 *                   - ID 建议一次最大 100 个，因为数量过多可能会导致数据包太大被后台拒绝，后台限制数据包最大为 1M。
 *  @param deleteType 删除类型（单向好友、双向好友）
 */
- (void)deleteFromFriendList:(NSArray *)userIDList deleteType:(HDIMFriendType)deleteType succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail;

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
- (void)checkFriend:(NSArray<NSString *> *)userIDList checkType:(HDIMFriendType)checkType succ:(HDIMFriendCheckResultListSucc)succ fail:(IMSDKFail)fail;

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
- (void)getFriendApplicationList:(HDIMFriendApplicationResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  同意好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 *  @param acceptType 建立单向/双向好友关系
 */
- (void)acceptFriendApplication:(HDIMFriendApplication *)application type:(HDIMFriendAcceptType)acceptType succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  拒绝好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 */
- (void)refuseFriendApplication:(HDIMFriendApplication *)application succ:(HDIMFriendOperationResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  删除好友申请
 *
 *  @param application 好友申请信息，getFriendApplicationList 成功后会返回
 */
- (void)deleteFriendApplication:(HDIMFriendApplication *)application succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  设置好友申请已读
 */
- (void)setFriendApplicationRead:(IMSDKSucc)succ fail:(IMSDKFail)fail;


/////////////////////////////////////////////////////////////////////////////////
//
//                          黑名单
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加用户到黑名单
 */
- (void)addToBlackList:(NSArray *)userIDList succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail;

/**
 *  把用户从黑名单中删除
 */
- (void)deleteFromBlackList:(NSArray *)userIDList succ:(HDIMFriendOperationResultListSucc)succ fail:(IMSDKFail)fail;

/**
 *  获取黑名单列表
 */
- (void)getBlackList:(HDIMFriendInfoListSucc)succ fail:(IMSDKFail)fail;
@end


/////////////////////////////////////////////////////////////////////////////////
//
//                      资料关系链回调
//
/////////////////////////////////////////////////////////////////////////////////
/// 资料关系链回调
@protocol HDIMFriendshipListener <NSObject>
@optional
/**
 *  好友申请新增通知,两种情况会收到这个回调：
 *  1. 自己申请加别人好友
 *  2. 别人申请加自己好友
 */
- (void)onFriendApplicationListAdded:(NSArray<HDIMFriendApplication *> *)applicationList;

/**
 *  好友申请删除通知，四种情况会收到这个回调：
 *  1. 调用 deleteFriendApplication 主动删除好友申请
 *  2. 调用 refuseFriendApplication 拒绝好友申请
 *  3. 调用 acceptFriendApplication 同意好友申请
 *  4. 申请加别人好友被拒绝
 */
- (void)onFriendApplicationListDeleted:(NSArray *)userIDList;

/**
 *  好友申请已读通知，如果调用 setFriendApplicationRead 设置好友申请列表已读，会收到这个回调（主要用于多端同步）
 */
- (void)onFriendApplicationListRead;

/**
 *  好友新增通知
 */
- (void)onFriendListAdded:(NSArray<HDIMFriendInfo *>*)infoList;

/**
 *  好友删除通知，两种情况会收到这个回调：
 *  1. 自己删除好友（单向和双向删除都会收到回调）
 *  2. 好友把自己删除（双向删除会收到）
 */
- (void)onFriendListDeleted:(NSArray*)userIDList;

/**
 *  黑名单新增通知
 */
- (void)onBlackListAdded:(NSArray<HDIMFriendInfo *>*)infoList;

/**
 *  黑名单删除通知
 */
- (void)onBlackListDeleted:(NSArray*)userIDList;

/**
 *  好友资料变更通知
 */
- (void)onFriendProfileChanged:(NSArray<HDIMFriendInfo *> *)infoList;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                      好友资料
//
/////////////////////////////////////////////////////////////////////////////////
/// 好友资料
@interface HDIMFriendInfo : NSObject

/// 好友 ID
@property(nonatomic,strong) NSString *userID;

/**
 * 好友备注
 *
 * @note
 * - 备注长度最长不得超过 96 个字节;
*/
@property(nonatomic,strong) NSString *friendRemark;

/// 好友自定义字段
@property(nonatomic,strong) NSDictionary<NSString *,NSData *> *friendCustomInfo;


/// 好友个人资料
@property(nonatomic,strong,readonly) HDIMSDKUserFullInfo *userFullInfo;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                      好友资料获取结果
//
/////////////////////////////////////////////////////////////////////////////////
/// 好友资料获取结果
@interface HDIMFriendInfoResult : NSObject

/// 返回码
@property(nonatomic,assign) int resultCode;

/// 返结果表述
@property(nonatomic,strong) NSString *resultInfo;

/// 好友类型
@property(nonatomic,assign) HDIMFriendRelationType relation;

/// 好友个人资料，如果不是好友，除了 userID 字段，其他字段都为空
@property(nonatomic,strong) HDIMFriendInfo *friendInfo;
@end

/// 好友申请列表
@interface HDIMFriendApplicationResult : NSObject

/// 好友申请未读数量
@property(nonatomic,assign) uint64_t unreadCount;

/// 好友申请列表
@property(nonatomic,strong) NSMutableArray<HDIMFriendApplication *> * applicationList;

@end

/// 好友申请
@interface HDIMFriendApplication : NSObject

/// 用户标识
@property(nonatomic,strong,readonly) NSString* userID;

/// 用户昵称
@property(nonatomic,strong,readonly) NSString* nickName;

/// 用户头像
@property(nonatomic,strong,readonly) NSString* faceUrl;

/// 添加时间
@property(nonatomic,assign,readonly) uint64_t addTime;

/// 来源
@property(nonatomic,strong,readonly) NSString* addSource;

/// 加好友附言
@property(nonatomic,strong,readonly) NSString* addWording;

/// 好友申请类型
@property(nonatomic,assign,readonly) HDIMFriendApplicationType type;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                      好友申请相关对象
//
/////////////////////////////////////////////////////////////////////////////////

/// 加好友
@interface HDIMFriendAddApplication : NSObject

/// 用户 userID（必填）
@property (nonatomic,strong) NSString* userID;

/// 备注（备注最大96字节）
@property (nonatomic,strong) NSString* friendRemark;

/// 预分组名（最大96字节）
@property (nonatomic,strong) NSString* friendGroup;

/// 请求说明（最大120字节）
@property (nonatomic,strong) NSString* addWording;

/// 添加来源
@property (nonatomic,strong) NSString* addSource;

/// 加好友方式
@property (nonatomic,assign) HDIMFriendType addType;

@end
/////////////////////////////////////////////////////////////////////////////////
//
//                 好友操作结果（添加、删除、加黑名单、添加分组等）
//
/////////////////////////////////////////////////////////////////////////////////
/// 好友操作结果（添加、删除、加黑名单、添加分组等）
@interface HDIMFriendOperationResult : NSObject

/// 用户Id
@property(nonatomic,strong) NSString* userID;

/// 返回码
@property(nonatomic,assign) NSInteger resultCode;

/// 返回信息
@property(nonatomic,strong) NSString *resultInfo;

@end
/////////////////////////////////////////////////////////////////////////////////
//
//                    好友关系链检查结果
//
/////////////////////////////////////////////////////////////////////////////////
/// 好友关系链检查结果
@interface HDIMFriendCheckResult : NSObject

/// 用户id
@property(nonatomic,strong) NSString* userID;

/// 返回码
@property(nonatomic,assign) NSInteger resultCode;

/// 返回信息
@property(nonatomic,strong) NSString *resultInfo;

/// 检查结果
@property(nonatomic,assign) HDIMFriendRelationType relationType;

@end
