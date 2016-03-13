public class Arbore implements AbstractTrie {
	Nod start = new Nod();
	Functii fx = new Functii();
	@Override
	public void add(TrieElement element) {
		String word ; 
		char[] path ;
		Nod var = start;
		int way;
		/**
		 * Parcurg arborele iterativ si adaug noduri noi,daca este nevoie
		 * + transform caracterele in indice pentru muchii
		 */
		if(element instanceof Tip1)
		{
			word = ((Tip1) element).word;
			path = ((Tip1) element).toCharArray();
		}
		else
		{
			word = ((Tip2) element).word;
			path = ((Tip2) element).toCharArray();
		}
		for ( int i = 0 ; i < path.length;  i ++)
		{
			way = fx.intreg(path[i]); // pe ce subarbore cobor la pasul i
			if(var.fiu[way] == null)
				var.fiu[way] = new Nod();
			var = var.fiu[way];
		}
		var.nr ++;
		var.word  = new String(fx.sir_lexicografic(var.word, word));
	}

	@Override
	public int count(TrieElement element) {
		/** 
		 * caut nodul in mod iterativ si afisez nod.contor
		 */
		char [] path = element.toCharArray();
		Nod var = start;
		int way;
		for(int i = 0 ; i < path.length ; i ++)
		{
			if(var == null ) return 0;
			way = fx.intreg(path[i]);
			var = var.fiu[way];
		}
		if(var == null ) return 0;
		return var.nr;
	}

	@Override
	public void remove(TrieElement element) {
		/**
		 * caut nodul iterativ si ii decrementez contorul
		 */
		char [] path = element.toCharArray();
		Nod var = start;
		int way;
		for(int i = 0 ; i < path.length ; i ++)
		{
			if(var == null ) return ;
			way = fx.intreg(path[i]);
			var = var.fiu[way];
		}
		if(var == null ) return;
		if(var.nr > 0 ) var.nr -- ;
		if(var.nr == 0 ) var.word = null;
	}

	@Override
	public TrieElement[] getSortedElements(TrieElement prefix) {
		/**
		 * caut prefixul in mod iterativ;
		 * returnez un vector cu toti subarborii prefixului in mod recursiv
		 */
		TrieElement [] vector = new TrieElement[500040];
		int way;
		Nod var = start;
		char [] path  = prefix.toCharArray();
		for(int i = 0 ; i < path.length ; i ++)
		{
			way = fx.intreg(path[i]);
			if(var == null) return vector;
			var = var.fiu[way];
		}
		poz = 0 ;
		recursiv_sorted_el(var,vector);
		return vector;
	}
	private int poz ;
	public void recursiv_sorted_el(Nod var, TrieElement[] vector)
	{   /**
		* Partea recursiva a metodei getsortedelements();
		*/
		if(var == null ) return;
		if(var.nr > 0 ) {
			vector[poz++] = var;
		}
		for(int i = 0 ; i < 74 ; i ++)
		{
			recursiv_sorted_el(var.fiu[i],  vector);
		}
	}

}
