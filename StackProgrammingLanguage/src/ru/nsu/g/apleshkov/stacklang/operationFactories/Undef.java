package ru.nsu.g.apleshkov.stacklang.operationFactories;

import ru.nsu.g.apleshkov.stacklang.InputSequence;
import ru.nsu.g.apleshkov.stacklang.SyntaxInterpreter;
import ru.nsu.g.apleshkov.stacklang.exceptions.InvalidInputSequenceException;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;
import ru.nsu.g.apleshkov.stacklang.operations.UndefOp;

public class Undef extends OperationFactory
{
	@Override
	public Operation createOperation(InputSequence input, SyntaxInterpreter interpreter)
			throws InvalidInputSequenceException
	{
		String name = null;

		if (input.hasNext())
			name = input.next();
		else throw new InvalidInputSequenceException("undef parameter not found");

		return new UndefOp(name);
	}
}
