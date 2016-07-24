package up.interface_casa;

import android.os.Handler;
import android.os.Message;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

/**
 * Created by aluno on 19/07/2016.
 */
public class Connection extends Thread {
    private Socket socket;
    private boolean conected;
    private Handler handler;

    public Connection(Socket socket, Handler handler)
    {
        this.socket = socket;
        this.handler = handler;
        conected = true;
    }
    @Override
    public void run()
    {
        super.run();
        try
        {
            InputStream inputStream = socket.getInputStream();
            while(conected)
            {
                if(inputStream.available() > 0)
                {
                    byte[] bytes = new byte[1024];
                    inputStream.read(bytes);
                    String message = new String(bytes);

                    Message _message = new Message();
                    _message.obj = message;
                    handler.sendMessage(_message);
                }
                Thread.sleep(50);
            }
        }
        catch (Exception e)
        {
            conected = false;
        }
    }

    public boolean Send_Data(String message)
    {
        try
        {
            OutputStream outputStream = socket.getOutputStream();
            outputStream.write(message.getBytes());
            outputStream.flush();
            return true;
        }
        catch (Exception e)
        {
            conected = false;
            return false;
        }
    }
    public void SetConnection(boolean conected)
    {
        this.conected=conected;
    }
}
