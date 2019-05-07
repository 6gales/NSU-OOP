package ru.nsu.g.apleshkov.mtfactory.staff;

import ru.nsu.g.apleshkov.mtfactory.Car;
import ru.nsu.g.apleshkov.mtfactory.Item;
import ru.nsu.g.apleshkov.mtfactory.Storage;

import java.io.IOException;
import java.time.LocalTime;
import java.util.Observer;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.logging.FileHandler;
import java.util.logging.Logger;

public class Dealer extends Staff implements Runnable
{
	private static Logger log = Logger.getLogger(Dealer.class.getName());
	private Storage<Car> storage;
	private boolean logging;
	private long sellTime;
	private Item soldCars;
	private Lock lock;
	private Condition soldCarsApplied;

	public Dealer(int id, String name,
	              Storage<Car> storage, boolean logging, long sellTime,
	              Item soldCars, Lock lock, Condition soldCarsApplied)
	{
		super(id, name);

		this.storage = storage;
		this.logging = logging;
		this.sellTime = sellTime;
		this.soldCars = soldCars;
		this.lock = lock;
		this.soldCarsApplied = soldCarsApplied;

		setChanged();
		notifyObservers(soldCars.toString());

		if (logging)
		{
			try
			{
				FileHandler fileHandler = new FileHandler("SalesLog.log");
				log.addHandler(fileHandler);
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
	}

	@Override
	public void run()
	{
		while (!Thread.interrupted())
		{
			try
			{
				Car product = storage.get();
				Thread.sleep(sellTime);
				System.out.println("Car sold: id = " + product.getId());

				if (logging)
					log.info("<" + LocalTime.now() + ">: "
							+ "Dealer <" + getId() + ">: "
							+ "Auto <" + product.getId() + ">"
							+ "(Body: <" + product.getBody().getId() + ">, "
							+ "Motor: <" + product.getMotor().getId() + ">, "
							+ "Accessory: <" + product.getAccessory().getId() + ">)");

				lock.lock();
				soldCars.incrementAndGet();
				System.out.println("Sold cars counter: " + soldCars);
				soldCarsApplied.signal();
				lock.unlock();

				setChanged();
				notifyObservers(soldCars.toString());
			}
			catch (InterruptedException e) { break; }
		}
		System.out.println("Dealer finished");
	}
}
