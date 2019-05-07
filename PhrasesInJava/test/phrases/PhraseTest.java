package phrases;

import org.junit.Test;
import static org.junit.Assert.assertEquals;

import java.io.*;
import java.util.Map;

public class PhraseTest
{
	@Test
	public void setValues1()
	{
		String args[] = { "-n", "4", "-m", "3" };
		Phrases t = new Phrases(args);
		assertEquals(t.checkSize(), 4);
		assertEquals(t.checkRepetitions(), 3);
	}

	@Test
	public void setValues2()
	{
		String args[] = { "-n", "-5" };
		Phrases t = new Phrases(args);
		assertEquals(t.checkSize(), 2);
		assertEquals(t.checkRepetitions(), 2);
	}

	@Test
	public void readingTest()
	{
		byte[] ba = { 'a', 'a', 'a', ' ', 'a', 'a', 'a', ' ', 's', 's', 's', ' ', 'w', 'w', 'w', ' ',
				'a', 'a', 'a', ' ', 'a', 'a', 'a', ' ', 'a', 'a', 'a', ' ', 's', 's', 's', ' ', 'w', 'w', 'w', ' ',
				'a', 'a', 'a', ' ', 'l', 'l', 'l', ' ', 'a', 'a', 'a', ' ', 'l', 'l', 'l', ' ',  'a', 'a', 'a', ' ',
				's', 's', 's', ' ', 'w', 'w', 'w', ' ', 'w', 'w', 'w' };

		ByteArrayInputStream bais = new ByteArrayInputStream(ba);
		InputStream old = System.in;
		System.setIn(bais);
		String args[] = new String[0];
		Phrases t = new Phrases(args);
		t.readToMap();
		Map<String, Integer> collection = t.getCollection();

		assertEquals(3, (long)collection.get("aaa aaa"));
		assertEquals(3, (long)collection.get("aaa sss"));
		assertEquals(3, (long)collection.get("sss www"));
		assertEquals(2, (long)collection.get("www aaa"));
		assertEquals(2, (long)collection.get("lll aaa"));
		assertEquals(2, (long)collection.get("aaa lll"));
		assertEquals(1, (long)collection.get("www www"));

		System.setIn(old);
	}

	@Test
	public void printResultsTest()
	{
		String args[] = new String[1];
		args[0] = "test.txt";
		Phrases t = new Phrases(args);
		t.readToMap();

		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		PrintStream ps = new PrintStream(baos);
		PrintStream old = System.out;
		System.setOut(ps);

		t.printResults();

		String res = "aaa aaa (6)\r\n" + "aaa i (3)\r\n" + "at all (3)\r\n"
				+ "everything at (3)\r\n" + "i wonna (3)\r\n" + "wonna be (3)\r\n" + "be everything (2)\r\n";
//      in test.txt:
//		aaa aaa aaa
//		i wonna be
//		aaa aaa aaa
//		i wonna be
//		everything at all
//		everything at all
//		aaa aaa aaa
//		i wonna be
//		everything at all

		String output = new String(baos.toByteArray());

		assertEquals(res.replaceAll("\\r", ""),
				output.replaceAll("\\r", ""));

		System.out.flush();
		System.setOut(old);
	}
}
