import java.util.ArrayList;
import java.util.Scanner;

import servidor.Servidor;
import eventos.RecebeInformacaoListener;
import eventos.SevidorConexaoListener;

public class Main {

	//private static final String ipServidor = "192.168.0.5";
	
	private static ArrayList<String> clientesAndroid;
	private static ArrayList<String> clientesRasp;	
	public static void main(String[] args) {
		clientesAndroid = new ArrayList<String>();
		clientesRasp = new ArrayList<String>();
		
		
		/*Cliente cliente = new Cliente(new RecebeInformacaoListener() {
			
			@Override
			public void onMensagemRecebida(String identificador, String mensagem) {
				System.out.println("Mensagem Recebida : " + mensagem);
			}
			
			@Override
			public void onErroConexao() {
				System.out.println("Erro de Conexão");
			}
		});
		
		cliente.iniciaConexao(ipServidor, 1234, new ClienteConexaoListener() {
			
			@Override
			public void onErroConexao() {
				System.out.println("Erro de Conexão");
			}
			
			@Override
			public void onClienteConectado() {
				System.out.println("Cliente Conectado :" + ipServidor);
			}
		});
		
		Scanner scan= new Scanner(System.in);
		while(true){
		    String text= scan.nextLine();
		    if(text.equals("sair")){
		    	scan.close();
		    	break;
		    }
			cliente.enviarMensagem(text);
		}*/
		
		Servidor servidor = new Servidor();
		servidor.iniciaServidor(10, 1234, new SevidorConexaoListener() {
			
			@Override
			public void onTempoConexaoTerminado() {
				System.out.println("Tempo Conexao Terminado");
				
			}
			
			@Override
			public void onNovoClienteConectado(String nome) {
				System.out.println("Cliente Conectado " + nome);
			}
		}, new RecebeInformacaoListener() {
			
			@Override
			public void onMensagemRecebida(String identificador, String mensagem) {
						
				System.out.println("Mensagem recebida de : " + identificador + " mensagem:" + mensagem);
									
				if (mensagem.contains("android")){
					clientesAndroid.add(identificador);
				}else if (mensagem.contains("pi")){
					clientesRasp.add(identificador);
				}else{
					//try{
						String[] mensagem1 = mensagem.split("-");
						//Scanner scan= new Scanner(System.in);
						if(clientesAndroid.contains(identificador))
						{
							int temp = Integer.parseInt(mensagem1[0].replace(" ",""));
							servidor.enviarMensagem(clientesRasp.get(temp), clientesAndroid.indexOf(identificador)+ "-" + mensagem1[1]+"#");
						}
						else
						{
							int temp = Integer.parseInt(mensagem1[0].replace(" ",""));
							servidor.enviarMensagem(clientesAndroid.get(temp), mensagem1[1]);
						}
					//}
					//catch(Exception e){}
				}
			}
			
			@Override
			public void onErroConexao() {
				System.out.println("Erro de Conexão");
				
			}
		});
		
		
		Scanner scan= new Scanner(System.in);
		while(true){
		    String text= scan.nextLine();
		    if(text.equals("sair")){
		    	scan.close();
		    	break;
		    }
		    
		    /*if(clienteIdentificado != null){
		    	servidor.enviarMensagem(clienteIdentificado,text);
		    }*/
		}
	}

}
