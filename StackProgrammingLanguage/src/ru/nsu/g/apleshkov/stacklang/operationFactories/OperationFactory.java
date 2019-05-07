package ru.nsu.g.apleshkov.stacklang.operationFactories;

import ru.nsu.g.apleshkov.stacklang.InputSequence;
import ru.nsu.g.apleshkov.stacklang.SyntaxInterpreter;
import ru.nsu.g.apleshkov.stacklang.exceptions.InvalidInputSequenceException;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import java.util.LinkedList;

public abstract class OperationFactory
{
	protected LinkedList<Operation> parseTillDelimeter(InputSequence input,
	                                                   SyntaxInterpreter interpreter,
	                                                   String delimeter) throws Exception
	{
		LinkedList<Operation> body = new LinkedList<>();

		boolean finished = false;

		while (input.hasNext())
		{
			String command = input.next();
			if (command.equals(delimeter))
			{   finished = true;
				break;
			}

			body.add(interpreter.choose(command, input));
		}
		if (!finished)
			throw new InvalidInputSequenceException("finishing character '" + delimeter + "' not found");

		return body;
	}

	public abstract Operation createOperation(InputSequence input, SyntaxInterpreter interpreter) throws Exception;
}
