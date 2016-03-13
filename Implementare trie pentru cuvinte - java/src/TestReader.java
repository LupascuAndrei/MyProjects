import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
public class TestReader {
    
    private String[] words;
    private Command[] firstCommands;
    private Command[] secondCommands;
    
    
    public TestReader(String fileName) {
        try {
            Scanner in = new Scanner(new File(fileName));
            String text = in.nextLine();
            words = text.split(" ");
            firstCommands = parseCommands(in);
            secondCommands = parseCommands(in);
        } catch (FileNotFoundException ex) {
            Logger.getLogger(TestReader.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    private Command[] parseCommands(Scanner s) {
        int n = s.nextInt();
        Command[] commands = new Command[n];
        for (int i = 0; i < n; i++) {
            commands[i] = parseCommand(s);
        }
        return commands;
    }
    
    private Command parseCommand(Scanner s) {
        int type = s.nextInt();
        switch (type) {
            case Command.ADD:
                return new AddCommand(s.next());
            case Command.COUNT:
                return new CountCommand(s.next());
            case Command.REMOVE:
                return new RemoveCommand(s.next());
            case Command.LIST:
                return new ListCommand(s.next());
        }
        return null;
    }

    /**
     * @return the words
     */
    public String[] getWords() {
        return words;
    }

    /**
     * @return the firstCommands
     */
    public Command[] getFirstCommands() {
        return firstCommands;
    }

    /**
     * @return the secondCommands
     */
    public Command[] getSecondCommands() {
        return secondCommands;
    }
    
}