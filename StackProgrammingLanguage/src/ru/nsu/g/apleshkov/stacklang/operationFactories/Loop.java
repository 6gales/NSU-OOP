package ru.nsu.g.apleshkov.stacklang.operationFactories;

import ru.nsu.g.apleshkov.stacklang.InputSequence;
import ru.nsu.g.apleshkov.stacklang.SyntaxInterpreter;
import ru.nsu.g.apleshkov.stacklang.exceptions.InvalidInputSequenceException;
import ru.nsu.g.apleshkov.stacklang.operations.LoopOp;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import java.util.LinkedList;

public class Loop extends OperationFactory
{
	@Override
	public Operation createOperation(InputSequence input, SyntaxInterpreter interpreter) throws Exception
	{
		boolean finished = false;

		LinkedList <Operation> body = parseTillDelimeter(input, interpreter, "]");

		return new LoopOp(body);
	}
}
