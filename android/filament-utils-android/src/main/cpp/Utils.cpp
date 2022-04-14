/*
 * Copyright (C) 2020 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>

#include <filament/Engine.h>
#include <filament/IndirectLight.h>
#include <filament/Skybox.h>

#include <image/KtxUtility.h>

#include "common/NioUtils.h"

using namespace filament;
using namespace filament::math;
using namespace image;

jlong nCreateHDRTexture(JNIEnv* env, jclass,
        jlong nativeEngine, jobject javaBuffer, jint remaining, jint internalFormat);

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void*) {
    JNIEnv* env;
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        return -1;
    }

    int rc;

    // HDRLoader
    jclass hdrloaderClass = env->FindClass("com/google/android/filament/utils/HDRLoader");
    if (hdrloaderClass == nullptr) return JNI_ERR;
    static const JNINativeMethod hdrMethods[] = {
        {(char*)"nCreateHDRTexture", (char*)"(JLjava/nio/Buffer;II)J", reinterpret_cast<void*>(nCreateHDRTexture)},
    };
    rc = env->RegisterNatives(hdrloaderClass, hdrMethods, sizeof(hdrMethods) / sizeof(JNINativeMethod));
    if (rc != JNI_OK) return rc;

    return JNI_VERSION_1_6;
}
