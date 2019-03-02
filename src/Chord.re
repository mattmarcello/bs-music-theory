//TODO: notation
//TODO: description

type t = ChordT.t;

let equals = (t': option(t), t'': option(t)) => {
  switch (t', t'') {
  | (Some(t'), Some(t'')) => t'.key == t''.key && t'.type_ == t''.type_
  | (None, None) => true
  | _ => false
  };
};

let pitches =
    ({type_, key, inversion}: ChordT.t, ~octave: int, ()): list(PitchType.t) => {
  let shifted =
    fun
    | [head, ...tail] => Belt.List.concat(tail, [head])
    | l => l;

  let intervals = ref(type_->ChordTypeT.intervals);

  for (_ in 0 to inversion - 1) {
    intervals := (intervals^)->shifted;
  };

  let root = PitchType.{key, octave};

  let invertedPitches = (intervals^)->Belt.List.map(Pitch.addInterval(root));

  invertedPitches->Belt.List.mapWithIndex((index, pitch) =>
    index < type_->ChordTypeT.intervals->Belt.List.length - inversion ?
      pitch : PitchType.{key: pitch.key, octave: pitch.octave + 1}
  );
};

// TODO: rename
let pitchesWithOctaves =
    ({type_, key, inversion}: ChordT.t, ~octaves: list(int), ())
    : list(PitchType.t) => {
  octaves
  ->Belt.List.map(octave => pitches({type_, key, inversion}, ~octave, ()))
  ->Belt.List.flatten
  ->Belt.List.sort((a, b) => a->Pitch.rawValue - b->Pitch.rawValue);
};

let keys: t => list(Key.t) =
  t => t->pitches(~octave=1, ())->Belt.List.map(pitch => pitch.key);

let romanNumeric =
    ({type_, key, inversion}: ChordT.t, ~for_ as scale: ScaleT.t) => {
  //TODO: ScalePitch.get MUST BE REWRITTEN

  let chordIndex = scale->Scale.ScalePitch.get->Util.indexOf(key);

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

    if (type_.third == ChordTypeT.ChordThirdType.Minor) {
      roman := (roman^)->Js.String.toLowerCase;
    };

    if (type_.sixth->Belt.Option.isSome) {
      roman := roman^ ++ "6";
    };

    if (type_.fifth == ChordTypeT.ChordFifthType.Augmented) {
      roman := roman^ ++ "+";
    };

    if (type_.fifth == ChordTypeT.ChordFifthType.Diminished) {
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
              a.type_->ChordTypeT.ChordExtensionType.ExtensionType.rawValue
              - b.type_->ChordTypeT.ChordExtensionType.ExtensionType.rawValue
            )
          )
        ->Belt.Option.flatMap(Belt.List.head);

      switch (last) {
      | Some((extension: ChordTypeT.ChordExtensionType.t)) =>
        roman :=
          roman^
          ++ extension.type_
             ->ChordTypeT.ChordExtensionType.ExtensionType.rawValue
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

let description = ({type_, key, inversion}: ChordT.t) => {
  let inversionNotation =
    inversion > 0 ? " " ++ string_of_int(inversion) ++ ". Inversion" : "";

  key->Key.description ++ " " ++ type_->ChordTypeT.description ++ inversionNotation;
};
