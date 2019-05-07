package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

public class Push implements Operation
{
	Integer value;

	public Push(String arg)
	{
		value = Integer.parseInt(arg);
	}

	@Override
	public void operate(Context context)
	{
		context.getStack().push(value);
	}
}
