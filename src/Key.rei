type t =
  MusicTheory.Model.Key.t = {
    type_: MusicTheory.Model.KeyType.t,
    accidental: MusicTheory.Model.Accidental.t,
  };
let make:
  (
    ~type_: MusicTheory.Model.KeyType.t,
    ~accidental: MusicTheory.Model.Accidental.t=?,
    unit
  ) =>
  t;
let makeWithString: string => t;
let equals: (t, t) => bool;
let equalsStrict: (t, t) => bool;
let keysWithSharps: list(t);
let keysWithFlats: list(t);
let description: t => string;
module Infix: {
  let (==): (t, t) => bool;
  let (===): (t, t) => bool;
};
