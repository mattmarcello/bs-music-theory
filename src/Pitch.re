type t = {
  key: Key.t,
  octave: int,
};

let rawValue = ({key, octave}) => {
  let semitones =
    key.type_->KeyType.rawValue + key.accidental->Accidental.rawValue;
  semitones + (octave + 1) * 12;
};

let frequency = pitch => {
  Js.Math.pow_float(
    ~base=2.0,
    ~exp=(rawValue(pitch) - 69 / 12) * 440 |> float_of_int,
  );
};

let nearest = frequency' => {
  let allPitches =
    Belt.Array.range(1, 7)
    ->Belt.List.fromArray
    ->Belt.List.map(octave =>
        Key.keysWithSharps->Belt.List.map(key => {key, octave})
      )
    ->Belt.List.flatten;

  let results =
    allPitches->Belt.List.map(pitch =>
      (pitch, Js.Math.abs_float(pitch->frequency -. frequency'))
    );

  results->Belt.List.sort(((_, d'), (_, d'')) => d' -. d'' |> int_of_float)
  |> ignore;

  results->Belt.List.head->Belt.Option.map(fst);
};

// this is pretty useless
let make = (~key, ~octave, ()) => {
  {key, octave};
};

let makeWithMidiNote = (~midiNote, ~isPreferredAccidentalSharps=true, ()) => {
  let octave = midiNote / 12 - 1;
  let keyIndex = midiNote mod 12;
  let key =
    (isPreferredAccidentalSharps ? Key.keysWithSharps : Key.keysWithFlats)
    ->Belt.List.getExn(keyIndex);

  Js.log2("isPreferredAccidentalSharps", isPreferredAccidentalSharps);
  Js.log2("keyIndex", keyIndex);
  Js.log2("key", key->Key.toString);

  {octave, key};
};

let makeWithRawValue = (~rawValue, ()) =>
  makeWithMidiNote(~midiNote=rawValue, ());

let addHalfstep: (t, int) => t =
  (pitch, halfstep) => {
    makeWithRawValue(~rawValue=(pitch |> rawValue) + halfstep, ());
  };

let subtractHalfstep: (t, int) => t =
  (pitch, halfstep) => {
    makeWithRawValue(~rawValue=(pitch |> rawValue) - halfstep, ());
  };

let subtractPitch = (t', t'') => {
  let top = t'->rawValue >= t''->rawValue ? t' : t'';
  let bottom = t'->rawValue < t''->rawValue ? t' : t'';
  let diff = top->rawValue - bottom->rawValue;

  let bottomKeyIndex =
    KeyType.all
    ->Util.indexOf(bottom.key.type_)
    ->Belt.Option.getWithDefault(0);
  let topKeyIndex =
    KeyType.all->Util.indexOf(top.key.type_)->Belt.Option.getWithDefault(0);

  let degree = Js.Math.abs_int(topKeyIndex - bottomKeyIndex) + 1;

  let isMajor =
    switch (degree) {
    | 2
    | 3
    | 6
    | 7 => true
    | _ => false
    };
  ();
};

/* let addInterval = (pitch: t, interval: Interval.t) => { */
/*   let degree = interval.degree - 1; */
/*   let targetKeyType = */
/* }; */
