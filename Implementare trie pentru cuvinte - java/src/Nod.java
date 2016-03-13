public class Nod implements TrieElement{
	String word;
	int nr;
	Nod fiu[] = new Nod[75];
	@Override
	public char[] toCharArray() {
		return word.toCharArray();
	}

}
