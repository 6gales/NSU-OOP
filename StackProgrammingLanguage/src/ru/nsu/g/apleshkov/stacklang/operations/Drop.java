package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;

public class Drop implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		if (context.getStack().size() == 0)
			throw new EmptyStackException();

		context.getStack().pop();
	}
}
