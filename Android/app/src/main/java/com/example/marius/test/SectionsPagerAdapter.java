package com.example.marius.test;

/**
 * Created by marius on 7/7/17.
 */

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

public class SectionsPagerAdapter extends FragmentPagerAdapter {

    public SectionsPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    @Override
    public Fragment getItem(int i) {
        switch (i) {
            case 0:
                return ManualControl.newInstance();
            case 1:
                return Patterns.newInstance();
            case 2:
                return MusicMode.newInstance();
        }
        return null;

    }

    @Override
    public int getCount() {
        // TODO Auto-generated method stub
        return 3; //No of Tabs
    }

    @Override
    public CharSequence getPageTitle(int position) {
        switch (position) {
            case 0:
                return "Manual Control";
            case 1:
                return "Patterns";
            case 2:
                return "Music Mode";
        }
        return null;
    }
}