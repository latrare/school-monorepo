-module(interp).
-export([scanAndParse/1,runFile/1,runStr/1]).
-include("types.hrl").

loop(InFile,Acc) ->
    case io:request(InFile,{get_until,prompt,lexer,token,[1]}) of
        {ok,Token,_EndLine} ->
            loop(InFile,Acc ++ [Token]);
        {error,token} ->
            exit(scanning_error);
        {eof,_} ->
            Acc
    end.

scanAndParse(FileName) ->
    {ok, InFile} = file:open(FileName, [read]),
    Acc = loop(InFile,[]),
    file:close(InFile),
    {Result, AST} = parser:parse(Acc),
    case Result of 
	ok -> AST;
	_ -> io:format("Parse error~n")
    end.

-spec runFile(string()) -> valType().
runFile(FileName) ->
    valueOf(scanAndParse(FileName),env:new()).

scanAndParseString(String) ->
    {_ResultL, TKs, _L} = lexer:string(String),
    parser:parse(TKs).

-spec runStr(string()) -> valType().
runStr(String) ->
    {Result, AST} = scanAndParseString(String),
    case Result  of 
    	ok -> valueOf(AST,env:new());
    	_ -> io:format("Parse error~n")
    end.

-spec numVal2Num(numValType()) -> integer().
numVal2Num({num, N}) ->
    N.

-spec boolVal2Bool(boolValType()) -> boolean().
boolVal2Bool({bool, B}) ->
    B.

-spec valueOf(expType(),envType()) -> valType().
valueOf(Exp,Env) ->
	[CurNode|Rest] = tuple_to_list(Exp),
	case CurNode of
		idExp ->
			{_, _, Key} = hd(Rest),
			env:lookup(Env, Key);
		numExp ->
			{_, _, Value} = hd(Rest),
			{num, Value};
		diffExp ->
			[Arg1|Arg2] = Rest,
			{num, numVal2Num(valueOf(hd(Arg2), Env)) - numVal2Num(valueOf(Arg1, Env))};
		plusExp ->
			[Arg1|Arg2] = Rest,
			{num, numVal2Num(valueOf(Arg1, Env)) + numVal2Num(valueOf(hd(Arg2), Env))};
		isZeroExp -> 
			[Arg1|_] = Rest,
			Num = numVal2Num(valueOf(Arg1, Env)),
			if Num =:= 0 ->
					{bool, true};
			   Num > 0 ->
					{bool, false}
			end;
		ifThenElseExp -> 
			[Arg1|IfRest] = Rest,
			[Arg2|Arg3] = IfRest,
			case boolVal2Bool(valueOf(Arg1, Env)) of
				true ->
					valueOf(Arg2, Env);
				_ ->
					valueOf(hd(Arg3), Env)
			end;
		letExp -> 
			[Arg1|Arg2] = Rest,
			{_, _, Id} = Arg1,
			Val = valueOf(hd(Arg2), Env),
			NewEnv = env:add(Env, Id, Val),
			valueOf(hd(tl(Arg2)), NewEnv);
		procExp -> 
			[Arg1|Arg2] = Rest,
			{_, _, Key} = Arg1,
			{proc, Key, hd(Arg2), Env};
		appExp ->
			[Arg1|Arg2] = Rest,
			Id = element(2, valueOf(Arg1, Env)),
			Pass = valueOf(hd(Arg2), Env),
			NewEnv = env:add(Env, Id, Pass),
			valueOf(element(3, valueOf(Arg1, NewEnv)), NewEnv)
	end.
