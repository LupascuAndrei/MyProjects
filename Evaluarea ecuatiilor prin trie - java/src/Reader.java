import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Reader {
	public BufferedReader reader;
	public String linie = null;
	public char[] linie_char;
	public int paranteze;
	public int i = 0; // indice linie curenta
	/**
	 * citeste fisier si returneaza
	 * @param input - fisier de intrare
	 * @throws FileNotFoundException
	 */
	public Reader(String input) throws FileNotFoundException
	{
		FileReader fis = new FileReader(input);
		reader =  new BufferedReader(fis);
	}
	/**
	 * citeste o linie noua si o salveaza in String linie
	 * @return true daca am citit ultima linie din fisier;
	 * @throws IOException
	 */
	public Boolean endOfFile() throws IOException
	{
		linie = reader.readLine();
		if(linie == null ) return true;
		linie_char = linie.toCharArray();
		return false ;
	}
	/** 
	 * @return (pozitia i este ultima din sirul citit)
	 */
	public Boolean endOfLine()
	{
		return i == linie_char.length ;
	}
	/**
	 * reseteaza indicele de parcurgere si elibereaza memoria ocupata de arbore 
	 * utilitate - citeste linie noua 
	 */
	public void reset()
	{
		i=0; //indice pentru citire
		System.gc();
	}
	/**
	 * citeste "(((..." , variabila , ")))..."
	 * @return urmatoarea variabila citita parsat
	 */
	public String readNextWord()
	{
		String to_return = null;
		paranteze = 0;
		while (i < linie_char.length && linie_char[i] == '(') {
			paranteze++;
			i++;
		}
		if (i == linie_char.length)
			return null;
		if (linie_char[i] >= '0' && linie_char[i] <= '9')
			to_return = readConst();
		else if ((linie_char[i] >= 'a' && linie_char[i] <= 'z')
				|| (linie_char[i] >= 'A' || linie_char[i] <= 'Z'))
			to_return = readVariable();
		while (i < linie_char.length && linie_char[i] == ')') {
			paranteze--;
			i++;
		}
		return to_return;
	}
	/**
	 * avanseaza indicele i si citeste operatorul curent
	 * @return operatorul citit
	 */
	public char readOperator()
	{
		if(linie_char[i] == '-' || linie_char[i] == '+' || linie_char[i] == '*' 
		|| linie_char[i] == ':' || linie_char[i] == '?' || linie_char[i] == '>'
		|| linie_char[i] == '=')
		{
			i++;
			return linie_char[i-1];
		}
		return 0;
	}
	/**
	 * citeste parsat un sir de numere si il returneaza sub forma de string
	 * @return numar - string
	 */
	public String readConst() {
		char [] aux = new char [40];
		int pas = 0;
		while(i<linie_char.length)
		{
			if(linie_char[i] <'0' || linie_char[i] > '9')
				break;
			aux[pas++] = linie_char[i++];
		}
		// aloc memorie pentru numarul citit pentru a-l returna
		char [] fin = new char [pas];
		for(int j = 0 ; j < pas ; j ++)
			fin[j]=aux[j];
		return String.valueOf(fin);
	}
	/**
	 * citeste parsat o variabila si o returneaza sub forma de string
	 * analog readConst()
	 * @return cuvant - string
	 */
	public String readVariable()
	{
		char[] aux = new char[40];
		int pas = 0;
		while (i < linie_char.length) {
			if (!((linie_char[i] >= '0' && linie_char[i] <= '9' ) || (linie_char[i] >='a' && linie_char[i] <= 'z') || 
					(linie_char[i] >='A' && linie_char[i] <='Z')))
				break;
			aux[pas++] = linie_char[i++];
		}
		char[] fin = new char[pas];
		for (int j = 0; j < pas; j++)
			fin[j] = aux[j];
		return String.valueOf(fin);
	}
	/**
	 * 
	 * @param word - string ( variabila sau constanta)
	 * @return TRUE daca WORD incepe cu o litera (daca e variabila)
	 */
	public Boolean checkVariable(String word)
	{
		char aux[] = word.toCharArray();
		return (aux[0] >='a' && aux[0]<='z') || (aux[0] >='A' && aux[0] <= 'Z');
	}
}
