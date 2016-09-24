import java.util.ArrayList;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.SynchronousQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;

public class Gym implements Runnable {
	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private ConcurrentHashMap<WeightPlateSize, Integer> noOfWeightPlates;
	private ArrayList<Client> clients; // There's no point to a set here
	private ExecutorService executor;
	
	private ConcurrentHashMap<ApparatusType, Semaphore> atSemaphores;
	private ConcurrentHashMap<WeightPlateSize, Semaphore> weightSemaphores;
	
	public Gym() {
		// Create semaphores for apparatuses
		atSemaphores = new ConcurrentHashMap<ApparatusType, Semaphore>();
		atSemaphores.put(ApparatusType.BARBELL, new Semaphore(1));
		atSemaphores.put(ApparatusType.CABLECROSSOVERMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.HACKSQUATMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LATPULLDOWNMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGCURLMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGEXTENSIONMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGPRESSMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.PECDECKMACHINE, new Semaphore(1));
		
		// Establish number of weight plates per assignment description
		noOfWeightPlates = new ConcurrentHashMap<WeightPlateSize, Integer>();
		noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 40);
		noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 30);
		noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 20);
		
		// Create semaphores for weights
		weightSemaphores = new ConcurrentHashMap<WeightPlateSize, Semaphore>();
		weightSemaphores.put(WeightPlateSize.SMALL_3KG,
				new Semaphore(noOfWeightPlates.get(WeightPlateSize.SMALL_3KG)));
		weightSemaphores.put(WeightPlateSize.MEDIUM_5KG,
				new Semaphore(noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG)));
		weightSemaphores.put(WeightPlateSize.LARGE_10KG,
				new Semaphore(noOfWeightPlates.get(WeightPlateSize.LARGE_10KG)));

		// Generate and populate all of the clients
		clients = new ArrayList<Client>();
		for (int i = 0; i < GYM_REGISTERED_CLIENTS; i++)
			clients.add(Client.generateRandom(i, noOfWeightPlates));
	}
	
	public void run() {
		System.out.println("Change the sign on the front door to 'OPEN'.");
		// Setup executor pool
		executor = Executors.newFixedThreadPool(GYM_SIZE);
		
		// Delegate clients to executor pool
		System.out.println("Setting up all the clients to get busy...");
		for (Client c : clients) {
			executor.execute(new Runnable() {
				public void run() {
				}
			});
		}
		
		// Wait for everyone to finish before closing down
		System.out.println("Waiting for clients to finish...");
		executor.shutdown();
		
		try {
			executor.awaitTermination(Long.MAX_VALUE, TimeUnit.MILLISECONDS);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("Gym is now closed."); 
	}
}
