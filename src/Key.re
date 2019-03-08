type t =
  Model.Key.t = {
    type_: Model.KeyType.t,
    accidental: Model.Accidental.t,
  };

let make = (~type_, ~accidental=Accidental.Natural, ()) => {
  type_,
  accidental,
};

let makeWithString = str => {
  let pattern = Js.Re.fromString("([A-Ga-g])([#♯♭b]*)");

  switch (
    str
    ->Js.Re.exec(pattern)
    ->Belt.Option.map(Js.Re.captures)
    ->Belt.Option.map(Belt.List.fromArray)
    ->Belt.Option.map(l => l->Belt.List.map(Js.Nullable.toOption))
  ) {
  | Some([_, Some(keyTypeString), Some(accidentalString)]) => {
      type_: KeyType.makeWithString(keyTypeString),
      accidental: Accidental.makeWithString(accidentalString),
    }

  | _ => {type_: C, accidental: Natural}
  };
};

let equals = (k', k'') => {
  let k'mod =
    ((k'.type_ |> KeyType.rawValue) + (k'.accidental |> Accidental.rawValue))
    mod 12;
  let normalizedK' = k'mod < 0 ? 12 + k'mod : k'mod;

  let k''mod =
    ((k''.type_ |> KeyType.rawValue) + (k''.accidental |> Accidental.rawValue))
    mod 12;
  let normalizedK'' = k''mod < 0 ? 12 + k''mod : k''mod;

  normalizedK' == normalizedK'';
};

let equalsStrict = Pervasives.(==);

let keysWithSharps = [
  {type_: KeyType.C, accidental: Accidental.natural},
  {type_: C, accidental: Accidental.sharp},
  {type_: D, accidental: Accidental.natural},
  {type_: D, accidental: Accidental.sharp},
  {type_: E, accidental: Accidental.natural},
  {type_: F, accidental: Accidental.natural},
  {type_: F, accidental: Accidental.sharp},
  {type_: G, accidental: Accidental.natural},
  {type_: G, accidental: Accidental.sharp},
  {type_: A, accidental: Accidental.natural},
  {type_: A, accidental: Accidental.sharp},
  {type_: B, accidental: Accidental.natural},
];

let keysWithFlats = [
  {type_: KeyType.C, accidental: Accidental.natural},
  {type_: D, accidental: Accidental.flat},
  {type_: D, accidental: Accidental.natural},
  {type_: E, accidental: Accidental.flat},
  {type_: E, accidental: Accidental.natural},
  {type_: F, accidental: Accidental.natural},
  {type_: G, accidental: Accidental.flat},
  {type_: G, accidental: Accidental.natural},
  {type_: A, accidental: Accidental.flat},
  {type_: A, accidental: Accidental.natural},
  {type_: B, accidental: Accidental.flat},
  {type_: B, accidental: Accidental.natural},
];

let description = ({type_, accidental}) => {
  KeyType.description(type_) ++ " " ++ Accidental.notation(accidental);
};

