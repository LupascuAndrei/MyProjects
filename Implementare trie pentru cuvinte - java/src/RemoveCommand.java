/**
 *
 * @author Lupascu
 */
public class RemoveCommand extends Command{

    public RemoveCommand(String word) {
        this.word = word;
        this.type = Command.REMOVE;
    }
}