package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Swap implements Operation
{
	@Override
	public void operate(Context context)
	{
		Stack<Integer> stack = context.getStack();
		if (stack.size() < 2)
			throw new EmptyStackException();

		Integer a = stack.pop(),
				b = stack.pop();
		stack.push(a);
		stack.push(b);
	}
}
