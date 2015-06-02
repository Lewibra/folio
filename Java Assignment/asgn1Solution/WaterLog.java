package asgn1Solution;



import asgn1Question.Log;
import asgn1Question.SimulationException;

import java.util.HashMap;


public class WaterLog implements Log {
	//Custon variables to avoid magic numbers
	private static final Integer firstIndex = 0;
	private static final Integer noEntries = 0;
	private static final Integer minimumEntry = 0;

	//Vital variables for the constructor
	private Integer windowSize;
	private Integer maxEntry;
	private Integer lastIndex;
	
	//Values for the index and values in the hashmap (need them to shift values to the right!)
	private Integer keyNumber;
	private Integer keyValue;
	//assigning memory to hashmap variable
	private HashMap<Integer, Integer> logHashMap;
	//variables to keep track of tallies and the first entry
	private Integer logEntriesTally = 0;
	private Integer firstEntryEver;
	
	/**
	 * A WaterLog class is used to hold a log of the dam's water levels over the past
	 * specified amount of days. These levels are indexed in a negative order, from 0 to
	 *  -specifiedAmountOfDays where 0 should be the newest entry.
	 *  
	 * This class has the ability to allow the user to add an entry to the front of the
	 * log, and it pushes everything to the right, getting rid of the last entry
	 * in the last index. They can return how much entries have been
	 * made, the first entry added ever, and return any entry that is currently stored in the
	 * log.
	 * 
	 * Throws: The windowSize must be strictly positive and the maxEntry can't be negative.
	 * 
	 * @param windowSize amount of prior days you want to record
	 * @param maxEntry maximum MLs you can enter into the log
	 * 
	 */
	public WaterLog(Integer windowSize, Integer maxEntry) throws SimulationException {

		if (windowSize <= firstIndex){
			throw new SimulationException("windowSize is not strictly positive");
		}
		
		if (maxEntry < minimumEntry){
			throw new SimulationException("the maxEntry can't be negative");
		}
		
		this.windowSize = windowSize;
		this.maxEntry = maxEntry;
		//set up the hash map and fill it
		logHashMap =  new HashMap<Integer, Integer>();	
		for (Integer indexes=0; indexes < windowSize; indexes++){
			logHashMap.put(-indexes, null);
		}
		
		//setting up the variable to hold the last index (magic number)
		this.lastIndex = -windowSize + 1;
		
	}
	
	
	public void addEntry(Integer newEntry) throws SimulationException {

		if ((newEntry < minimumEntry)){
			throw new SimulationException("The new entry is below 0");
		} else if (newEntry > maxEntry){
			throw new SimulationException("The new entry is above the maximum!");
		}
		//Shift all values one index (key) right
		for (Integer i = (windowSize - 1); i >= firstIndex; i--){
			keyNumber = -i;
			keyValue = logHashMap.get(keyNumber + 1);
			logHashMap.put(keyNumber, keyValue);
		}
		
		//If there are no entries, the first entry will be recorded
		if (logEntriesTally == noEntries){
			firstEntryEver = new Integer(newEntry);
		}
		
		logEntriesTally++;
		//Place the newest entry in index 0
		logHashMap.put(firstIndex, newEntry);
		
		
	}
	
	
	public Integer getEntry(Integer index) throws SimulationException {
		//Throws this if you give an incorrect index
		if ((index > firstIndex) || (index < (-windowSize))){
			throw new SimulationException("the supplied index is not within range!");
		}
		return logHashMap.get(index);
	}

	
	public Integer variation() throws SimulationException {
		if (logEntriesTally == noEntries){
			throw new SimulationException("there are no entries to calculate!");
		}
		//Use this method to calculate the variation if
		//the log isn't full
		if (logEntriesTally <= windowSize){
			return (logHashMap.get(firstIndex) - firstEntryEver);
		}
		//uses this for a full log
		return (logHashMap.get(firstIndex) - logHashMap.get(lastIndex));
	}

	
	public Integer numEntries() {
		return logEntriesTally;
	}

}
