import java.util.*;
import java.io.File;

public class StringData
{
	private static String[] stringDataSet = null;

	public static String[] getData()
	{
		if (stringDataSet == null)
		{
			stringDataSet = new String[26 * 26 * 26 * 26 * 26];
			char[] tempSet = new char[5];
			int index = 0;

			for (tempSet[0] = 'a'; tempSet[0] <= 'z'; tempSet[0]++)
			{
				for (tempSet[1] = 'a'; tempSet[1] <= 'z'; tempSet[1]++)
				{
					for (tempSet[2] = 'a'; tempSet[2] <= 'z'; tempSet[2]++)
					{
						for (tempSet[3] = 'a'; tempSet[3] <= 'z'; tempSet[3]++)
						{
							for (tempSet[4] = 'a'; tempSet[4] <= 'z'; tempSet[4]++)
							{
								stringDataSet[index++] = new String(tempSet);
							}
						}
					}
				}
			}
		}

		return stringDataSet;
	}
}