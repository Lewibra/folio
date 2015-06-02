package asgn1Solution;

import static org.junit.Assert.*;

import org.junit.Test;




import asgn1Question.SimulationException;

public class LogTests {
	
	private static final Integer oneWeek = 7;
	private static final Integer twoWeeks = 14;
	private static final Integer negativeNumber = -10;
	private static final Integer bigPositiveNumber = 200;
	private static final Integer aboveRangeNumber = 201;
	private static final Integer middleOfBigPositiveNumber = 100;
	private static final Integer newestIndex = 0;
	private static final Integer zero = 0;
	private static final Integer testNumber = 50;
	
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if we can initiate a waterLog object
	 * @throws SimulationException
	 * @result Passes if a WaterLog object is created
	 */
	@Test
	public void testSetUp() throws SimulationException {
		@SuppressWarnings("unused")
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
	}
	
	
	
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if a negative number entry into
	 * setting up a new waterLog will be caught.
	 * Passes if the exception of a negative number is thrown.
	 * @throws SimulationException
	 * @result Passes if a non strictly positive number catch is thrown for windowSize
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedSetUpFailNegativeWindowSize() throws SimulationException{
		@SuppressWarnings("unused")
		WaterLog testInstance = new WaterLog(negativeNumber, bigPositiveNumber);
		
	}
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if a negative number entry into
	 * setting up a new waterLog will be caught.
	 * Passes if the exception of a negative number is thrown.
	 * @throws SimulationException
	 * @result passes if a negative parameter catch for maxEntry is thrown
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedSetUpFailNegativeMaxEntry() throws SimulationException{
		@SuppressWarnings("unused")
		WaterLog testInstance = new WaterLog(oneWeek, negativeNumber);
	}
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if the operators (<, >, <=, >=) for the throws 
	 * are set up properly
	 * @throws SimulationException
	 * @result passes if the bare minimum acceptable values for parametres are accepted for windowSize
	 */
	@Test
	public void testSetUpTwo() throws SimulationException{
		Integer lowestAcceptedWindowSize = zero + 1;
		@SuppressWarnings("unused")
		WaterLog testInstance = new WaterLog(lowestAcceptedWindowSize, bigPositiveNumber);
	}
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if the operators (<, >, <=, >=) for the throws 
	 * are set up properly
	 * @throws SimulationException
	 * @result passes if the bare minimum acceptable values for parametres are accepted for maxEntry
	 */
	@Test
	public void testSetUpFive() throws SimulationException{
		Integer lowestAcceptedMaxEntry = zero;
		@SuppressWarnings("unused")
		WaterLog testInstance = new WaterLog(oneWeek, lowestAcceptedMaxEntry);
	}
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if the operators (<, >, <=, >=) for the throws 
	 * are set up properly for windowSize.
	 * non strict positive numbers are rejected, meaning that 0 and below should be
	 * rejected.
	 * We'll sub 0 into windowSize and expect a throw to be caught.
	 * @throws SimulationException
	 * @result passes if 0 for windowSize is rejected
	 */
	@Test (expected = SimulationException.class)
	public void testSetUpThree() throws SimulationException{
		Integer lowestRejectedWindowSize = zero;
		@SuppressWarnings("unused")
		WaterLog testInstance1 = new WaterLog(lowestRejectedWindowSize, bigPositiveNumber);
	}
	
	/**
	 * Method to test: WaterLog(Integer windowSize, Integer maxEntry)
	 * 
	 * Tests to see if the operators (<, >, <=, >=) for the throws 
	 * are set up properly for maxEntry, meaning that it should
	 * reject values of -1 and below.
	 *  We'll sub -1 into maxEntry and expect a throw to be caught
	 * @throws SimulationException
	 * @result passes if the bare minimum rejectable values for parametres are rejected for maxEntry
	 */
	@Test (expected = SimulationException.class)
	public void testSetUpFour() throws SimulationException{
		Integer lowestRejectedMaxEntry = zero - 1;
		@SuppressWarnings("unused")
		WaterLog testInstance1 = new WaterLog(oneWeek, lowestRejectedMaxEntry);
	}
	

	
	
	
	/**
	 * Method to test: addEntry(Integer entry)
	 * 
	 * tests to see if a value within the water
	 * log's window can be added.
	 * @throws SimulationException
	 * @result passes if a value can be added to the waterLog
	 */
	@Test
	public void testCanBeAdded() throws SimulationException {
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.addEntry(middleOfBigPositiveNumber);		
	}
	
	
	
	/**
	 * Tests to see if the whole hashMap can
	 * be filled with values.
	 * 
	 * Also uses assertEquals to see if the values
	 * are being shifted to the right in the hashMap.
	 * @throws SimulationException
	 * @result Passes if one weeks worth of values (7) are added correctly
	 */
	@Test
	public void testFillHashMap() throws SimulationException {
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer eldestIndex = -oneWeek + 1;
		//I will fill the hashMap in the WaterLog with values
		//from 0 to 6 with the indexes of 0 to -N+1 (which is -6)
		//older values will shift to the right
		for (Integer i = 0; i < oneWeek; i++) {
			testInstance.addEntry(i);	
			//passes if values are shifting along, and are equal to what they should be
			assertEquals( i, testInstance.getEntry(newestIndex));
		}
		
		//Checking to see if the final hashMap stored the values correctly
		//with the newest entry at the front (with an index of 0) and
		//the eldest entry at the back with an index of  (-n+1).
		
		//Eldest Entry was i = 0
		assertEquals("Last entry index = -n + 1", (Integer)0, testInstance.getEntry(eldestIndex));
		//Newest entry was i = 6
		assertEquals("Newest entry index = 0", (Integer)6, testInstance.getEntry(newestIndex));
		//middle entries (Index -1 to -5)
		Integer index;
		for (Integer j = 1; j < 5; j++) {
			index = -oneWeek+ (j+1); //index will be {-1, -2, -3, -4, -5}
			assertEquals(j, testInstance.getEntry(index));
		}
	}
	
	
	/**
	 * Method to test: addEntry(Integer newEntry)
	 * 
	 * Passes if it throws when an entry not within range
	 * of 0 and the maxEntry is attempted to be added to
	 * the waterLog. This case is BELOW the range.
	 * @throws SimulationException
	 * @result Passes if the throw exception, of adding a number not in range if the window (0 to maxEntry), is caught
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedAddEntryBelow() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.addEntry(negativeNumber);
	}
	
	/**
	 * Method to test: addEntry(Integer newEntry)
	 * 
	 * Passes if it throws when an entry not within range
	 * of 0 and the maxEntry is attempted to be added to
	 * the waterLog. This case is the smallest rejectable
	 * value that is BELOW the range; which is -1.
	 * @throws SimulationException
	 * @result Passes if the throw exception, of adding a number not in range if the window (0 to maxEntry), is caught
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedAddEntryBelowTwo() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer smallestRejectable = -1;
		testInstance.addEntry(smallestRejectable);
	}
	
	/**
	 * Method to test: addEntry(Integer newEntry)
	 * 
	 * tests to see if the given range can be added to
	 * the log; api states to throw if the given value is not in the range 0 to maxEntry, inclusive
	 * @throws SimulationException
	 * @result Passes 0 to maxEntry can be added
	 */
	@Test
	public void testExpectedAddEntryRangeWorking() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer maxEntry = bigPositiveNumber;
		
		//Testing to see if all values between 0 and the maxEntry can be added
		for (Integer acceptableValues = 0; acceptableValues <= maxEntry; acceptableValues++){
			testInstance.addEntry(acceptableValues);
		}

	}
	
	/**
	 * Method to test: addEntry(Integer newEntry)
	 * 
	 * Passes if it throws when an entry not within range
	 * of 0 and the maxEntry is attempted to be added to
	 * the waterLog. This case is ABOVE the range.
	 * @throws SimulationException
	 * @result Passes if the throw exception, of adding a number not in range if the window (0 to maxEntry), is caught
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedAddAboveRange() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		//Adding a number above the maxEntry is expected to fail
		testInstance.addEntry(aboveRangeNumber);
	}
	
	/**
	 * Method to test: addEntry(Integer newEntry)
	 * 
	 * Passes if it throws when an entry not within range
	 * of 0 and the maxEntry is attempted to be added to
	 * the waterLog. This case is ABOVE the maximum range by 1 unit.
	 * Meaning maxEntry+1;
	 * @throws SimulationException
	 * @result Passes if the throw exception, of adding a number not in range if the window (0 to maxEntry), is caught
	 */
	@Test (expected = SimulationException.class)
	public void testExpectedAddAboveRangeTwo() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer justAbove = bigPositiveNumber + 1;
		//Adding a number above the maxEntry is expected to fail
		testInstance.addEntry(justAbove);
	}
	
	
	/**
	 * 
	 *Test getEntry throw exceptions
	 * getEntry returns the log entry at the
	 * given index.
	 * If the index is not in range (e.g. there are indexes from 0 to -6
	 * getEntry will throw if it's parameter is 7)
	 * @result Passes if the throw exception, of using getEntry to return the value of an invalid index, is caught
	 */
	@Test (expected = SimulationException.class)
	public void testGetEntryThrow() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		//Try to access index 14, two weeks into the future! This is expected to fail.
		testInstance.getEntry(twoWeeks);
	}
	
	/**
	 * Tests the operators (<, >, <=, >=) for
	 * the getEntry method's index parameter.
	 * We will attempt to acces an index that is too large. (-8)
	 * @result Passes if the closest index outside the edge of the range is rejected
	 */
	@Test (expected = SimulationException.class)
	public void testGetEntryOperators() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer eightDays = -(oneWeek + 1);
		//Try to acces data from index -8(8 days ago). This is expected to fail.
		testInstance.getEntry(eightDays);
	}
	
	/**
	 *Tests the operators (<, >, <=, >=) for
	 * the getEntry method's index parameter.
	 * We will attempt to access an index that is too low (1)
	 * @result Passes if the closest index outside the beginning of the range is rejected
	 */
	@Test (expected = SimulationException.class)
	public void testGetEntryOperatorsTwo() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		Integer tomorrow = newestIndex + 1;
		//Try to access the data from, supposedly, tomorrow. This is expected to fail.
		testInstance.getEntry(tomorrow);
	}
		

	
	/**
	 * tests to see if WaterLog.getEntry(Integer index)
	 * returns the correct value in the WaterLog
	 * @throws SimulationException
	 * @result Passes if the getEntry method returns the value in the newest index, which is 50
	 */
	@Test
	public void testGetEntry() throws SimulationException {
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		//Add two random numbers
		testInstance.addEntry(middleOfBigPositiveNumber);
		testInstance.addEntry(testNumber);
		
		//The newest entry is expected to be equal to testNumber
		assertEquals("Index 0 should hold testNumber = 50",testNumber, testInstance.getEntry(newestIndex));
	}
	
	
	/**
	 * Tests to see if WaterLog.numEntries() returns
	 * the correct amount of entries added to the
	 * WaterLog
	 * @throws SimulationException
	 * @result Passes if the correct amount of entries made is returned by the numEntries() method
	 */
	@Test
	public void testNumEntriesMethod() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		//lets add 14 values to the testInstance
		for (Integer i = 0; i < twoWeeks; i++) {
			testInstance.addEntry(i);	
		}
		//testInstance.numEntries() should return twoWeeks = 14
		assertEquals("testInstance.numEntries() should return twoWeeks = 14", twoWeeks, testInstance.numEntries());
		
	}

	/**
	 * Tests WaterLog.Variaton()'s throw exception
	 * which is if you use Variation() on a log with 0 entries
	 * @result Passes if the throw of no entries is caught
	 */
	@Test (expected = SimulationException.class)
	public void testVariationThrowException() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.variation();
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it can return 0, the correct amount for a water log
	 * with 3 entries (all the same) and window of 7
	 * @result Passes if 0 is returned
	 */
	@Test
	public void testVariationOne() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.addEntry(testNumber);
		testInstance.addEntry(testNumber);
		testInstance.addEntry(testNumber);
		//variation = newestEntry - eldest ever
		Integer expectedVariation = testNumber - testNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it can return 0, the correct amount for a water log
	 * with 7 entries (all the same) and window of 7
	 * @result Passes if 0 is returned
	 */
	@Test
	public void testVariationTwo() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		for (Integer i = 0; i < oneWeek; i++) {
			testInstance.addEntry(testNumber);
		}
		//variation = newestEntry - eldest ever
		Integer expectedVariation = testNumber - testNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it will return a negative value because
	 * the newest entry will be smaller than that of the
	 * last index. This is for a water log with only 3 entries,
	 * and a windowSize of 7
	 * @result Passes if the correct positive amount is returned
	 */
	@Test
	public void testVariationThree() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.addEntry(testNumber);
		testInstance.addEntry(testNumber);
		testInstance.addEntry(bigPositiveNumber);
		//variation = newestEntry - eldest ever
		Integer expectedVariation = bigPositiveNumber - testNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it will return a positive value because
	 * the newest entry will be larger than that of the
	 * last index.  This is for a water log with only 3 entries,
	 * and a windowSize of 7; This shows that the waterLog can also
	 * keep track of the eldest entry ever.
	 * @result Passes if the correct negative amount is returned
	 */
	@Test
	public void testVariationFour() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		testInstance.addEntry(bigPositiveNumber);
		testInstance.addEntry(testNumber);
		testInstance.addEntry(testNumber);
		//variation = newestEntry - eldest ever
		Integer expectedVariation = testNumber - bigPositiveNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it will return 0 for a water log
	 * with 14 entries (All the same) and window of 7
	 * @result Passes if 0 is returned
	 */
	@Test
	public void testVariationFive() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		for (Integer i = 0; i < twoWeeks; i++) {
			testInstance.addEntry(testNumber);
		}
		//variation = newestEntry - eldest ever
		Integer expectedVariation = testNumber - testNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it will return a negative value for a water log
	 * with 15 entries (where the newest entry is smaller than that of the last index) and window of 7
	 * @result Passes if the correct negative amount is returned
	 * 
	 */
	@Test
	public void testVariationSix() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		for (Integer i = 0; i < twoWeeks; i++) {
			testInstance.addEntry(bigPositiveNumber);
		}
		testInstance.addEntry(testNumber);
		//variation = newestEntry - eldest ever
		Integer expectedVariation = testNumber - bigPositiveNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	/**
	 * Tests WaterLog.variation() to see if 
	 * it will return a negative value for a water log
	 * with 15 entries (where the newest entry is smaller than that of the last index) and window of 7
	 * @result Passes if the correct positive amount is returned
	 */
	@Test
	public void testVariationSeven() throws SimulationException{
		WaterLog testInstance = new WaterLog(oneWeek, bigPositiveNumber);
		for (Integer i = 0; i < twoWeeks; i++) {
			testInstance.addEntry(testNumber);
		}
		testInstance.addEntry(bigPositiveNumber);
		//variation = newestEntry - eldest ever
		Integer expectedVariation = bigPositiveNumber - testNumber;
		assertEquals("testInstanc.variation should return 0",expectedVariation, testInstance.variation());
	}
	
	
}
