package ru.nsu.g.apleshkov.mtfactory.staff;

import ru.nsu.g.apleshkov.mtfactory.Storage;
import ru.nsu.g.apleshkov.mtfactory.supplies.Supply;

public class Supplier<T extends Supply> extends Staff implements Runnable
{
	public interface SupplyBuilder
	{
		Supply build(int id);
	}

	private SupplyBuilder builder;
	private Storage<T> storage;
	private long supplyTime;

	public Supplier(int id, String name, SupplyBuilder _builder, Storage<T> _storage, long _supplyTime)
	{
		super(id, name);
		builder = _builder;
		storage = _storage;
		supplyTime = _supplyTime;
	}

	@Override
	public void run()
	{
		while (!Thread.interrupted())
		{
			try
			{
				Thread.sleep(supplyTime);

				int id = storage.askId();
				T thing = (T)builder.build(id);
				storage.add(thing);

				System.out.println("Added supply: " + thing.getClass().toString());
			}
			catch (InterruptedException e) { break; }
		}
		System.out.println("Supplier finished");
	}
}
