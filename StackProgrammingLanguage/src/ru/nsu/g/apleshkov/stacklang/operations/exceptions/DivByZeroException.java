package ru.nsu.g.apleshkov.stacklang.operations.exceptions;

public class DivByZeroException extends Exception
{
	String message;
	public DivByZeroException() { message = "division by zero"; }

	public DivByZeroException(String _message) { message = _message; }

	@Override
	public String getMessage()
	{
		return message;
	}
}
