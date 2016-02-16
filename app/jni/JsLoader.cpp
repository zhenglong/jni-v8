/*
 * JsLoader.cpp
 * Copyright (C) 2016 tristan <tristan@tristan-Satellite-L600>
 *
 * Distributed under terms of the MIT license.
 */

#include "JsLoader.h"
#include <android/asset_manage_jni.h>

string JsLoader::ReadFile(JNIEnv* env, const string& path) {
	auto mgr = AAssetManager_fromJava(env, JsLoader.AssetManager);
	auto asset = AAssetManager_open(mgr, path.c_str(), 0);
	auto buffer = AAsset_getBuffer(asset);
	AAsset_close(asset);
	return new string(buffer)
}


