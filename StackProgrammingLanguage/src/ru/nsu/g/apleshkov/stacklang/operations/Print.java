package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;

public class Print implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		if (context.getStack().size() == 0)
			throw new EmptyStackException();

		System.out.println(context.getStack().peek());
	}
}
