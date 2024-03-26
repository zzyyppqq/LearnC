//
// Created by zhangyipeng on 2023/8/9.
//

#include <cstdint>
#include <iostream>

// 定义一个句柄类型
//typedef uint64_t VkDeviceHandle;

// 定义句柄的无效值
#define VK_NULL_DEVICE_HANDLE 0

// 定义句柄处理宏
#define VK_DEFINE_HANDLE(name) \
  struct name##_T { uint64_t handle; }; \
  typedef struct name##_T* name; \
  inline bool IsValid##name(const name h) { return h != nullptr && h->handle != VK_NULL_DEVICE_HANDLE; } \
  inline void Invalidate##name(name& h) { h = nullptr; }

VK_DEFINE_HANDLE(VkDeviceHandle)

void InvalidateVkDevice(VkDeviceHandle &pT) {
    printf("InvalidateVkDevice\n");
    pT->handle = VK_NULL_DEVICE_HANDLE;
}

// 使用句柄
void SomeFunction(VkDeviceHandle handle)
{
    // 使用句柄
    if (handle != VK_NULL_DEVICE_HANDLE)
    {
        std::cout << "Using handle: " << handle << std::endl;
    }
    else
    {
        std::cout << "Invalid handle!" << std::endl;
    }
}

int main()
{
    // 创建句柄
    VkDeviceHandle deviceHandle = reinterpret_cast<VkDeviceHandle>(new VkDeviceHandle());
    deviceHandle->handle = 1234;

    // 使用句柄
    SomeFunction(deviceHandle);

    // 使句柄无效
    InvalidateVkDevice(deviceHandle);

    // 使用无效句柄
    SomeFunction(deviceHandle);

    // 释放句柄内存
    delete deviceHandle;

    return 0;
}


