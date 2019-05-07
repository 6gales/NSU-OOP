package ru.nsu.g.apleshkov.mtfactory.staff;

import java.util.Observable;

public abstract class Staff extends Observable
{
	private int id;
	private String name;

	public Staff()
	{
		id = 0;
		name = null;
	}

	public Staff(int _id, String _name)
	{
		id = _id;
		name = _name;
	}

	public int getId() { return id; }
	public String getName() { return name; }
}
