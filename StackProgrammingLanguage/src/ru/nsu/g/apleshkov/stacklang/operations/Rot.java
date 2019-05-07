package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Rot implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		Stack<Integer> stack = context.getStack();
		if (stack.size() < 3)
			throw new EmptyStackException();

		Integer a = stack.pop(),
					b = stack.pop(),
					c = stack.pop();
		stack.push(b);
		stack.push(a);
		stack.push(c);
	}
}
