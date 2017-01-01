/* Edited by: Trevor Miranda */

#define N    5    /* number of processes in the ring */
#define L    10   /* size of buffer ( >= 2*N) */
byte I;           /* will be used in init for assigning ids to nodes */

mtype = { one, two, winner }; /* symb . Msg . Names */
chan q[N] = [L] of { mtype, byte }; /* asynchronous channels */

proctype nnode(chan inp, out; byte mynumber)
{
    bit Active = 1, know_winner = 0;
	byte nr, maximum = mynumber;

	xr inp;    /* channel assertion : exclusive recv access to channel in */
    xs out;    /* channel assertion : exclusive send access to channel out */

    printf("MSC: %d\n", mynumber);
    out!one(mynumber);

end:    do
        :: inp?one(nr) ->
            if
            :: Active ->
			    if
				:: nr == mynumber ->
				    Active = 0;
				    know_winner = 1;
				    out!winner,nr;
				    printf("MSC: LEADER\n");
				:: nr > mynumber ->
				    Active = 0;
					out!one(nr);
				:: else ->
				   skip;
				fi
			:: else ->
			    out!one(nr)
			fi
		:: inp?winner,nr ->
		    if
			:: nr == mynumber ->
			    printf("MSC: LEADER\n");
			:: else ->
			    printf("MSC: LOST\n");
			fi;
			if
			:: !know_winner
			    out!winner,nr
			fi;
			break;
		od
}

init {
    byte proc;
	byte Ini[6];    /* N<=6 randomize the process numbers */
	atomic {
	    I = 1;    /* pick a number to be assigned 1..N */
		do
		:: I <= N ->
		    if    /* non-deterministic choice */
			:: Ini[0] == 0 && N >= 1 -> Ini[0] = I
			:: Ini[1] == 0 && N >= 2 -> Ini[1] = I
			:: Ini[2] == 0 && N >= 3 -> Ini[2] = I
			:: Ini[3] == 0 && N >= 4 -> Ini[3] = I
			:: Ini[4] == 0 && N >= 5 -> Ini[4] = I
			:: Ini[5] == 0 && N >= 6 -> Ini[5] = I /* works for up to N=6 */
			fi;
			I++
		:: I > N ->
		    break
		od;

		/* start all nodes in the ring */
		proc = 1;
		do
		:: proc <= N ->
		    run nnode (q[proc-1], q[proc%N], Ini[proc-1]);
			proc++
		:: proc > N ->
		    break
		od
	}
}
