import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.Semaphore;
import java.util.concurrent.ThreadLocalRandom;

public class Client implements Runnable {
	private int id;
	private List<Exercise> routine;
	
	// Gym semaphores
	private ConcurrentHashMap<ApparatusType, Semaphore> atSemaphores;
	private ConcurrentHashMap<WeightPlateSize, Semaphore> weightSemaphores;
	
	public Client(int id, ConcurrentHashMap<ApparatusType, Semaphore> atsem,
			ConcurrentHashMap<WeightPlateSize, Semaphore> wsem) {
		this.id = id;
		this.routine = new ArrayList<Exercise>();
		this.atSemaphores = atsem;
		this.weightSemaphores = wsem;
	}

	public void addExercise(Exercise e) {
		routine.add(e);
	}
	
	public static Client generateRandom(int id,
			Map<WeightPlateSize, Integer> weight,
			ConcurrentHashMap<ApparatusType, Semaphore> atsem,
			ConcurrentHashMap<WeightPlateSize, Semaphore> wsem) {
		
		int exercises = ThreadLocalRandom.current().nextInt(15, 21);
		Client client = new Client(id, atsem, wsem);
		for (int i = 0; i < exercises; i++)
			client.addExercise(Exercise.generateRandom(weight));
		
		return client;
	}

	public int getId() {
		return id;
	}

	public List<Exercise> getRoutine() {
		return routine;
	}
	
	public void run() {
		// Do that exercising stuff using the concurrent semaphores from gym
	}
}
