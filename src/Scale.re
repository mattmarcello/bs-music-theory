type t =
  Model.Scale.t = {
    type_: Model.ScaleType.t,
    key: Model.Key.t,
  };
let make =
    (~type_: Model.ScaleType.t, ~key: Model.Key.t) => {
  type_,
  key,
};
let pitches = (scale: t, ~octaves: list(int), ()) => {
  octaves->Belt.List.reduce(
    [],
    (acc, octave) => {
      let root: Model.Pitch.t = Model.Pitch.{key: scale.key, octave};
      let pitches =
        scale.type_.intervals
        ->Belt.List.map(interval => {
            let result = root->Pitch.addInterval(interval);
            result;
          });
      Belt.List.concat(acc, pitches);
    },
  );
};
let keys: t => list(Model.Key.t) =
  scale => {
    pitches(scale, ~octaves=[1], ())->Belt.List.map(pitch => pitch.key);
  };
let harmonicField =
    (t: t, ~for_ as field: HarmonicField.t, ~inversion=0, ())
    : list(Model.Chord.t) => {
  let octaves = [0, 1, 2, 3, 4];
  let scalePitches = pitches(t, ~octaves, ());
  let chords: ref(list(Model.Chord.t)) = ref([]);
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
    let root = chordPitches->Belt.List.headExn /*   chordPitches->Belt.List.toArray->Belt.Array.map(Pitch.description), */ /*   "chord pitches", */ /* Js.log2( */;
    /* ); */ let intervals =
               chordPitches->Belt.List.map(pitch =>
                 pitch->Pitch.subtractPitch(root)
               );
    switch (ChordType.makeWithIntervals(intervals)) {
    | None => ()
    | Some(chord) =>
      chords :=
        Belt.List.concat(
          chords^,
          [Model.Chord.{type_: chord, key: root.key, inversion}],
        )
    };
  };
  chords^;
};
let description = t => {
  t.key->Key.description
  ++ " "
  ++ t.type_.description
  ++ (
    t->keys->Belt.List.map(Key.description)->Belt.List.toArray
    |> Js.Array.joinWith(", ")
  );
};
