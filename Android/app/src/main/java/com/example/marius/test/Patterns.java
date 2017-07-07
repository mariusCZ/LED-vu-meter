package com.example.marius.test;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListView;
import android.widget.Toast;

import static com.example.marius.test.MainActivity.client;

public class Patterns extends Fragment {

    public static Patterns newInstance () {
        Patterns fragment = new Patterns();
        return fragment;
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                            Bundle savedInstanceState) {

        final View Patterns = inflater.inflate(R.layout.activity_patterns, container, false);
        String[] myItems = new String[]{"Rainbow", "Confetti", "Cylon", "Juggle", "Mood Light", "Rain", "Manual Control"};

        ArrayAdapter<String> adapter = new ArrayAdapter<String> (getContext(),  R.layout.list, myItems);

        ListView list = Patterns.findViewById(R.id.listView);
        list.setAdapter(adapter);
        list.setFadingEdgeLength(5);
        list.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View viewClicked, int position, long id) {
                // TODO Auto-generated method stub
                Toast.makeText(getContext(), String.valueOf(position), Toast.LENGTH_SHORT).show();
            }
        });
        return Patterns;
    }
}


