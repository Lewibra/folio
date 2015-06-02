package asgn1Solution;

import static org.junit.Assert.*;

import org.junit.Test;

import asgn1Question.SimulationException;

public class ActionsTests {
	
	private static final Integer oneWeek = 7;
	private static final Integer negativeNumber = -10;
	private static final Integer reallyLargeWindow = 5000;
	private static final Integer overflowableAmount = 4000;
	private static final Integer noOutFlow = 0;
	private static final Integer noInFlow = 0;
	private static final Integer empty = 0;
	


	private static final Integer newestIndex = 0;

	
	private static final Integer oddTestNumber = 1243;
	//Rounded down when halving oddTestNumber
	private static final Integer idealHalfOfTestNumber = 621;
	
	private static final Integer largeDamCapacity = 3000;
	private static final Integer failableDamCapacity = 99;
	private static final Integer normalDefaultRelease = 150;
	private static final Integer normalHalfRelease = normalDefaultRelease/2;
	private static final Integer normalDoubleRelease = normalDefaultRelease*2;
	private static final Integer normalWaterConsumption = 200;
	private static final Integer normalWaterInflow = 200;
	
	public WaterLog damLog;
	

	/**
	 * Methods to test if the DamActions constructor works
	 * @result passes if the DamAction can be constructed
	 */
	@Test
	public void testDamActions() throws SimulationException{
		//we need to set up a water log for the DamActions
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		@SuppressWarnings("unused") 
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
	}
	
	/**
	 * Testing the throws of DamActions constructor
	 * @result passes if the damCapacity being less than 100ml throw is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDamActionsThrowOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		
		//substituting in a fail-able damCapacity parameter
		@SuppressWarnings("unused") 
		DamActions testInstance = new DamActions(failableDamCapacity, normalDefaultRelease, oneWeek, damLog);
	}
	
	/**
	 * Testing the throws of DamActions constructor
	 * @result passes if the possibility of the job duration being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDamActionsThrowTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		
		//substituting in a negative job duration
		@SuppressWarnings("unused") 
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, negativeNumber, damLog);
	}
	
	/**
	 * Testing the throws of DamActions constructor testing with a negative number
	 * @result passes if the possibility of the default release not being strictly positive is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDamActionsThrowThree() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		
		//substituting in a negative job duration
		@SuppressWarnings("unused") 
		DamActions testInstance = new DamActions(largeDamCapacity, negativeNumber, oneWeek, damLog);
	}
	
	/**
	 * Testing the throws of DamActions constructor, testing with 0
	 * @result passes if the possibility of the default release not being strictly positive is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDamActionsThrowFour() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		
		//substituting in a negative job duration
		@SuppressWarnings("unused") 
		DamActions testInstance = new DamActions(largeDamCapacity, empty, oneWeek, damLog);
	}
	
	
	
	/**
	 * Testing to see if the first entry (assumed as half the true capacity)
	 * is actually the ideal half of the true capacity
	 * ; e.g., if the dam's capacity is 1,243ML then the water level on the first day should be 621ML
	 * @throws SimulationException
	 * @result Passes if the dams capacity is rounded down correctly for the first day
	 */
	@Test
	public void testDamActionsRoundDown() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, oddTestNumber);
		@SuppressWarnings("unused")
		DamActions testInstance = new DamActions(oddTestNumber, normalDefaultRelease, oneWeek, damLog);
		
		//the right answer will be half of the oddTestNumber rounded down
		//idealHalfOfTest number is the ideal half of oddTestNumber (621 and 1243)
		Integer rightAnswer = idealHalfOfTestNumber;
		Integer firstDay = damLog.getEntry(newestIndex);
		//Comparing the two variables.
		assertEquals("This fails if the initial starting capacity is wrong",rightAnswer, firstDay);
	}
	
	/**
	 * Testing damOverFlowed returns true if the previous day's intake + the current day's inflow
	 * and minus the outflow has exceeded the full dam capacity.
	 * @results Passes if the DamAction floods
	 */
	@Test
	public void testDamOverFlowedTrue() throws SimulationException{
		//I'm going to increase the WaterLog window so I
		//can add an amount larger than the damCapacity
		//to flood it :)
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		testInstance.defaultRelease(noOutFlow, overflowableAmount);
		//this should return as true because I added 4000mega litres
		//to a dam with a capacity 3000ML
		assertTrue("The dam was expected to flood",testInstance.damOverflowed());
	}
	
	/**
	 * Testing damOverFlowed returns false if the previous day's intake + the current day's inflow
	 * and minus the outflow does not exceeded the full dam capacity.
	 * @results Passes if the DamAction does not flood
	 */
	@Test
	public void testDamOverFlowedFalse() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		//this should return true, I will add 150ML to the dam,
		//leaving it just abit over the halfway mark
		testInstance.defaultRelease(noOutFlow, normalDefaultRelease);
		assertFalse("The dam shouldn't have flooded",testInstance.damOverflowed());
	}
	
	/**
	 * If the water level is equal to the dam capacity, it is still acceptable
	 * as not flooding. Lets test if damOverflowed() realises this
	 * @throws SimulationException
	 * @result Passes if damOverFlowed() returns false if the level is equal, and false when 1ML above
	 */
	@Test
	public void testDamOverFlowedEven() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		
		//Now I'm going to test if this returns false if the
		//water level is the same as the capacity,
		//it should still count as not overflowed.
		//Half the dam capacity plus the normaldefault release should be enough water
		//to make the level equal to the dam capacity
		Integer fillUpToMax = (largeDamCapacity/2) + normalDefaultRelease;
		testInstance.defaultRelease(noOutFlow, fillUpToMax);
		assertFalse(testInstance.damOverflowed());

	}
	
	/**
	 * testing to see if the waterLevel being on the maximum
	 * capacity plus 1, should get the manager fired!
	 * @throws SimulationException
	 * @result Passes if you get fired when if the dam overflows by 1ML
	 */
	@Test
	public void testDamOverFlowedByOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//variable to hold an amount of water that will overflow the dam by 1ML
		Integer getToOneOver = normalDefaultRelease + (largeDamCapacity/2) + 1;
		//this statement will get the waterLevel equal to the largeDamCapacity
		testInstance.defaultRelease( noOutFlow, getToOneOver);
		assertTrue("The dam should have flooded",testInstance.damOverflowed());
	}
	
	
	
	
	/**
	 * Testing levelTooLow to see if it will return true
	 * if the currentWaterLevel has fallen beneath the 
	 * threshold
	 * @result Passes if the DamAction water level is too low
	 */
	@Test
	public void testLevelTooLowOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		//this should return true, I will add 150ML to the dam,
		//leaving it just abit over the halfway mark
		
		//The minimum threshold for largeDamCapacity is 750ML
		//getLevelOneBelowThresh when put into default release will get the water level
		//to 749ML
		Integer getLevelOneBelowThresh = 600  +1;
		testInstance.defaultRelease(getLevelOneBelowThresh, noInFlow);
		
		//This will come up true if the dam level is too low!
		assertTrue(testInstance.levelTooLow());
	}
	
	/**
	 * Testing levelTooLow to see if it will return false
	 * if the currentWaterLevel is at the minimum capacity threshold
	 * @result Passes if the DamAction water is not too low
	 */
	@Test
	public void testLevelTooLowTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		//this should return true, I will add 150ML to the dam,
		//leaving it just abit over the halfway mark
		
		//The minimum threshold for largeDamCapacity is 750ML
		
		//The below few statements will get the waterLevel to 750ML
		Integer getToThresh = 600;
		testInstance.defaultRelease(getToThresh, noInFlow);
		//This will come up true if the dam level is fine;
		assertFalse(testInstance.levelTooLow());

	}
	
	
	/**
	 * Testing levelTooLow to see if it will return false
	 * if the currentWaterLevel is one ML above the minimum capacity threshold
	 * @result Passes if the DamAction water is not too low
	 */
	@Test
	public void testLevelTooLowThree() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		//this should return true, I will add 150ML to the dam,
		//leaving it just abit over the halfway mark
		
		//The minimum threshold for largeDamCapacity is 750ML
		//The below few statements will get the waterLevel to 751ML
		Integer getToOneAboveThresh = 599;
		testInstance.defaultRelease(getToOneAboveThresh, noInFlow);
		//This will come up true if the dam level is fine;
		assertFalse(testInstance.levelTooLow());

	}

	
	


	
	
	/**
	 * Test to see if the defaultRelease method can calculate a new water level
	 * by releasing the default amount of water, track the day's water consumption and
	 * inflow, and add that all with the previous day's water level.
	 * @throws SimulationException
	 * @result Passes if the expected water level after using defaultRelease is what we want
	 */
	@Test
	public void testDefaultReleaseReleasing() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		Integer currentWaterLevel = largeDamCapacity/2;
		//The current water level is half of the dam's capacity, which should be 1500ML
		//Lets add and release some water
		//This will release 200MLs aswell as 150ML for the defaultRelease, and add 200MLs
		//Leaving a 150ML deacrease
		testInstance.defaultRelease(normalWaterConsumption, normalWaterInflow);
		
		//The current water level should be equal to:
		//current water level + normalWaterInflow - (normalDefaultRelease + normalWaterInflow)
		Integer expectedWaterLevel = currentWaterLevel + normalWaterInflow - (normalDefaultRelease + normalWaterInflow);
		//See if this is right
		assertEquals(expectedWaterLevel, damLog.getEntry(newestIndex));	
	}
	
	/**
	 * same as {@link #testDefaultReleaseReleasing()} but with HalfRelease
	 * @throws SimulationException
	 * @result Passes if the expected water level after using defaultRelease is what we want
	 */
	@Test
	public void testHalfReleaseReleasing() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		Integer currentWaterLevel = largeDamCapacity/2;
		//The current water level is half of the dam's capacity, which should be 1500ML
		//Lets add and release some water
		//This will release 200MLs aswell as 75ML for the defaultRelease, and add 200MLs
		//Leaving a 150ML deacrease
		testInstance.halfRelease(normalWaterConsumption, normalWaterInflow);
		
		//The current water level should be equal to:
		//current water level + normalWaterInflow - (normalHalfRelease + normalWaterInflow)
		Integer expectedWaterLevel = currentWaterLevel + normalWaterInflow - (normalHalfRelease + normalWaterInflow);
		//See if this is right
		assertEquals(expectedWaterLevel, damLog.getEntry(newestIndex));	
	}
	
	
	/**
	 * same as {@link #testDefaultReleaseReleasing()} but with doubleRelease
	 * @throws SimulationException
	 * @result Passes if the expected water level after using defaultRelease is what we want
	 */
	@Test
	public void testDoubleReleaseReleasing() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, largeDamCapacity);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		Integer currentWaterLevel = largeDamCapacity/2;
		//The current water level is half of the dam's capacity, which should be 1500ML
		//Lets add and release some water
		//This will release 200MLs aswell as 75ML for the defaultRelease, and add 200MLs
		//Leaving a 150ML deacrease
		testInstance.doubleRelease(normalWaterConsumption, normalWaterInflow);
		
		//The current water level should be equal to:
		//current water level + normalDoubleRelease - (normalHalfRelease + normalWaterInflow)
		Integer expectedWaterLevel = currentWaterLevel + normalWaterInflow - (normalDoubleRelease + normalWaterInflow);
		//See if this is right
		assertEquals(expectedWaterLevel, damLog.getEntry(newestIndex));	
	}
	
	
	/**
	 * These few tests below are to test the fact that theoretically, the water level can't be below 0 
	 * and it also can't hold more water than it's capacity. Therefore, if the the value
	 * to be recorded to the log would be 0 if the dam looses all of it's water. It will
	 * also record the water level as the maximum if the water level exceeds the capacity.
	 * @throws SimulationException
	 * @result Passes if 0 is recorded when more litres than the capacity is taken out
	 */
	@Test
	public void testDoubleReleaseRange() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		
		//Completly drain the dam with more water than the capacity
		testInstance.doubleRelease(reallyLargeWindow, noInFlow);
		testInstance.doubleRelease(reallyLargeWindow, noInFlow);
		//The most recent entry should be 0 ML
		assertEquals(damLog.getEntry(newestIndex), empty);
		
		
	}
	
	
	/**
	 * Test to see if draining the dam with more water than it's capacity with defaultRelease
	 * will make the water level stay at 0ML
	 * @throws SimulationException
	 */
	@Test
	public void testDefaultReleaseRange() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		
		
		//Do the same thing as above, but with default and half release
		testInstance.defaultRelease(reallyLargeWindow, noInFlow);
		testInstance.defaultRelease(reallyLargeWindow, noInFlow);
		assertEquals(damLog.getEntry(newestIndex), empty);

	}
	
	/**
	 * Test to see if draining the dam with more water than it's capacity with halfRelease
	 * will make the water level stay at 0ML
	 * @throws SimulationException
	 */
	@Test
	public void testHalfReleaseRange() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);

		//Do the same thing as above, but with default and half release
		testInstance.halfRelease(reallyLargeWindow, noInFlow);
		testInstance.halfRelease(reallyLargeWindow, noInFlow);
		assertEquals(damLog.getEntry(newestIndex), empty);
	}
	
	/**
	 * Test to see if flooding the dam with more water than it's capacity by using doubleRelease
	 * will make the water level stay at the maximum capacity
	 * @throws SimulationException
	 */
	@Test
	public void testDoubleReleaseRangeFlood() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
	
		//Now let's flood the dam way past the capacity!!
		testInstance.doubleRelease(noOutFlow, reallyLargeWindow);
		testInstance.doubleRelease(noOutFlow, reallyLargeWindow);
		//now the most recent entry should be equal to largeDamCapacity
		assertEquals(damLog.getEntry(newestIndex), largeDamCapacity);
	}
	
	
	/**
	 * Test to see if flooding the dam with more water than it's capacity by using defaultRelease
	 * will make the water level stay at the maximum capacity
	 * @throws SimulationException
	 */
	@Test
	public void testDefaultReleaseRangeFlood() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//Do the same thing above, but with half and default release
		testInstance.defaultRelease(noOutFlow, reallyLargeWindow);
		testInstance.defaultRelease(noOutFlow, reallyLargeWindow);
		assertEquals(damLog.getEntry(newestIndex), largeDamCapacity);
	}
	
	/**
	 * Test to see if flooding the dam with more water than it's capacity by using halfRelease
	 * will make the water level stay at the maximum capacity
	 * @throws SimulationException
	 */
	@Test
	public void testHalfReleaseRangeFlood() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		//Do the same thing as above, but with default and half release
		testInstance.halfRelease(noOutFlow, reallyLargeWindow);
		testInstance.halfRelease(noOutFlow, reallyLargeWindow);
		assertEquals(damLog.getEntry(newestIndex), largeDamCapacity);
	}
	
	
	
	
	
	/**
	 * Testing the throws for defaultRelease, this one is where the given WaterConsumption
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given consumption for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDefaultReleaseThrowOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.defaultRelease(negativeNumber, noInFlow);

	}
	
	/**
	 * Testing the throws for defaultRelease, this one is where the given water
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given inflow for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDefaultReleaseThrowTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.defaultRelease(noOutFlow, negativeNumber);
	}
	
	/**
	 * Testing the throws for HalfRelease, this one is where the given WaterConsumption
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given consumption for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testHalfReleaseThrowOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.halfRelease(negativeNumber, noInFlow);

	}
	
	/**
	 * Testing the throws for HalfRelease, this one is where the given water
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given inflow for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testHalfReleaseThrowTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.halfRelease(noOutFlow, negativeNumber);
	}
	
	/**
	 * Testing the throws for DoubleRelease, this one is where the given WaterConsumption
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given consumption for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDoubleReleaseThrowOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.doubleRelease(negativeNumber, noInFlow);

	}
	
	/**
	 * Testing the throws for DoubleRelease, this one is where the given water
	 * can't be negative. Similar to the tests below with negative numbers, but this one
	 * has a larger negative value.
	 * @throws SimulationException
	 * @result Passes if the given inflow for defaultRelease being negative is caught
	 */
	@Test (expected = SimulationException.class)
	public void testDoubleReleaseThrowTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the dailyOutflow as a negative number
		testInstance.doubleRelease(noOutFlow, negativeNumber);
	}
	
	
	
	
	
	/**
	 * Testing the todaysConsumption and todaysInflow parameters negative throw
	 * in defaultRelease. We want to see if a positive number
	 * can be used for it. Negative numbers are rejected though.
	 * @throws SimulationException
	 * @result Passes if positive numbers are accepted for todaysConsumption and todaysInflow
	 */
	@Test
	public void testDefaultReleaseParametresOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest acceptable positive values in, which are 0
		Integer lowestPositive = 0;
	    testInstance.defaultRelease(lowestPositive, lowestPositive);
	    //double check by increasing the value to 1
	    Integer doubleCheck = 1;
	    testInstance.defaultRelease(doubleCheck, doubleCheck);
	}
	
	/**
	 * Testing the todaysConsumption parameter negative throw
	 * in defaultRelease. Similar to testDefaultReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1
	 */
	@Test (expected = SimulationException.class)
	public void testDefaultReleaseParametresTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.defaultRelease(lowestFailableNumber, noOutFlow);
	}
	
	/**
	 * Testing the todaysInflow parameter negative throw
	 * in defaultRelease. Similar to testDefaultReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1
	 */
	@Test (expected = SimulationException.class)
	public void testDefaultReleaseParametresThree() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.defaultRelease(noInFlow, lowestFailableNumber);
	}
	
	
	
	
	/**
	 * Testing the todaysConsumption and todaysInflow parameters negative throw
	 * in doubleRelease. We want to see if a positive number
	 * can be used for it. Negative numbers are rejected though.
	 * @throws SimulationException
	 * @result Passes if positive numbers are accepted for todaysConsumption and todaysInflow in doubleRelease
	 */
	@Test
	public void testDoubleReleaseParametresOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest acceptable positive values in, which are 0
		Integer lowestPositive = 0;
	    testInstance.defaultRelease(lowestPositive, lowestPositive);
	    //double check by increasing the value to 1
	    Integer doubleCheck = 1;
	    testInstance.doubleRelease(doubleCheck, doubleCheck);
	}
	
	/**
	 * Testing the todaysConsumption parameter negative throw
	 * in doubleRelease. Similar to testDoubleReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1 in doubleRelease
	 */
	@Test (expected = SimulationException.class)
	public void testDoubleReleaseParametresTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.doubleRelease(lowestFailableNumber, noOutFlow);
	}
	
	/**
	 * Testing the todaysInflow parameter negative throw
	 * in doubleRelease. Similar to testDoubleReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1 in doubleRelease
	 */
	@Test (expected = SimulationException.class)
	public void testDoubleReleaseParametresThree() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.doubleRelease(noInFlow, lowestFailableNumber);
	}
	
	
	
	/**
	 * Testing the todaysConsumption and todaysInflow parameters negative throw
	 * in halfRelease. We want to see if a positive number
	 * can be used for it. Negative numbers are rejected though.
	 * @throws SimulationException
	 * @result Passes if positive numbers are accepted for todaysConsumption and todaysInflow in halfRelease
	 */
	@Test
	public void testHalfReleaseParametresOne() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest acceptable positive values in, which are 0
		Integer lowestPositive = 0;
	    testInstance.defaultRelease(lowestPositive, lowestPositive);
	    //double check by increasing the value to 1
	    Integer doubleCheck = 1;
	    testInstance.halfRelease(doubleCheck, doubleCheck);
	}
	
	/**
	 * Testing the todaysConsumption parameter negative throw
	 * in halfRelease. Similar to testHalfReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1 in halfRelease
	 */
	@Test (expected = SimulationException.class)
	public void testHalfReleaseParametresTwo() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.halfRelease(lowestFailableNumber, noOutFlow);
	}
	
	/**
	 * Testing the todaysInflow parameter negative throw
	 * in halfRelease. Similar to testHalfReleaseThrowOne(), but
	 * We want to know if the operators (<, >, <=, >=)
	 * are working correctly.
	 * @throws SimulationException
	 * @result Passes if the negative throw is caught for todaysConsumption when it is -1 in halfRelease
	 */
	@Test (expected = SimulationException.class)
	public void testHalfReleaseParametresThree() throws SimulationException{
		WaterLog damLog = new WaterLog(oneWeek, reallyLargeWindow);
		DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
		//I am going to put the lowest failable number in, and this should fail
		Integer lowestFailableNumber = -1;
	    testInstance.halfRelease(noInFlow, lowestFailableNumber);
	}
	
	
	
		/**
		 * Test class to force no entry throws, overrides addEntry
		 * @author Lewis
		 *
		 */
		private class BadWaterLog extends WaterLog{
			public BadWaterLog(Integer windowSize, Integer maxEntry)
					throws SimulationException {
				super(windowSize, maxEntry);
				// TODO Auto-generated constructor stub
			}
			
			/**
			 * Overriding addEntry so that the test below can catch a throw
			 */
			@Override
			public void addEntry(Integer newEntry) throws SimulationException {
				// TODO Auto-generated method stub
				//changes addEntry so it adds noting to a log,
				//need this so that the log being empty catch is
				//thrown
			}
		}
		
			//These below indented tests use the BadWaterLog class to force throws;
			 // I had to do this, because the current classes would never force these
			 //throws. 
		
			/**
			 * Testing the throws for defaultRelease, this one is where the log is
			 * empty
			 * @throws SimulationException
			 * @result Passes if the log being empty is caught
			 */
			@Test  (expected = SimulationException.class)
			public void testDefaultReleaseEmpty() throws SimulationException{
				BadWaterLog damLog = new BadWaterLog(oneWeek, reallyLargeWindow);
				//This below damAction will be created without any entries
				DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
				//this will force a throw because the DamAction log is empty
				testInstance.defaultRelease(noOutFlow, noInFlow);
				
			}
			/**
			 * Testing the throws for doubleRelease, this one is where the log is
			 * empty
			 * @throws SimulationException
			 * @result Passes if the log being empty is caught
			 */
			@Test  (expected = SimulationException.class)
			public void testDoubleReleaseEmpty() throws SimulationException{
				BadWaterLog damLog = new BadWaterLog(oneWeek, reallyLargeWindow);
				//This below damAction will be created without any entries
				DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
				//this will force a throw because the DamAction log is empty
				testInstance.doubleRelease(noOutFlow, noInFlow);
				
			}
			/**
			 * Testing the throws for halfRelease, this one is where the log is
			 * empty
			 * @throws SimulationException
			 * @result Passes if the log being empty is caught
			 */
			@Test  (expected = SimulationException.class)
			public void testHalfReleaseEmpty() throws SimulationException{
				BadWaterLog damLog = new BadWaterLog(oneWeek, reallyLargeWindow);
				//This below damAction will be created without any entries
				DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
				//this will force a throw because the DamAction log is empty
				testInstance.halfRelease(noOutFlow, noInFlow);
				
			}
			
			/**
			 * Testing the throws for levelTooLow, when the log is
			 * empty and you try to calculate if the water level is too
			 * low
			 * @throws SimulationException
			 * @result Passes if the log being empty is caught
			 */
			@Test  (expected = SimulationException.class)
			public void testLevelTooLowCatch() throws SimulationException{
				BadWaterLog damLog = new BadWaterLog(oneWeek, reallyLargeWindow);
				//This below damAction will be created without any entries
				DamActions testInstance = new DamActions(largeDamCapacity, normalDefaultRelease, oneWeek, damLog);
		
				//this will force a throw because the DamAction log is empty
				testInstance.levelTooLow();
				
			}
	
			
			

	
	
}
