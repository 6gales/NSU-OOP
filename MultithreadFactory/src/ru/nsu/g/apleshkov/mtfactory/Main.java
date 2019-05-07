package ru.nsu.g.apleshkov.mtfactory;

import ru.nsu.g.apleshkov.mtfactory.view.View;

import java.io.IOException;

public class Main
{
	static public void main(String args[])
	{
		View obs = new View();

		try
		{
			Factory f = new Factory(obs);
			f.run();
		}
		catch (IOException e) { System.out.println(e.getMessage()); }
		System.out.println("Main? finished");
	}
}
