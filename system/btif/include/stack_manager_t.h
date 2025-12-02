/******************************************************************************
 *
 *  Copyright 2014 Google, Inc.
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

#pragma once

#include <stdbool.h>

#include <future>

#include "core_callbacks.h"
#include "osi/include/future.h"

using ProfileStartCallback = void();
using ProfileStopCallback = void();

typedef struct {
  // 初始化
  void (*init_stack)(bluetooth::core::CoreInterface*);
  // 启动
  void (*start_up_stack_async)(bluetooth::core::CoreInterface*, ProfileStartCallback,
                               ProfileStopCallback);
  // 关闭
  void (*shut_down_stack_async)(ProfileStopCallback);
  // 清理
  void (*clean_up_stack)(ProfileStopCallback);
  // 启动rust模块
  void (*start_up_rust_module_async)(std::promise<void> promise);
  // 关闭rust模块
  void (*shut_down_rust_module_async)();
  // 协议栈是否在运行
  bool (*get_stack_is_running)(void);
} stack_manager_t;

// 获取stack_manager_t来执行对应的stack管理方法
const stack_manager_t* stack_manager_get_interface();

// 用于外部等待操作这个future, 太不优雅了...
// TODO(zachoverflow): remove this terrible hack once the startup sequence is
// more sane
future_t* stack_manager_get_hack_future();

// init_stack时传入的CoreInterface
bluetooth::core::CoreInterface* GetInterfaceToProfiles();
