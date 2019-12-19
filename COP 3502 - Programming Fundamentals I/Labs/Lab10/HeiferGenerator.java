import java.lang.reflect.Constructor;
import java.io.FileFilter;
import java.io.File;

public class HeiferGenerator
{
    static class HeiferFilter implements FileFilter
    {
        public boolean accept(File path)
        {
            String filename = path.getName();
            try
            {
                return filename.substring(filename.lastIndexOf(".") + 1).toLowerCase().equals("cow");
            }
            catch (Exception e)
            {
                return false;
            }
        }
    }

    public static Cow[] getFileCows()
    {
        if (fileCows == null)
        {
            File[] fileCowList = new File("cows").listFiles(new HeiferFilter());
            fileCows = new Cow[fileCowList.length];

            // Add file cows
            for (int index = 0; index < fileCows.length; index++)
            {
                String filename = fileCowList[index].getName();
                String cowName = filename.substring(0, filename.lastIndexOf("."));
                fileCows[index] = new FileCow(cowName, "cows" + File.separator + filename);
            }
        }

        return fileCows;
    }

    public static Cow[] getCows()
    {
        if (cows == null)
        {
            cows = new Cow[cowNames.length + dragonNames.length];

            // Add the "regular" cows
            for (int index = 0; index < cowNames.length; index++)
            {
                cows[index] = new Cow(cowNames[index]);
                cows[index].setImage(quoteLines + cowImages[index]);
            }

            // Add the dragons
            for (int offset = cowNames.length, index = 0; index < dragonNames.length; index++)
            {
                try
                {
                    @SuppressWarnings("unchecked")
                    Constructor<Cow> constructor = dragonTypes[index].getConstructor(String.class, String.class);
                    cows[offset + index] = constructor.newInstance(dragonNames[index], quoteLines + dragonImage);
                }
                catch (Exception ignored) { }
            }
        }

        return cows;
    }

    public static void addCow(Cow newMoo)
    {
        Cow[] oldCows = cows;

            if (oldCows == null)
            cows = new Cow[1];
        else
            cows = new Cow[oldCows.length + 1];
            
        for (int index = 0; index < oldCows.length; index++)
            cows[index] = oldCows[index];
            
        cows[oldCows.length] = newMoo;
    }

    // Hard-coded values for some of the cows
    private static String[] cowNames = { "heifer", "kitteh" };

    private static String quoteLines =      "       \\\n" +
                                            "        \\\n" +
                                            "         \\\n";

    private static String[] cowImages = {   "        ^__^\n" +
                                            "        (oo)\\_______\n" +
                                            "        (__)\\       )\\/\\\n" +
                                            "            ||----w |\n" +
                                            "            ||     ||\n",


                                            "       (\"`-'  '-/\") .___..--' ' \"`-._\n" +
                                            "         ` *_ *  )    `-.   (      ) .`-.__. `)\n" +
                                            "         (_Y_.) ' ._   )   `._` ;  `` -. .-'\n" +
                                            "      _.. `--'_..-_/   /--' _ .' ,4\n" +
                                            "   ( i l ),-''  ( l i),'  ( ( ! .-'\n"
                                        };

    private static String[] dragonNames = { "dragon", "ice-dragon" };
    private static Class[] dragonTypes = { Dragon.class, IceDragon.class };

    private static String dragonImage =     "           |\\___/|       /\\  //|\\\\\n" +
                                            "           /0  0  \\__   /  \\// | \\ \\\n" +
                                            "          /     /  \\/_ /   //  |  \\  \\\n" +
                                            "          \\_^_\\'/   \\/_   //   |   \\   \\\n" +
                                            "          //_^_/     \\/_ //    |    \\    \\\n" +
                                            "       ( //) |        \\ //     |     \\     \\\n" +
                                            "     ( / /) _|_ /   )   //     |      \\     _\\\n" +
                                            "   ( // /) '/,_ _ _/  ( ; -.   |    _ _\\.-~       .-~~~^-.\n" +
                                            " (( / / )) ,-{        _      `.|.-~-.          .~         `.\n" +
                                            "(( // / ))  '/\\      /                ~-. _.-~      .-~^-.  \\\n" +
                                            "(( /// ))      `.   {            }                 /      \\  \\\n" +
                                            " (( / ))     .----~-.\\        \\-'               .~         \\  `.   __\n" +
                                            "            ///.----..>        \\            _ -~            `.  ^-`  \\\n" +
                                            "              ///-._ _ _ _ _ _ _}^ - - - - ~                   `-----'\n";

    private static Cow[] cows = null;
    private static Cow[] fileCows = null;
}
