package com.example.marius.test;

import android.os.AsyncTask;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class SocketClient extends AsyncTask<Void, Void, Void> {

    String message;

    SocketClient(String msg) {
        message = msg;
    }

    @Override
    protected Void doInBackground(Void... arg0) {

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
        return null;
    }

    @Override
    protected void onPostExecute(Void result) {

    }

}
