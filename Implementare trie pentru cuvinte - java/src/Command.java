/**
 *
 * @author Lupascu
 */
public abstract class Command {
    
    public static final int ADD = 0;
    public static final int COUNT = 2;
    public static final int REMOVE = 1;
    public static final int LIST = 3;
    
    protected String word;
    protected int type;
    
    public String getWord() {
        return word;
    }
    
    public int getType() {
        return type;
    }
}