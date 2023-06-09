/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef OHOS_DEVICE_MANAGER_IPC_GET_DM_FA_PARAM_RSP_H
#define OHOS_DEVICE_MANAGER_IPC_GET_DM_FA_PARAM_RSP_H

#include "dm_device_info.h"
#include "ipc_req.h"

namespace OHOS {
namespace DistributedHardware {
class IpcGetDmFaParamRsp : public IpcRsp {
    DECLARE_IPC_MODEL(IpcGetDmFaParamRsp);

public:
    /**
     * @tc.name: IpcGetDmFaParamRsp::GetDmAuthParam
     * @tc.desc: Ipc Get DeviceManager Fa Param Response Get DeviceManager Auth Param
     * @tc.type: FUNC
     */
    const DmAuthParam GetDmAuthParam() const
    {
        return dmFaParam_;
    }

    /**
     * @tc.name: IpcGetDmFaParamRsp::SetDmAuthParam
     * @tc.desc: Ipc Get DeviceManager Fa Param Response Set DeviceManager Auth Param
     * @tc.type: FUNC
     */
    void SetDmAuthParam(const DmAuthParam &dmFaParam)
    {
        dmFaParam_ = dmFaParam;
    }

private:
    DmAuthParam dmFaParam_;
};
} // namespace DistributedHardware
} // namespace OHOS
#endif // OHOS_DEVICE_MANAGER_IPC_GET_DM_FA_PARAM_RSP_H
