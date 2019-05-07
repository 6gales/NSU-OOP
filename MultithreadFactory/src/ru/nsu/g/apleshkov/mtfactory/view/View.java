package ru.nsu.g.apleshkov.mtfactory.view;

import ru.nsu.g.apleshkov.mtfactory.Item;
import ru.nsu.g.apleshkov.mtfactory.Storage;
import ru.nsu.g.apleshkov.mtfactory.staff.Staff;

import javax.swing.*;
import java.awt.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Observable;
import java.util.Observer;
import java.util.TreeMap;
import java.util.concurrent.Callable;

public class View implements Observer
{
	private Map<String, List<JComponent>> components;

	private JFrame frame;
	private GridLayout layout;

	private int rows = 0;
	private final int columns = 3;

	private final int nameLabel = 0,
		infoLabel = 1,
		progressBar = 2;

	private JPanel panel;

	public View()
	{
		components = new TreeMap<>();

		frame = new JFrame("Factory");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setSize(1400,700);

		panel = new JPanel();
		frame.add(panel);

		panel.setLayout(layout = new GridLayout(rows, columns));

		frame.setVisible(true);
	}

	private void addComponents(String name, List<JComponent> row, JComponent third)
	{
		layout.setRows(++rows);
		components.put(name, row);

		row.add(new JLabel(name, SwingConstants.CENTER));
		row.add(new JLabel("", SwingConstants.CENTER));
		row.add(third);

		for (var i : row)
			panel.add(i);

		frame.revalidate();
	}

	private List<JComponent> getRow(String name, Callable<JComponent> creator)
	{
		List<JComponent> row;

		if (!components.containsKey(name))
		{
			row = new ArrayList<>(columns);

			try
			{
				addComponents(name, row, creator.call());
			}
			catch (Exception e)
			{
				e.printStackTrace();
			}
		}
		else row = components.get(name);

		return row;
	}

	private void updateStorageInfo(Storage o)
	{
		String name = o.getName();

		List<JComponent> row = getRow(name, () -> {
					JProgressBar pb = new JProgressBar(0, 100);
					pb.setStringPainted(true);
					return pb; });

		int size = o.size(),
			capacity = o.capacity();

		((JLabel)row.get(infoLabel)).setText(size + "/" + capacity);
		((JProgressBar)row.get(progressBar)).setValue(size * 100 / capacity);
	}

	private void updateStatusInfo(String name, String arg)
	{
		List<JComponent> row = getRow(name, JLabel::new);

		((JLabel)row.get(infoLabel)).setText(arg);
	}

	@Override
	public void update(Observable o, Object arg)
	{
		if (o instanceof Storage)
		{
			updateStorageInfo((Storage)o);
		}
		else if (o instanceof Staff)
		{
			updateStatusInfo(((Staff)o).getName(), (String)arg);
		}
		else if (o instanceof Item)
		{
			updateStatusInfo(((Item)o).getName(), (String)arg);
		}
	}
}
