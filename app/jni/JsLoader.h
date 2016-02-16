/*
 * JsLoader.h
 * Copyright (C) 2016 tristan <tristan@tristan-VirtualBox>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef JSLOADER_H
#define JSLOADER_H
#include <string>
using namespace std;

class JsLoader {
    public:
		static jobject AssetManager;
        string ReadFile(const string& path);
};

#endif /* !JSLOADER_H */
