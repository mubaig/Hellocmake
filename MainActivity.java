/*
  Copyright 2019 mirza baig

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
        limitations under the License.
*/




package com.seahawk.hello_cmake;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity
{

    private MyStructure myStructure;
    private String strcallback;
    private String strcallbackfromworkerthread = "Callback from worker thread";

    // Used to load the 'native-lib' library on application startup.
    static
    {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        myStructure = stringFromJNI();

        // Example of a call to a native method
        TextView tvk = (TextView) findViewById(R.id.textviewk);
        tvk.setText("from C:" +myStructure.k);

        TextView tvinsidek = (TextView) findViewById(R.id.textviewinsidek);
        tvinsidek.setText("from C:" +myStructure.insideMyStructure.insidek);
    }

    //callback from c++ native-lib.cpp
    public void callback()
    {
        strcallback = "from Java callback:";
    }

    //callback From worker thread in native-lib.cpp
    public void callbackFromWorkerThread()
    {
        setContentView(R.layout.activity_main);
        TextView tvfromdifferentthread = (TextView)findViewById(R.id.textviewfromdifferentthread);
        TextView tvcallback = (TextView)findViewById(R.id.textviewcallback);
        tvfromdifferentthread.setText(strcallbackfromworkerthread);
        tvcallback.setText(strcallback);
    }


    @Override
    protected void onStart()
    {
        super.onStart();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
    }


    @Override
    protected void onPause()
    {
        super.onPause();
    }

    @Override
    protected void onStop()
    {
        super.onStop();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */

    public native MyStructure stringFromJNI();
}