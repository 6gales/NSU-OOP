package ru.nsu.g.apleshkov.mtfactory.supplies;

public abstract class Supply
{
	private int id;

	Supply(int _id) { id = _id; }

	public int getId() { return id; }
}
