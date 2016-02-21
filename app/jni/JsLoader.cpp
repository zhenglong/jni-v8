/*
 * JsLoader.cpp
 * Copyright (C) 2016 tristan <tristan@tristan-Satellite-L600>
 *
 * Distributed under terms of the MIT license.
 */

#include "JsLoader.h"
#include <cstring>

#include "my-log.h"
#include <android/asset_manager_jni.h>

#define LOG_TAG "JsLoader"

jobject JsLoader::AssetManager = NULL;
JNIEnv* JsLoader::env = NULL;

string JsLoader::ReadFile(const string& path) {
	auto mgr = AAssetManager_fromJava(JsLoader::env, JsLoader::AssetManager);
	auto asset = AAssetManager_open(mgr, path.c_str(), AASSET_MODE_BUFFER);
    auto len = AAsset_getLength(asset);
	char* buffer = new char[len+1];
	memset(buffer, 0, sizeof(char)*(len+1));
	int res = AAsset_read(asset, buffer, len);
	LOGD(LOG_TAG, "%d", res);
	AAsset_close(asset);
    string str(buffer);
	return str;
}
