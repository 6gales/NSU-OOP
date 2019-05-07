package ru.nsu.g.apleshkov.stacklang;

import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import java.util.Map;
import java.util.Stack;
import java.util.TreeMap;

public class Context
{
	private Stack <Integer> stack;
	private Map<String, Operation> defines;

	public Context()
	{
		stack = new Stack<Integer>();
		defines = new TreeMap<String, Operation>();
	}

	public Stack<Integer> getStack() { return stack; }

	public void define(String name, Operation defOperation)
	{
		defines.put(name, defOperation);
	}

	public boolean isDefined(String name) { return defines.containsKey(name); }

	public void undef(String name) { defines.remove(name); }

	public Operation getDefine(String name) { return defines.get(name); }
}