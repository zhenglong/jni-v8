package com.example.hellojni;
import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.StringWriter;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.Executor;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;
import android.util.Log;


public class AndroidHttp {
    private Executor mExecutor;

    public AndroidHttp() {
        BlockingQueue<Runnable> workQueue = new LinkedBlockingQueue<Runnable>();
        mExecutor = new ThreadPoolExecutor(1, 20, 60, TimeUnit.SECONDS, workQueue);
    }
    public void get(final String urlString, final HttpCallback callback) {
		Log.d("AndroidHttp", "url:" + urlString);
        mExecutor.execute(new Runnable() {
            @Override
            public void run() {
                //try {
                    //URL url = new URL(urlString);
                    //HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                    //int httpCode = conn.getResponseCode();
                    //BufferedInputStream iStream = new BufferedInputStream(conn.getInputStream());
                    //String response = getString(iStream, "UTF-8");
                    //callback.onSuccess((short)httpCode, response);
					callback.onSuccess((short)200, "{\"data\":\"from java\"}");
                //} catch (MalformedURLException ex) {
                //    callback.onNetworkError();
                //} catch (IOException ex) {
                //    callback.onNetworkError();
                //}
            }
        });
    }
    private static String getString(InputStream stream, String charsetName) throws IOException
    {
        int n = 0;
        char[] buffer = new char[1024 * 4];
        InputStreamReader reader = new InputStreamReader(stream, charsetName);
        StringWriter writer = new StringWriter();
        while (-1 != (n = reader.read(buffer))) {
            writer.write(buffer, 0, n);
        }
        return writer.toString();
    }
}
