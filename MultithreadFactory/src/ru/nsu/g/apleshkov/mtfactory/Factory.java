package ru.nsu.g.apleshkov.mtfactory;

import ru.nsu.g.apleshkov.mtfactory.staff.*;
import ru.nsu.g.apleshkov.mtfactory.supplies.*;

import java.io.IOException;
import java.io.InputStream;
import java.util.LinkedList;
import java.util.List;
import java.util.Observer;
import java.util.Properties;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.function.Function;

public class Factory
{
	private Properties configurations;

	private List <Thread> staff;

	private volatile Item soldCars;

	private Lock lock;
	private Condition soldCarsApplied;

	public Factory(Observer obs) throws IOException
	{
		staff = new LinkedList<>();

		soldCars = new Item(0, "SoldCars", obs);

		lock = new ReentrantLock();
		soldCarsApplied = lock.newCondition();

		InputStream in = this.getClass().getResourceAsStream("factory.properties");
		configurations = new Properties();
		configurations.load(in);

		String storageSize = "StorageSize";

		MassiveStorage mStorage = new MassiveStorage(
				obs,
				Integer.parseInt(configurations.getProperty("Body" + storageSize)),
				Integer.parseInt(configurations.getProperty("Motor" + storageSize)),
				Integer.parseInt(configurations.getProperty("Accessory" + storageSize)),
				Integer.parseInt(configurations.getProperty("Car" + storageSize)));

		Manager manager = new Manager(staff);

		String suppliers = "Suppliers";
		int accessorySuppliers = Integer.parseInt(configurations.getProperty("Accessory" + suppliers)),
				bodySuppliers = Integer.parseInt(configurations.getProperty("Body" + suppliers)),
				motorSuppliers = Integer.parseInt(configurations.getProperty("Motor" + suppliers)),
				workers = Integer.parseInt(configurations.getProperty("Workers")),
				dealers = Integer.parseInt(configurations.getProperty("Dealers"));

		String workTime = "Worktime";
		String defaultWtime = configurations.getProperty("Default" + workTime);

		Function<String, Long> getWorktime = (String name) ->
				Long.parseLong(configurations.getProperty(name + workTime, defaultWtime));

		manager.createStaff(accessorySuppliers, "AccessorySupplier",
				(int id, String name) -> new Supplier<>(
						id, name,
						Accessory::new,
						mStorage.getAccessories(),
						getWorktime.apply("AccessorySupplier")));

		manager.createStaff(bodySuppliers, "BodySupplier",
				(int id, String name) -> new Supplier<>(
						id, name,
						Body::new,
						mStorage.getBodies(),
						getWorktime.apply("BodySupplier")));

		manager.createStaff(motorSuppliers, "MotorSupplier",
				(int id, String name) -> new Supplier<>(
						id, name,
						Motor::new,
						mStorage.getMotors(),
						getWorktime.apply("MotorSupplier")));

		manager.createStaff(workers, "Worker",
				(int id, String name) -> new Worker(
						id, name, obs,
						mStorage,
						getWorktime.apply("Worker")));

		manager.createStaff(dealers, "Dealer",
				(int id, String name) -> new Dealer(
						id, name,
						mStorage.getCars(),
						Boolean.parseBoolean(configurations.getProperty("LogSale")),
						getWorktime.apply("Dealer"),
						soldCars,
						lock,
						soldCarsApplied));
	}

	public void run()
	{
		int order = Integer.parseInt(configurations.getProperty("SaleOrder"));


		for (var employee : staff)
		{
			employee.start();
		}

		lock.lock();
		while (soldCars.get() < order)
		{
			try
			{
				System.out.println("Condition awaiting, sold cars = " + soldCars + ", order = " + order);
				soldCarsApplied.await();
			}
			catch (InterruptedException e) { break; }
		}
		lock.unlock();

		for (var employee : staff)
		{
			employee.interrupt();
		}

		System.out.println("Factory finished");
	}
}