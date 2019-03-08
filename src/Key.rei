type t =
  Model.Key.t = {
    type_: Model.KeyType.t,
    accidental: Model.Accidental.t,
  };
let make:
  (
    ~type_: Model.KeyType.t,
    ~accidental: Model.Accidental.t=?,
    unit
  ) =>
  t;
let makeWithString: string => t;
let equals: (t, t) => bool;
let equalsStrict: (t, t) => bool;
let keysWithSharps: list(t);
let keysWithFlats: list(t);
let description: t => string;
