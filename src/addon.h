#ifndef ADDON_H
#define ADDON_H

#include <napi.h>

Napi::Value Add(const Napi::CallbackInfo& info);
Napi::Object Init(Napi::Env env, Napi::Object exports);

#endif