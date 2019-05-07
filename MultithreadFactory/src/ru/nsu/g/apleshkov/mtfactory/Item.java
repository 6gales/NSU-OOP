package ru.nsu.g.apleshkov.mtfactory;

import java.util.Observable;
import java.util.Observer;

public class Item extends Observable
{
	private String name;
	private int value;

	public Item(int v, String name, Observer obs)
	{
		value = v;
		this.name = name;
		addObserver(obs);
	}

	public String getName() { return name; }

	public int incrementAndGet()
	{
		value++;

		setChanged();
		notifyObservers(String.valueOf(value));

		return value;
	}

	public int get() { return value; }

	public int decrementAndGet()
	{
		value--;

		setChanged();
		notifyObservers(String.valueOf(value));

		return value;
	}

	public void set(int v)
	{
		value = v;

		setChanged();
		notifyObservers(String.valueOf(value));
	}
}
