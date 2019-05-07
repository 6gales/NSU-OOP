package ru.nsu.g.apleshkov.stacklang;

import ru.nsu.g.apleshkov.stacklang.operationFactories.OperationFactory;
import ru.nsu.g.apleshkov.stacklang.operations.*;
import ru.nsu.g.apleshkov.stacklang.exceptions.OperationNotFoundException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;
import java.util.TreeMap;
import java.util.Properties;

public class SyntaxInterpreter
{
	private Context context;

	private Map<String, OperationFactory> factories;

	private Map<String, Operation> operations;

	private Properties opProperties,
			factProperties;

	private String operationPackage = "ru.nsu.g.apleshkov.stacklang.operations.",
			factoryPackage = "ru.nsu.g.apleshkov.stacklang.operationFactories.";

	SyntaxInterpreter(Context _context)
	{
		context = _context;

		factories = new HashMap<>();

		operations = new HashMap<>();

		loadProperties();
	}

	private void loadProperties()
	{
		try{
			InputStream in = this.getClass().getResourceAsStream("factories.properties");
			factProperties = new Properties();
			factProperties.load(in);
		}
		catch (IOException e) { System.out.println(e.getMessage()); }

		try{
			InputStream in = this.getClass().getResourceAsStream("operations.properties");
			opProperties = new Properties();
			opProperties.load(in);
		}
		catch (IOException e) { System.out.println(e.getMessage()); }
	}

	private boolean isParsable(String str)
	{
		try
		{
			Integer.parseInt(str);
			return true;
		}
		catch (NumberFormatException e)
		{
			return false;
		}
	}

	private <T> boolean load(String nickname, String className, Map<String, T> into)
			throws ClassNotFoundException, IllegalAccessException, ClassCastException,
			InstantiationException, NoSuchMethodException, InvocationTargetException
	{
		T object = (T) Class.forName(className).getDeclaredConstructor().newInstance();
		into.put(nickname, object);
		return true;
	}

	private boolean load(String nickname)
			throws ClassNotFoundException, IllegalAccessException, InstantiationException,
			NoSuchMethodException, InvocationTargetException
	{
		String className = nickname.substring(0, 1).toUpperCase() + nickname.substring(1);

		try
		{
			Operation object = (Operation) Class.forName(operationPackage + className)
					.getDeclaredConstructor().newInstance();
			operations.put(nickname, object);
			return true;
		}
		catch (Exception e) {}

		OperationFactory object = (OperationFactory) Class.forName(factoryPackage + className)
				.getDeclaredConstructor().newInstance();
		factories.put(nickname, object);
		return true;

	}

	public Operation choose(String command, InputSequence input) throws Exception
	{
		if (factories.containsKey(command))
		{
			return factories.get(command).createOperation(input, this);
		}

		if (operations.containsKey(command))
		{
			return operations.get(command);
		}

		if (context.isDefined(command))
		{
			return context.getDefine(command);
		}

		if (isParsable(command))
		{
			Push p = new Push(command);
			operations.put(command, p);
			return p;
		}

		String name;
		if ((name = opProperties.getProperty(command)) != null)
		{
			if (load(command, name, operations))
				return choose(command, input);
		}

		if ((name = factProperties.getProperty(command)) != null)
		{
			if (load(command, name, factories))
				return choose(command, input);
		}

		if (load(command))
			return choose(command, input);

		throw new OperationNotFoundException();
	}
}