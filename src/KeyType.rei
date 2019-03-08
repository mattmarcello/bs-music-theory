type t = Model.KeyType.t = C | D | E | F | G | A | B;
let makeWithString: string => t;
let rawValue: t => int;
let all: list(t);
let key: (t, ~at: int) => t;
let distance: (t, ~from: t) => int;
let octaveDiff: (t, ~for_: Model.Interval.t, ~isHigher: bool) => int;
let description: t => string;
