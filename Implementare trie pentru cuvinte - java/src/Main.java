
public class Main {
	public static void main(String args[])
	{
		/**
		 * Citesc datele cu testreader / testwriter
		 * Tratez problema in doi arbori diferiti; dupa prelucrarea primului arbore,eliberez complet memoria si tratez al 2lea arbore
		 * Diferenta dintre arbori e la nivelul metodei tochararray() din cele 2 clase care implementeaza TrieElmeent (tip1,tip2)
		 */
		//creez testreader pentru a citi datele
		TestReader read = new TestReader("trie.in");
		TestWriter write = new TestWriter("trie.out");
		String[] cuv= read.getWords();
		Command[] mod = read.getFirstCommands();
		Tip1 var = new Tip1();
		Arbore trie = new Arbore();
		for(int i =0 ; i < cuv.length ; i ++)
		{
			//inserez primul rand de cuvinte in trie
			var.word = cuv[i];
			trie.add(var);
		}
		for(int i = 0 ; i < mod.length ; i++)
		{
			switch (mod[i].type)
			{
			case 0 :
				var.word = mod[i].word;
				trie.add(var);
				break;
			case 1 :
				var.word = mod[i].word;
				trie.remove(var);
				break;
			case 2 :
				var.word = mod[i].word;
				write.printCount(trie.count(var));
				break;
			case 3 : 
				var.word = mod[i].word;
				write.printSortedWords(trie.getSortedElements(var));
				break;
			}
		}
		//pregatesc datele pentru al 2lea trie ; eliberez memoria dupa
		Tip2 var2 = new Tip2();
		trie = new Arbore();
		mod = read.getSecondCommands();
		System.gc();
		for(int i =0 ; i < cuv.length ; i ++)
		{
			var2.word = cuv[i];
			trie.add(var2);
		}
		for(int i = 0 ; i < mod.length ; i++)
		{
			switch (mod[i].type)
			{
			case 0 :
				var2.word = mod[i].word;
				trie.add(var2);
				break;
			case 1 :
				var2.word = mod[i].word;
				trie.remove(var2);
				break;
			case 2 :
				var2.word = mod[i].word;
				write.printCount(trie.count(var2));
				break;
			case 3 : 
				var2.word = mod[i].word;
				write.printSortedWords(trie.getSortedElements(var2));
				break;
			}
		}
		write.close();
	}
}
