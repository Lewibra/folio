package asgn1Solution;



import asgn1Question.Actions;
import asgn1Question.SimulationException;

public class DamActions implements Actions{
	//Important variables for constructor
	private Integer damCapacity;
	private Integer defaultRelease;
	private Integer jobDuration;
	private WaterLog damLog;
	
	//Variables to avoid magic numbers
	private static final Integer empty = 0;
	private static final Integer none = 0;
	
	private Integer halfDefaultRelease;
	private Integer doubleDefaultRelease;
	
	//Half the absolute physical capacity of 200%
	private Integer hundredPercentCapacity;
	private Integer currentWaterLevel;
	private Integer minimumThreshold;
	
	private Integer daysWorked;
	
	/**
	 * A DamActions can store all the necessary values to run a dam, it is an object that holds
	 * the dam's capacity, how much water it will release by default, how long the manager is
	 * going to work for, and the log of water levels for the specified amount of days. With those variables, the manager can use the methods in this class to add water and release
	 * water. They can check if the dam is overflowed, or under the threshold. This class will also
	 * tell them when their job is done.
	 * 
	 * Throws: Dam capacity being less than 100ML, Job duration must be positive and the defaultRelease must be strictly positive
	 * 
	 * @param damCapacity Capacity of the dam
	 * @param defaultRelease The amount of water let out by the defaultRelease
	 * @param jobDuration Days in a job
	 * @param damLog Logs the prior water levels
	 * 
	 */
	public DamActions(Integer damCapacity, Integer defaultRelease, Integer jobDuration, WaterLog damLog) throws SimulationException{
		if (damCapacity < 100){
			throw new SimulationException("The dam capacity is less that 100 megaLitres");
		}
		if (jobDuration <= none){
			throw new SimulationException("The job duration isn't positive");
		}
		if (defaultRelease <= none){
			throw new SimulationException("The default release isn't strictly positive, it must be above 0");
		}
		
		this.damCapacity = damCapacity;
		this.defaultRelease = defaultRelease;
		this.jobDuration = jobDuration;
		this.damLog = damLog;
		
		//Set up the DamAction log with half the dam capacity
		hundredPercentCapacity = damCapacity / 2;
		currentWaterLevel = hundredPercentCapacity;
		damLog.addEntry(currentWaterLevel);
		
		//Setting up variables to hold the release amounts 
		halfDefaultRelease = new Integer(defaultRelease / 2);
		doubleDefaultRelease = new Integer(defaultRelease * 2);
		minimumThreshold = new Integer(damCapacity / 4);
		//0 for beginning
		daysWorked = none;

	}

	public boolean levelTooLow() throws SimulationException {
		if (damLog.numEntries() == empty){
			throw new SimulationException ("The log is empty o.O");
		}
		
		if (currentWaterLevel < minimumThreshold){
			return true;
		}

		return false;
	}

	public boolean damOverflowed(){
		if (currentWaterLevel > damCapacity){
			return true;
		}
		
		return false;
	}

	public boolean jobDone() {
		if (daysWorked == jobDuration){
			return true;
			//you did it!
		}
		return false;
	}

	public void defaultRelease(Integer todaysConsumption, Integer todaysInflow)
			throws SimulationException {
		if ((todaysConsumption < none) || (todaysInflow < none)){
			throw new SimulationException("You've given me negative entries!");
		}
		
		if (damLog.numEntries() == empty){
			throw new SimulationException ("The log is empty o.O");
		}
	
		currentWaterLevel = calculateWaterLevel(defaultRelease, todaysInflow, todaysConsumption);
		
		//Test the calculated water levels to see if you're not flooding
		//or draining the dam
		//If the current water level exceeds the dam's capacity
		//the dam's capacity will be added to the log and
		//you will be fired!
		//Else, continue adding normal water levels
		
		//this code below also makes sure that, the throws in WaterLog.addEntry are never
		//caught
		if (damOverflowed()){
			//No need to set the current water level to the damCapacity,
			//because once this line runs, the manager will be fired
			damLog.addEntry(damCapacity);
		} else if (levelTooLow()){
			//if the water falls below the threshold,
			//add the current levels to the log
			if (currentWaterLevel <= empty){
				//else add 0 if the water level
				//falls to or beneath 0 (somehow)
				currentWaterLevel = empty;
			}
			damLog.addEntry(currentWaterLevel);
		} else{
			//else continue on, you still have your job!
			damLog.addEntry(currentWaterLevel);
		}
				
		daysWorked++;
		
	}

	public void halfRelease(Integer todaysConsumption, Integer todaysInflow)
			throws SimulationException {
		if ((todaysConsumption < none) || (todaysInflow < none)){
			throw new SimulationException("You've given me negative entries!");
		}
		
		if (damLog.numEntries() == empty){
			throw new SimulationException ("The log is empty o.O");
		}

		//Test the calculated water levels to see if you're not flooding
		//or draining the dam
		currentWaterLevel = calculateWaterLevel(halfDefaultRelease, todaysInflow, todaysConsumption);
		
		if (damOverflowed()){
			damLog.addEntry(damCapacity);
		} else if (levelTooLow()){
			if (currentWaterLevel <= empty){
				currentWaterLevel = empty;
			}
			damLog.addEntry(currentWaterLevel);
		} else{
			damLog.addEntry(currentWaterLevel);
		}
		
		daysWorked++;		
	}

	public void doubleRelease(Integer todaysConsumption, Integer todaysInflow)
			throws SimulationException {
		if ((todaysConsumption < none) || (todaysInflow < none)){
			throw new SimulationException("You've given me negative entries!");
		}
		
		if (damLog.numEntries() == empty){
			throw new SimulationException ("The log is empty o.O");
		}
		
		//Test the calculated water levels to see if you're not flooding
		//or draining the dam
		currentWaterLevel = calculateWaterLevel(doubleDefaultRelease, todaysInflow, todaysConsumption);
		
		if (damOverflowed()){
			damLog.addEntry(damCapacity);
		} else if (levelTooLow()){
			if (currentWaterLevel <= empty){
				currentWaterLevel = empty;
			}
			damLog.addEntry(currentWaterLevel);
		} else{
			damLog.addEntry(currentWaterLevel);
		}

		daysWorked++;
	}
	
	
	
	
	/**
	 * just a small function to calculate a new waterlevel, did this for
	 * refactoring
	 * @param releaseAmount
	 * @param todaysInflow
	 * @param todaysConsumption
	 * @return
	 */
	private Integer calculateWaterLevel(Integer releaseAmount, Integer todaysInflow, Integer todaysConsumption){
		return currentWaterLevel + todaysInflow - (todaysConsumption + releaseAmount);
	}
}
