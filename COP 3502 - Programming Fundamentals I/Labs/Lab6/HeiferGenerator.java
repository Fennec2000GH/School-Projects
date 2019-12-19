public class HeiferGenerator
{
	public static Cow[] getCows()
	{
		if (cows == null)
		{
			cows = new Cow[cowImages.length];

			for (int index = 0; index < cows.length; index++)
			{
				cows[index] = new Cow(cowNames[index]);
				cows[index].setImage(quoteLines + cowImages[index]);
			}
		}

		return cows;
	}
	
	private static String[] cowNames = { "heifer", "kitteh" };

	private static String quoteLines = 		"    \\\n" +
											"     \\\n" +
											"      \\\n";

	private static String[] cowImages = {	"        ^__^\n" +
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

	private static Cow[] cows = null;
}