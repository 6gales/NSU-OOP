package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

public class UndefOp implements Operation
{
	String name;

	public UndefOp(String _name)
	{
		name = _name;
	}

	@Override
	public void operate(Context context)
	{
		context.undef(name);
	}
}
