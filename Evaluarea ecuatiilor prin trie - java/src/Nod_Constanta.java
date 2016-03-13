
public class Nod_Constanta extends Nod{
	/**
	 * returneaza parantezele deschise salvate de nod,apoi informatia tinuta de nod
	 * ,iar apoi parantezele inchise salvate de nod
	 */
	@Override
	public String toString()
	{
		String x = "";
		for(int i = 0 ; i < pr ; i ++)
			x+= "(";
		x+= String.valueOf(tip);
		for(int i = 0 ; i < -pr ; i ++)
			x+= ")";
		return x;
	}
}
