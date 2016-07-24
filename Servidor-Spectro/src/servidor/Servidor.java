package servidor;

import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

import eventos.RecebeInformacaoListener;
import eventos.SevidorConexaoListener;
import socket.ThreadConexao;

public class Servidor {
	
	private ArrayList<ThreadConexao> conexoes;
	private Thread conexaoServidor;
	public static String terminoDaMensagem = "#";
	private int porta;
	private RecebeInformacaoListener informacaoListener;
	
	private SevidorConexaoListener conexaoListener;
	
	public void iniciaServidor(int tempoAguardoClientesSegundos, int porta,
			SevidorConexaoListener conexaoListener,RecebeInformacaoListener informacaoListener ){
		
		this.informacaoListener = informacaoListener;
		this.conexaoListener = conexaoListener;
		this.porta = porta;
		conexoes = new ArrayList<ThreadConexao>();
		ThreadRunnableControle controle = new ThreadRunnableControle();
		conexaoServidor = new Thread(controle);
		conexaoServidor.start();
		
		/*new Thread(new Runnable() {
			
			@Override
			public void run() {
				for(int count = 0; count <=  tempoAguardoClientesSegundos ; count++){
					count++;
					try {
						Thread.sleep(1000);
					} catch (InterruptedException e) {
					}					
				}
				try {
					controle.encerrar();
					conexaoServidor.join();
					
					if(conexaoListener != null){
						conexaoListener.onTempoConexaoTerminado();
					}
				} catch (Exception e) {}
			}
		}).start();*/
	}
	
	private class ThreadRunnableControle implements Runnable{

		private volatile boolean execucao = true;
		
		public void encerrar(){
			execucao = false;
		}
		
		@Override
		public void run() {
			try {
				ServerSocket servidor = new ServerSocket(porta);
				while(execucao){
					Socket cliente = servidor.accept();
					ThreadConexao conexao = new ThreadConexao(cliente, terminoDaMensagem,informacaoListener);
					conexao.start();
					if(conexaoListener != null){
						conexaoListener.onNovoClienteConectado(
								cliente.getRemoteSocketAddress().toString());
					}
					conexoes.add(conexao);
				}
				
				servidor.close();
				
			} catch (Exception e) {

			}
		}
	}
	
	public boolean enviarMensagem(String cliente, String mensagem){
		for(ThreadConexao conexao : conexoes){
			if(conexao.getConexaoNome().equals(cliente)){
				return conexao.enviarMensagem(mensagem);
			}
		}
		return false;
	}
}
