/**
 *
 * @author Lupascu
 */
public class ListCommand extends Command{

    public ListCommand(String word) {
        this.word = word;
        this.type = Command.LIST;
    }
}