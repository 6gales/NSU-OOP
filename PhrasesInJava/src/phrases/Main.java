package phrases;

public class Main
{
	public static void main(String[] args)
	{
		Phrases phraseSet = new Phrases(args);
		phraseSet.readToMap();
		phraseSet.printResults();
	}
}