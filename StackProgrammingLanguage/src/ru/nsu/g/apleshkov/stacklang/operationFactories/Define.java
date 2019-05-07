package ru.nsu.g.apleshkov.stacklang.operationFactories;

import ru.nsu.g.apleshkov.stacklang.*;
import ru.nsu.g.apleshkov.stacklang.exceptions.InvalidInputSequenceException;
import ru.nsu.g.apleshkov.stacklang.operations.DefineOp;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import java.util.LinkedList;

public class Define extends OperationFactory
{
	public Operation createOperation(InputSequence input, SyntaxInterpreter interpreter) throws Exception
	{
		String name = null;

		if (input.hasNext())
			name = input.next();

		LinkedList<Operation> body = parseTillDelimeter(input, interpreter, ";");

		return new DefineOp(name, body);
	}
}
