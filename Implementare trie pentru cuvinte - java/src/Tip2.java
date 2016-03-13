public class Tip2 implements TrieElement {
	String word;

	/**
	 * metoda care returneaza cuvantul fara caracterele speciale
	 */
	@Override
	public char[] toCharArray() {
		char aux[] = word.toCharArray();
		int j = 0 ;
		for(int i = 0 ; i < aux.length; i ++)
		{
			if(aux[i] == '-' || aux[i] == '_' || aux[i] == ')' || aux[i] == '(')
				continue;
			j++;
		} 
		char rez[] = new char[j];
		j=0;
		for(int i = 0 ; i < aux.length; i ++)
		{
			if(aux[i] == '-' || aux[i] == '_' || aux[i] == ')' || aux[i] == '(')
				continue;
			rez[j++] = aux[i];
		} 
		return rez;
	}
}

