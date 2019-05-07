package ru.nsu.g.apleshkov.mtfactory;

import ru.nsu.g.apleshkov.mtfactory.supplies.Accessory;
import ru.nsu.g.apleshkov.mtfactory.supplies.Body;
import ru.nsu.g.apleshkov.mtfactory.supplies.Motor;

public class Car
{
	private int id;
	private Body body;
	private Motor motor;
	private Accessory accessory;

	public Car(int _id, Body b, Motor m, Accessory a)
	{
		id = _id;
		body = b;
		motor = m;
		accessory = a;
	}

	public int getId() { return id; }

	public final Body getBody() { return body; }

	public final Motor getMotor() { return motor; }

	public final Accessory getAccessory() { return accessory; }
}
