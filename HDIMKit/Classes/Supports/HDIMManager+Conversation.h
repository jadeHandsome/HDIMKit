//
//  HDIMManager+Conversation.h
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager.h"
#import "HDIMManager+Message.h"
@protocol HDIMConversationListener;
@class HDIMConversation;

@interface HDIMManager (Conversation)
/// 获取会话列表成功的回调，nextSeq：下一次分页拉取的游标 isFinished：会话列表是否已经拉取完毕
typedef void(^HDIMConversationResultSucc)(NSArray<HDIMConversation *>*list, uint64_t nextSeq, BOOL isFinished);
/// 获取单个会话成功回调
typedef void(^HDIMConversationSucc)(HDIMConversation *conv);
/// 搜索会话列表成功回调
typedef void(^HDIMConversationListSucc)(NSArray<HDIMConversation *>*list);
/// 获取会话总未读数回调
typedef void(^HDIMTotalUnreadMessageCountSucc)(UInt64 totalCount);

/// 会话类型
typedef NS_ENUM(NSInteger, HDIMConversationType) {
    HDIM_C2C                             = 1,  ///< 单聊
    HDIM_GROUP                           = 2,  ///< 群聊
};
/**
 * 添加会话监听器
 */
- (void)addConversationListener:(id<HDIMConversationListener>)listener;

/**
 * 移除会话监听器
 */
- (void)removeConversationListener:(id<HDIMConversationListener>)listener;

/**
 * 1.3 获取会话列表
 *
 * - 一个会话对应一个聊天窗口，比如跟一个好友的 1v1 聊天，或者一个聊天群，都是一个会话。
 * - 由于历史的会话数量可能很多，所以该接口希望您采用分页查询的方式进行调用，每次分页拉取的个数建议为 100 个。
 * - 该接口拉取的是本地缓存的会话，如果服务器会话有更新，SDK 内部会自动同步，然后在 @ref V2TIMConversationListener 回调告知客户。
 * - 如果会话全部拉取完毕，成功回调里面 V2TIMConversationResult 中的 isFinished 获取字段值为 YES。
 *
 *
 * @param nextSeq   分页拉取的游标，第一次默认取传 0，后续分页拉传上一次分页拉取成功回调里的 nextSeq
 * @param count    分页拉取的个数，一次分页拉取不宜太多，会影响拉取的速度，建议每次拉取 100 个会话
 */
- (void)getConversationList:(uint64_t)nextSeq count:(int)count succ:(HDIMConversationResultSucc)succ fail:(IMSDKFail)fail;


/**
 * 获取单个会话
 *
 * @param conversationID  会话唯一 ID, C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 */
- (void)getConversation:(NSString *)conversationID succ:(HDIMConversationSucc)succ fail:(IMSDKFail)fail;

/**
 * 获取指定会话列表
 *
 * @param conversationIDList 会话唯一 ID 列表，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 */
- (void)getConversationList:(NSArray<NSString *> *)conversationIDList succ:(HDIMConversationResultSucc)succ fail:(IMSDKFail)fail;

/**
 *  删除会话以及该会话中的历史消息
 *
 * @param conversationID 会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 *
 * @note 请注意:
 * - 该会话以及会话中的历史消息，会被 SDK 从本地和服务端一同删除掉，并且不可恢复。
 */
- (void)deleteConversation:(NSString *)conversationID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  设置会话草稿
 *
 *  @param conversationID 会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 *
 *  只在本地保存，不会存储 Server，不能多端同步，程序卸载重装会失效。
 */
- (void)setConversationDraft:(NSString *)conversationID draftText:(NSString *)draftText succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  设置会话置顶
 *
 * @param conversationID  会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 * @param isPinned 是否置顶
 */
- (void)pinConversation:(NSString *)conversationID isPinned:(BOOL)isPinned succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  获取所有会话的未读消息总数（
 * @note
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 V2TIMMessage.V2TIM_NOT_RECEIVE_MESSAGE 或 V2TIMMessage.V2TIM_RECEIVE_NOT_NOTIFY_MESSAGE 的会话。
 */
- (void)getTotalUnreadMessageCount:(HDIMTotalUnreadMessageCountSucc)succ fail:(IMSDKFail)fail;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                         会话变更监听器
//
/////////////////////////////////////////////////////////////////////////////////

@protocol HDIMConversationListener <NSObject>
@optional
/**
 * 同步服务器会话开始，SDK 会在登录成功或者断网重连后自动同步服务器会话，您可以监听这个事件做一些 UI 进度展示操作。
 */
- (void)onSyncServerStart;

/**
 * 同步服务器会话完成，如果会话有变更，会通过 onNewConversation | onConversationChanged 回调告知客户
 */
- (void)onSyncServerFinish;

/**
 * 同步服务器会话失败
 */
- (void)onSyncServerFailed;

/**
 * 有新的会话（比如收到一个新同事发来的单聊消息、或者被拉入了一个新的群组中），可以根据会话的 lastMessage -> timestamp 重新对会话列表做排序。
 */
- (void)onNewConversation:(NSArray<HDIMConversation*> *) conversationList;

/**
 * 某些会话的关键信息发生变化（未读计数发生变化、最后一条消息被更新等等），可以根据会话的 lastMessage -> timestamp 重新对会话列表做排序。
 */
- (void)onConversationChanged:(NSArray<HDIMConversation*> *) conversationList;

/**
 * 会话未读总数变更通知（5.3.425 及以上版本支持）
 * @note
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 V2TIMMessage.V2TIM_NOT_RECEIVE_MESSAGE 或 V2TIMMessage.V2TIM_RECEIVE_NOT_NOTIFY_MESSAGE 的会话。
 */
- (void)onTotalUnreadMessageCountChanged:(UInt64) totalUnreadCount;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                         会话对象 V2TIMConversation
//
/////////////////////////////////////////////////////////////////////////////////
/// 会话对象
@interface HDIMConversation : NSObject

/// 会话类型
@property(nonatomic,assign,readonly) HDIMConversationType type;

/// 会话唯一 ID，如果是 C2C 单聊，组成方式为 c2c_userID，如果是群聊，组成方式为 group_groupID
@property(nonatomic,strong,readonly) NSString *conversationID;

/// 如果会话类型为 C2C 单聊，userID 会存储对方的用户ID，否则为 nil
@property(nonatomic,strong,readonly) NSString *userID;

/// 如果会话类型为群聊，groupID 会存储当前群的群 ID，否则为 nil
@property(nonatomic,strong,readonly) NSString *groupID;

/// 如果会话类型为群聊，groupType 为当前群类型，否则为 nil
@property(nonatomic,strong,readonly) NSString *groupType;

/// 会话展示名称（群组：群名称 >> 群 ID；C2C：对方好友备注 >> 对方昵称 >> 对方的 userID）
@property(nonatomic,strong,readonly) NSString *showName;

/// 会话展示头像（群组：群头像；C2C：对方头像）
@property(nonatomic,strong,readonly) NSString *faceUrl;

/// 会话未读消息数量,直播群（AVChatRoom）不支持未读计数，默认为 0
@property(nonatomic,assign,readonly) int unreadCount;

/// 消息接收选项（接收 | 接收但不提醒 | 不接收）
@property(nonatomic,assign,readonly) HDIMReceiveMessageOpt recvOpt;

/**
 * 会话最后一条消息
 * @note 5.5.892 以前版本，请您使用 lastMessage -> timestamp 对会话做排序，timestamp 越大，会话越靠前
 */
@property(nonatomic,strong,readonly) HDIMMessage *lastMessage;


/// 草稿信息，设置草稿信息请调用 setConversationDraft() 接口
@property(nonatomic,strong,readonly) NSString *draftText;

/// 草稿编辑时间，草稿设置的时候自动生成
@property(nonatomic,strong,readonly) NSDate *draftTimestamp;

/// 是否置顶
@property(nonatomic,assign,readonly) BOOL isPinned;

/**
 * 排序字段（5.5.892 及以后版本支持）
 * @note
 * - 排序字段 orderKey 是按照会话的激活时间线性递增的一个数字（注意：不是时间戳，因为同一时刻可能会有多个会话被同时激活）
 * - 5.5.892 及其以后版本，推荐您使用该字段对所有会话进行排序，orderKey 值越大，代表该会话排序越靠前
 * - 当您 “清空会话所有消息” 或者 “逐个删除会话的所有消息” 之后，会话的 lastMessage 变为空，但会话的 orderKey 不会改变；如果想保持会话的排序位置不变，可以使用该字段对所有会话进行排序
 */
@property(nonatomic,assign,readonly) NSUInteger orderKey;

@end
