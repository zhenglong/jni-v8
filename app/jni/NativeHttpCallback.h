/*
 * NativeHttpCallback.h
 * Copyright (C) 2016 tristan <tristan@tristan-VirtualBox>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NATIVEHTTPCALLBACK_H
#define NATIVEHTTPCALLBACK_H

class NativeHttpCallback {
    public:
        void onNetworkError();
        void onSuccess(int, const string& data);
}

#endif /* !NATIVEHTTPCALLBACK_H */
