# Node.js Native Addon Module with C++

This project implements a Node.js native addon module using C++20, demonstrating how to create high-performance native extensions for Node.js applications.

## 功能特性 / Features

- 基于 C++20 实现核心功能 / Core functionality implemented in C++20
- 使用 N-API 构建 Node.js 原生模块 / Node.js native addon using N-API
- 包含 TypeScript 类型定义 / TypeScript type definitions included
- 跨平台兼容性 / Cross-platform compatibility
- 数学运算功能(当前支持加法) / Mathematical operations (currently supports addition)

## 环境要求 / Prerequisites

开发前请确保已安装以下工具 / Before development, ensure you have installed:

- Node.js (v16.20.0 或更高版本 / or higher)
- npm (随 Node.js 一起安装 / comes with Node.js)
- Python (用于 node-gyp / for node-gyp)
- C++ 编译器 / C++ compiler:
  - Windows: Visual Studio with C++ workload
  - Linux: GCC
  - macOS: Xcode Command Line Tools

## 项目结构 / Project Structure

```
project-root/
├── src/
│   ├── addon.cpp        # C++ 实现 / C++ implementation
│   └── addon.h          # C++ 头文件 / C++ header file
├── binding.gyp          # node-gyp 构建配置 / build configuration
├── index.js            # JavaScript 封装 / JavaScript wrapper
├── index.d.ts          # TypeScript 类型定义 / TypeScript definitions
├── package.json        # 项目配置 / Project configuration
└── test.js            # 测试文件 / Test file
```

## 开发指南 / Development Guide

### C++ 开发 / C++ Development

1. **头文件 / Header File (src/addon.h)**

   ```cpp
   #ifndef ADDON_H
   #define ADDON_H

   #include <napi.h>

   Napi::Value Add(const Napi::CallbackInfo& info);
   Napi::Object Init(Napi::Env env, Napi::Object exports);

   #endif
   ```

2. **实现文件 / Implementation File (src/addon.cpp)**

   ```cpp
   #include "addon.h"

   Napi::Value Add(const Napi::CallbackInfo& info) {
       Napi::Env env = info.Env();
       
       // 参数验证 / Parameter validation
       if (info.Length() < 2) {
           Napi::TypeError::New(env, "Wrong number of arguments")
               .ThrowAsJavaScriptException();
           return env.Null();
       }
       
       // 获取并验证参数 / Get and validate arguments
       double arg0 = info[0].As<Napi::Number>().DoubleValue();
       double arg1 = info[1].As<Napi::Number>().DoubleValue();
       
       // 执行计算并返回结果 / Perform calculation and return result
       Napi::Number result = Napi::Number::New(env, arg0 + arg1);
       return result;
   }
   ```

### 构建配置 / Build Configuration

**binding.gyp**

```gyp
{
  "targets": [{
    "target_name": "addon",
    "sources": [ "src/addon.cpp" ],
    "include_dirs": [
      "<!@(node -p \"require('node-addon-api').include\")"
    ],
    "cflags_cc": ["-std=c++20"]
  }]
}
```

## 构建步骤 / Build Steps

1. 安装依赖 / Install dependencies:

```bash
npm install
```

2. 编译原生模块 / Build native addon:

```bash
npm run build
```

编译后的模块位于 / The built addon will be in: `build/Release/addon.node`

## 测试 / Testing

运行测试套件 / Run the test suite:

```bash
node test.js
```

测试文件示例 / Example test file:

```javascript
const { add } = require('./index.js');

console.log('Testing add function:');
console.log('add(5, 3) =', add(5, 3));
console.log('add(10, -5) =', add(10, -5));
console.log('add(3.14, 2.86) =', add(3.14, 2.86));
```

## 使用方法 / Usage

### JavaScript

```javascript
const { add } = require('your-module-name');

const result = add(5, 3);
console.log(result); // 输出 / Output: 8
```

### TypeScript

```typescript
import { add } from 'your-module-name';

const result: number = add(5, 3);
console.log(result); // 输出 / Output: 8
```

## 常见问题及解决方案 / Troubleshooting

1. **构建失败 / Build Failures**
   - 确保所有依赖都已安装 / Ensure all prerequisites are installed
   - 检查 C++ 编译器配置 / Check C++ compiler configuration
   - 验证 binding.gyp 语法 / Verify binding.gyp syntax

2. **运行时错误 / Runtime Errors**
   - 检查参数类型是否匹配 / Check parameter types match
   - 确保 .node 文件正确链接 / Ensure .node file is properly linked

## 调试技巧 / Debug Tips

1. 在构建时启用详细输出 / Enable verbose output during build:

```bash
node-gyp rebuild --verbose
```

2. 检查开发环境 / Check development environment:
   - Node.js 版本 / version: `node --version`
   - npm 版本 / version: `npm --version`
   - C++ 编译器版本 / compiler version:
     - Linux/macOS: `g++ --version`
     - Windows: `cl`
