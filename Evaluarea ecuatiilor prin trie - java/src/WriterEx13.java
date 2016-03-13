import java.io.FileNotFoundException;
import java.io.PrintWriter;


public class WriterEx13 {
	PrintWriter out;
	public WriterEx13(String file) throws FileNotFoundException
	{
		out  = new PrintWriter(file);
	}
	public void write(String s)
	{
		out.println(s);
	}
	public void close()
	{
		out.close();
	}
}
