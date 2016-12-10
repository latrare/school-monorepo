// Author: Trevor Miranda
// I pledge my honor by the Stevens Honor System

monitor ConferenceRoom {
	private int capacity = 0;
	private bool isTalking = false;
	private Condition notFull, notEmpty;
	
	public synchronized void enter() {
			// People enter
			if (capacity == 50 || isTalking) {
				notFull.wait();
			}
			capacity += 1;
			notEmpty.signal();
	}

	public synchronized void speaker_enter() {
			// Speaker enters
			if (capacity == 0)
				// Speaker rests if no one is there
				this.rest();
			else {
				// Talks for random amount of time
				isTalking = true;
				this.talk();
			}
			notEmpty.signalAll();
			notFull.signalAll();
	}

	public synchronized void talk() {
			// Talk happens
			Thread.sleep(Math.random() * 1000);
	}

	public synchronized void leave() {
			// People leave
			if (isTalking)
				notEmpty.wait();
			else
				notFull.signal();
	}

	public synchronized void rest() {
			// Speaker rests
			Thread.sleep(1000 * 60 * 5); // 5 minutes
	}
}
