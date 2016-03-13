
public class Nod_Operator extends Nod {
	private int aux;
	public Nod_Operator(char k )
	{
		operator = k ;
	}
	@Override 
	public String toString()
	{
		return String.valueOf(operator);
	}
	/**
	 * (Pentru cerinta 1,daca vreau sa afisez un nod care se afla pe nivelul maxim atins la pasul i )
	 * cobor recursiv in nod pentru a vedea cate paranteze deschise / inchise contin subarborii sai
	 * afisez,astfel, "(((...", "E" , ")))..."
	 */
	@Override
	public String expresie()
	{
		aux = contorParanteze(left);
		aux+= contorParanteze(right);
		String toReturn = "";
		for(int i = 0 ; i < aux; i++)
			toReturn += "(";
		toReturn += "E";
		for(int i = 0 ; i < -aux ; i++)
			toReturn += ")";
		return toReturn;
	}
	/**
	 * 
	 * @param x - nod
	 * @return - cate paranteze deschise sau inchise sunt salvate in subarborii nodului 
	 */
	public int contorParanteze(Nod x)
	{
		if(x == null)
			return 0;
		return x.pr + contorParanteze(x.left) + contorParanteze(x.right);
	}
}
