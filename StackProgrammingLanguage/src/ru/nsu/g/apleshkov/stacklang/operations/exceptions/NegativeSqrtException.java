package ru.nsu.g.apleshkov.stacklang.operations.exceptions;

public class NegativeSqrtException extends Exception
{
	String message;
	public NegativeSqrtException() { message = "negative parameter passed to sqrt"; }

	public NegativeSqrtException(String _message) { message = _message; }

	@Override
	public String getMessage()
	{
		return message;
	}
}
