package com.example.marius.test;

/**
 * Created by marius on 7/7/17.
 */

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

import static com.example.marius.test.MainActivity.client;

public class SectionsPagerAdapter extends FragmentPagerAdapter {

    public SectionsPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int i) {
        switch (i) {
            case 0:
                return MusicMode.newInstance();
            case 1:
                return Patterns.newInstance();
            case 2:
                return ManualControl.newInstance();
        }
        return null;

    }

    @Override
    public int getCount() {
        // TODO Auto-generated method stub
        return 3; //No of Tabs
    }

}