package ru.nsu.g.apleshkov.stacklang.exceptions;

public class OperationNotFoundException extends Exception
{
	String message;

	public OperationNotFoundException() { message = "operation not found"; }

	public OperationNotFoundException(String _message) { message = _message; }

	@Override
	public String getMessage()
	{
		return message;
	}
}
