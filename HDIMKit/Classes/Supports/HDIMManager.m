//
//  HDMessageManager.m
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager.h"


@implementation HDIMManager
/////////////////////////////////////////////////////////////////////////////////
//                               初始化
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取 HDIMManager 管理器实例
 */
+ (HDIMManager *)sharedManager {
#pragma -- 需要实现
    return nil;
}

/**
 *  初始化 SDK
 *
 *  @param config 配置信息实体类
 *  @return YES：成功；NO：失败
 */
- (BOOL)initMessageSDKWithConfig:(HDIMSDKConfig *)config {
#pragma -- 需要实现
    return YES;
}

/**
 *  添加 IMSDK 监听
 */
- (void)addMessageSDKListener:(id<HDIMSDKListener>)listener {
#pragma -- 需要实现
}

/**
 *  移除 IMSDK 监听
 */
- (void)removeMesssageSDKListener:(id<HDIMSDKListener>)listener {
#pragma -- 需要实现
}

/**
 *  反初始化 IMSDK
 */
- (void)unInitSDK {
#pragma -- 需要实现
}

/**
 *  获取版本号
 *
 *  @return 返回版本号，字符串表示，例如 5.0.10
 */
- (NSString*)getVersion {
#pragma -- 需要实现
    return @"";
}

/**
 *  获取服务器时间戳
 *
 *  @return 服务器时间时间戳，单位 s
 */
- (uint64_t)getServerTime {
#pragma -- 需要实现
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//                               登录登出
/////////////////////////////////////////////////////////////////////////////////

/**
 *  登录
 *
 *  登录需要设置用户名 userID 和 password
 *
 */
- (void)login:(NSString *)userID pwd:(NSString *)password succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  登出
 *
 *  退出登录，如果切换账号，需要 logout 回调成功或者失败后才能再次 login，否则 login 可能会失败。
 */
- (void)logout:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  获取登录用户
 */
- (NSString *)getLoginUser {
#pragma -- 需要实现
    return @"";
}

/**
 *  获取登录状态
 *
 *  如果用户已经处于已登录和登录中状态，请勿再频繁调用登录接口登录。
 */
- (IMSDKLoginStatus)getLoginStatus {
#pragma -- 需要实现
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////
//                         消息收发
/////////////////////////////////////////////////////////////////////////////////

/**
 *  设置基本消息（文本消息和自定义消息）的事件监听器
 */
- (void)addSimpleMsgListener:(id<HDIMSimpleMsgListener>)listener {
#pragma -- 需要实现
}

/**
 *  移除基本消息（文本消息和自定义消息）的事件监听器
 */
- (void)removeSimpleMsgListener:(id<HDIMSimpleMsgListener>)listener {
#pragma -- 需要实现
}

/**
 *  发送单聊普通文本消息（最大支持 8KB）
 *
 *  文本消息支持云端的脏词过滤，如果用户发送的消息中有敏感词，V2TIMFail 回调将会返回 80001 错误码。
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendC2CTextMessage:(NSString *)text to:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}

/**
 *  发送单聊自定义消息
 *
 *  自定义消息本质就是一端二进制 buffer，您可以在其上自由组织自己的消息格式（常用于发送信令），但是自定义消息不支持云端敏感词过滤。
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendC2CCustomMessage:(NSData *)customData to:(NSString *)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}

/**
 *  发送群聊普通文本消息
 *  @return 返回消息的唯一标识 ID
 */
- (NSString *)sendGroupTextMessage:(NSString *)text to:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}

/**
 *  发送群聊自定义消息
 *
 *  @return 返回消息的唯一标识 ID
 *
 */
- (NSString*)sendGroupCustomMessage:(NSData *)customData to:(NSString *)groupID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
    return @"";
}




/////////////////////////////////////////////////////////////////////////////////
//                        资料相关操作
/////////////////////////////////////////////////////////////////////////////////

/**
 *  获取用户资料
 *  @note 请注意:
 *  - 获取自己的资料，传入自己的 ID 即可。
 */
- (void)getUsersInfo:(NSArray<NSString *> *)userIDList succ:(IMSDKUserFullInfoListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  修改个人资料
 */
- (void)setSelfInfo:(HDIMSDKUserFullInfo *)Info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
@end




