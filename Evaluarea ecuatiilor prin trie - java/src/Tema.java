import java.io.FileNotFoundException;
import java.io.IOException;


public class Tema {
	public static void main(String args[]) throws IOException
	{
		Reader input;
		//incerc sa citesc fisierul cu numele args[0]
		try {
			input = new Reader ( args[0]);
		} catch (FileNotFoundException e) {
			System.out.println("ERROR : FILE NOT FOUND");
			return;
		}
		//fisiere de output
		WriterEx13 w1 = new WriterEx13(args[0]  + "_pt");
		WriterEx2 w2 = new WriterEx2(args[0]  + "_sa");
		WriterEx13 w3 = new WriterEx13(args[0]  + "_ee");
		char op; // operator
		String word, first_word = null; // "buffer" pt cuvant
		ListaVar lista = new ListaVar(); //dictionar pentru variabile
		int eroare , linie = 0 , poz , valoare , ordin_multiplicator = 0;
		//tip de eroare,linie curenta, valoarea liniei (ex3) , nr paranteze deschise
		Arbore arb = new Arbore(w1); //arborele pentru fiecare linie
		Nod de_adaugat ;
		while(! input.endOfFile())
		{
			eroare = 0;
			linie ++;
			valoare = 0;
			while (!input.endOfLine()) 
			{
				if ((op = input.readOperator()) != 0)
				{
					//citesc operator
					de_adaugat = new Nod_Operator(op);
					de_adaugat.ord = ordinul_operatorului(op) + ordin_multiplicator * 10;
					arb.insert(de_adaugat);
				} 
				else 
				{
					//citesc cuvant
					word = input.readNextWord();
					de_adaugat = new Nod_Constanta();
					ordin_multiplicator += input.paranteze;
					// initializez campurile nodului nou creat
					de_adaugat.pr = input.paranteze;
					de_adaugat.val = valoare ; 
					de_adaugat.ord = 9999999; // valorile au prioritatea cea mai mica in arbore
					StructVar struct = new StructVar(0,word);
					if(first_word == null)
					{
						first_word = word;
						if(!input.checkVariable(first_word))
						{
							// primul cuvant nu e variabila
							eroare = 2;
							w2.write(linie,0,eroare); // afisez eroare la linia curenta pentru primul cuvant citit ( nu e variabila)
						}
						arb.insert(de_adaugat);
					}
					else
					{
						if(input.checkVariable(word) && eroare == 0 )
						{
							//caut cuvantul in dictionar
							poz = lista.search(struct);
							if(poz == -1)
							{
								//daca nu il gasesc,returnez celalalt tip de eroare
								eroare = 1;
								w2.write(linie, input.i - word.length(), eroare);
							}
							else
							{
								//salvez valoarea variabilei gasite in dictionar
								struct.val = lista.val(poz);
								de_adaugat.val = struct.val;
							}
						}
						if(!input.checkVariable(word))
							de_adaugat.val = Integer.valueOf(word);
						//adaug valoarea integer a cuvantului sau constantei citite in arbore
						arb.insert(de_adaugat);
					}
				}
			}
			if(eroare == 0 )
			{
				//nu a fost nicio eroare pe linia citita,afisez campurile respective
				int sol = arb.ValueofArb(arb.radacina.right);
				w2.write(0,0,0);//afiseaza "Ok!" pt cerinta 2
				StructVar t = new StructVar ( sol,first_word);
				w3.write(String.valueOf(sol));
				lista.add(t,lista.search(t));
			}
			else
				w3.write("error");
			first_word = null;
			//afisez arborele conform cerintei 1
			arb.define_type();
			arb.afiseaza();
			//resetez arborele si eliberez memoria
			arb = new Arbore(w1);
			input.reset();
			System.gc();
		}
		//lista.afis();
		w1.close();
		w2.close();
		w3.close();
	}
	/**
	 * @param operator - semnul operatorului
	 * @return - un ordin specific operatorului ( "*" > "+-" > "?:>" > "=")
	 */
	public static int ordinul_operatorului(char operator)
	{
		switch (operator) {
		case '=':
			return 1;
		case '>':
			return 2;
		case ':':
			return 2;
		case '?':
			return 2;
		case '+':
			return 3;
		case '-':
			return 3;
		case '*':
			return 4;
		default:
			System.out.println("EROARE SEMN " + operator);
			return -1;
		
		}
	}
}
