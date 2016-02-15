package com.example.hellojni;

import java.util.concurrent.atomic.AtomicBoolean;

public class HttpCallback {
    private final AtomicBoolean destroyed = new AtomicBoolean(false);
    private long nativeRef;

    public HttpCallback(long nativeRef)
    {
        if (nativeRef == 0) throw new RuntimeException("nativeRef is zero");
        this.nativeRef = nativeRef;
    }

    private native void nativeDestroy(long nativeRef);
    public void destroy()
    {
        boolean destroyed = this.destroyed.getAndSet(true);
        if (!destroyed) nativeDestroy(this.nativeRef);
    }
    protected void finalize() throws java.lang.Throwable
    {
        destroy();
        super.finalize();
    }

    public void onNetworkError()
    {
        assert !this.destroyed.get() : "trying to use a destroyed object";
        native_onNetworkError(this.nativeRef);
    }
    private native void native_onNetworkError(long _nativeRef);

    public void onSuccess(short httpCode, String data)
    {
        assert !this.destroyed.get() : "trying to use a destroyed object";
        native_onSuccess(this.nativeRef, httpCode, data);
    }
    private native void native_onSuccess(long _nativeRef, short httpCode, String data);
}
