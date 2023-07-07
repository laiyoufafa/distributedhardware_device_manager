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

#include <string>
#include <cstdlib>
#include <random>
#include <vector>

#include "device_manager_service_listener.h"
#include "dm_auth_manager.h"
#include "hichain_connector.h"

#include "on_finish_fuzzer.h"

namespace OHOS {
namespace DistributedHardware {
void OnFinishFuzzTest(const uint8_t* data, size_t size)
{
    if ((data == nullptr) || (size < sizeof(int64_t))) {
        return;
    }

    std::shared_ptr<DeviceManagerServiceListener> listener = std::make_shared<DeviceManagerServiceListener>();
    std::shared_ptr<SoftbusConnector> softbusConnector = std::make_shared<SoftbusConnector>();
    std::shared_ptr<HiChainConnector> hiChainConnector = std::make_shared<HiChainConnector>();
    std::shared_ptr<DmAuthManager> discoveryMgr =
        std::make_shared<DmAuthManager>(softbusConnector, listener, hiChainConnector);

    std::shared_ptr<HiChainConnector> hichainConnector = std::make_shared<HiChainConnector>();
    hichainConnector->RegisterHiChainCallback(std::shared_ptr<IHiChainConnectorCallback>(discoveryMgr));

    int64_t requestId = *(reinterpret_cast<const int64_t*>(data));
    std::random_device rd;
    int operationCode = static_cast<GroupOperationCode>(rd() % 6);
    std::string str(reinterpret_cast<const char*>(data), size);
    const char *returnData = str.data();
    hichainConnector->onFinish(requestId, operationCode, returnData);
}
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DistributedHardware::OnFinishFuzzTest(data, size);

    return 0;
}