

public class Arbore {
	//fisier output pt cerinta 1
	private WriterEx13 file;
	public Nod radacina ;
	public Arbore(WriterEx13 x )
	{
		radacina = null;
		file = x;
	}
	/**
	 * inserez un nou nod in arbore
	 * @param x - nod de inserat
	 */
	public void insert(Nod x)
	{
		if(radacina == null)
		{
			radacina = x ;
			return;
		}
		// trebuie sa schimb nodul curent cu radacina?
		if(radacina.ord > x.ord)
		{
			x.left = radacina;
			radacina = x ;
			return ;
		}
		//parcurg recursiv arborele si adaug nodul unde ar trebui
		dfs_add(radacina,x);
	}
	/**
	 * adauga recursiv nodul x in arbore in partea dreapta a lui,la nivelul la care ordinul nodului este mai mic decat ordinul curent
	 * @param x - nod de adaugat
	 * @param arb - nodul curent din arbore
	 * @return 
	 */
	public void dfs_add(Nod arb,Nod x)
	{
		if(arb.left == null)
		{
			arb.left = x;
			return;
		}
		if(arb.right == null) 
		{
			arb.right = x;
			return;
		}
		if(arb.right.ord >= x.ord)
		{
			x.left = arb.right;
			arb.right = x;
			return;
		}
		dfs_add(arb.right,x);
	}
	/**
	 * cerinta 1)
	 */
	public void afiseaza()
	{
		dfs_afis(radacina);
	}
	/**
	 * pentru fiecare numar mai mic decat lungimea maxima a arborelui,apelez dfs_afis(nod,int,int)
	 * @param x
	 */
	public void dfs_afis(Nod x)
	{
		for(int i = 0; dfs_afis(radacina,i,0); i++) 
			file.out.println();
		file.out.println();
	}
	/**
	 * afisez arborele in mod recursiv pana la adancimea LUNG atinsa pentru cerinta 1
	 * @param x - nod
	 * @param lung - adancimea maxima de atins
	 * @param pas - adancimea curenta atinsa in recursivitate
	 * @return -  TRUE daca LUNG > lungimea maxima a arborelui
	 */
	public Boolean dfs_afis(Nod x, int lung , int pas )
	{
		if(x==null) return false;
		if(pas == lung && x.left != null )
		{
			file.out.print(x.expresie() + " ");
			return true;
		}
		Boolean aux1 = dfs_afis(x.left,lung,pas+1);
		file.out.print(x+ " "); // metoda toString salvata de nod
		Boolean aux2 = dfs_afis(x.right,lung,pas+1);
		return aux1 == true || aux2 == true; // LUNG > lungimea maxima a arborelui?
	}
	public void define_type()
	{
		dfs_define(radacina);
	}
	/**
	 * specifica tipul subarborilor unui nod in functie de tipul operatorului salvat de nod ( Ternar , Factor , Termen etc)
	 * @param x - nod
	 */
	public void dfs_define(Nod x)
	{
		if(x.left == null )
			return;
		x.tip = x.operator;
		x.left.tip = operatorTip(x.operator);
		x.right.tip = operatorTip(x.operator);
		//cobor in recursivitate
		dfs_define(x.left);
		dfs_define(x.right);
	}
	/**
	 * 
	 * @param operator caracterul citit
	 * @return operatorul transformat intr-un caracter specific cerintei 2
	 */
	public char operatorTip(char operator)
	{
		switch (operator) {
		case '=':
			return 'T';
		case '>':
			return 'N';
		case ':':
			return 'N';
		case '?':
			return 'N';
		case '+':
			return 'T';
		case '-':
			return 'T';
		case '*':
			return 'F';
		}
		System.out.println("EROARE OPERATOR");
		return 0;
	}
	/**
	 * Ex 3 ; returneaza valoarea integer a expresiei salvata de arbore
	 * @param x arbore
	 * @return valoarea arborelui in mod recursiv
	 */
	public int ValueofArb(Nod x)
	{
		switch(x.operator){
		case 0:
			// e frunza ( numar intreg )
			return x.val;
		case '+':
			// cobor in recursivitate,dupa caz
			return ValueofArb(x.left) + ValueofArb(x.right);
		case '-':
			return ValueofArb(x.left) - ValueofArb(x.right);
		case '*':
			return ValueofArb(x.left) * ValueofArb(x.right);
		case '>':
			if(ValueofArb(x.left) > ValueofArb(x.right)) return 1;
			return 0;
		case '?': 
			return ValueofArb(x.left);
		case ':':
			if(ValueofArb (x.left) == 1 ) return ValueofArb(x.left.right);
			return ValueofArb(x.right);
		}
		// debug
		System.out.println("Eroare arbore,expresie invalida " + x);
		return 0;
	}
}
