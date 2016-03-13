
/**
 *
 * @author Lupascu
 */
public interface AbstractTrie {
    
    public abstract void add(TrieElement element);
    
    public abstract int count(TrieElement element);
    
    public abstract void remove(TrieElement element);
    
    public abstract TrieElement[] getSortedElements(TrieElement prefix);
    
}