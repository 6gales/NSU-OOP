package ru.nsu.g.apleshkov.stacklang;

import ru.nsu.g.apleshkov.stacklang.exceptions.OperationNotFoundException;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import java.util.Optional;

class StackLang
{
	private InputSequence input;

	private Context context;

	private SyntaxInterpreter interpreter;

	public StackLang(String args[])
	{
		String filename = null;
		if (args.length > 0) filename = args[0];

		input = new InputSequence(filename);
		context = new Context();
		interpreter = new SyntaxInterpreter(context);
	}

	public void run()
	{
		while (input.hasNext())
		{
			try
			{
				interpreter.choose(input.next(), input).operate(context);
			}
			catch (Exception e) { input.getError(e); }
		}
		input.close();
	}
}