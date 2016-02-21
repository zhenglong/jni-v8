/*
 * my-log.h
 * Copyright (C) 2016 tristan <tristan@tristan-VirtualBox>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef MY_LOG_H
#define MY_LOG_H

#define DEBUG 0

#if DEBUG == 1
#include <android/log.h>

#define LOGI(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, fmt, ##args)
#define LOGD(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, fmt, ##args)
#define LOGE(LOG_TAG, fmt, args...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, fmt, ##args)
#else
void dummy();

#define LOGI(LOG_TAG, fmt, args...) dummy()
#define LOGD(LOG_TAG, fmt, args...) dummy()
#define LOGE(LOG_TAG, fmt, args...) dummy()
#endif

#endif /* !MY_LOG_H */
