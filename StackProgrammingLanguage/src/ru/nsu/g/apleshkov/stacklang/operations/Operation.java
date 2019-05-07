package ru.nsu.g.apleshkov.stacklang.operations;

import ru.nsu.g.apleshkov.stacklang.Context;

import java.util.EmptyStackException;

public interface Operation
{
	public void operate(Context context) throws Exception;
}