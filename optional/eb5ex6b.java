// Author: Trevor Miranda
// I pledge my honor by the Stevens Honor System

public class Hemotherapy {
    private Semaphore beds;
    private Semaphore magazines;

    public static void main(String[] args) {
        /* Create bed and magazine semaphores */
        beds = new Semaphore(4);
        magazines = new Semaphore(10);

        /* Let's assume there are 100 patients for the whole day */
        for (int i = 0; i < 100; i++) {
            patient = new Thread() {
                public void run() {
                    boolean hasMagazine = false;
                    while (true) {
                        /* Try to get a bed */
                        if (beds.tryAcquire()) {
                            hasMagazine = false;
                            magazines.release();

                            /* Get your blood sucked for a random amount of time */
                            Time.sleep(Math.random() * 1000);

                            /* Go home, you husk of a man */
                            beds.release();
                            break;
                        } else {
                            /* Oops, no bed, time to sit in waiting room hell (or continue sitting here if this is another iteration) */

                            /* Do we already have a magazine? */
                            if (!hasMagazine) {
                                /* Can we at least get a magazine over here!?! */
                                if (magazines.tryAcquire()) {
                                    hasMagazine = true;
                                }
                                /* Oh well, I guess TV isn't so bad */
                            }
                        }
                    }
                }
                    
            };
            patient.start();
        }
    }
}
