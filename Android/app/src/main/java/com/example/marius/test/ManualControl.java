package com.example.marius.test;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import com.madrapps.pikolo.HSLColorPicker;
import com.madrapps.pikolo.listeners.SimpleColorSelectionListener;
import com.yahoo.mobile.client.android.util.rangeseekbar.RangeSeekBar;

import static com.example.marius.test.MainActivity.client;

public class ManualControl extends Fragment {

    private HSLColorPicker colorPicker;
    private RangeSeekBar rangeSeekBar;
    int minVal = 0, maxVal = 0, histCol = 0;

    public static ManualControl newInstance () {
        ManualControl fragment = new ManualControl();
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View ManualControl = inflater.inflate(R.layout.activity_manual_control, container, false);


        rangeSeekBar = ManualControl.findViewById(R.id.rangeBar);
        // Set the range
        rangeSeekBar.setRangeValues(0, 59);
        rangeSeekBar.setNotifyWhileDragging(true);
        rangeSeekBar.setOnRangeSeekBarChangeListener(new RangeSeekBar.OnRangeSeekBarChangeListener<Integer>() {

            @Override
            public void onRangeSeekBarValuesChanged(RangeSeekBar<?> bar, Integer minValue, Integer maxValue) {
                if (minValue != minVal || maxValue != maxVal) {
                    final String values = 'L' + String.valueOf(minValue) + '\n' + String.valueOf(maxValue) + '\n';
                    client.send(values);
                    //ctrlStateOutgoing.put(values, null);
                    System.out.print(values);
                    minVal = minValue;
                    maxVal = maxValue;
                }
            }
        });

        colorPicker = ManualControl.findViewById(R.id.colorPicker);
        colorPicker.setColorSelectionListener(new SimpleColorSelectionListener() {
            @Override
            public void onColorSelected(int color) {
                if (histCol != color) {
                    final String hexColor = 'H' + String.format("0x%06X", (0xFFFFFF & color)) + '\n';
                    client.send(hexColor);
                    histCol = color;
                }
            }
        });
        return ManualControl;
    }
}
