%% Author: Trevor Miranda
%% I pledge that I have abided by the Stevens Honor System

-module(sensor).
-export([sensor_spawn_thread/2]).


%% Called by `WatcherPid` to spawn new sensor with `SensorId`
sensor_spawn_thread(WatcherPid, SensorId) ->
    %% Generate random number [1, 11] for sensor value
    Measurement = rand:uniform(11),

    if
        Measurement =:= 11 ->
            %% Report anomalous reading, crash out
            WatcherPid ! {SensorId, "anomalous_reading"},
            exit(crash);
		true ->
			WatcherPid ! {SensorId, Measurement}
    end, 

    %% Sleep randomly, then recurse into new thread to spawn new measurement
    timer:sleep(rand:uniform(10000)),
    sensor_spawn_thread(WatcherPid, SensorId).
