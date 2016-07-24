package cliente;

import java.net.Socket;

import servidor.Servidor;
import socket.ThreadConexao;
import eventos.ClienteConexaoListener;
import eventos.RecebeInformacaoListener;

public class Cliente {

	private volatile Socket socket;
	private RecebeInformacaoListener informacaoListener;
	private ThreadConexao threadConexao;
	
	public Cliente(RecebeInformacaoListener informacaoListener) {
		this.informacaoListener = informacaoListener;
	}
	
	public void iniciaConexao(String ip, int porta, ClienteConexaoListener conexaoListener){
		new Thread(new Runnable() {
			
			@Override
			public void run() {
				try{
					socket = new Socket(ip,porta);
					if(conexaoListener != null){
						conexaoListener.onClienteConectado();
					}

					threadConexao = new ThreadConexao(socket, Servidor.terminoDaMensagem, informacaoListener);
					threadConexao.start();
				}
				catch(Exception e){
					if(conexaoListener != null){
						conexaoListener.onErroConexao();
					}
				}
			}
		}).start();
	}
	
	public boolean enviarMensagem(String mensagem){
		try{
			threadConexao.enviarMensagem(mensagem);
			return true;
		}catch(Exception e){
			return false;
		}
	}
}
