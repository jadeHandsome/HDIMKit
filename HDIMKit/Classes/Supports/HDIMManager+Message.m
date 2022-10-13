//
//  HDIMManager+Message.m
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager+Message.h"
NSString * const hdImSDK_MesssageAtALL = @"";
@implementation HDIMManager (Message)
/////////////////////////////////////////////////////////////////////////////////
//
//                         监听 - 高级（图片、语音、视频等）消息
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加高级消息的事件监听器
 */
- (void)addAdvancedMsgListener:(id<HDIMMessageMsgListener>)listener {
#pragma -- 需要实现
}
/**
 *  移除高级消息的事件监听器
 */
- (void)removeAdvancedMsgListener:(id<HDIMMessageMsgListener>)listener {
#pragma -- 需要实现
}


/////////////////////////////////////////////////////////////////////////////////
//
//                         创建 - 高级（图片、语音、视频等）消息
//
/////////////////////////////////////////////////////////////////////////////////
/**
 *  创建文本消息
 */
- (HDIMMessage *)createTextMessage:(NSString *)text {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建文本消息，并且可以附带 @ 提醒功能（最大支持 8KB）
 *
 *  提醒消息仅适用于在群组中发送的消息
 *
 *  @param atUserList 需要 @ 的用户列表，如果需要 @ALL，请传入 hdImSDK_MesssageAtALL 常量字符串。
 *
 */
- (HDIMMessage *)createTextAtMessage:(NSString *)text atUserList:(NSMutableArray<NSString *> *)atUserList {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建自定义消息 预留
 */
- (HDIMMessage *)createCustomMessage:(NSData *)data {
    return nil;
}

/**
 *  创建自定义消息 预留
 *
 */
- (HDIMMessage *)createCustomMessage:(NSData *)data desc:(NSString *)desc extension:(NSString *)extension {
    return nil;
}

/**
 *  创建图片消息（图片文件最大支持 28 MB）
 *
 *  @note 如果是系统相册拿的图片，需要先把图片导入 APP 的目录下
 */
- (HDIMMessage *)createImageMessage:(NSString *)imagePath {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建图片消息（图片文件最大支持 28 MB）
 *
 *  @note 如果是系统相册拿的图片，需要先把图片导入 APP 的目录下
 */
- (HDIMMessage *)createImageMessageWithUIImage:(UIImage *)image {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建语音消息（语音文件最大支持 28 MB）
 *
 *  @param duration 音频时长，单位 s
 */
- (HDIMMessage *)createSoundMessage:(NSString *)audioFilePath duration:(int)duration {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建视频消息（视频文件最大支持 100 MB）
 *
 *  @param type 视频类型，如 mp4 mov 等
 *  @param duration 视频时长，单位 s
 *  @param snapshotPath 视频封面文件路径
 *
 *  @note 如果是系统相册拿的视频，需要先把视频导入 APP 的目录下
 */
- (HDIMMessage *)createVideoMessage:(NSString *)videoFilePath
                                type:(NSString *)type
                            duration:(int)duration
                       snapshotPath:(NSString *)snapshotPath {
#pragma -- 需要实现
    return nil;
}

/**
 *  创建表情消息
 *
 *  SDK 并不提供表情包，如果开发者有表情包，可使用 index 存储表情在表情包中的索引，或者使用 data 存储表情映射的字符串 key，这些都由用户自定义，SDK 内部只做透传。
 *
 *  @param index 表情索引
 *  @param data 自定义数据
 */
- (HDIMMessage *)createFaceMessage:(int)index data:(NSData *)data {
#pragma -- 需要实现
    return nil;
}


/**
 *  创建转发消息
 *
 *  如果需要转发一条消息，不能直接调用 sendMessage 接口发送原消息，需要先 createForwardMessage 创建一条转发消息再发送。
 *
 *  @return 转发消息对象，elem 内容和原消息完全一致。
 */
- (HDIMMessage *)createForwardMessage:(HDIMMessage *)message {
#pragma -- 需要实现
    return nil;
}

/////////////////////////////////////////////////////////////////////////////////
//
//                         发送 - 高级（图片、语音、视频等）消息
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  发送消息
 *
 *  @param message 待发送的消息对象，需要通过对应的 createXXXMessage 接口进行创建。
 *  @param receiver 消息接收者的 userID, 如果是发送 C2C 单聊消息，只需要指定 receiver 即可。
 *  @param groupID 目标群组 ID，如果是发送群聊消息，只需要指定 groupID 即可。
 *  @param onlineUserOnly 是否只有在线用户才能收到，如果设置为 YES ，接收方历史消息拉取不到，常被用于实现”对方正在输入”或群组里的非重要提示等弱提示功能，该字段不支持 AVChatRoom。
 *  @param progress 文件上传进度（当发送消息中包含图片、语音、视频、文件等富媒体消息时才有效）。
 *  @return msgID 消息唯一标识
 *
 */
- (NSString *)sendMessage:(HDIMMessage *)message
                 receiver:(NSString *)receiver
                  groupID:(NSString *)groupID
           onlineUserOnly:(BOOL)onlineUserOnly
                 progress:(HDIMProgress)progress
                     succ:(IMSDKSucc)succ
                     fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}

/////////////////////////////////////////////////////////////////////////////////
//
//                         接收 - 设置消息的接口选项（接收|接收但不提醒|不接收）
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  设置针对某个用户的 C2C 消息接收选项（支持批量设置）
 *
 *  @note
 *  - 该接口支持批量设置，您可以通过参数 userIDList 设置一批用户，但一次最大允许设置 30 个用户。
 *  - 该接口调用频率被限制为1秒内最多调用5次。
 */
- (void)setC2CReceiveMessageOpt:(NSArray<NSString *> *)userIDList
                            opt:(HDIMReceiveMessageOpt)opt
                           succ:(IMSDKSucc)succ
                           fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
/**
 *  查询针对某个用户的 C2C 消息接收选项
 */
- (void)getC2CReceiveMessageOpt:(NSArray<NSString *> *)userIDList
                           succ:(HDIMReceiveMessageOptListSucc)succ
                           fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  设置群消息的接收选项
 */
- (void)setGroupReceiveMessageOpt:(NSString*)groupID
                              opt:(HDIMReceiveMessageOpt)opt
                             succ:(IMSDKSucc)succ
                             fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/////////////////////////////////////////////////////////////////////////////////
//
//                         获取历史消息、撤回、删除、标记已读等高级接口
//
/////////////////////////////////////////////////////////////////////////////////


/**
 *  获取历史消息
 *  @param option 拉取消息选项设置，可以设置从云端、本地拉取更老或更新的消息
 *
 *  @note 请注意：
 *  - 如果设置为拉取云端消息，当 SDK 检测到没有网络，默认会直接返回本地数据
 *
 */
- (void)getHistoryMessageList:(HDIMMessageListGetOption *)option succ:(HDIMMessageListSucc)succ
                         fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  删除本地消息
 *  @note 该接口只能删除本地历史，消息删除后，SDK 会在本地把这条消息标记为已删除状态，getHistoryMessage 不能再拉取到，如果程序卸载重装，本地会失去对这条消息的删除标记，getHistoryMessage 还能再拉取到该条消息。
 */
- (void)deleteMessageFromLocalStorage:(HDIMMessage *)msg succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 * 删除本地以及云端消息
 *  @note 该接口会在 deleteMessageFromLocalStorage 的基础上，同步删除云端存储的消息，且无法恢复。需要注意的是：
 *  - 一次最多只能删除 30 条消息
 *  - 要删除的消息必须属于同一会话
 *  - 一秒钟最多只能调用一次该接口
 *  - 如果该账号在其他设备上拉取过这些消息，那么调用该接口删除后，这些消息仍然会保存在那些设备上，即删除消息不支持多端同步。
 */
- (void)deleteMessages:(NSArray<HDIMMessage *>*)msgList succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 * 删除跟某个人的所有聊天记录 同步到云端
 * @note 请注意：
 * - 会话内的消息在本地删除的同时，在服务器也会同步删除。
 */
- (void)clearC2CHistoryMessage:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 * 删除某个群的所有聊天记录 同步到云端
 * @note 请注意：
 * 
 * - 会话内的消息在本地删除的同时，在服务器也会同步删除。
 */
- (void)clearGroupHistoryMessage:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  群聊插入消息到本地
 *  该接口主要用于满足向群组聊天会话中插入一些提示性消息的需求，比如“您已经退出该群”，这类消息有展示
 *  在聊天消息区的需求，但并没有发送给其他人的必要。
 *  所以 insertGroupMessageToLocalStorage() 相当于一个被禁用了网络发送能力的 sendMessage() 接口。
 *
 *  @return msgID 消息唯一标识
 *  @note 通过该接口 save 的消息只存本地，程序卸载后会丢失。
 */
- (NSString *)insertGroupMessageToLocalStorage:(HDIMMessage *)msg to:(NSString *)groupID sender:(NSString *)sender succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}

/**
 *  单聊插入消息到本地
 *  该接口主要用于满足向C2C聊天会话中插入一些提示性消息的需求，比如“您已成功发送消息”，这类消息有展示
 *  在聊天消息区的需求，但并没有发送给对方的必要。
 *  所以 insertC2CMessageToLocalStorage()相当于一个被禁用了网络发送能力的 sendMessage() 接口。
 *
 *  @return msgID 消息唯一标识
 *  @note 通过该接口 save 的消息只存本地，程序卸载后会丢失。
 */
- (NSString *)insertC2CMessageToLocalStorage:(HDIMMessage *)msg to:(NSString *)userID sender:(NSString *)sender succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}


/**
 * 搜索聊天记录
 * @param param 消息搜索参数，详见 V2TIMMessageSearchParam 的定义
*/
- (void)searchLocalMessages:(HDIMMessageSearchParam *)param succ:(HDIMSearchMessageListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
@end
