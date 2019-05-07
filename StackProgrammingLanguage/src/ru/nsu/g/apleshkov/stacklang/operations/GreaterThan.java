package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class GreaterThan implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		if (context.getStack().size() < 2)
			throw new EmptyStackException();

		Stack<Integer> stack = context.getStack();
		Integer top = stack.pop();
		stack.push((stack.pop() > top ? 1 : 0));
	}
}