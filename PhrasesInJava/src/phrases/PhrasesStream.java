package phrases;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.TreeMap;
import java.util.function.Function;
import java.util.stream.Collectors;

class PhrasesStream
{
	private List<String> lines;
	private int m,
				n;

	private Map<String, Long> phraseCollection;

	public final int checkSize() { return n; }
	public final int checkRepetitions() { return m; }
	public final Map<String, Long> getCollection() { return phraseCollection; }

	private String setValues(String[] argv)
	{
		m = 2;
		n = 2;
		switch (argv.length)
		{
			case 0:
				return "-";

			case 1:
				return argv[0];

			case 2:
				if (argv[0].equals("-n") && (Integer.parseInt(argv[1]) > 0))
					n = Integer.parseInt(argv[1]);
				else if (argv[0].equals("-m") && (Integer.parseInt(argv[1]) > 0))
					m = Integer.parseInt(argv[1]);
				else System.out.println("Incorrect input. Continuing with stdin...");
				return "-";

			case 3:
				if (argv[0].equals("-n") && (Integer.parseInt(argv[1]) > 0))
					n = Integer.parseInt(argv[1]);
				else if (argv[0].equals("-m") && (Integer.parseInt(argv[1]) > 0))
					m = Integer.parseInt(argv[1]);
				else System.out.println("Incorrect input. Continuing with stdin...");
				return argv[2];

			case 4:
				if (argv[0].equals("-n") && argv[2].equals("-m") && (Integer.parseInt(argv[1]) > 0) && (Integer.parseInt(argv[3]) > 0))
				{
					n = Integer.parseInt(argv[1]);
					m = Integer.parseInt(argv[3]);
				}
				return "-";

			default:
				if (argv[0].equals("-n") && argv[2].equals("-m") && (Integer.parseInt(argv[1]) > 0) && (Integer.parseInt(argv[3]) > 0))
				{
					n = Integer.parseInt(argv[1]);
					m = Integer.parseInt(argv[3]);
				}
				return argv[4];
		}

	}

	public PhrasesStream(String argv[])
	{
		String filename = setValues(argv);
		Scanner sr;
		lines = new ArrayList<String>();
		if (filename.equals("-"))
			sr = new Scanner(System.in);
		else
		{
			try
			{
				lines = new ArrayList<String>();
				FileReader fin = new FileReader(filename);
				sr = new Scanner(fin);
			}
			catch (FileNotFoundException e)
			{
				System.out.println("File " + filename + " not found. Continuing with stdin...");
				sr = new Scanner(System.in);
			}
		}

		String phrase[] = new String[n];
		int currentPos = 0;

		for (; currentPos < n && sr.hasNext(); currentPos++)
		{
			phrase[currentPos]  = sr.next();
		}

		if (currentPos == n)
		{
			currentPos = 0;
			while (true)
			{
				String sum = phrase[currentPos];
				for (int i = 1, j = (currentPos + 1) % n; i < phrase.length; ++i, ++j, j %= n)
				{
					sum += ' ' + phrase[j];
				}
				lines.add(sum);

				if (!sr.hasNext())
					break;

				phrase[currentPos] = sr.next();
				currentPos = (currentPos + 1) % n;
			}
		}
		sr.close();

		phraseCollection = new TreeMap<String, Long>();
	}

	public void readToMap()
	{
		phraseCollection = lines.stream()
				.collect(Collectors.groupingBy(Function.identity(), Collectors.counting()));
	}

	public void printResults()
	{
		phraseCollection.entrySet()
				.stream()
				.sorted((a, b) -> b.getValue().compareTo(a.getValue()))
				.filter(entry -> entry.getValue() >= m)
				.forEach(entry -> { System.out.println(entry.getKey() + " (" + entry.getValue() + ")"); });
	}
}
