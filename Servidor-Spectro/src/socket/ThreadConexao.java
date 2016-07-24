package socket;

import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;

import eventos.RecebeInformacaoListener;

public class ThreadConexao extends Thread{
	
	private String conexaoNome;
	private Socket socket;
	private String terminoMensagem;
	private boolean connected;
	private String mensagem;
	private RecebeInformacaoListener informacaoListener;
	
	public ThreadConexao(Socket socket,String terminoMensagem,RecebeInformacaoListener informacaoListener) {
		this.socket = socket;
		if(socket!= null){
			conexaoNome = socket.getRemoteSocketAddress().toString();
		}
		this.terminoMensagem = terminoMensagem;
		mensagem = "";
		
		this.informacaoListener = informacaoListener;
		this.connected = true;
	}
	
	@Override
	public void run() {
		
		while(connected){
			
			try{
				InputStream fluxoEntrada = socket.getInputStream();
				while(fluxoEntrada.available() > 0){
					
					String caracter =  String.valueOf((char)fluxoEntrada.read());
					
					if(caracter.equals(terminoMensagem)){
						
						if(informacaoListener != null){
							informacaoListener.onMensagemRecebida(
									socket.getRemoteSocketAddress().toString(),mensagem);
						}		
						mensagem = "";
					}else{
						mensagem = mensagem + caracter;
					}	
				}
				
			}catch(Exception e){
				break;
			}
		}
	}

	public String getConexaoNome() {
		return conexaoNome;
	}

	public void setConexaoNome(String conexaoNome) {
		this.conexaoNome = conexaoNome;
	}

	public boolean isConnected() {
		return connected;
	}

	public void setConnected(boolean connected) {
		this.connected = connected;
	}
	
	public boolean enviarMensagem(String mensagem){
		
		try{
			OutputStream fluxoSaida = socket.getOutputStream();
			fluxoSaida.write(mensagem.getBytes());
			fluxoSaida.flush();
			return true;
		}catch(Exception e){
			return false;
		}	
	}
}
