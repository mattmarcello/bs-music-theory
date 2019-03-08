type t =
  Model.Pitch.t = {
  key: Model.Key.t,
  octave: int,
};
let make: (~key: Model.Key.t, ~octave: int) => t;
let makeWithString: string => t;
let makeWithMidiNote:
  (~midiNote: int, ~isPreferredAccidentalSharps: bool=?, unit) => t;
let makeWithInteger: int => t;
let rawValue: t => int;
let addHalfstep: (t, int) => t;
let addInterval: (t, Model.Interval.t) => t;
let subtractHalfstep: (t, int) => t;
let subtractInterval: (t, Model.Interval.t) => t;
let equals: (t, t) => bool;
let equalsStrict: ('a, 'a) => bool;
let lessThan: (t, t) => bool;
let frequency: t => float;
let nearest: float => option(t);
let _keysForScale: Model.Scale.t => list(Model.Key.t);
let subtractPitch: (t, t) => Model.Interval.t;
let description: t => string;
