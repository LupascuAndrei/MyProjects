public class Tip1 implements TrieElement {
	String word;

	/**
	 * metoda care returneaza cuvantul convertit in caractere lowercase
	 */
	@Override
	public char[] toCharArray() {
		return word.toLowerCase().toCharArray();
	}
}
