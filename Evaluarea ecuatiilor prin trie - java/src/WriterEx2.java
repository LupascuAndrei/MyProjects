import java.io.FileNotFoundException;
import java.io.PrintWriter;


public class WriterEx2 {
	PrintWriter out;
	public WriterEx2(String file) throws FileNotFoundException
	{
		out  = new PrintWriter(file);
	}
	public void write(int i,int j,int error)
	{
		if(error == 0 )
			out.println("Ok!");
		if(error == 1 )
			out.println("Val nedeclarata la linia " + i + " coloana " + j);
		if(error == 2 )
			out.println("membrul stang nu este o variabila la linia " + i + " coloana 1");
	}
	public void close()
	{
		out.close();
	}
}
