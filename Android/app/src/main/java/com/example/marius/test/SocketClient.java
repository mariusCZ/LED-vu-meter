package com.example.marius.test;

import java.io.BufferedOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.InetSocketAddress;
import java.net.Socket;

public class SocketClient {
    private Socket socket;
    //private OutputStream socketOutput;
    private BufferedOutputStream bos;

    private String ip;
    private int port;
    private ClientCallback listener=null;

    public SocketClient(String ip, int port){
        this.ip=ip;
        this.port=port;
    }

    public void connect(){
        new Thread(new Runnable() {
            @Override
            public void run() {
                socket = new Socket();
                InetSocketAddress socketAddress = new InetSocketAddress(ip, port);
                try {
                    socket.setTcpNoDelay(true);
                    socket.connect(socketAddress);
                    //socketOutput = socket.getOutputStream();
                    bos = new BufferedOutputStream(socket.getOutputStream());

                    if(listener!=null)
                        listener.onConnect(socket);
                } catch (IOException e) {
                    if(listener!=null)
                        listener.onConnectError(socket, e.getMessage());
                }
            }
        }).start();
    }

    public void disconnect(){
        try {
            socket.close();
        } catch (IOException e) {
            if(listener!=null)
                listener.onDisconnect(socket, e.getMessage());
        }
    }

    public void send(final String message) {
        try {
            bos.write(message.getBytes());
            bos.flush();
        } catch (IOException e) {
            if(listener!=null)
                listener.onDisconnect(socket, e.getMessage());
        }
    }

    public void setClientCallback(ClientCallback listener){
        this.listener=listener;
    }

    public void removeClientCallback(){
        this.listener=null;
    }

    public interface ClientCallback {
        void onConnect(Socket socket);
        void onDisconnect(Socket socket, String message);
        void onConnectError(Socket socket, String message);
    }
}

/*
import android.os.AsyncTask;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;

public class SocketClient extends AsyncTask<Void, Void, Void> {

    String message;
    Socket s;
    OutputStream out;
    PrintWriter output;
    Boolean running;

    SocketClient(String msg, Boolean run) {
        message = msg;
        running = run;
    }

    @Override
    protected Void doInBackground(Void... arg0) {
        if(running) {
            try {
                //Replace below IP with the IP of that device in which server socket open.
                //If you change port then change the port number in the server side code also.
                s = new Socket("192.168.1.96", 3000);

                out = s.getOutputStream();

                output = new PrintWriter(out);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        output.print(message);
        output.flush();
        //output.close();
        //out.close();
        //s.close();
        return null;
    }

    @Override
    protected void onPostExecute(Void result) {

    }

}
*/