//
//  HDIMManager+Conversation.m
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager+Conversation.h"

@implementation HDIMManager (Conversation)
/**
 * 添加会话监听器
 */
- (void)addConversationListener:(id<HDIMConversationListener>)listener {
#pragma -- 需要实现
}

/**
 * 移除会话监听器
 */
- (void)removeConversationListener:(id<HDIMConversationListener>)listener {
#pragma -- 需要实现
}

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
- (void)getConversationList:(uint64_t)nextSeq count:(int)count succ:(HDIMConversationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}


/**
 * 获取单个会话
 *
 * @param conversationID  会话唯一 ID, C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 */
- (void)getConversation:(NSString *)conversationID succ:(HDIMConversationSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 * 获取指定会话列表
 *
 * @param conversationIDList 会话唯一 ID 列表，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 */
- (void)getConversationList:(NSArray<NSString *> *)conversationIDList succ:(HDIMConversationResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  删除会话以及该会话中的历史消息
 *
 * @param conversationID 会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 *
 * @note 请注意:
 * - 该会话以及会话中的历史消息，会被 SDK 从本地和服务端一同删除掉，并且不可恢复。
 */
- (void)deleteConversation:(NSString *)conversationID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  设置会话草稿
 *
 *  @param conversationID 会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 *
 *  只在本地保存，不会存储 Server，不能多端同步，程序卸载重装会失效。
 */
- (void)setConversationDraft:(NSString *)conversationID draftText:(NSString *)draftText succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  设置会话置顶
 *
 * @param conversationID  会话唯一 ID，C2C 单聊组成方式：[NSString stringWithFormat:@"c2c_%@",userID]；群聊组成方式为 [NSString stringWithFormat:@"group_%@",groupID]
 * @param isPinned 是否置顶
 */
- (void)pinConversation:(NSString *)conversationID isPinned:(BOOL)isPinned succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  获取所有会话的未读消息总数（
 * @note
 *  - 未读总数会减去设置为免打扰的会话的未读数，即消息接收选项设置为 V2TIMMessage.V2TIM_NOT_RECEIVE_MESSAGE 或 V2TIMMessage.V2TIM_RECEIVE_NOT_NOTIFY_MESSAGE 的会话。
 */
- (void)getTotalUnreadMessageCount:(HDIMTotalUnreadMessageCountSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
@end
