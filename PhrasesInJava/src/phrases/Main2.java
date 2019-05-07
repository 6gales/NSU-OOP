package phrases;

public class Main2
{
	public static void main(String[] args)
	{
		PhrasesStream phraseSet = new PhrasesStream(args);
		phraseSet.readToMap();
		phraseSet.printResults();
	}
}