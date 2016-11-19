%% Author: Trevor Miranda
%% I pledge that I have abided by the Stevens Honor System

-module(watcher).
-export([watcher_spawn_thread/2]).


watcher_spawn_thread(SensorIdBegin, SensorIdEnd) ->
    Sensors = generate_sensors(SensorIdBegin, SensorIdEnd, []),
    print_watchers_info(Sensors),
    watcher_eventloop(Sensors).


generate_sensors(SensorIdCurrent, SensorIdEnd, SensorList) ->
    if
        SensorIdCurrent =< SensorIdEnd ->
            {Pid, _} = spawn_monitor(sensor, sensor_spawn_thread, [self(), SensorIdCurrent]),
            generate_sensors(SensorIdCurrent + 1, SensorIdEnd,
                             SensorList ++ [{SensorIdCurrent, Pid}]);
        true ->
            SensorList
    end.


watcher_eventloop(Sensors) ->
    receive
        {SensorId, Report} ->
            if
                Report == "anomalous_reading" ->
                    io:fwrite("Watcher [~p], Sensor (~p) has crashed with error: ~p.~n",
                              [self(), SensorId, "anomalous_reading"]),

                    {Pid, _} = spawn_monitor(sensor, sensor_spawn_thread, [self(), SensorId]),

                    ListElem = lists:last(
                             lists:filter(
                               fun({SensorStoredId, _}) ->
                                       SensorStoredId == SensorId
                               end, Sensors
                              )
                            ),

                    SensorsNew = lists:append(
                                   lists:delete(ListElem, Sensors), [{SensorId, Pid}]),
                    print_watchers_info(SensorsNew);
                true ->
                    io:fwrite("Watcher [~p], Sensor (~p) reported: ~p.~n",
                              [self(), SensorId, Report]),
                    SensorsNew = Sensors
            end
    end,
    watcher_eventloop(SensorsNew).


print_watchers_info(Sensors) ->
    io:fwrite("Watcher [~p] watching: ~p~n", [self(), Sensors]).
