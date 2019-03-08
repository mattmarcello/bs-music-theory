type t = Model.Interval.t = {
    quality: Model.IntervalQuality.t,
    degree: int,
    semitones: int,
  };

let make:
  (
    ~quality: Model.IntervalQuality.t,
    ~degree: int,
    ~semitones: int
  ) =>
  t;

let equals: (t, t) => bool;
let equalsStrict: (t, t) => bool;

let notation: t => string;
let description: t => string;

let perfect1: t;
let perfect4: t;
let perfect5: t;
let perfect8: t;
let perfect11: t;
let perfect12: t;
let perfect15: t;
let minor2: t;
let minor3: t;
let minor6: t;
let minor7: t;
let minor9: t;
let minor10: t;
let minor13: t;
let minor14: t;
let major2: t;
let major3: t;
let major6: t;
let major7: t;
let major9: t;
let major10: t;
let major13: t;
let major14: t;
let diminished1: t;
let diminished2: t;
let diminished3: t;
let diminished4: t;
let diminished5: t;
let diminished6: t;
let diminished7: t;
let diminished8: t;
let diminished9: t;
let diminished10: t;
let diminished11: t;
let diminished12: t;
let diminished13: t;
let diminished14: t;
let diminished15: t;
let augmented1: t;
let augmented2: t;
let augmented3: t;
let augmented4: t;
let augmented5: t;
let augmented6: t;
let augmented7: t;
let augmented8: t;
let augmented9: t;
let augmented10: t;
let augmented11: t;
let augmented12: t;
let augmented13: t;
let augmented14: t;
let augmented15: t;

let all: list(t);

module Infix: {
  let (==): (t, t) => bool;
  let (===): (t, t) => bool;
};
