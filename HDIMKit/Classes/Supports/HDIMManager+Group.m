//
//  HDIMManager+Group.m
//  hideout2.0
//
//  Created by apple on 2022/10/13.
//

#import "HDIMManager+Group.h"

@implementation HDIMManager (Group)
/////////////////////////////////////////////////////////////////////////////////
//                         群管理
/////////////////////////////////////////////////////////////////////////////////

/**
 *
 *  @param info 自定义群组信息，可以设置 groupID | groupType | groupName | notification | introduction | faceURL 字段
 *  @param memberList 指定初始的群成员（直播群 AVChatRoom 不支持指定初始群成员，memberList 请传 nil）
 *
 */
- (void)createGroup:(HDIMGroupInfo *)info memberList:(NSArray<HDIMCreateGroupMemberInfo *>*) memberList succ:(IMSDKCreateGroupSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  1.2 获取当前用户已经加入的群列表
 */
- (void)getJoinedGroupList:(VHDIMGroupInfoListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/////////////////////////////////////////////////////////////////////////////////
//                         群资料管理
/////////////////////////////////////////////////////////////////////////////////

/**
 * 拉取群资料
 *
 *  @param groupIDList 群组 ID 列表
 */
- (void)getGroupsInfo:(NSArray<NSString *> *)groupIDList succ:(HDIMGroupInfoResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}


/**
 *  2.3 修改群资料
 */
- (void)setGroupInfo:(HDIMGroupInfo *)info succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}



/////////////////////////////////////////////////////////////////////////////////
//                         群成员管理
/////////////////////////////////////////////////////////////////////////////////
/**
 *  3.1 获取群成员列表
 *
 *  @param nextSeq  分页拉取标志，第一次拉取填0，回调成功如果 nextSeq 不为零，需要分页，传入再次拉取，直至为 0。
 *
 */
- (void)getGroupMemberList:(NSString*)groupID nextSeq:(uint64_t)nextSeq succ:(HDIMGroupMemberInfoResultSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  3.2 指定的群成员资料
 */
- (void)getGroupMembersInfo:(NSString*)groupID memberList:(NSArray<NSString*>*)memberList succ:(HDIMGroupMemberInfoListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}





/**
 *  邀请他人入群
 */
- (void)inviteUserToGroup:(NSString*)groupID userList:(NSArray<NSString *>*)userList succ:(HDIMGroupMemberOperationResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}

/**
 *  踢人  只有群主可以踢人
 */
- (void)kickGroupMember:(NSString*)groupID memberList:(NSArray<NSString *>*)memberList reason:(NSString*)reason succ:(HDIMGroupMemberOperationResultListSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}


/**
 *  转让群主
 *
 */
- (void)transferGroupOwner:(NSString*)groupID member:(NSString*)userID succ:(IMSDKSucc)succ fail:(IMSDKFail)fail {
#pragma -- 需要实现
}
@end
