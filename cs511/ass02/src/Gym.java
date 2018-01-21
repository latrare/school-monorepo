import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class Gym implements Runnable {
	private static final int GYM_SIZE = 30;
	private static final int GYM_REGISTERED_CLIENTS = 10000;
	private Map<WeightPlateSize, Integer> noOfWeightPlates;
	private ArrayList<Client> clients; // There's no point to a set here
	private ExecutorService executor;
	
	private static Map<ApparatusType, Semaphore> atSemaphores;
	private static Map<WeightPlateSize, Semaphore> weightSemaphores;
	private static Semaphore weightAccessSemaphore;
	
	public Gym() {
		// Create semaphores for apparatuses
		atSemaphores = Collections.synchronizedMap(new HashMap<ApparatusType, Semaphore>());
		atSemaphores.put(ApparatusType.BARBELL, new Semaphore(1));
		atSemaphores.put(ApparatusType.CABLECROSSOVERMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.HACKSQUATMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LATPULLDOWNMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGCURLMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGEXTENSIONMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.LEGPRESSMACHINE, new Semaphore(1));
		atSemaphores.put(ApparatusType.PECDECKMACHINE, new Semaphore(1));
		
		// Establish number of weight plates per assignment description
		noOfWeightPlates = Collections.synchronizedMap(new HashMap<WeightPlateSize, Integer>());
		noOfWeightPlates.put(WeightPlateSize.SMALL_3KG, 40);
		noOfWeightPlates.put(WeightPlateSize.MEDIUM_5KG, 30);
		noOfWeightPlates.put(WeightPlateSize.LARGE_10KG, 20);
		
		// Create semaphores for weights
		weightSemaphores = Collections.synchronizedMap(new HashMap<WeightPlateSize, Semaphore>());
		weightSemaphores.put(WeightPlateSize.SMALL_3KG,
							 new Semaphore(noOfWeightPlates.get(WeightPlateSize.SMALL_3KG)));
		weightSemaphores.put(WeightPlateSize.MEDIUM_5KG,
							 new Semaphore(noOfWeightPlates.get(WeightPlateSize.MEDIUM_5KG)));
		weightSemaphores.put(WeightPlateSize.LARGE_10KG,
							 new Semaphore(noOfWeightPlates.get(WeightPlateSize.LARGE_10KG)));
		
		weightAccessSemaphore = new Semaphore(1);

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
						ArrayList<Exercise> routine = c.getRoutine();
						for (Exercise e: routine) {
							System.out.println("Client " + c.getId() + ": wants to start exercising...");
							
							try {
								// Get access to the machine
								atSemaphores.get(e.getAt()).acquire();
								System.out.println("Client " + c.getId() + ": acquired the apparatus.");
								
								int small = e.getWeight().get(WeightPlateSize.SMALL_3KG);
								int medium = e.getWeight().get(WeightPlateSize.MEDIUM_5KG);
								int large = e.getWeight().get(WeightPlateSize.LARGE_10KG);
								
								System.out.println("Client: " + c.getId() + " needs " + small + "S " + medium + "M " + large + "L");
								
								// One person getting weights at a time, reasonably
								weightAccessSemaphore.acquire();
										
								// Acquire small weights
								for (int i = 0; i < small; i++)
									weightSemaphores.get(WeightPlateSize.SMALL_3KG).acquire();
								System.out.println("Client " + c.getId() + ": acquired all of their small weights.");
		
								// Acquire medium weights
								for (int i = 0; i < medium; i++)
									weightSemaphores.get(WeightPlateSize.MEDIUM_5KG).acquire();
								System.out.println("Client " + c.getId() + ": acquired all of their meidum weights.");
									
								// Acquire large weights
								for (int i = 0; i < large; i++)
									weightSemaphores.get(WeightPlateSize.LARGE_10KG).acquire();
								System.out.println("Client " + c.getId() + ": acquired all of their large weights.");
								
								weightAccessSemaphore.release();
								
								// Dance
								Thread.sleep(e.getDuration());
								
								// Release apparatus
								atSemaphores.get(e.getAt()).release();
								System.out.println("Client " + c.getId() + ": released the apparatus.");
								
								// Release small weights
								for (int i = 0; i < small; i++)
									weightSemaphores.get(WeightPlateSize.SMALL_3KG).release();
								System.out.println("Client " + c.getId() + ": released all of their small weights.");
									
								// Release medium weights
								for (int i = 0; i < medium; i++)
									weightSemaphores.get(WeightPlateSize.MEDIUM_5KG).release();
								System.out.println("Client " + c.getId() + ": released all of their medium weights.");
										
								// Release large weights
								for (int i = 0; i < large; i++)
									weightSemaphores.get(WeightPlateSize.LARGE_10KG).release();
								System.out.println("Client " + c.getId() + ": released all of their large weights.");
								
								System.out.println("Client " + c.getId() + ": is done exercising.");
							} catch (InterruptedException e1) {
								e1.printStackTrace();
							}
						}
					}
				});
		}
		
		// Wait for everyone to finish before closing down
		executor.shutdown();
		
		try {
			executor.awaitTermination(Long.MAX_VALUE, TimeUnit.MILLISECONDS);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}

		System.out.println("Gym is now closed."); 
	}
}
