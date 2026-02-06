cmake_minimum_required (VERSION 3.10)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("nlohmann_json_learn")

# 判断是否是单配置生成器 (如 Makefile, Ninja)，且用户没有指定类型
# MSVC 无效, 需要 在 cmake 的 build 和install 时手动添加 --config Release/Debug/MinSizeRel/RelWithDebInfo
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "未指定构建类型，默认设置为 Release")

    # 强制更新缓存，设置默认值为 Release
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)

    # (可选) 设置 cmake-gui 中的下拉菜单选项
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()
message(STATUS CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 20)
# 设置为 ON 表示指定的 C++ 标准是必需的
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# 设置为 OFF 表示禁用编译器特定的语言扩展
# 具体来说：
#   当设置为 OFF 时，编译器会使用纯标准的 C++ 标志，例如 -std=c++17
#   当设置为 ON（默认值）时，编译器会使用带扩展的标志，例如 -std=gnu++17
# 禁用扩展可以确保你的代码具有更好的可移植性，能够在不同的编译器之间兼容
set(CMAKE_CXX_EXTENSIONS OFF)

set(BINARY "main")
set(SHAREDLIB "lib_test")

# 只有当用户没有在命令行通过 -DCMAKE_INSTALL_PREFIX 指定路径时，才覆盖默认值。
# CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT 这个变量专门用来检测是否使用了系统默认路径(通常是 /usr/local)。
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # 将安装路径设置为：当前源码目录下的 aarch64_install 文件夹
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "Default install prefix" FORCE)
endif()
set(SHARELIB_INSTALL_DIR "lib")
set(BINARY_INSTALL_DIR "bin")
set(INCLUDE_INSTALL_DIR "include")

if(MSVC)
    add_compile_options(/bigobj /utf-8)
endif()

include_directories("include")

# 将源代码添加到此项目的可执行文件。
add_executable (
    ${BINARY}
    "main.h"
    "main.cpp"
)

# 尝试制作运行库
add_library(
    ${SHAREDLIB}
    "lib.h"
    "lib.cpp"
)

# 安装执行文件
install(TARGETS ${BINARY}
    RUNTIME DESTINATION ${BINARY_INSTALL_DIR}
)
# 安装库
install(TARGETS ${SHAREDLIB}
    LIBRARY DESTINATION ${SHARELIB_INSTALL_DIR} # 共享库(Shared Libraries)(非 Windows 平台): Linux 上的 .so，macOS 上的 .dylib
    ARCHIVE DESTINATION ${SHARELIB_INSTALL_DIR} # 静态库(Static Libraries) 以及 Windows 导入库(Import Libraries): Windows .lib 或 Linux/macOS .a 文件
    RUNTIME DESTINATION ${BINARY_INSTALL_DIR} # 可执行文件(Executables) 和 Windows 动态库(DLLs): Windows .dll 或可执行文件
)
# 安装头文件和其他资源
install(FILES "lib.h" DESTINATION ${INCLUDE_INSTALL_DIR})

if (WIN32)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .lib)
elseif (UNIX)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
endif()
