package eventos;

public interface SevidorConexaoListener {
	public void onNovoClienteConectado(String nome);
	public void onTempoConexaoTerminado();
}
