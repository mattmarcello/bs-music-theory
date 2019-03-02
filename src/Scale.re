module B = Belt;

type t = ScaleT.t;

module ScalePitch = {
  type scale = t;
  type t = PitchType.t;

  let rawValue = ({key, octave}: t) => {
    let semitones =
      key.type_->KeyType.rawValue + key.accidental->Accidental.rawValue;
    semitones + (octave + 1) * 12;
  };

  let makeWithMidiNote = (~midiNote, ~isPreferredAccidentalSharps=true, ()) => {
    let octave = midiNote / 12 - 1;
    let keyIndex = midiNote mod 12;
    let key =
      (isPreferredAccidentalSharps ? Key.keysWithSharps : Key.keysWithFlats)
      ->Belt.List.getExn(keyIndex);

    PitchType.{octave, key};
  };
  let makeWithRawValue = (~rawValue, ()) =>
    makeWithMidiNote(~midiNote=rawValue, ());
  let addHalfstep: (t, int) => t =
    (pitch, halfstep) => {
      makeWithRawValue(~rawValue=(pitch |> rawValue) + halfstep, ());
    };

  let addInterval = (pitch: t, interval: Interval.t) => {
    let degree = interval.degree - 1;

    /* Js.log2("degree", degree); */

    let targetKeyType = pitch.key.type_->KeyType.atDistance(degree);

    /* Js.log2("targetKeyType", targetKeyType -> KeyType.description); */

    let targetPitch = pitch->addHalfstep(interval.semitones);

    /* Js.log2("targetPitch", targetPitch -> Pitch.description  ) */

    // TARGET OCTABE IS INCORRECT
    let targetOctave =
      pitch.octave
      + pitch.key.type_->KeyType.octaveDiff(interval, Octave.Higher);

    /* Js.log2("targetOctave", targetOctave ); */

    //convert pitch

    let convertedPitch =
      PitchType.{
        key: Key.makeWithType(~type_=targetKeyType, ()),
        octave: targetOctave,
      };


    let diff = targetPitch->rawValue - convertedPitch->rawValue;


    {
      ...convertedPitch,
      key: {
        ...convertedPitch.key,
        accidental: Accidental.initializeWithInteger(diff),
      },
    };
  };

  // TODO: this definitely needs to be cleaned up
  let acrossOctaves = (scale: scale, ~octaves: list(int), ()) => {
    octaves->B.List.reduce(
      [],
      (acc, octave) => {
        let root: t = {key: scale.key, octave};


        let pitches =
          scale.type_.intervals
          ->B.List.map(interval => {

              let result = root->addInterval(interval);


              result;
            });

        B.List.concat(acc, pitches);
      },
    );
  };

  let get: scale => list(Key.t) =
    scale => {
      acrossOctaves(scale, ~octaves=[1], ())
      ->Belt.List.map(pitch => pitch.key);
    };

  let subtractPitch: (t, t) => Interval.t =
    (t', t'') => {
      let top = t'->rawValue >= t''->rawValue ? t' : t'';
      let bottom = t'->rawValue < t''->rawValue ? t' : t'';
      let diff = top->rawValue - bottom->rawValue;

      /* Js.log4("xxx", top->Pitch.description, bottom->Pitch.description, diff); */

      let bottomKeyIndex =
        KeyType.all
        ->Util.indexOf(bottom.key.type_)
        ->Belt.Option.getWithDefault(0);
      let topKeyIndex =
        KeyType.all
        ->Util.indexOf(top.key.type_)
        ->Belt.Option.getWithDefault(0);

      let degree = Js.Math.abs_int(topKeyIndex - bottomKeyIndex) + 1;

      /* Js.log2("yyy", degree); */

      let isMajor =
        switch (degree) {
        | 2
        | 3
        | 6
        | 7 => true
        | _ => false
        };

      let majorScale: scale = {type_: ScaleType.major, key: bottom.key};

      /* Js.log2( */
      /*   "majorScale", */
      /*   majorScale.key->Key.description */
      /*   ++ " " */
      /*   ++ majorScale.type_.description */
      /* ++ " " */
      /*   ++ ( */
      /*     majorScale-> get->Belt.List.map(Key.description)->Belt.List.toArray */
      /*     |> Js.Array.joinWith(", ") */
      /*   ), */
      /* ); */

      get(majorScale)->Belt.List.has(top.key, (==)) ?
        {
          Interval.{
            quality: isMajor ? Major : Perfect,
            degree,
            semitones: diff,
          };
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
};

/* // TODO: this definitely needs to be cleaned up */
/* let get: t => list(Key.t) = */
/*   scale => { */
/*     acrossOctaves(scale, ~octaves=[1], ()) */
/*     ->Belt.List.map(pitch => pitch.key); */
/*   }; */

let harmonicField =
    (t: t, ~for_ as field: HarmonicField.t, ~inversion=0, ()): list(ChordT.t) => {
  let octaves = [0, 1, 2, 3, 4];

  let scalePitches = ScalePitch.acrossOctaves(t, ~octaves, ());

  let chords: ref(list(ChordT.t)) = ref([]);

  /* Js.log2("field", field->HarmonicField.description); */

  for (i in 0 to scalePitches->Belt.List.length / octaves->Belt.List.length - 1) {
    let chordPitches =
      switch (field) {
      | Triad => [
          scalePitches->Belt.List.getExn(i),
          scalePitches->Belt.List.getExn(i + 2),
          scalePitches->Belt.List.getExn(i + 4),
        ]
      | Tetrad => [
          scalePitches->Belt.List.getExn(i),
          scalePitches->Belt.List.getExn(i + 2),
          scalePitches->Belt.List.getExn(i + 4),
          scalePitches->Belt.List.getExn(i + 6),
        ]
      | Ninth => [
          scalePitches->Belt.List.getExn(i),
          scalePitches->Belt.List.getExn(i + 2),
          scalePitches->Belt.List.getExn(i + 4),
          scalePitches->Belt.List.getExn(i + 6),
          scalePitches->Belt.List.getExn(i + 8),
        ]
      | Eleventh => [
          scalePitches->Belt.List.getExn(i),
          scalePitches->Belt.List.getExn(i + 2),
          scalePitches->Belt.List.getExn(i + 4),
          scalePitches->Belt.List.getExn(i + 6),
          scalePitches->Belt.List.getExn(i + 8),
          scalePitches->Belt.List.getExn(i + 10),
        ]
      | Thirteenth => [
          scalePitches->Belt.List.getExn(i),
          scalePitches->Belt.List.getExn(i + 2),
          scalePitches->Belt.List.getExn(i + 4),
          scalePitches->Belt.List.getExn(i + 6),
          scalePitches->Belt.List.getExn(i + 8),
          scalePitches->Belt.List.getExn(i + 10),
          scalePitches->Belt.List.getExn(i + 12),
        ]
      };

    let root = chordPitches->Belt.List.headExn;

    /* Js.log2( */
    /*   "chord pitches", */
    /*   chordPitches->Belt.List.toArray->Belt.Array.map(Pitch.description), */
    /* ); */

    let intervals =
      chordPitches->Belt.List.map(pitch =>
        pitch->ScalePitch.subtractPitch(root)
      );

    /* Js.log2("intervals raw", intervals->Belt.List.toArray); */

    Js.log2(
      "intervals",
      intervals->Belt.List.toArray->Belt.Array.map(Interval.description),
    );

    switch (ChordTypeT.makeWithIntervals(intervals)) {
    | None =>
      /* Js.log("not able to make courd with intevals") */
      ()
    | Some(chord) =>
      chords :=
        Belt.List.concat(
          chords^,
          [ChordT.{type_: chord, key: root.key, inversion: 0}],
        )
    };
  };

  chords^;
};

let description = (t: ScaleT.t) => {
  t.key->Key.description
  ++ " "
  ++ t.type_.description
  ++ (
    t->ScalePitch.get->Belt.List.map(Key.description)->Belt.List.toArray
    |> Js.Array.joinWith(", ")
  );
};
