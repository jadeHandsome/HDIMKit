//
//  HDIMManager+Group.h
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager.h"

@class HDIMGroupInfo;
@class HDIMCreateGroupMemberInfo;
@class HDIMGroupInfoResult;
@class HDIMGroupMemberOperationResult;

@protocol HDIMGroupListener;

@interface HDIMManager (Group)

/// 加群选项
typedef NS_ENUM(NSInteger, HDIMGroupAddOpt) {
    HDIM_GROUP_ADD_FORBID                 = 0,  ///< 禁止群成员邀请人加群
    HDIM_GROUP_ADD_ANY                    = 2,  ///< 任何人可以邀请加入
};

///  群组操作结果
typedef NS_ENUM(NSInteger, HDIMGroupMemberResult) {
    HDIM_GROUP_MEMBER_RESULT_FAIL         = 0,  ///< 操作失败
    HDIM_GROUP_MEMBER_RESULT_SUCC         = 1,  ///< 操作成功
    HDIM_GROUP_MEMBER_RESULT_INVALID      = 2,  ///< 无效操作，加群时已经是群成员，移除群组时不在群内
    HDIM_GROUP_MEMBER_RESULT_PENDING      = 3,  ///< 等待处理，邀请入群时等待对方处理
    HDIM_GROUP_MEMBER_RESULT_OVERLIMIT    = 4,  ///< 操作失败，创建群指定初始群成员列表或邀请入群时，被邀请者加入的群总数超限
};

/// 创建群组成功回调
typedef void (^IMSDKCreateGroupSucc)(NSString * groupID);
/// 获取已加入群列表成功回调
typedef void (^VHDIMGroupInfoListSucc)(NSArray<HDIMGroupInfo *> *groupList);
/// 获取指定群列表成功回调
typedef void (^HDIMGroupInfoResultListSucc)(NSArray<HDIMGroupInfoResult *> *groupResultList);

/// 获取指定群成员列表成功回调
typedef void (^HDIMGroupMemberInfoResultSucc)(uint64_t nextSeq, NSArray<HDIMGroupMemberFullInfo *> * memberList);

/// 获取群成员列表成功回调
typedef void (^HDIMGroupMemberInfoListSucc)(NSArray<HDIMGroupMemberFullInfo *> *memberList);

/// 群成员操作成功回调
typedef void (^HDIMGroupMemberOperationResultListSucc)(NSArray<HDIMGroupMemberOperationResult*> * resultList);
/////////////////////////////////////////////////////////////////////////////////
//                         群管理
/////////////////////////////////////////////////////////////////////////////////
///

/**
 *  设置群组监听器
 */
- (void)addGroupListener:(id<HDIMGroupListener>)listener;

/**
 *  设置群组监听器
 */
- (void)removeGroupListener:(id<HDIMGroupListener>)listener;


/**
 *  加入群组
 * @param msg 预留字段  后期申请加群的信息可以有用户自行输入
 */
- (void)joinGroup:(NSString *)groupID msg:(NSString *)msg succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  退出群组
 *
 */
- (void)quitGroup:(NSString*)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  解散群组
 *  只能由群主发起
 */
- (void)dismissGroup:(NSString*)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *
 *  @param info 自定义群组信息，可以设置 groupID | groupType | groupName | notification | introduction | faceURL 字段
 *  @param memberList 指定初始的群成员（直播群 AVChatRoom 不支持指定初始群成员，memberList 请传 nil）
 *
 */
- (void)createGroup:(HDIMGroupInfo *)info memberList:(NSArray<HDIMCreateGroupMemberInfo *>*) memberList succ:(IMSDKCreateGroupSucc)succ fail:(IMSDKFail)fail;

/**
 *  1.2 获取当前用户已经加入的群列表
 */
- (void)getJoinedGroupList:(VHDIMGroupInfoListSucc)succ fail:(IMSDKFail)fail;

/////////////////////////////////////////////////////////////////////////////////
//                         群资料管理
/////////////////////////////////////////////////////////////////////////////////

/**
 * 拉取群资料
 *
 *  @param groupIDList 群组 ID 列表
 */
- (void)getGroupsInfo:(NSArray<NSString *> *)groupIDList succ:(HDIMGroupInfoResultListSucc)succ fail:(IMSDKFail)fail;


/**
 *  2.3 修改群资料
 */
- (void)setGroupInfo:(HDIMGroupInfo *)info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;



/////////////////////////////////////////////////////////////////////////////////
//                         群成员管理
/////////////////////////////////////////////////////////////////////////////////
/**
 *  3.1 获取群成员列表
 *
 *  @param nextSeq  分页拉取标志，第一次拉取填0，回调成功如果 nextSeq 不为零，需要分页，传入再次拉取，直至为 0。
 *
 */
- (void)getGroupMemberList:(NSString*)groupID nextSeq:(uint64_t)nextSeq succ:(HDIMGroupMemberInfoResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  3.2 指定的群成员资料
 */
- (void)getGroupMembersInfo:(NSString*)groupID memberList:(NSArray<NSString*>*)memberList succ:(HDIMGroupMemberInfoListSucc)succ fail:(IMSDKFail)fail;





/**
 *  邀请他人入群
 */
- (void)inviteUserToGroup:(NSString*)groupID userList:(NSArray<NSString *>*)userList succ:(HDIMGroupMemberOperationResultListSucc)succ fail:(IMSDKFail)fail;

/**
 *  踢人  只有群主可以踢人
 */
- (void)kickGroupMember:(NSString*)groupID memberList:(NSArray<NSString *>*)memberList reason:(NSString*)reason succ:(HDIMGroupMemberOperationResultListSucc)succ fail:(IMSDKFail)fail;


/**
 *  转让群主
 *
 */
- (void)transferGroupOwner:(NSString*)groupID member:(NSString*)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;


@end

/////////////////////////////////////////////////////////////////////////////////
//
//             群基本资料（可以通过 getGroupInfo 获取，不支持由客户自行创建）
//
/////////////////////////////////////////////////////////////////////////////////
/// 群资料
@interface HDIMGroupInfo : NSObject

/**
 * 群组 ID
 *
 * @note 自定义群组 ID 必须为可打印 ASCII 字符（0x20-0x7e），最长48个字节，且前缀不能为 @TGS#（避免与默认分配的群组 ID 混淆）
 */
@property(nonatomic,strong) NSString* groupID;

/// 群类型
@property(nonatomic,strong) NSString* groupType;

/**
 * 群名称
 *
 * @note 群名称最长30字节
 */
@property(nonatomic,strong) NSString* groupName;

/**
 * 群公告
 *
 * @note 群公告最长300字节
 */
@property(nonatomic,strong) NSString* notification;

/**
 * 群简介
 *
 * @note 群简介最长240字节
 */
@property(nonatomic,strong) NSString* introduction;

/**
 * 群头像
 *
 * @note 群头像 URL 最长100字节
 */
@property(nonatomic,strong) NSString* faceURL;


/// 群创建人/管理员
@property(nonatomic,strong,readonly) NSString *owner;

/// 群创建时间
@property(nonatomic,assign,readonly) uint32_t createTime;

/// 加群是否需要管理员审批
@property(nonatomic,assign) HDIMGroupAddOpt groupAddOpt;

/// 群最近一次群资料修改时间
@property(nonatomic,assign,readonly) uint32_t lastInfoTime;

/// 群最近一次发消息时间
@property(nonatomic,assign,readonly) uint32_t lastMessageTime;

/// 已加入的群成员数量
@property(nonatomic,assign,readonly) uint32_t memberCount;

/// 在线的群成员数量
@property(nonatomic,assign,readonly) uint32_t onlineCount;

/// 最多允许加入的群成员数量
@property(nonatomic,assign,readonly) uint32_t memberMaxCount;

/// 当前用户在此群组中的角色（V2TIMGroupMemberRole），切换角色请调用 setGroupMemberRole 接口
@property(nonatomic,assign,readonly) uint32_t role;

/// 当前用户在此群组中的消息接收选项,修改群消息接收选项请调用 setGroupReceiveMessageOpt 接口
@property(nonatomic,assign,readonly) HDIMReceiveMessageOpt recvOpt;

/// 当前用户在此群中的加入时间，不支持设置，系统自动生成
@property(nonatomic,assign,readonly) uint32_t joinTime;
@end

/////////////////////////////////////////////////////////////////////////////////
//
//                        创建群时指定群成员
//
/////////////////////////////////////////////////////////////////////////////////
/// 创建群时指定群成员
@interface HDIMCreateGroupMemberInfo : NSObject

/// 被操作成员
@property(nonatomic,strong) NSString* userID;

/** 群成员类型，需要注意一下事项：
 * 1. role 不设置或则设置为 V2TIM_GROUP_MEMBER_UNDEFINED，进群后默认为群成员。
 * 2. 工作群（Work）不支持设置 role 为管理员。
 * 3. 所有的群都不支持设置 role 为群主。
 */
@property(nonatomic,assign) uint32_t role;

@end
/// 获取群组资料结果
@interface HDIMGroupInfoResult : NSObject

/// 结果 0：成功；非0：失败
@property(nonatomic,assign) int resultCode;

/// 如果获取失败，会返回错误信息
@property(nonatomic,strong) NSString *resultMsg;

/// 如果获取成功，会返回对应的 info
@property(nonatomic,strong) HDIMGroupInfo *info;

@end
/////////////////////////////////////////////////////////////////////////////////
//
//                        邀请其他人入群的操作结果
//
/////////////////////////////////////////////////////////////////////////////////
/// 邀请其他人入群的操作结果
@interface HDIMGroupMemberOperationResult : NSObject

/// 被操作成员
@property(nonatomic,strong) NSString* userID;

/// 返回状态
@property(nonatomic,assign) HDIMGroupMemberResult result;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//       IMSDK 群组事件回调
//
/////////////////////////////////////////////////////////////////////////////////
/// IMSDK 群组事件回调
@protocol HDIMGroupListener <NSObject>
@optional

/////////////////////////////////////////////////////////////////////////////////
//        群成员相关通知
/////////////////////////////////////////////////////////////////////////////////

/// 有新成员加入群
- (void)onMemberEnter:(NSString *)groupID memberList:(NSArray<HDIMGroupMemberInfo *>*)memberList;

/// 有成员离开群
- (void)onMemberLeave:(NSString *)groupID member:(HDIMGroupMemberInfo *)member;

/// 某成员被拉入某群（该群所有的成员都能收到）
- (void)onMemberInvited:(NSString *)groupID opUser:(HDIMGroupMemberInfo *)opUser memberList:(NSArray<HDIMGroupMemberInfo *>*)memberList;

/// 有成员被踢出某群（该群所有的成员都能收到）
- (void)onMemberKicked:(NSString *)groupID opUser:(HDIMGroupMemberInfo *)opUser memberList:(NSArray<HDIMGroupMemberInfo *>*)memberList;

/// 某成员信息发生变更（该群所有的成员都能收到）。
- (void)onMemberInfoChanged:(NSString *)groupID changeInfoList:(NSArray<HDIMSDKGroupMemberChangeInfo *> *)changeInfoList;

/////////////////////////////////////////////////////////////////////////////////
//        群生命周期相关通知
/////////////////////////////////////////////////////////////////////////////////

/// 有新的群创建（创建者能收到，应用于多端消息同步的场景）
- (void)onGroupCreated:(NSString *)groupID;

/// 某个已加入的群被解散了（该群所有的成员都能收到）
- (void)onGroupDismissed:(NSString *)groupID opUser:(HDIMGroupMemberInfo *)opUser;


/// 某个已加入的群的信息被修改了（该群所有的成员都能收到）
- (void)onGroupInfoChanged:(NSString *)groupID changeInfoList:(NSArray<HDIMSDKGroupChangeInfo *> *)changeInfoList;

/// 某个已加入的群的属性被修改了，会返回所在群组的所有属性（该群所有的成员都能收到）
- (void)onGroupAttributeChanged:(NSString *)groupID attributes:(NSMutableDictionary<NSString *,NSString *> *)attributes;


/////////////////////////////////////////////////////////////////////////////////
//        其他相关通知
/////////////////////////////////////////////////////////////////////////////////


/// 自己主动退出群组 主要用于多端同步
- (void)onQuitFromGroup:(NSString *)groupID;

/// 收到 RESTAPI 下发的自定义系统消息
- (void)onReceiveRESTCustomData:(NSString *)groupID data:(NSData *)data;

@end
