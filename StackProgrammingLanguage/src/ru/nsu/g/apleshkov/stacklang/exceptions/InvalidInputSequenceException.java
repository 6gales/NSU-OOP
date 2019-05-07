package ru.nsu.g.apleshkov.stacklang.exceptions;

public class InvalidInputSequenceException extends Exception
{
	String message;

	public InvalidInputSequenceException() { message = "invalid input sequence"; }

	public InvalidInputSequenceException(String _message) { message = _message; }

	@Override
	public String getMessage()
	{
		return message;
	}
}
