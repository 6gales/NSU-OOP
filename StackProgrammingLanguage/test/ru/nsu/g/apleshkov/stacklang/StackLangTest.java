package ru.nsu.g.apleshkov.stacklang;

import org.junit.Assert;
import org.junit.Test;
import ru.nsu.g.apleshkov.stacklang.operations.Add;
import ru.nsu.g.apleshkov.stacklang.operations.Operation;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import static org.junit.Assert.fail;


public class StackLangTest
{
	@Test
	public void contextTest()
	{
		Context context = new Context();

		assertNotNull(context.getStack());
		assertEquals("class java.util.Stack", context.getStack().getClass().toString());
		context.define("add", new Add());
		assertNotNull(context.getDefine("add"));
		assertEquals("class ru.nsu.g.apleshkov.stacklang.operations.Add", context.getDefine("add").getClass().toString());
		assertTrue(context.isDefined("add"));
		context.undef("add");
		assertNull(context.getDefine("add"));
		assertFalse(context.isDefined("add"));
	}

	@Test
	public void inputSeqTest()
	{
		InputSequence input = new InputSequence("programm.txt");
		String expected = "define factorial 1 swap dup [ dup rot * swap 1 - dup ] drop ; 5 factorial print ",
				result = "";
		while (input.hasNext())
			result += input.next() + ' ';
		input.close();
		assertEquals(expected, result);
	}

	@Test
	public void interpreterTest()
	{
		Context context = new Context();
		InputSequence input = new InputSequence("programm.txt");
		SyntaxInterpreter interpreter = new SyntaxInterpreter(context);

		String command;
		while (input.hasNext())
		{
			command = input.next();
			Operation op = null;
			try
			{
				op = interpreter.choose(command, input);

				if (command.equals("define"))
				{
					assertEquals("class ru.nsu.g.apleshkov.stacklang.operations.DefineOp",
							op.getClass().toString());
					op.operate(context);
				}
				else if (command.equals("["))
					assertEquals("class ru.nsu.g.apleshkov.stacklang.operations.LoopOp",
							op.getClass().toString());
			} catch (Exception e) { fail(); }
		}

	}
}
