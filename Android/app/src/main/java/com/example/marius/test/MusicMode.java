package com.example.marius.test;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.EditText;
import android.widget.Spinner;
import android.widget.Toast;
import android.widget.ToggleButton;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

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
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                //EditText editText = (EditText) findViewById(R.id.editText);
                String text = "P" + String.valueOf(pos);
                try {
                    //Replace below IP with the IP of that device in which server socket open.
                    //If you change port then change the port number in the server side code also.
                    Socket s = new Socket("192.168.1.96", 3000);

                    OutputStream out = s.getOutputStream();

                    PrintWriter output = new PrintWriter(out);

                    //String message = .toString();

                    output.print(text);
                    output.flush();
                    output.close();
                    out.close();
                    s.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
    }

    public void onNothingSelected(AdapterView<?> parent) {
        // Another interface callback
    }

    public void startMusic (View view) {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                //EditText editText = (EditText) findViewById(R.id.editText);
                try {
                    //Replace below IP with the IP of that device in which server socket open.
                    //If you change port then change the port number in the server side code also.
                    Socket s = new Socket("192.168.1.96", 3000);

                    OutputStream out = s.getOutputStream();

                    PrintWriter output = new PrintWriter(out);

                    //String message = .toString();

                    output.print("m");
                    output.flush();
                    output.close();
                    out.close();
                    s.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
    }

    public void sendColors (View view) {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
                EditText[] mEdit = {(EditText)findViewById(R.id.redVal), (EditText)findViewById(R.id.redDecay), (EditText)findViewById(R.id.greenVal),
                        (EditText)findViewById(R.id.greenDecay), (EditText)findViewById(R.id.blueVal), (EditText)findViewById(R.id.blueDecay)};
                ToggleButton[] toggle = {(ToggleButton)findViewById(R.id.redToggle), (ToggleButton)findViewById(R.id.greenToggle), (ToggleButton)findViewById(R.id.blueToggle)};
                String message = "C";
                int i = 0;
                while (i < 6) {
                    message = message + mEdit[i].getText().toString() + '\n';
                    message = message + mEdit[i + 1].getText().toString() + '\n';
                    if (toggle[i / 2].isChecked()) message = message + '1' + '\n';
                    else message = message + '0' + '\n';
                    i = i + 2;
                }
                try {
                    //Replace below IP with the IP of that device in which server socket open.
                    //If you change port then change the port number in the server side code also.
                    Socket s = new Socket("192.168.1.96", 3000);

                    OutputStream out = s.getOutputStream();

                    PrintWriter output = new PrintWriter(out);

                    //String message = .toString();

                    output.print(message);
                    output.flush();
                    output.close();
                    out.close();
                    s.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
    }
}

