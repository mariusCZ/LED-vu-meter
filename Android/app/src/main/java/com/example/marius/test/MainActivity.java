package com.example.marius.test;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

//import static com.example.marius.test.R.id.button3;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }


    public void musicMode(View view) {
        //mClient.run();
        Intent intent = new Intent(this, MusicMode.class);
        startActivity(intent);
    }
    public void manualControl(View view) {
        Intent intent = new Intent(this, ManualControl.class);
        startActivity(intent);
    }
    public void patterns(View view) {
        Intent intent = new Intent(this, Patterns.class);
        startActivity(intent);
    }
}

