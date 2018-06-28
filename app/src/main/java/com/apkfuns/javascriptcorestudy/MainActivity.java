package com.apkfuns.javascriptcorestudy;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        String expression = "3*2 + 1.5";
        String value = expression + "=" + calculation(expression);
        tv.setText(value);
        callObject();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    /**
     * 四则运算
     * @param jsBuffer js
     * @return calculation value
     */
    public native double calculation(String jsBuffer);

    public native void callObject();
}
