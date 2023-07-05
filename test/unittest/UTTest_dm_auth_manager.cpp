/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "UTTest_dm_auth_manager.h"

#include "nlohmann/json.hpp"

#include "dm_log.h"
#include "dm_constants.h"
#include "dm_auth_manager.h"
#include "auth_message_processor.h"
#include "device_manager_service_listener.h"

namespace OHOS {
namespace DistributedHardware {
void DmAuthManagerTest::SetUp()
{
}
void DmAuthManagerTest::TearDown()
{
}
void DmAuthManagerTest::SetUpTestCase()
{
}
void DmAuthManagerTest::TearDownTestCase()
{
}

namespace {
std::shared_ptr<SoftbusConnector> softbusConnector = std::make_shared<SoftbusConnector>();
std::shared_ptr<DeviceManagerServiceListener> listener = std::make_shared<DeviceManagerServiceListener>();
std::shared_ptr<HiChainConnector> hiChainConnector_ = std::make_shared<HiChainConnector>();
const int32_t MIN_PIN_CODE = 100000;
const int32_t MAX_PIN_CODE = 999999;
/**
 * @tc.name: DmAuthManager::UnAuthenticateDevice_001
 * @tc.desc: Call unauthenticateddevice to check whether the return value is DM_ FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, UnAuthenticateDevice_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<SoftbusSession> sessionSession = std::shared_ptr<SoftbusSession>();
    std::shared_ptr<DmAuthRequestContext> authRequestContext = std::make_shared<DmAuthRequestContext>();
    std::string pkgName = "";
    std::string deviceId = "222";
    int32_t ret = authManager->UnAuthenticateDevice(pkgName, deviceId);
    ASSERT_EQ(ret, ERR_DM_FAILED);
}

/**
 * @tc.name: DmAuthManager::HandleAuthenticateTimeout_001
 * @tc.desc: authResponseContext_= nullptr; Call handleauthenticatemeout to check whether return value is ERR_DM_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, HandleAuthenticateTimeout_001, testing::ext::TestSize.Level0)
{
    std::string name = "test";
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthRequestState> authRequestState = std::make_shared<AuthRequestNetworkState>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authRequestState_ = std::make_shared<AuthRequestNetworkState>();
    authManager->authResponseContext_ = nullptr;
    authManager->SetAuthRequestState(authRequestState);
    authManager->HandleAuthenticateTimeout(name);
    ASSERT_TRUE(authManager->authResponseContext_ != nullptr);
}

/**
 * @tc.name: DmAuthManager::HandleAuthenticateTimeout_002
 * @tc.desc: authResponseContext_= nullptr; Call handleauthenticatemeout to check whether the return value is DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, HandleAuthenticateTimeout_002, testing::ext::TestSize.Level0)
{
    std::string name = "test";
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthRequestState> authRequestState = std::make_shared<AuthRequestFinishState>();
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authRequestState_ = std::make_shared<AuthRequestFinishState>();
    authManager->SetAuthRequestState(authRequestState);
    authManager->HandleAuthenticateTimeout(name);
    ASSERT_TRUE(authManager->authRequestState_ != nullptr);
}

/**
 * @tc.name: DmAuthManager::EstablishAuthChannel_001
 * @tc.desc: Call establishauthchannel to check whether the return value is DM_ FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, EstablishAuthChannel_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<SoftbusSession> sessionSession = std::shared_ptr<SoftbusSession>();
    std::shared_ptr<DmAuthResponseContext> authRequestContext = std::make_shared<DmAuthResponseContext>();
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authRequestState_ = std::make_shared<AuthRequestFinishState>();
    std::string deviceId1;
    int32_t ret = authManager->EstablishAuthChannel(deviceId1);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::StartAuthProcess_001
 * @tc.desc: Whether the return value of calling startauthprocess is ERR_DM_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, StartAuthProcess_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthResponseState> authResponseState = std::make_shared<AuthResponseConfirmState>();
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authResponseState_ = std::make_shared<AuthResponseConfirmState>();
    authManager->SetAuthResponseState(authResponseState);
    int32_t action = 0;
    authManager->StartAuthProcess(action);
    bool ret = authManager->authRequestContext_->deviceName.empty();
    ASSERT_EQ(ret, true);
}

/**
 * @tc.name: DmAuthManager::StartAuthProcess_002
 * @tc.desc: Whether the return value of calling startauthprocess is DM_ OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, StartAuthProcess_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthResponseState> authResponseState = std::make_shared<AuthResponseInitState>();
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authResponseState_ = std::make_shared<AuthResponseInitState>();
    authManager->authMessageProcessor_ = std::make_shared<AuthMessageProcessor>(authManager);
    authManager->SetAuthResponseState(authResponseState);
    authManager->authResponseContext_->sessionId = 111;
    authManager->softbusConnector_->GetSoftbusSession()->RegisterSessionCallback(authManager);
    int32_t action = 1;
    int32_t ret = authManager->StartAuthProcess(action);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::StartAuthProcess_003
 * @tc.desc: Set authResponseContext_ is nullptr return ERR_DM_AUTH_NOT_START
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, StartAuthProcess_003, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = nullptr;
    int32_t action = 1;
    int32_t ret = authManager->StartAuthProcess(action);
    ASSERT_EQ(ret, ERR_DM_AUTH_NOT_START);
}

/**
 * @tc.name: DmAuthManager::CreateGroup_001
 * @tc.desc: Whether the return value of calling creategroup is DM_ OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, CreateGroup_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthResponseState> authResponseState = std::make_shared<AuthResponseConfirmState>();
    std::shared_ptr<HiChainConnector> hiChainConnector = std::make_shared<HiChainConnector>();
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authResponseState_ = std::make_shared<AuthResponseConfirmState>();
    authManager->authMessageProcessor_ = std::make_shared<AuthMessageProcessor>(authManager);
    authManager->SetAuthResponseState(authResponseState);
    authManager->authResponseContext_->requestId = 111;
    authManager->authResponseContext_->groupName = "111";
    int32_t ret = authManager->CreateGroup();
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::CreateGroup_002
 * @tc.desc: Whether the return value of calling creategroup is ERR_DM_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, CreateGroup_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = nullptr;
    int32_t ret = authManager->CreateGroup();
    ASSERT_EQ(ret, ERR_DM_FAILED);
}

/**
 * @tc.name: DmAuthManager::AddMember_001
 * @tc.desc: Whether the return value of calling addmember is DM_ OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AddMember_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthResponseState> authResponseState = std::make_shared<AuthResponseInitState>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    std::shared_ptr<HiChainConnector> hiChainConnector = std::make_shared<HiChainConnector>();
    authManager->authMessageProcessor_ = std::make_shared<AuthMessageProcessor>(authManager);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    nlohmann::json jsonObject;
    authManager->authResponseContext_->groupId = "111";
    authManager->authResponseContext_->groupName = "222";
    authManager->authResponseContext_->code = 123;
    authManager->authResponseContext_->requestId = 234;
    authManager->authResponseContext_->deviceId = "234";
    int32_t pinCode = 444444;
    authManager->timer_ = std::make_shared<DmTimer>();
    authManager->hiChainConnector_->RegisterHiChainCallback(authManager);
    authManager->SetAuthResponseState(authResponseState);
    int32_t ret = authManager->AddMember(pinCode);
    ASSERT_NE(ret, -1);
}

/**
 * @tc.name: DmAuthManager::AddMember_002
 * @tc.desc: Whether the return value of calling  AddMember is ERR_DM_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AddMember_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    int32_t pinCode = 33333;
    authManager->authResponseContext_ = nullptr;
    int32_t ret = authManager->AddMember(pinCode);
    ASSERT_EQ(ret, ERR_DM_FAILED);
}

/**
 * @tc.name: DmAuthManager::JoinNetwork_001
 * @tc.desc: Whether the return value of calling joinnetwork is DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, JoinNetwork_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthRequestState> authRequestState = std::make_shared<AuthRequestFinishState>();
    authManager->timer_ = std::make_shared<DmTimer>();
    authManager->authMessageProcessor_ = std::make_shared<AuthMessageProcessor>(authManager);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->authRequestState_ = std::make_shared<AuthRequestFinishState>();
    const int32_t sessionId = 65;
    const std::string message = "messageTest";
    int64_t requestId = 444;
    const std::string groupId = "{}";
    int32_t status = 1;
    authManager->OnGroupCreated(requestId, groupId);
    authManager->OnMemberJoin(requestId, status);
    authManager->OnDataReceived(sessionId, message);
    authManager->SetAuthRequestState(authRequestState);
    int32_t ret = authManager->JoinNetwork();
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::JoinNetwork_002
 * @tc.desc: Whether the return value of calling joinnetwork is ERR_DM_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, JoinNetwork_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = nullptr;
    int32_t userId = 1;
    bool isShow = false;
    authManager->UserSwitchEventCallback(userId);
    authManager->AuthenticateFinish();
    authManager->CancelDisplay();
    authManager->UpdateInputDialogDisplay(isShow);
    int32_t ret = authManager->JoinNetwork();
    ASSERT_EQ(ret, ERR_DM_FAILED);
}

/**
 * @tc.name: DmAuthManager::SetAuthResponseState_001
 * @tc.desc: Is the authresponsestate assignment successful
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetAuthResponseState_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::shared_ptr<AuthResponseState> authResponseState = std::make_shared<AuthResponseFinishState>();
    authManager->authResponseState_ = std::make_shared<AuthResponseFinishState>();
    authManager->SetAuthResponseState(authResponseState);
    int32_t ret = authManager->SetAuthResponseState(authResponseState);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::GetPinCode_001
 * @tc.desc: Return authresponsecontext - > code
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GetPinCode_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authResponseContext_->code = 123456;
    int32_t ret = authManager->GetPinCode();
    ASSERT_EQ(ret, 123456);
}

/**
 * @tc.name: DmAuthManager::GetPinCode_002
 * @tc.desc: Set authResponseContext_ is nullptr Return ERR_DM_AUTH_NOT_START
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GetPinCode_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = nullptr;
    authManager->ShowConfigDialog();
    authManager->ShowAuthInfoDialog();
    authManager->ShowStartAuthDialog();
    int32_t ret = authManager->GetPinCode();
    ASSERT_EQ(ret, ERR_DM_AUTH_NOT_START);
}

/**
 * @tc.name: DmAuthManager::SetPageId_001
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetPageId_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    int32_t pageId = 123;
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    int32_t ret = authManager->SetPageId(pageId);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::SetPageId_002
 * @tc.desc: Return ERR_DM_AUTH_NOT_START
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetPageId_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    int32_t pageId = 123;
    authManager->authResponseContext_ = nullptr;
    authManager->authMessageProcessor_ = nullptr;
    const int32_t sessionId = 65;
    const std::string message = "messageTest";
    int64_t requestId = 555;
    int32_t status = 2;
    authManager->OnMemberJoin(requestId, status);
    authManager->OnDataReceived(sessionId, message);
    int32_t ret = authManager->SetPageId(pageId);
    ASSERT_EQ(ret, ERR_DM_AUTH_NOT_START);
}

/**
 * @tc.name: DmAuthManager::SetReasonAndFinish_001
 * @tc.desc: Return ERR_DM_AUTH_NOT_START
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetReasonAndFinish_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    const int32_t sessionId = 78;
    int32_t reason = 123;
    int32_t state = 456;
    authManager->OnSessionClosed(sessionId);
    authManager->authResponseContext_ = nullptr;
    int64_t requestId = 333;
    const std::string groupId = "{}";
    authManager->OnGroupCreated(requestId, groupId);
    int32_t ret = authManager->SetReasonAndFinish(reason, state);
    ASSERT_EQ(ret, ERR_DM_AUTH_NOT_START);
}

/**
 * @tc.name: DmAuthManager::SetReasonAndFinish_002
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetReasonAndFinish_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestState_ = std::make_shared<AuthRequestFinishState>();
    int32_t reason = 1234;
    int32_t state = 5678;
    int64_t requestId = 22;
    const std::string groupId = "{}";
    authManager->OnGroupCreated(requestId, groupId);
    int32_t ret = authManager->SetReasonAndFinish(reason, state);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::SetReasonAndFinish_003
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, SetReasonAndFinish_003, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestState_ = nullptr;
    authManager->authResponseState_ = std::make_shared<AuthResponseFinishState>();
    int32_t reason = 12;
    int32_t state = 36;
    int32_t ret = authManager->SetReasonAndFinish(reason, state);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::IsIdenticalAccount_001
 * @tc.desc: Return false
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, IsIdenticalAccount_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    bool ret = authManager->IsIdenticalAccount();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: DmAuthManager::GeneratePincode_001
 * @tc.desc: Return OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GeneratePincode_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    int32_t openedSessionId = 66;
    int32_t sessionSide = 0;
    int32_t result = 3;
    const int32_t closedSessionId = 11;
    authManager->OnSessionOpened(openedSessionId, sessionSide, result);
    authManager->OnSessionClosed(closedSessionId);
    int32_t ret = authManager->GeneratePincode();
    ASSERT_LE(ret, MAX_PIN_CODE);
    ASSERT_GE(ret, MIN_PIN_CODE);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_001
 * @tc.desc: Return ERR_DM_AUTH_FAILED
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 0;
    std::string deviceId = "113456";
    std::string extra = "extraTest";
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_AUTH_FAILED);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_002
 * @tc.desc: Return ERR_DM_INPUT_PARA_INVALID
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "";
    int32_t authType = 1;
    std::string deviceId = "113456";
    std::string extra = "extraTest";
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_INPUT_PARA_INVALID);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_003
 * @tc.desc: Return ERR_DM_INPUT_PARA_INVALID
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_003, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 1;
    std::string deviceId = "234568";
    std::string extra = "extraTest";
    authManager->listener_ = nullptr;
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_INPUT_PARA_INVALID);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_004
 * @tc.desc: Return ERR_DM_UNSUPPORTED_AUTH_TYPE
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_004, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 4;
    std::string deviceId = "deviceIdTest";
    std::string extra = "extraTest";
    authManager->authenticationMap_.emplace(authType, nullptr);
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_UNSUPPORTED_AUTH_TYPE);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_005
 * @tc.desc: Return ERR_DM_AUTH_BUSINESS_BUSY
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_005, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 1;
    std::string deviceId = "deviceIdTest";
    std::string extra = "extraTest";
    authManager->authRequestState_ = std::make_shared<AuthRequestNetworkState>();
    authManager->authResponseState_ = std::make_shared<AuthResponseConfirmState>();
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_AUTH_BUSINESS_BUSY);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_006
 * @tc.desc: Return ERR_DM_INPUT_PARA_INVALID
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_006, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 1;
    std::string deviceId = "deviceIdTest";
    std::string extra = "extraTest";
    const int32_t sessionId = 1;
    authManager->authRequestState_ = nullptr;
    authManager->authResponseState_ = nullptr;
    authManager->authResponseContext_ = nullptr;
    authManager->StartNegotiate(sessionId);
    authManager->RespNegotiate(sessionId);
    authManager->SendAuthRequest(sessionId);
    authManager->StartRespAuthProcess();
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, ERR_DM_INPUT_PARA_INVALID);
}

/**
 * @tc.name: DmAuthManager::AuthenticateDevice_007
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, AuthenticateDevice_007, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    int32_t authType = 1;
    std::string deviceId = "deviceIdTest";
    std::string extra = "extraTest";
    std::shared_ptr<DeviceInfo> infoPtr = std::make_shared<DeviceInfo>();
    authManager->authRequestState_ = nullptr;
    authManager->authResponseState_ = nullptr;
    authManager->timer_ = nullptr;
    authManager->softbusConnector_->discoveryDeviceInfoMap_.emplace(deviceId, infoPtr);
    int32_t ret = authManager->AuthenticateDevice(pkgName, authType, deviceId, extra);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::GenerateGroupName_001
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GenerateGroupName_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = nullptr;
    std::string ret = authManager->GenerateGroupName();
    ASSERT_TRUE(ret.empty());
}

/**
 * @tc.name: DmAuthManager::GenerateGroupName_002
 * @tc.desc: Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GenerateGroupName_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authResponseContext_->targetPkgName = "targetPkgNameTest";
    authManager->authResponseContext_->localDeviceId = "localDeviceIdTest";
    std::string ret = authManager->GenerateGroupName();
    ASSERT_TRUE(!ret.empty());
}

/**
 * @tc.name: DmAuthManager::GetIsCryptoSupport_001
 * @tc.desc: Set authResponseState_ is nullptr Return false
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GetIsCryptoSupport_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseState_ = nullptr;
    bool ret = authManager->GetIsCryptoSupport();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: DmAuthManager::GetIsCryptoSupport_002
 * @tc.desc: Set authResponseState_ is not nullptr and authRequestState_ is nullptr Return false
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GetIsCryptoSupport_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseState_ = std::make_shared<AuthResponseNegotiateState>();
    authManager->authRequestState_ = nullptr;
    bool ret = authManager->GetIsCryptoSupport();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: DmAuthManager::GetIsCryptoSupport_003
 * @tc.desc: Set authResponseState_ is not nullptr and authRequestState_ is nullptr Return false
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, GetIsCryptoSupport_003, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseState_ = std::make_shared<AuthResponseNegotiateState>();
    authManager->authRequestState_ = std::make_shared<AuthRequestNegotiateState>();
    bool ret = authManager->GetIsCryptoSupport();
    ASSERT_EQ(ret, false);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_001
 * @tc.desc: Set authResponseContext_ is nullptr Return ERR_DM_AUTH_NOT_START
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    int32_t action = 0;
    std::string params = "paramsTest";
    authManager->authResponseContext_ = nullptr;
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, ERR_DM_AUTH_NOT_START);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_002
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authResponseState_ = std::make_shared<AuthResponseConfirmState>();
    authManager->authMessageProcessor_ = std::make_shared<AuthMessageProcessor>(authManager);
    int32_t action = 1;
    std::string params = "paramsTest1";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_003
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_003, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    int32_t action = 2;
    std::string params = "paramsTest2";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_004
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_004, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    int32_t action = 3;
    std::string params = "paramsTest3";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_005
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_005, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    int32_t action = 4;
    std::string params = "paramsTest4";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_006
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_006, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    authManager->authRequestContext_ = std::make_shared<DmAuthRequestContext>();
    authManager->timer_ = std::make_shared<DmTimer>();
    int32_t action = 5;
    std::string params = "5";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::OnUserOperation_007
 * @tc.desc: Set authResponseContext_ is not nullptr Return DM_OK
 * @tc.type: FUNC
 * @tc.require: AR000GHSJK
 */
HWTEST_F(DmAuthManagerTest, OnUserOperation_007, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    authManager->authResponseContext_ = std::make_shared<DmAuthResponseContext>();
    int32_t action = 1111;
    std::string params = "paramsTest1111";
    int32_t ret = authManager->OnUserOperation(action, params);
    ASSERT_EQ(ret, DM_OK);
}

/**
 * @tc.name: DmAuthManager::UnBindDevice001
 * @tc.desc: Set pkgName not null
 *           Set udidHash not null
 * @tc.type: FUNC
 */
HWTEST_F(DmAuthManagerTest, UnBindDevice001, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName = "com.ohos.test";
    std::string udidHash = "udidHash";
    int32_t ret = authManager->UnBindDevice(pkgName, udidHash);
    ASSERT_EQ(ret, ERR_DM_FAILED);
}

/**
 * @tc.name: DmAuthManager::UnBindDevice002
 * @tc.desc: Set pkgName not null
 *           Set udidHash not null
 * @tc.type: FUNC
 */
HWTEST_F(DmAuthManagerTest, UnBindDevice002, testing::ext::TestSize.Level0)
{
    std::shared_ptr<DmAuthManager> authManager =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector_);
    std::string pkgName;
    std::string udidHash = "udidHash";
    int32_t ret = authManager->UnBindDevice(pkgName, udidHash);
    ASSERT_EQ(ret, ERR_DM_FAILED);
}
} // namespace
} // namespace DistributedHardware
} // namespace OHOS
