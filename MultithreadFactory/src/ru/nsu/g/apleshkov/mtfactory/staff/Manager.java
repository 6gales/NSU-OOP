package ru.nsu.g.apleshkov.mtfactory.staff;

import java.util.List;

public class Manager
{
	public interface StaffCreator
	{
		Runnable create(int id, String name);
	}

	private List<Thread> staff;

	public Manager(List<Thread> staff)
	{
		this.staff = staff;
	}

	public void createStaff(int num, String name, StaffCreator sc)
	{
		for (int i = 0; i < num; i++)
		{
			staff.add(new Thread(sc.create(i, name + " " + i)));
		}
	}
}
