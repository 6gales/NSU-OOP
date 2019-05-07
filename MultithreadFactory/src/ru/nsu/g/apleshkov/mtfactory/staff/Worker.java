package ru.nsu.g.apleshkov.mtfactory.staff;

import ru.nsu.g.apleshkov.mtfactory.Car;
import ru.nsu.g.apleshkov.mtfactory.MassiveStorage;
import ru.nsu.g.apleshkov.mtfactory.supplies.Accessory;
import ru.nsu.g.apleshkov.mtfactory.supplies.Body;
import ru.nsu.g.apleshkov.mtfactory.supplies.Motor;

import java.util.Observer;

public class Worker extends Staff implements Runnable
{
	private MassiveStorage storages;

	private long workTime;

	public Worker(int id, String name, Observer obs, MassiveStorage _storages, long _workTime)
	{
		super(id, name);
		addObserver(obs);

		storages = _storages;
		workTime = _workTime;

		setChanged();
		notifyObservers("Applied for work");
	}

	@Override
	public void run()
	{
		while (!Thread.interrupted())
		{
			try
			{
				setChanged();
				notifyObservers("Waiting for body");

				Body b = storages.getBodies().get();

				setChanged();
				notifyObservers("Waiting for motor");

				Motor m = storages.getMotors().get();

				setChanged();
				notifyObservers("Waiting for accessory");

				Accessory a = storages.getAccessories().get();

				int id = storages.getCars().askId();

				setChanged();
				notifyObservers("Working");

				Thread.sleep(workTime);
				System.out.println("Worker built car with id: " + id);

				setChanged();
				notifyObservers("Waiting to add car");

				storages.getCars().add(new Car(id, b, m, a));
			}
			catch (InterruptedException e) { break; }
		}
		System.out.println("Worker finished");

		setChanged();
		notifyObservers("Finished");
	}
}
