package up.interface_casa;

import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.net.Socket;

public class MainActivity extends AppCompatActivity {

    private Button send_btn;
    private EditText send_txt;
    private TextView data_txt;
    private RadioGroup radioGroup;
    private Connection connection;

    private final static int PORTA = 1234;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        send_btn = (Button) findViewById(R.id.activity_main_send_btn);
        send_txt = (EditText) findViewById(R.id.activity_main_send_txt);
        data_txt = (TextView) findViewById(R.id.activity_main_data_txt);
        radioGroup = (RadioGroup) findViewById(R.id.main_activity_radio_group);

        new Thread(new Runnable() {
            @Override
            public void run() {
                try
                {
                    Socket socket = new Socket("192.168.132.106", PORTA);
                    connection = new Connection(socket,actualization_handler);
                    connection.start();
                    connection.Send_Data("android#");
                    Toast_Message("Conectado");
                }
                catch(Exception e)
                {
                    Toast_Message("Erro de Conexão");
                }
            }
        }).start();

        send_btn.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v)
            {
                String temp="";
                switch (radioGroup.getCheckedRadioButtonId())
                {
                    case R.id.main_activity_casa_1_btn:
                        temp = "0-" + send_txt.getText().toString()+"#";
                        break;
                    case R.id.main_activity_casa_2_btn:
                        temp = "1-" + send_txt.getText().toString()+"#";
                        break;
                }
                connection.Send_Data(temp);
                send_txt.setText("");
            }
        });
    }

    private Handler actualization_handler = new Handler(Looper.myLooper())
    {
        @Override
        public  void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            String string = (String)msg.obj;
            data_txt.setText(data_txt.getText() + "\n" + string);
        }
    };

    private Handler handler = new Handler(Looper.myLooper()){
        @Override
        public void handleMessage(Message msg)
        {
            super.handleMessage(msg);
            String str = (String) msg.obj;
            Toast.makeText(MainActivity.this,str,Toast.LENGTH_SHORT).show();
        }
    };

    private void Toast_Message(final String message)
    {
        Message _message = new Message();
        _message.obj=message;
        handler.sendMessage(_message);
    }
}
