import java.util.Set;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ExecutorService;

public class Gym implements Runnable {
	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private Map<WeightPlateSize, Integer> noOfWeightPlates;
	private Set<Integer> clients; // for generating fresh client ids
	private ExecutorService executor;
	
	// XXX: There will be semaphores declared here later
	
	public Gym() {
		// Establish number of weight plates per assignment description
		noOfWeightPlates = new Map<WeightPlateSize, Integer>();
		noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 40);
		noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 30);
		noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 20);
	}
	
	public void run() {
		// Generate all of the clients
		// Populate the Set of clients
		// Start exercising all of the clients
	}
}
