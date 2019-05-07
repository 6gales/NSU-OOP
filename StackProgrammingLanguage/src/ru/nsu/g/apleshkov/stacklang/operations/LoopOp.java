package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.LinkedList;

public class LoopOp implements Operation
{
	LinkedList <Operation> iteration;

	public LoopOp(LinkedList <Operation> loopBody)
	{
		iteration = loopBody;
	}

	@Override
	public void operate(Context context) throws Exception
	{
		while (context.getStack().size() > 0 && context.getStack().pop() != 0)
		{
			for (Operation op : iteration)
			{
				try { op.operate(context); }

				catch (Exception e) { throw e; }
			}
		}
	}

}
