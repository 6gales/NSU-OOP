package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;
import java.util.Stack;

public class Mul implements Operation
{
	@Override
	public void operate(Context context) throws EmptyStackException
	{
		if (context.getStack().size() < 2)
			throw new EmptyStackException();

		Stack<Integer> stack = context.getStack();
		stack.push(stack.pop() * stack.pop());
	}
}