package com.example.marius.test;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.ToggleButton;

import static com.example.marius.test.MainActivity.client;

//import static com.example.marius.test.MainActivity.client;

public class MusicMode extends Fragment implements AdapterView.OnItemSelectedListener {

    public static MusicMode newInstance () {
        MusicMode fragment = new MusicMode();
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                            Bundle savedInstanceState) {
        View MusicMode = inflater.inflate(R.layout.activity_music_mode, container, false);
        populateSpinner(MusicMode);
        /*
        final Button button = MusicMode.findViewById(R.id.button2);
        button.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // do something
                client.send(toString().button.getTag());
            }
        });
        Button button2 = MusicMode.findViewById(R.id.button3);
        button2.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                // do something
            }
        });
        */

        Button sendButton = MusicMode.findViewById(R.id.sendButton);
        sendButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                EditText[] mEdit = {getView().findViewById(R.id.redVal), getView().findViewById(R.id.redDecay), getView().findViewById(R.id.greenVal),
                        getView().findViewById(R.id.greenDecay), getView().findViewById(R.id.blueVal), getView().findViewById(R.id.blueDecay)};
                ToggleButton[] toggle = {getView().findViewById(R.id.redToggle), getView().findViewById(R.id.greenToggle), getView().findViewById(R.id.blueToggle)};
                String message = "C";
                int i = 0;
                while (i < 6) {
                    message = message + mEdit[i].getText().toString() + '\n';
                    message = message + mEdit[i + 1].getText().toString() + '\n';
                    if (toggle[i / 2].isChecked()) message = message + '1' + '\n';
                    else message = message + '0' + '\n';
                    i = i + 2;
                }
                client.send(message);
            }
        });
        return MusicMode;
    }

    private void populateSpinner (View view) {
        Spinner spinner = view.findViewById(R.id.spinnerMusic);
        // Create an ArrayAdapter using the string array and a default spinner layout
        spinner.setOnItemSelectedListener(this);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(getContext(), R.array.choices, android.R.layout.simple_spinner_item);
        // Specify the layout to use when the list of choices appears
        adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        // Apply the adapter to the spinner
        spinner.setAdapter(adapter);
    }

    public void onItemSelected(AdapterView<?> parent, View view,
                               final int pos, long id) {
        // An item was selected. You can retrieve the selected item using
        parent.getItemAtPosition(pos);
        //EditText editText = (EditText) findViewById(R.id.editText);
        String text = "P" + String.valueOf(pos) + '\n';
        client.send(text);
    }

    public void onNothingSelected(AdapterView<?> parent) {
        // Another interface callback
    }

}

