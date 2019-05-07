package ru.nsu.g.apleshkov.mtfactory;

import ru.nsu.g.apleshkov.mtfactory.supplies.Accessory;
import ru.nsu.g.apleshkov.mtfactory.supplies.Body;
import ru.nsu.g.apleshkov.mtfactory.supplies.Motor;

import java.util.Observer;

public class MassiveStorage
{
	private Storage<Body> bodies;
	private Storage<Motor> motors;
	private Storage<Accessory> accessories;
	private Storage<Car> cars;

	MassiveStorage(Observer obs, int bCapacity, int mCapacity, int aCapacity, int cCapacity)
	{
		bodies = new Storage<>(bCapacity, "Bodies", obs);
		motors = new Storage<>(mCapacity, "Motors", obs);
		accessories = new Storage<>(aCapacity, "Accessories", obs);
		cars = new Storage<>(cCapacity, "Cars", obs);
	}

	public Storage<Body> getBodies() { return bodies; }

	public Storage<Motor> getMotors() { return motors; }

	public Storage<Accessory> getAccessories() { return accessories; }

	public Storage<Car> getCars() { return cars; }
}
