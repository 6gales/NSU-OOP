package ru.nsu.g.apleshkov.mtfactory;

import java.util.Observable;
import java.util.Observer;
import java.util.Queue;
import java.util.concurrent.ConcurrentLinkedQueue;

public class Storage<T> extends Observable
{
	private volatile int nextId;
	private final int capacity;

	private Queue<T> stuff;

	private String name;

	Storage(int capacity, String name, Observer obs)
	{
		addObserver(obs);

		this.name = name;
		this.capacity = capacity;
		nextId = 0;
		stuff = new ConcurrentLinkedQueue<>();

		setChanged();
		notifyObservers();
	}

	public void add(T thing) throws InterruptedException
	{
		synchronized (this)
		{
			while (stuff.size() == capacity)
			{
				wait();
			}

			stuff.add(thing);

			setChanged();
			notifyObservers();

			notifyAll();
		}
	}

	public T get() throws InterruptedException
	{
		synchronized (this)
		{
			while (stuff.size() == 0)
			{
				wait();
			}

			T thing = stuff.poll();

			setChanged();
			notifyObservers();

			notifyAll();

			return thing;
		}
	}

	public synchronized int askId() { return nextId++; }

	public final String getName() { return name; }

	public final int capacity() { return capacity; }

	public final int size() { return stuff.size(); }
}
