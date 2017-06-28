package com.example.marius.test;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.ToggleButton;

public class MusicMode extends AppCompatActivity implements AdapterView.OnItemSelectedListener {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_music_mode);
        Spinner spinner = (Spinner) findViewById(R.id.spinnerMusic);
        // Create an ArrayAdapter using the string array and a default spinner layout
        spinner.setOnItemSelectedListener(this);
        ArrayAdapter<CharSequence> adapter = ArrayAdapter.createFromResource(this, R.array.choices, android.R.layout.simple_spinner_item);
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
        String text = "P" + String.valueOf(pos);
        SocketClient myClient = new SocketClient(text);
        myClient.execute();
    }

    public void onNothingSelected(AdapterView<?> parent) {
        // Another interface callback
    }

    public void startMusic (View v) {
        Button b = (Button)v;
        String buttonText = b.getTag().toString();
        SocketClient myClient = new SocketClient(buttonText);
        myClient.execute();
    }

    public void sendColors (View view) {
        EditText[] mEdit = {(EditText)findViewById(R.id.redVal), (EditText)findViewById(R.id.redDecay), (EditText)findViewById(R.id.greenVal),
                (EditText)findViewById(R.id.greenDecay), (EditText)findViewById(R.id.blueVal), (EditText)findViewById(R.id.blueDecay)};
        ToggleButton[] toggle = {(ToggleButton)findViewById(R.id.redToggle), (ToggleButton)findViewById(R.id.greenToggle), (ToggleButton)findViewById(R.id.blueToggle)};
        String message = "C";
        int i = 0;
        while (i < 6) {
            message = message + mEdit[i].getText().toString() + 'n';
            message = message + mEdit[i + 1].getText().toString() + 'n';
            if (toggle[i / 2].isChecked()) message = message + '1' + 'n';
            else message = message + '0' + 'n';
            i = i + 2;
        }
        SocketClient myClient = new SocketClient(message);
        myClient.execute();
    }
}

