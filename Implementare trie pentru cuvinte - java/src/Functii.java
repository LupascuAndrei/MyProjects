
public class Functii {
	public int intreg(char q)
	{
		/**
		 * transforma caracterul q intr-un numar intre 0 si 70 
		 * (pentru a-l transforma intr-un indice pentru muchie )
		 */
		if (q >= 'A' && q <= 'Z')
			return 16 + q - 'A';
		if (q >= '0' && q <= '9')
			return 5 + q - '0';
		if (q >= 'a' && q <= 'z')
			return 43 + q - 'a';
		switch (q) {
		case '!':
			return 0;
		case '(':
			return 1;
		case ')':
			return 2;
		case '?':
			return 3;
		case '-':
			return 4;
		case '_':
			return 15;
		}
		// eroare
		return -1;
	}
	public char[] sir_lexicografic(String x, String y)
	{ 
		/**
		 * returneaza cel mai mic sir dpdv lexicografic
		 */
		if (x== null) return y.toCharArray();
		int a,b;
		char[] sir1 = x.toCharArray();
		char[] sir2 = y.toCharArray();
		for(int i = 0 ; i < sir1.length ; i ++)
		{
			if(i >= sir2.length)
				return sir2;
			a = intreg(sir1[i]);
			b = intreg(sir2[i]);
			if(a == b ) continue;
			if(a < b)
				return sir1;
			return sir2;
			
		}
		return sir1;
	}
}
