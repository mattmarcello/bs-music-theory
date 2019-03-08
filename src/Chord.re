type t =
  Model.Chord.t = {
    type_: Model.ChordType.t,
    key: Model.Key.t,
    inversion: int,
  };

let make = (~type_: Model.ChordType.t, ~key: Model.Key.t, ~inversion: int=0, ()): t => {
  type_,
  key,
  inversion,
};

let equals = (t': option(t), t'': option(t)) => {
  switch (t', t'') {
  | (Some(t'), Some(t'')) => t'.key == t''.key && t'.type_ == t''.type_
  | (None, None) => true
  | _ => false
  };
};

let pitches =
    ({type_, key, inversion}, ~octave: int, ()): list(Model.Pitch.t) => {
  let shifted =
    fun
    | [head, ...tail] => Belt.List.concat(tail, [head])
    | l => l;

  let intervals = ref(type_->ChordType.intervals);

  for (_ in 0 to inversion - 1) {
    intervals := (intervals^)->shifted;
  };

  let root = Pitch.{key, octave};

  let invertedPitches = (intervals^)->Belt.List.map(Pitch.addInterval(root));

  invertedPitches->Belt.List.mapWithIndex((index, pitch) =>
    index < type_->ChordType.intervals->Belt.List.length - inversion ?
      pitch : Pitch.{key: pitch.key, octave: pitch.octave + 1}
  );
};

let pitchesWithOctaves =
    ({type_, key, inversion}, ~octaves: list(int), ()): list(Pitch.t) => {
  octaves
  ->Belt.List.map(octave => pitches({type_, key, inversion}, ~octave, ()))
  ->Belt.List.flatten
  ->Belt.List.sort((a, b) => a->Pitch.rawValue - b->Pitch.rawValue);
};

let keys: t => list(Key.t) =
  t => t->pitches(~octave=1, ())->Belt.List.map(pitch => pitch.key);

let inversions = t => {
  Belt.Array.range(0, t->keys->Belt.List.length - 1)
  ->Belt.List.fromArray
  ->Belt.List.map(inversion => {...t, inversion});
};

let romanNumeric = ({type_, key, inversion}, ~for_ as scale: Scale.t) => {
  //TODO: ScalePitch.get MUST BE REWRITTEN

  let chordIndex = scale->Scale.keys->Util.indexOf(key);

  let roman =
    switch (chordIndex) {
    | Some(0) => Some("I")
    | Some(1) => Some("II")
    | Some(2) => Some("III")
    | Some(3) => Some("IV")
    | Some(4) => Some("V")
    | Some(5) => Some("VI")
    | Some(6) => Some("VII")
    | _ => None
    };

  switch (roman) {
  | None => None
  | Some(roman) =>
    let roman = ref(roman);

    if (type_.third == ChordType.ChordThirdType.Minor) {
      roman := (roman^)->Js.String.toLowerCase;
    };

    if (type_.sixth->Belt.Option.isSome) {
      roman := roman^ ++ "6";
    };

    if (type_.fifth == ChordType.ChordFifthType.Augmented) {
      roman := roman^ ++ "+";
    };

    if (type_.fifth == ChordType.ChordFifthType.Diminished) {
      roman := roman^ ++ "°";
    };

    if (type_.seventh->Belt.Option.isSome
        && (
          type_.extensions->Belt.Option.isNone
          || type_.extensions
             ->Belt.Option.mapWithDefault(true, extensions =>
                 extensions->Belt.List.size == 0
               )
        )) {
      roman := roman^ ++ "7";
    };

    if (type_.extensions->Belt.Option.isSome
        && type_.extensions
           ->Belt.Option.mapWithDefault(false, extensions =>
               extensions->Belt.List.length > 0
             )) {
      let last =
        type_.extensions
        ->Belt.Option.map(extensions =>
            Belt.List.sort(extensions, (a, b) =>
              a.type_->ChordType.ChordExtensionType.ExtensionType.rawValue
              - b.type_->ChordType.ChordExtensionType.ExtensionType.rawValue
            )
          )
        ->Belt.Option.flatMap(Belt.List.head);

      switch (last) {
      | Some((extension: ChordType.ChordExtensionType.t)) =>
        roman :=
          roman^
          ++ extension.type_
             ->ChordType.ChordExtensionType.ExtensionType.rawValue
             ->string_of_int

      | None => ()
      };
    };

    if (inversion > 0) {
      roman := roman^ ++ inversion->string_of_int;
    };

    Some(roman^);
  };
};

let notation = t => {
  let keys = keys(t);
  let inversionNotation =
    t.inversion > 0 && t.inversion < keys->Belt.List.length ?
      keys->Belt.List.headExn->Key.description : "";

  t.key->Key.description ++ t.type_->ChordType.notation ++ inversionNotation;
};

let description = ({type_, key, inversion}) => {
  let inversionNotation =
    inversion > 0 ? " " ++ string_of_int(inversion) ++ ". Inversion" : "";

  key->Key.description
  ++ " "
  ++ type_->ChordType.description
  ++ inversionNotation;
};

module Infix = {
  let (==) = equals;
};
