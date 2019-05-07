package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.operations.exceptions.NegativeSqrtException;
import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Sqrt implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException, NegativeSqrtException
	{
		Stack<Integer> stack = context.getStack();
		if (stack.size() < 2)
			throw new EmptyStackException();
		if (stack.peek() < 0)
			throw new NegativeSqrtException();

		Double a = Math.sqrt(stack.pop());
		stack.push(a.intValue());
	}
}