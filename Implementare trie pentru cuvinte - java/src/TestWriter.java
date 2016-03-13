import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.logging.Level;
import java.util.logging.Logger;
public class TestWriter {
    
    private PrintWriter out = null;

    public TestWriter(String filename) {
        try {
            out = new PrintWriter(filename);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(TestWriter.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void printCount(int count) {
        out.println(count);
    }
    
    public void printSortedWords(TrieElement[] words) {
        for (TrieElement word : words) {
        	if(word == null) break;
            out.print(word.toCharArray() );
            out.print(" ");
        }
        out.println();
    }
    
    public void close() {
        out.close();
    }
    
    
}