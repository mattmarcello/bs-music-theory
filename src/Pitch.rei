type t =
  MusicTheory.Model.Pitch.t = {
  key: MusicTheory.Model.Key.t,
  octave: int,
};

let makeWithString: string => t;
let makeWithMidiNote:
  (~midiNote: int, ~isPreferredAccidentalSharps: bool=?, unit) => t;
let makeWithRawValue: (int) => t;

let rawValue: t => int;
let addHalfstep: (t, int) => t;
let addInterval: (t, MusicTheory.Interval.t) => t;
let subtractHalfstep: (t, int) => t;
let subtractInterval: (t, MusicTheory.Interval.t) => t;
let subtractPitch: (t, t) => MusicTheory.Interval.t;

let toString: t => string;
let make:
  [< `IntegerLiteral(int)
   | `MidiNote(int)
   | `RawValue(int)
   | `StringLiteral(string) ] =>
  t;
let equal: (t, t) => bool;
let frequency: t => float;
let nearest: float => option(t);
module ScaleKeys:
  {
    module B = Belt;
    let acrossOctaves:
      (~scale: MusicTheory.Scale.t, ~octaves: list(int), unit) => B.List.t(t);
    let get: MusicTheory.Scale.t => list(MusicTheory.Key.t);
  };
let description: t => string;
