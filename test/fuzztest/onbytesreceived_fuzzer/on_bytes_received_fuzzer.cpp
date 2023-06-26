/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "device_manager_service_listener.h"
#include "dm_auth_manager.h"
#include "dm_device_info.h"
#include "dm_publish_info.h"
#include "dm_subscribe_info.h"
#include "hichain_connector.h"
#include "softbus_bus_center.h"
#include "softbus_connector.h"
#include "softbus_session.h"
#include "onbytesreceived_fuzzer.h"

namespace OHOS {
namespace DistributedHardware {
void OnBytesReceivedFuzzTest(const uint8_t* data, size_t size)
{
    if ((data == nullptr) || (size < sizeof(int))) {
        return;
    }

    std::shared_ptr<SoftbusSession> softbusSession = std::make_shared<SoftbusSession>();
    std::shared_ptr<DeviceManagerServiceListener> listener = std::make_shared<DeviceManagerServiceListener>();
    std::shared_ptr<SoftbusConnector> softbusConnector = std::make_shared<SoftbusConnector>();
    std::shared_ptr<HiChainConnector> hiChainConnector = std::make_shared<HiChainConnector>();
    std::shared_ptr<DmAuthManager> discoveryMgr =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector);

    softbusSession->RegisterSessionCallback(discoveryMgr);
    int sessionId = *(reinterpret_cast<const int*>(data));
    softbusSession->OnBytesReceived(sessionId, data, size);
}
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DistributedHardware::OnBytesReceivedFuzzTest(data, size);

    return 0;
}
