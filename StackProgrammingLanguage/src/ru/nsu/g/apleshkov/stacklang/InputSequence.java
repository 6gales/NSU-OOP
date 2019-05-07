package ru.nsu.g.apleshkov.stacklang;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.util.Arrays;
import java.util.Optional;
import java.util.Scanner;
import java.util.Vector;

public class InputSequence
{
	private Scanner scanner;

	private Vector<String> commands;

	private boolean emptyLine = true;

	private int current = 0,
				lineNum = 0;

	public InputSequence(String filename)
	{
		commands = new Vector<>(64);

		if (filename != null)
		{
			try
			{
				FileReader fr = new FileReader(filename);
				scanner = new Scanner(fr);
				return;
			}
			catch (FileNotFoundException e)
			{
				System.out.println(e.getMessage());
			}
		}

		scanner = new Scanner(System.in);
	}

	private boolean loadLine()
	{
		if (emptyLine && !scanner.hasNextLine())
			return false;

		for (; emptyLine && scanner.hasNextLine(); )
		{
			String line = scanner.nextLine();
			if (!line.isEmpty() && line.toCharArray()[0] == '#')
				continue;

			Arrays.stream(line.split(" "))
					.filter(s -> !s.equals(""))
					.forEach(s -> commands.add(s));
			emptyLine = (current == commands.size());

			lineNum++;
		}

		if (emptyLine)
			return false;

		return true;
	}

	public boolean hasNext()
	{
		return loadLine();
	}

	public String next()
	{
		if (emptyLine)
			emptyLine = !loadLine();

		if (emptyLine) return null;

		if (++current == commands.size())
			emptyLine = true;

		return commands.get(current - 1);
	}

	public void getError(Exception e)
	{
		System.out.println("Error at line "
				+ Integer.toString(lineNum)
				+ ": " + e.getMessage()
				+ " at command " + commands.get(current - 1));
	}

	void close()
	{
		scanner.close();
	}
}