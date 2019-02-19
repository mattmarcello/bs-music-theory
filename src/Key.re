type t = {
  type_: KeyType.t,
  accidental: Accidental.t,
};

let makeWithStringLiteral = str => {
  let pattern = Js.Re.fromString("([A-Ga-g])([#♯♭b]*)");

  //TODO: rewrite this to be nicer
  switch (
    str
    ->Js.Re.exec(pattern)
    ->Belt.Option.map(Js.Re.captures)
    ->Belt.Option.map(Belt.List.fromArray)
    ->Belt.Option.map(l => l->Belt.List.map(Js.Nullable.toOption))
  ) {
  | Some([_, Some(keyTypeString), Some(accidentalString)]) => {
      type_: KeyType.ofString(keyTypeString),
      accidental: Accidental.ofString(accidentalString),
    }

  | _ => {type_: C, accidental: Natural}
  };
};

let make =
  fun
  | `StringLiteral(str) => makeWithStringLiteral(str);

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

/* math and equality operators */

let equal = (k', k'') => {
  let k'mod =
    ((k'.type_ |> KeyType.rawValue) + (k'.accidental |> Accidental.rawValue))
    mod 12;
  let normalizedK' = k'mod < 0 ? ( 12 + k'mod ) : k'mod;

  let k''mod =
    ((k''.type_ |> KeyType.rawValue) + (k''.accidental |> Accidental.rawValue))
    mod 12;
  let normalizedK'' = k''mod < 0 ? ( 12 + k''mod ) : k''mod;

  normalizedK' == normalizedK''
};

/* end math and equality operators */

let makeWithType = (~type_, ~accidental=Accidental.Natural, ()) => {
  type_,
  accidental,
};

let toString = ({type_, accidental}) => {
  KeyType.toString(type_) ++ " " ++ Accidental.toString(accidental);
};

let normalizedIntValue = k => {
  let kmod =
    (k.type_->KeyType.rawValue + k.accidental->Accidental.rawValue) mod 12;
  /* Js.log3("kmod", k.type_ -> KeyType.rawValue */

  kmod < 0 ? kmod + 12 : kmod;
};

let intEqual = (k', k'') => {
  normalizedIntValue(k') == normalizedIntValue(k'');
};
/* let intValueEqual = (k', k'') => { */

/* } */
