include Model.Pitch;


let toString = ({key, octave} : t ) => {
  key->Key.description  ++ string_of_int(octave);
};

let rawValue = ({key, octave}: t ) => {
  let semitones =
    key.type_->KeyType.rawValue + key.accidental->Accidental.rawValue;
  semitones + (octave + 1) * 12;
};

let makeWithMidiNote = (~midiNote, ~isPreferredAccidentalSharps=true, ()) : t => {
  let octave = midiNote / 12 - 1;
  let keyIndex = midiNote mod 12;
  let key =
    (isPreferredAccidentalSharps ? Key.keysWithSharps : Key.keysWithFlats)
    ->Belt.List.getExn(keyIndex);

  {octave, key};
};
let makeWithRawValue = (~rawValue, ()) =>
  makeWithMidiNote(~midiNote=rawValue, ());

let addHalfstep: (t, int) => t =
  (pitch, halfstep) => {
    makeWithRawValue(~rawValue=(pitch |> rawValue) + halfstep, ());
  };

let makeWithStringLiteral = (str: string) : t  => {
  let pattern = Js.Re.fromString("([A-Ga-g])([#♯♭b]*)(-?)(\\d+)");

  switch (
    str
    ->Js.Re.exec(pattern)
    ->Belt.Option.map(Js.Re.captures)
    ->Belt.Option.map(Belt.List.fromArray)
    ->Belt.Option.map(l => l->Belt.List.map(Js.Nullable.toOption))
  ) {
  | Some([
      _,
      Some(keyTypeString),
      Some(accidentalString),
      Some(signString),
      Some(octaveString),
    ]) =>
    let keyType = KeyType.makeWithString((keyTypeString));

    let accidental = Accidental.makeWithString(accidentalString);

    let octave = int_of_string(octaveString) * (signString == "-" ? (-1) : 1);

    {
      key: {
        type_: keyType,
        accidental,
      },
      octave,
    };

  | _ => {key: Key.makeWithString("c"), octave: 0}
  };
};

let make =
  fun
  | `IntegerLiteral(i)
  | `RawValue(i) => makeWithRawValue(~rawValue=i, ())
  | `MidiNote(midiNote) => makeWithMidiNote(~midiNote, ())
  | `StringLiteral(s) => makeWithStringLiteral(s);

//* TODO: organize math operators */

let subtractHalfstep: (t, int) => t =
  (pitch, halfstep) => {
    makeWithRawValue(~rawValue=(pitch |> rawValue) - halfstep, ());
  };

let subtractInterval: (t, Interval.t) => t =
  (pitch, interval) => {
    let degree = - (interval.degree - 1);
    let targetKeyType = pitch.key.type_->KeyType.key(~at=degree);
    let targetPitch = pitch->subtractHalfstep(interval.semitones);

    let targetOctave =
      pitch.octave
      + pitch.key.type_->KeyType.octaveDiff(~for_=interval, ~isHigher=true);

    // convert pitch

    let convertedPitch :  t = {
      key: Key.make(~type_=targetKeyType, ()),
      octave: targetOctave,
    };
    let diff = targetPitch->rawValue - convertedPitch->rawValue;

    {
      ...convertedPitch,

      key: {
        ...convertedPitch.key,
        accidental: Accidental.makeWithInteger(diff),
      },
    };
  };

let addInterval = (pitch: t, interval: Interval.t) => {
  let degree = interval.degree - 1;
  let targetKeyType = pitch.key.type_->KeyType.key(~at=degree);
  let targetPitch = pitch->addHalfstep(interval.semitones);
  let targetOctave =
    pitch.octave
    + pitch.key.type_->KeyType.octaveDiff(~for_=interval, ~isHigher=true);

  //convert pitch

  let convertedPitch : t = {
    key: Key.make(~type_=targetKeyType, ()),
    octave: targetOctave,
  };

  let diff = targetPitch->rawValue - convertedPitch->rawValue;

  {
    ...convertedPitch,
    key: {
      ...convertedPitch.key,
      accidental: Accidental.makeWithInteger(diff),
    },
  };
};

let equal = (p', p'') => p'->rawValue == p''->rawValue;

let frequency = pitch => {

  Js.Math.pow_float(
    ~base=2.,
    ~exp=(float_of_int(rawValue(pitch)) -. 69.) /. 12.,
  )
  *. 440.;
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


  let sorted =
    results->Belt.List.sort(((_, d'), (_, d'')) =>
      d' -. d'' |> int_of_float
    );

  sorted->Belt.List.head->Belt.Option.map(fst);
};


module ScaleKeys = {
  module B = Belt;

  // TODO: rename this
  let acrossOctaves = (~scale: Scale.t, ~octaves: list(int), ()) => {
    octaves->B.List.reduce(
      [],
      (acc, octave) => {
        let root: t = {key: scale.key, octave};

        let pitches =
          scale.type_.intervals
          ->B.List.map(interval => {
              let p = root->addInterval(interval);

              p;
            });

        B.List.concat(acc, pitches);
      },
    );
  };

  let get: Scale.t => list(Key.t) =
    scale => {
      acrossOctaves(~scale, ~octaves=[1], ())
      ->Belt.List.map(pitch => pitch.key);
    };
};

let subtractPitch: (t, t) => Interval.t =
  (t', t'') => {
    let top = t'->rawValue >= t''->rawValue ? t' : t'';
    let bottom = t'->rawValue < t''->rawValue ? t' : t'';
    let diff = top->rawValue - bottom->rawValue;

    let bottomKeyIndex =
      KeyType.all
      ->Util.indexOf(bottom.key.type_)
      ->Belt.Option.getWithDefault(0);
    let topKeyIndex =
      KeyType.all
      ->Util.indexOf(top.key.type_)
      ->Belt.Option.getWithDefault(0);

    let degree = Js.Math.abs_int(topKeyIndex - bottomKeyIndex) + 1;

    let isMajor =
      switch (degree) {
      | 2
      | 3
      | 6
      | 7 => true
      | _ => false
      };

    let majorScale: Scale.t = {type_: ScaleType.major, key: bottom.key};

    ScaleKeys.get(majorScale)->Belt.List.has(top.key, (==)) ?
      {
        Interval.{quality: isMajor ? Major : Perfect, degree, semitones: diff};
      } :
      (
        if (isMajor) {
          let majorPitch =
            bottom->addInterval(
              Interval.{quality: Major, degree, semitones: diff},
            );

          let offset = top->rawValue - majorPitch->rawValue;

          Interval.{
            quality: offset > 0 ? Augmented : Minor,
            degree,
            semitones: diff,
          };
        } else {
          let perfectPitch =
            bottom->addInterval(
              Interval.{quality: Perfect, degree, semitones: diff},
            );

          let offset = top->rawValue - perfectPitch->rawValue;

          Interval.{
            quality: offset > 0 ? Augmented : Diminished,
            degree,
            semitones: diff,
          };
        }
      );
  };


let description = ({ key, octave}) => key -> Key.description  ++ octave -> string_of_int
