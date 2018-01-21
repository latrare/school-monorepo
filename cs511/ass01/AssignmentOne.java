// Author: Trevor Miranda

import java.util.ArrayList;
import java.util.List;

public class AssignmentOne {
	private static List<Integer> results;
	
	public static List<Integer> lprimes(List<Integer[]> intervals) {
		List<PrimeFinder> runnables = new ArrayList<PrimeFinder>();
		List<Thread> threads = new ArrayList<Thread>();
		// Create all the Runnables
		for (Integer[] pair : intervals)
			runnables.add(new PrimeFinder(pair[0], pair[1]));
		
		// Create thread instances
		for (Runnable r : runnables)
			threads.add(new Thread(r));
		
		// Launch the threads
		for (Thread t : threads)
			t.start();
		
		// Join threads, set attribute, return attribute
		for (Thread t : threads) {
			try {
				t.join();
			} catch (InterruptedException e) {
				System.out.println(e);
			}
		}
			
		// Gather results, concatenate lists, return
		results = new ArrayList<Integer>();
		for (PrimeFinder r : runnables)
			for (Integer i : r.getPrimesList())
				results.add(i);
		
		return (results);
	}
	
	public static void main(String[] args) {
		List<Integer[]> input = new ArrayList<Integer[]>();
		
		for (int i = 0; i < args.length - 1;) {
			Integer[] pair = { Integer.decode(args[i]), Integer.decode(args[++i]) };
			input.add(pair);
		}
		
		List<Integer> output = lprimes(input);
		System.out.print("[");
		for (int i = 0; i < output.size(); i++) {
			System.out.print(output.get(i));
			if (i != output.size() - 1)
				System.out.print(", ");
		}
		System.out.println("]");
	}
}
