package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.operations.exceptions.DivByZeroException;
import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Div implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException, DivByZeroException
	{
		if (context.getStack().size() < 2)
			throw new EmptyStackException();

		Stack<Integer> stack = context.getStack();
		Integer a = stack.pop(),
				b = stack.pop();
		if (b == 0)
		{
			stack.push(b);
			stack.push(a);
			throw new DivByZeroException();
		}

		stack.push(b / a);
	}
}