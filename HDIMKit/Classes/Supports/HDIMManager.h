//
//  HDMessageManager.h
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import <Foundation/Foundation.h>
@protocol HDIMSDKListener;
@protocol HDIMSimpleMsgListener;


@class HDIMSDKUserFullInfo;
@class HDIMGroupMemberInfo;
@class HDIMSDKUserFullInfo;
@class HDIMSDKUserInfo;
@class HDIMSDKGroupMemberChangeInfo;
@class HDIMSDKGroupChangeInfo;
@class HDIMSDKConfig;

@interface HDIMManager : NSObject
/// 成功通用回调
typedef void (^IMSDKSucc)(void);
/// 失败通用回调
typedef void (^IMSDKFail)(int code, NSString * desc);
/// 获取用户资料成功回调
typedef void (^IMSDKUserFullInfoListSucc)(NSArray<HDIMSDKUserFullInfo *> * infoList);


/// 登录状态
typedef NS_ENUM(NSInteger, IMSDKLoginStatus) {
    IMSDK_STATUS_LOGINED                   = 1,  ///< 已登录
    IMSDK_STATUS_LOGINING                  = 2,  ///< 登录中
    IMSDK_STATUS_LOGOUT                    = 3,  ///< 无登录
};

/// 消息接收选项
typedef NS_ENUM(NSInteger, HDIMReceiveMessageOpt) {
    HDIM_RECEIVE_MESSAGE                     = 0,  ///< 在线正常接收消息，离线时会进行 APNs 推送
    HDIM_NOT_RECEIVE_MESSAGE                 = 1,  ///< 不会接收到消息，离线不会有推送通知
    HDIM_RECEIVE_NOT_NOTIFY_MESSAGE          = 2,  ///< 在线正常接收消息，离线不会有推送通知
};

/////////////////////////////////////////////////////////////////////////////////
//                               初始化
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取 HDIMManager 管理器实例
 */
+ (HDIMManager *)sharedManager;

/**
 *  初始化 SDK
 *
 *  @param config 配置信息实体类
 *  @return YES：成功；NO：失败
 */
- (BOOL)initMessageSDKWithConfig:(HDIMSDKConfig *)config;

/**
 *  添加 IMSDK 监听
 */
- (void)addMessageSDKListener:(id<HDIMSDKListener>)listener;

/**
 *  移除 IMSDK 监听
 */
- (void)removeMesssageSDKListener:(id<HDIMSDKListener>)listener;

/**
 *  反初始化 IMSDK
 */
- (void)unInitSDK;

/**
 *  获取版本号
 *
 *  @return 返回版本号，字符串表示，例如 5.0.10
 */
- (NSString*)getVersion;

/**
 *  获取服务器时间戳
 *
 *  @return 服务器时间时间戳，单位 s
 */
- (uint64_t)getServerTime;

/////////////////////////////////////////////////////////////////////////////////
//                               登录登出
/////////////////////////////////////////////////////////////////////////////////

/**
 *  登录
 *
 *  登录需要设置用户名 userID 和 password
 *
 */
- (void)login:(NSString *)userID pwd:(NSString *)password succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  登出
 *
 *  退出登录，如果切换账号，需要 logout 回调成功或者失败后才能再次 login，否则 login 可能会失败。
 */
- (void)logout:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  获取登录用户
 */
- (NSString *)getLoginUser;

/**
 *  获取登录状态
 *
 *  如果用户已经处于已登录和登录中状态，请勿再频繁调用登录接口登录。
 */
- (IMSDKLoginStatus)getLoginStatus;

/////////////////////////////////////////////////////////////////////////////////
//                         消息收发
/////////////////////////////////////////////////////////////////////////////////

/**
 *  设置基本消息（文本消息和自定义消息）的事件监听器
 */
- (void)addSimpleMsgListener:(id<HDIMSimpleMsgListener>)listener;

/**
 *  移除基本消息（文本消息和自定义消息）的事件监听器
 */
- (void)removeSimpleMsgListener:(id<HDIMSimpleMsgListener>)listener;

/**
 *  发送单聊普通文本消息（最大支持 8KB）
 *
 *  文本消息支持云端的脏词过滤，如果用户发送的消息中有敏感词，V2TIMFail 回调将会返回 80001 错误码。
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendC2CTextMessage:(NSString *)text to:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  发送单聊自定义消息
 *
 *  自定义消息本质就是一端二进制 buffer，您可以在其上自由组织自己的消息格式（常用于发送信令），但是自定义消息不支持云端敏感词过滤。
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendC2CCustomMessage:(NSData *)customData to:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  发送群聊普通文本消息
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendGroupTextMessage:(NSString *)text to:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

/**
 *  发送群聊自定义消息
 *
 *  @return 返回消息的唯一标识 ID
 *
 */
- (NSString*)sendGroupCustomMessage:(NSData *)customData to:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;





/////////////////////////////////////////////////////////////////////////////////
//                        资料相关操作
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取用户资料
 *  @note 请注意:
 *  - 获取自己的资料，传入自己的 ID 即可。
 */
- (void)getUsersInfo:(NSArray<NSString *> *)userIDList succ:(IMSDKUserFullInfoListSucc)succ fail:(IMSDKFail)fail;

/**
 *  修改个人资料
 */
- (void)setSelfInfo:(HDIMSDKUserFullInfo *)Info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail;

@end


//
//       IMSDK 主核心回调，帮助您时刻关注 IMSDK 的在线状态
//
/////////////////////////////////////////////////////////////////////////////////
/// IMSDK 主核心回调
@protocol HDIMSDKListener <NSObject>

@optional
/// SDK 正在连接到服务器
- (void)onConnecting;

/// SDK 已经成功连接到服务器
- (void)onConnectSuccess;

/// SDK 连接服务器失败
- (void)onConnectFailed:(int)code err:(NSString*)err;

/// 当前用户被踢下线，此时可以 UI 提示用户，并再次调用 SDKIMManager 的 login() 函数重新登录。
- (void)onKickedOffline;

/// 在线时票据过期
- (void)onUserSigExpired;

/// 当前用户的资料发生了更新
- (void)onSelfInfoUpdated:(HDIMSDKUserFullInfo *)Info;

@end

/////////////////////////////////////////////////////////////////////////////////
/// IMSDK 基本消息回调
@protocol HDIMSimpleMsgListener <NSObject>
@optional

/// 收到 C2C 文本消息
- (void)onRecvC2CTextMessage:(NSString *)msgID  sender:(HDIMSDKUserInfo *)info text:(NSString *)text;

/// 收到 C2C 自定义（信令）消息
- (void)onRecvC2CCustomMessage:(NSString *)msgID  sender:(HDIMSDKUserInfo *)info customData:(NSData *)data;

/// 收到群文本消息
- (void)onRecvGroupTextMessage:(NSString *)msgID groupID:(NSString *)groupID sender:(HDIMGroupMemberInfo *)info text:(NSString *)text;

/// 收到群自定义（信令）消息
- (void)onRecvGroupCustomMessage:(NSString *)msgID groupID:(NSString *)groupID sender:(HDIMGroupMemberInfo *)info customData:(NSData *)data;
@end



//初始化sdk配置类
@interface HDIMSDKConfig : NSObject

/**
 * appid 固定值 如果不传则使用sdk 默认值
 */
@property (nonatomic, strong) NSString *appId;
/**
 * Grpc:连接的服务端的地址
 */
@property (nonatomic, strong) NSString *serverAddr;
/**
 * 平台id: ios=1,android=2
 */
@property (nonatomic, assign) NSInteger platform;
/**
 * 日志缓存的路径
 */
@property (nonatomic, strong) NSString *dataDir;
/**
 * 控制日志输出的方式: 控制台+文件=6，控制=4,文件=2,关闭=1，其他值仅控制台输出
 */
@property (nonatomic, strong) NSString *logSwitch;
/**
 * 相对于本初子午线偏移的秒:8*3600
 */
@property (nonatomic, assign) NSInteger timeZoneOffset;
/**
 * 时区代表地区: Asia/Shanghai
 */
@property (nonatomic, assign) NSInteger timeZoneStr;
@end
/////////////////////////////////////////////////////////////////////////////////
//
//                         用户资料
//
/////////////////////////////////////////////////////////////////////////////////
/// 用户基本资料基类
@interface HDIMSDKUserInfo : NSObject

@end

/// 用户详细资料
@interface HDIMSDKUserFullInfo : HDIMSDKUserInfo


@end

/////////////////////////////////////////////////////////////////////////////////
//
//                        群成员资料
//
/////////////////////////////////////////////////////////////////////////////////
/// 群成员基本资料
@interface HDIMGroupMemberInfo : NSObject



@end

/// 群成员详细资料
@interface HDIMGroupMemberFullInfo : HDIMGroupMemberInfo


@end

