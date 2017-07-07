package com.example.marius.test;

import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;

public class MainActivity extends FragmentActivity {
    private SectionsPagerAdapter mSectionsPagerAdapter;

    public static SocketClient client = new SocketClient("192.168.1.96", 3000);

    private ViewPager mViewPager;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mSectionsPagerAdapter = new SectionsPagerAdapter(getSupportFragmentManager());

        // Set up the ViewPager with the sections adapter.
        mViewPager = findViewById(R.id.container);
        mViewPager.setAdapter(mSectionsPagerAdapter);
    }

    @Override
    protected void onStart () {
        client.connect();
        super.onStart();
    }

    @Override
    protected void onPause () {
        client.disconnect();
        super.onPause();
    }

}

