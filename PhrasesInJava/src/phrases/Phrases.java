package phrases;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Scanner;
import java.util.Map;
import java.util.TreeMap;
import java.util.Set;
import java.util.TreeSet;
import java.util.SortedMap;

class Phrases
{
	private Scanner stream;
	private int m,
				n,
				currentPos;
	private String phrase[];
	
	private Map<String, Integer> phraseCollection;

	public final int checkSize() { return n; }
	public final int checkRepetitions() { return m; }
	public final Map<String, Integer> getCollection() { return phraseCollection; }

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
			else System.out.println("Incorrect input: negative value. Continuing with default...");
			return "-";
	
			case 3:
			if (argv[0].equals("-n") && (Integer.parseInt(argv[1]) > 0))
				n = Integer.parseInt(argv[1]);
			else if (argv[0].equals("-m") && (Integer.parseInt(argv[1]) > 0))
				m = Integer.parseInt(argv[1]);
			else System.out.println("Incorrect input: negative value. Continuing with default...");
			return argv[2];

			case 4:
			if (argv[0].equals("-n") && argv[2].equals("-m") && (Integer.parseInt(argv[1]) > 0) && (Integer.parseInt(argv[3]) > 0))
			{
				n = Integer.parseInt(argv[1]);
				m = Integer.parseInt(argv[3]);
			}
			else System.out.println("Incorrect input: negative value. Continuing with default...");
			return "-";

			default:
			if (argv[0].equals("-n") && argv[2].equals("-m") && (Integer.parseInt(argv[1]) > 0) && (Integer.parseInt(argv[3]) > 0))
			{
				n = Integer.parseInt(argv[1]);
				m = Integer.parseInt(argv[3]);
			}
			else System.out.println("Incorrect input: negative value. Continuing with default...");
			return argv[4];
		}

	}

	private void addToMap()
	{
		String sum = phrase[currentPos];
		for (int i = 1, j = (currentPos + 1) % n; i < phrase.length; ++i, ++j, j%= n)
		{
			sum += ' ' + phrase[j];
		}

		Integer value = phraseCollection.get(sum);
		if (value == null)
			phraseCollection.put(sum, 1);
		else phraseCollection.replace(sum, value + 1);
	}


	public Phrases(String argv[])
	{
		String filename = setValues(argv);
		phrase = new String[n];
		
		if (filename.equals("-"))
			stream = new Scanner(System.in);
		else
		{
			try
			{
				FileReader fin = new FileReader(filename);
				stream = new Scanner(fin);
			}
			catch (FileNotFoundException e) 
			{ 
				System.out.println("File " + filename + " not found. Continuing with stdin...");
				stream = new Scanner(System.in);
			}
		}
		phraseCollection = new TreeMap<String, Integer>();
	}

	public void readToMap()
	{
		currentPos = 0;
		for (int i = 0; i < n; i++)
		{
			if (stream.hasNext())
				phrase[i] = stream.next();
			else return;
		}

		addToMap();
			
		while (stream.hasNext())
		{
			phrase[currentPos] = stream.next();
			currentPos = (currentPos + 1) % n;
			addToMap();
		}
		stream.close();
	}

	public void printResults()
	{
		SortedMap<Integer, Set<String>> inOrder = new TreeMap<Integer, Set<String>>((Integer a, Integer b) ->
		{
				return b.compareTo(a);
		});
		
		for (Map.Entry<String, Integer> i : phraseCollection.entrySet())
		{
			Set<String> value = inOrder.get(i.getValue());
			if (value == null)
			{
				value = new TreeSet<String>();
				inOrder.put(i.getValue(), value);
			}
			value.add(i.getKey());
		}

		inOrder.forEach((Integer k, Set<String> v) ->
		{
			if (k >= m)
				v.forEach((String s) -> { System.out.println(s + " (" + k + ")"); });
		});
	}

}