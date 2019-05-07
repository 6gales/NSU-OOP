package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Sub implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		Stack<Integer> stack = context.getStack();
		if (stack.size() < 2)
			throw new EmptyStackException();

		Integer a = stack.pop(),
				b = stack.pop();
		stack.push(b - a);
	}
}