/*
 * Copyright (C) 2009 The Android Open Source Project
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
package com.example.hellojni;

import android.app.Activity;
import android.os.PersistableBundle;
import android.widget.TextView;
import android.os.Bundle;
import android.util.Log;
import android.content.res.AssetManager;


public class HelloJni extends Activity
{

    private static final String LOG_TAG = HelloJni.class.getName();

    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* Create a TextView and set its content.
         * the text is retrieved by calling a native
         * function.
         */
        TextView  tv = new TextView(this);
        Log.d(LOG_TAG, "on create");
		loadAssetManager(getAssets());
        tv.setText( String.valueOf(add(100,200)));
        unloadAssetManager();
        setContentView(tv);
    }

    @Override
    protected void onStart() {
        super.onStart();
        Log.d(LOG_TAG, "on start");
    }

    @Override
    protected void onSaveInstanceState(Bundle outState) {
        super.onSaveInstanceState(outState);
        Log.d(LOG_TAG, "onSaveInstanceState 2");
    }

    @Override
    public void onSaveInstanceState(Bundle outState, PersistableBundle outPersistentState) {
        super.onSaveInstanceState(outState, outPersistentState);
        Log.d(LOG_TAG, "onSaveInstanceState 1");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.d(LOG_TAG, "on stop");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.d(LOG_TAG, "on restart");
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.d(LOG_TAG, "on resume");
    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.d(LOG_TAG, "on pause");
    }

    public native void loadAssetManager(AssetManager manager);

	public native void unloadAssetManager();

    /* A native method that is implemented by the
     * 'hello-jni' native library, which is packaged
     * with this application.
     */
    public native double add(double i, double j);

    /* this is used to load the 'hello-jni' library on application
     * startup. The library has already been unpacked into
     * /data/data/com.example.hellojni/lib/libhello-jni.so at
     * installation time by the package manager.
     */
    static {
        // System.loadLibrary("v8");
        Log.d("HelloJni", "after v8");
        System.loadLibrary("hello-jni");
    }
}
