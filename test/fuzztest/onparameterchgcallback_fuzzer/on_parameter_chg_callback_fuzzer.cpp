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

#include <chrono>
#include <securec.h>
#include <string>

#include "device_manager_impl.h"
#include "dm_constants.h"
#include "softbus_listener.h"
#include "on_parameter_chg_callback_fuzzer.h"

namespace OHOS {
namespace DistributedHardware {
void OnParameterChgCallbackFuzzTest(const uint8_t* data, size_t size)
{
    if ((data == nullptr) || (size < sizeof(char))) {
        return;
    }

    std::shared_ptr<SoftbusListener> softbusListener = std::make_shared<SoftbusListener>();
    const char *key = reinterpret_cast<const char*>(data);
    std::string str(reinterpret_cast<const char*>(data), size);
    const char *value = str.c_str();
    void *context = nullptr;
    softbusListener->OnParameterChgCallback(key, value, context);
}
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size)
{
    /* Run your code on data */
    OHOS::DistributedHardware::OnParameterChgCallbackFuzzTest(data, size);

    return 0;
}
