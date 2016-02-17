/*
 * my-log.h
 * Copyright (C) 2016 tristan <tristan@tristan-VirtualBox>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MY_LOG_H
#define MY_LOG_H
#include <android/log.h>

#define LOGI(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)

#endif /* !MY_LOG_H */
