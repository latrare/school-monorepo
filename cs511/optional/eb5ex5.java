// Author: Trevor Miranda
// I pledge my honor by the Stevens Honor System

/*
 * "No route requires unloading in the reception platform or loading from the finished product platform"
 *
 * The above makes no sense w.r.t the "reception" (unloading) platform and
 * the "finished" (loading) platform, so I'm going to assume this is a mistake and proceed
 * based on the names of the platforms. 
 */

class Route {
    public int machine;
    public String action;

    public Route(int machine, String action) {
        /* machine must be between 0 and 8 */
        this.machine = machine;

        /* action must be either "unloading" or "loading" */
        this.action = action;
    }
}

class Vehicle {
    public ArrayList<Route> routes;

    public Vehicle(ArrayList<Route> routes) {
        this.routes = routes;
    }
}

class Machine {
    public int products;
    public Semaphore busy;

    public Machine () {
        this.products = 0;
        this.busy = new Semaphore(1);
    }
}

class OilRig {
    private ArrayList<Semaphore> machines;
      
    public void main(String[] args) {
        /* Have a class for each machine which has its own semaphore */
        for (int i = 0; i < 8; i++)
            machines.append(new Machine());

        /* Create a thread for each Truck */
        for (int i = 0; i < 4; i++) {
            /* ASSUME ROUTES CREATED AND STORED IN NEW VARIABLE `newroute` */
            vehicle = new Thread() {
                public void run() {
                    for (route = myroute.next(); myroute.hasNext();) {
                        if (route.action == "unloading") {
                            /* Goto reception dock (imaginary step because sleep at end of loop does the "moving") */
                            /* Grab a machine semaphore and begin unloading for random amount of time */
                            machines[route.machine].busy.acquire();
                            Thread.sleep(Math.random() * 1000);

                            /* Machine just gained a product */
                            machines[route.machine].products += 1;

                            /* Machine now "processes" for another random period of time */
                            Thread.sleep(Math.random() * 1000);
                            machines[route.machine].busy.release();
                        } else {
                            /* Goto finished dock */
                            /* Grab a machine semaphore and begin loading */
                            machines[route.machine].busy.acquire();
                            /* Machine can only load trucks if it has products! */
                            if (machines[route.machine].products > 0) {
                                /* Being loading truck for random amount of time */
                                Thread.sleep(Math.random() * 1000);

                                /* Machine just gave away one of its products */
                                machines[route.machine].products -= 1;
                            }
                            machines[route.machine].busy.release();
                        }
                        /* Sleep while "moving" */
                        Thread.sleep(Math.random() * 1000);
                    }
				}
            };
            vehicle.start();
        }
    }
}
