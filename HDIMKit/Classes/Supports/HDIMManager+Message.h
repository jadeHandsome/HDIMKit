//
//  HDIMManager+Message.h
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager.h"

@protocol HDIMMessageMsgListener;
@class HDIMMessage;
@class HDIMMessageSearchResult;
@class HDIMReceiveMessageOptInfo;
@class HDIMMessageListGetOption;
@class HDIMMessageSearchParam;




/// 在接口 createTextAtMessage 中填入 kMesssageAtALL 表示当前消息需要 @ 群里所有人
extern NSString * const hdImSDK_MesssageAtALL;


@interface HDIMManager (Message)
/// 查询历史消息的结果回调（查询接口会批量地返回从某个时间点之前的历史消息）
typedef void (^HDIMMessageListSucc)(NSArray<HDIMMessage *> * msgs);
/// 搜索历史消息的结果回调（查询接口支持模糊匹配）
typedef void (^HDIMSearchMessageListSucc)(HDIMMessageSearchResult *searchResult);
/// 文件上传进度回调，取值 0 -100
typedef void (^HDIMProgress)(uint32_t progress);
/// 文件下载进度回调
typedef void (^HDIMDownLoadProgress)(NSInteger curSize, NSInteger totalSize);
/// 获取消息接收选项的结果回调
typedef void (^HDIMReceiveMessageOptListSucc)(NSArray<HDIMReceiveMessageOptInfo *> *optList);




/////////////////////////////////////////////////////////////////////////////////
//
//                         监听 - 高级（图片、语音、视频等）消息
//
/////////////////////////////////////////////////////////////////////////////////

/**
 *  添加高级消息的事件监听器
 */
- (void)addAdvancedMsgListener:(id<HDIMMessageMsgListener>)listener;
/**
 *  移除高级消息的事件监听器
 */
- (void)removeAdvancedMsgListener:(id<HDIMMessageMsgListener>)listener;


/////////////////////////////////////////////////////////////////////////////////
//
//                         创建 - 高级（图片、语音、视频等）消息
//
/////////////////////////////////////////////////////////////////////////////////
/**
 *  创建文本消息
 */
- (HDIMMessage *)createTextMessage:(NSString *)text;

/**
 *  创建文本消息，并且可以附带 @ 提醒功能（最大支持 8KB）
 *
 *  提醒消息仅适用于在群组中发送的消息
 *
 *  @param atUserList 需要 @ 的用户列表，如果需要 @ALL，请传入 hdImSDK_MesssageAtALL 常量字符串。
 *
 */
- (HDIMMessage *)createTextAtMessage:(NSString *)text atUserList:(NSMutableArray<NSString *> *)atUserList;

/**
 *  创建自定义消息 预留
 */
- (HDIMMessage *)createCustomMessage:(NSData *)data;

/**
 *  创建自定义消息 预留
 *
 */
- (HDIMMessage *)createCustomMessage:(NSData *)data desc:(NSString *)desc extension:(NSString *)extension;

/**
 *  创建图片消息（图片文件最大支持 28 MB）
 *
 *  @note 如果是系统相册拿的图片，需要先把图片导入 APP 的目录下
 */
- (HDIMMessage *)createImageMessage:(NSString *)imagePath;

/**
 *  创建图片消息（图片文件最大支持 28 MB）
 *
 *  @note 如果是系统相册拿的图片，需要先把图片导入 APP 的目录下
 */
- (HDIMMessage *)createImageMessageWithUIImage:(UIImage *)image;

/**
 *  创建语音消息（语音文件最大支持 28 MB）
 *
 *  @param duration 音频时长，单位 s
 */
- (HDIMMessage *)createSoundMessage:(NSString *)audioFilePath duration:(int)duration;

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
                        snapshotPath:(NSString *)snapshotPath;

/**
 *  创建表情消息
 *
 *  SDK 并不提供表情包，如果开发者有表情包，可使用 index 存储表情在表情包中的索引，或者使用 data 存储表情映射的字符串 key，这些都由用户自定义，SDK 内部只做透传。
 *
 *  @param index 表情索引
 *  @param data 自定义数据
 */
- (HDIMMessage *)createFaceMessage:(int)index data:(NSData *)data;


/**
 *  创建转发消息
 *
 *  如果需要转发一条消息，不能直接调用 sendMessage 接口发送原消息，需要先 createForwardMessage 创建一条转发消息再发送。
 *
 *  @return 转发消息对象，elem 内容和原消息完全一致。
 */
- (HDIMMessage *)createForwardMessage:(HDIMMessage *)message;

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
                     fail:(IMSDKFail)fail;

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
                           fail:(IMSDKFail)fail;
/**
 *  查询针对某个用户的 C2C 消息接收选项
 */
- (void)getC2CReceiveMessageOpt:(NSArray<NSString *> *)userIDList
                           succ:(HDIMReceiveMessageOptListSucc)succ
                           fail:(IMSDKFail)fail;

/**
 *  设置群消息的接收选项
 */
- (void)setGroupReceiveMessageOpt:(NSString*)groupID
                              opt:(HDIMReceiveMessageOpt)opt
                             succ:(IMSDKSucc)succ
                             fail:(IMSDKFail)fail;

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
                         fail:(IMSDKFail)fail;

/**
 *  删除本地消息
 *  @note 该接口只能删除本地历史，消息删除后，SDK 会在本地把这条消息标记为已删除状态，getHistoryMessage 不能再拉取到，如果程序卸载重装，本地会失去对这条消息的删除标记，getHistoryMessage 还能再拉取到该条消息。
 */
- (void)deleteMessageFromLocalStorage:(HDIMMessage *)msg succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 * 删除本地以及云端消息
 *  @note 该接口会在 deleteMessageFromLocalStorage 的基础上，同步删除云端存储的消息，且无法恢复。需要注意的是：
 *  - 一次最多只能删除 30 条消息
 *  - 要删除的消息必须属于同一会话
 *  - 一秒钟最多只能调用一次该接口
 *  - 如果该账号在其他设备上拉取过这些消息，那么调用该接口删除后，这些消息仍然会保存在那些设备上，即删除消息不支持多端同步。
 */
- (void)deleteMessages:(NSArray<HDIMMessage *>*)msgList succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 * 删除跟某个人的所有聊天记录 同步到云端
 * @note 请注意：
 * - 会话内的消息在本地删除的同时，在服务器也会同步删除。
 */
- (void)clearC2CHistoryMessage:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 * 删除某个群的所有聊天记录 同步到云端
 * @note 请注意：
 *
 * - 会话内的消息在本地删除的同时，在服务器也会同步删除。
 */
- (void)clearGroupHistoryMessage:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  群聊插入消息到本地
 *  该接口主要用于满足向群组聊天会话中插入一些提示性消息的需求，比如“您已经退出该群”，这类消息有展示
 *  在聊天消息区的需求，但并没有发送给其他人的必要。
 *  所以 insertGroupMessageToLocalStorage() 相当于一个被禁用了网络发送能力的 sendMessage() 接口。
 *
 *  @return msgID 消息唯一标识
 *  @note 通过该接口 save 的消息只存本地，程序卸载后会丢失。
 */
- (NSString *)insertGroupMessageToLocalStorage:(HDIMMessage *)msg to:(NSString *)groupID sender:(NSString *)sender succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  单聊插入消息到本地
 *  该接口主要用于满足向C2C聊天会话中插入一些提示性消息的需求，比如“您已成功发送消息”，这类消息有展示
 *  在聊天消息区的需求，但并没有发送给对方的必要。
 *  所以 insertC2CMessageToLocalStorage()相当于一个被禁用了网络发送能力的 sendMessage() 接口。
 *
 *  @return msgID 消息唯一标识
 *  @note 通过该接口 save 的消息只存本地，程序卸载后会丢失。
 */
- (NSString *)insertC2CMessageToLocalStorage:(HDIMMessage *)msg to:(NSString *)userID sender:(NSString *)sender succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;


/**
 * 搜索聊天记录
 * @param param 消息搜索参数，详见 V2TIMMessageSearchParam 的定义
*/
 - (void)searchLocalMessages:(HDIMMessageSearchParam *)param succ:(HDIMSearchMessageListSucc)succ fail:(IMSDKFail)fail;
@end

/////////////////////////////////////////////////////////////////////////////////
//
//                         高级消息监听器
//
/////////////////////////////////////////////////////////////////////////////////
/// 高级消息监听器
@protocol HDIMMessageMsgListener <NSObject>
@optional
/// 收到新消息
- (void)onRecvNewMessage:(HDIMMessage *)msg;

@end


/////////////////////////////////////////////////////////////////////////////////
//                         消息内容详解
/////////////////////////////////////////////////////////////////////////////////
/// 消息实体
@interface HDIMMessage : NSObject


@end
@interface HDIMMessageSearchResultItem : NSObject
/// 会话ID
@property(nonatomic,copy) NSString *conversationID;

/// 当前会话一共搜索到了多少条符合要求的消息
@property(nonatomic, assign) NSUInteger messageCount;

/**
 * 满足搜索条件的消息列表
 * <p>如果您本次搜索【指定会话】，那么 messageList 中装载的是本会话中所有满足搜索条件的消息列表。
 * <p>如果您本次搜索【全部会话】，那么 messageList 中装载的消息条数会有如下两种可能：
 * - 如果某个会话中匹配到的消息条数 > 1，则 messageList 为空，您可以在 UI 上显示“ messageCount 条相关记录”。
 * - 如果某个会话中匹配到的消息条数 = 1，则 messageList 为匹配到的那条消息，您可以在 UI 上显示之，并高亮匹配关键词。
*/
@property(nonatomic,strong) NSArray<HDIMMessage *> *messageList;
@end

@interface HDIMMessageSearchResult : NSObject

/**
 * 如果您本次搜索【指定会话】，那么返回满足搜索条件的消息总数量；
 * 如果您本次搜索【全部会话】，那么返回满足搜索条件的消息所在的所有会话总数量。
 */
@property(nonatomic, assign) NSUInteger totalCount;

/**
 * 如果您本次搜索【指定会话】，那么返回结果列表只包含该会话结果；
 * 如果您本次搜索【全部会话】，那么对满足搜索条件的消息根据会话 ID 分组，分页返回分组结果；
 */
@property(nonatomic, strong) NSArray<HDIMMessageSearchResultItem *> *messageSearchResultItems;

@end

/////////////////////////////////////////////////////////////////////////////////
//
//                         用户消息接收选项
//
/////////////////////////////////////////////////////////////////////////////////
@interface V2TIMReceiveMessageOptInfo:NSObject
/// 用户 ID
@property(nonatomic, strong) NSString *userID;

/// 消息接收选项
@property(nonatomic, assign) HDIMReceiveMessageOpt receiveOpt;
@end
/////////////////////////////////////////////////////////////////////////////////
//                         消息拉取
/////////////////////////////////////////////////////////////////////////////////

@interface HDIMMessageListGetOption : NSObject


/// 拉取单聊历史消息
@property(nonatomic,strong) NSString *userID;

/// 拉取群组历史消息
@property(nonatomic,strong) NSString *groupID;

/// 拉取消息数量
@property(nonatomic,assign) NSUInteger count;

/// 拉取的消息类型集合，getType 为 V2TIM_GET_LOCAL_OLDER_MSG 和 V2TIM_GET_LOCAL_NEWER_MSG 有效，传 nil 表示拉取全部类型消息，取值详见 @V2TIMElemType。
@property(nonatomic,strong) NSArray<NSNumber *> * messageTypeList;

/**
 * 拉取消息的起始消息
 *
 * @note 请注意，
 * <p>拉取 C2C 消息，只能使用 lastMsg 作为消息的拉取起点；如果没有指定 lastMsg，默认使用会话的最新消息作为拉取起点。
 * <p>拉取 Group 消息时，除了可以使用 lastMsg 作为消息的拉取起点外，也可以使用 lastMsgSeq 来指定消息的拉取起点，二者的区别在于：
 * - 使用 lastMsg 作为消息的拉取起点时，返回的消息列表里不包含当前设置的 lastMsg；
 * - 使用 lastMsgSeq 作为消息拉取起点时，返回的消息列表里包含当前设置的 lastMsgSeq 所表示的消息。
 *
 * @note 在拉取 Group 消息时，
 * <p>如果同时指定了 lastMsg 和 lastMsgSeq，SDK 优先使用 lastMsg 作为消息的拉取起点。
 * <p>如果 lastMsg 和 lastMsgSeq 都未指定，消息的拉取起点分为如下两种情况：
 * -  如果设置了拉取的时间范围，SDK 会根据 @getTimeBegin 所描述的时间点作为拉取起点；
 * -  如果未设置拉取的时间范围，SDK 默认使用会话的最新消息作为拉取起点。
 */
@property(nonatomic,strong) HDIMMessage *lastMsg;
@property (nonatomic, assign) NSUInteger lastMsgSeq;

/**
 * 拉取消息的时间范围
 * @getTimeBegin  表示时间范围的起点；默认为 0，表示从现在开始拉取；UTC 时间戳，单位：秒
 * @getTimePeriod 表示时间范围的长度；默认为 0，表示不限制时间范围；单位：秒
 *
 * @note
 * <p> 时间范围的方向由参数 getType 决定
 * <p> 如果 getType 取 V2TIM_GET_CLOUD_OLDER_MSG/V2TIM_GET_LOCAL_OLDER_MSG，表示从 getTimeBegin 开始，过去的一段时间，时间长度由 getTimePeriod 决定
 * <p> 如果 getType 取 V2TIM_GET_CLOUD_NEWER_MSG/V2TIM_GET_LOCAL_NEWER_MSG，表示从 getTimeBegin 开始，未来的一段时间，时间长度由 getTimePeriod 决定
 * <p> 取值范围区间为闭区间，包含起止时间，二者关系如下：
 * - 如果 getType 指定了朝消息时间更老的方向拉取，则时间范围表示为 [getTimeBegin-getTimePeriod, getTimeBegin]
 * - 如果 getType 指定了朝消息时间更新的方向拉取，则时间范围表示为 [getTimeBegin, getTimeBegin+getTimePeriod]
 */
@property (nonatomic, assign) NSUInteger getTimeBegin;
@property (nonatomic, assign) NSUInteger getTimePeriod;

@end

/// 消息搜索参数
@interface HDIMMessageSearchParam : NSObject
/**
 * 关键字列表，最多支持5个。当消息发送者以及消息类型均未指定时，关键字列表必须非空；否则，关键字列表可以为空。
 */
@property(nonatomic,strong) NSArray<NSString *> * keywordList;


/**
 * 指定 userID 发送的消息，最多支持5个。
 */
@property(nonatomic,strong) NSArray<NSString *> *senderUserIDList;

/// 指定搜索的消息类型集合，传 nil 表示搜索支持的全部类型消息（V2TIMFaceElem 和 V2TIMGroupTipsElem 不支持）取值详见 @V2TIMElemType。
@property(nonatomic,strong) NSArray<NSNumber *> * messageTypeList;

/**
 * 搜索“全部会话”还是搜索“指定的会话”：
 * <p> 如果设置 conversationID == nil，代表搜索全部会话。
 * <p> 如果设置 conversationID != nil，代表搜索指定会话。
 */
@property(nonatomic,strong) NSString *conversationID;

/// 搜索的起始时间点。默认为0即代表从现在开始搜索。UTC 时间戳，单位：秒
@property(nonatomic,assign) NSUInteger searchTimePosition;

/// 从起始时间点开始的过去时间范围，单位秒。默认为0即代表不限制时间范围，传24x60x60代表过去一天。
@property(nonatomic,assign) NSUInteger searchTimePeriod;

/**
 * 分页的页号：用于分页展示查找结果，从零开始起步。
 * 比如：您希望每页展示 10 条结果，请按照如下规则调用：
 * - 首次调用：通过参数 pageSize = 10, pageIndex = 0 调用 searchLocalMessage，从结果回调中的 totalCount 可以获知总共有多少条结果。
 * - 计算页数：可以获知总页数：totalPage = (totalCount % pageSize == 0) ? (totalCount / pageSize) : (totalCount / pageSize + 1) 。
 * - 再次调用：可以通过指定参数 pageIndex （pageIndex < totalPage）返回后续页号的结果。
*/
@property(nonatomic, assign) NSUInteger pageIndex;

/// 每页结果数量：用于分页展示查找结果，如不希望分页可将其设置成 0，但如果结果太多，可能会带来性能问题。
@property(nonatomic, assign) NSUInteger pageSize;

@end
