package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.LinkedList;

public class DefineOp implements Operation
{
	private String name;
	private LinkedList <Operation> body;

	public DefineOp(String _name, LinkedList <Operation> _body)
	{
		name = _name;
		body = _body;
	}

	@Override
	public void operate(Context context)
	{
		context.define(name, _context ->
		{
			for (Operation op : body)
			{
				try { op.operate(_context); }

				catch (Exception e) { throw e; }
			}
		});
	}
}