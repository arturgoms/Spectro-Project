package eventos;

public interface RecebeInformacaoListener {
	public void onMensagemRecebida(String identificador,String mensagem);
	public void onErroConexao();
}
