%% Author: Trevor Miranda
%% I pledge that I have abided by the Stevens Honor System

-module(sim).
-export([launch_sim/1]).


%% Launch the sim with `SensorNum`
launch_sim(SensorNum) ->
    launch_sim_helper(SensorNum, 0, 0).


launch_sim_helper(0, _, WatcherCount) ->
    io:fwrite("Created ~p watcher threads.~n", [WatcherCount]);


%% Helper function for sim launcher to recurse into
%% Starts creating sensors with IDs at `SensorCurrent` and `WatcherCount` watchers
launch_sim_helper(SensorNum, SensorCurrent, WatcherCount) when SensorNum > 0 ->
    %% Start sensor ID range at current sensor
    SensorIdBegin = SensorCurrent,

    %% Get number of sensors that this watcher will have to watch
    if
        (SensorNum - 10) > 0 ->
            SensorsToWatch = 10;
        true ->
            SensorsToWatch = (SensorNum rem 10)
    end,

    %% Get the end of the range of sensors that the next watcher will have to watch
    SensorIdEnd = SensorIdBegin + SensorsToWatch - 1,

    spawn(watcher, watcher_spawn_thread, [SensorIdBegin, SensorIdEnd]),
    %% Now recurse to get through next batch of sensors
    launch_sim_helper(SensorNum - SensorsToWatch, SensorIdEnd + 1, WatcherCount + 1).

