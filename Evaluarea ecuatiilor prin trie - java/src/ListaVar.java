import java.util.ArrayList;


public class ListaVar {
	public ArrayList<StructVar> list = new ArrayList<StructVar>();
	/**
	 * adauga un cuvant nou ( nume variabila ; valoarea salvata de ea ) in dictionar ( arraylist )
	 * @param t - cuvant
	 * @param indice
	 */
	public void add(StructVar t,int indice)
	{
		if(indice == -1 ) 
			list.add(t);
		else
			list.set(indice,t);
	}
	/**
	 * 
	 * @param t - cuvant
	 * @return pozitia parametrului T in dictionar
	 */
	public int search(StructVar t)
	{
		for(int i = 0 ; i < list.size(); i ++)
		{
			if(t.nume.equals(list.get(i).nume))
				return i;
		}
		return -1;
	}
	/**
	 * 
	 * @param poz
	 * @return valoarea integer a cuvantului salvat la pozitia POZ in dictionar
	 */
	public int val(int poz)
	{
		return list.get(poz).val;
	}
}

