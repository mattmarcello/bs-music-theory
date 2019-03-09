open Jest;

testAll(
  "intervals",
  [
    {
      let key = Key.make(~type_=C, ());

      let pitch = Pitch.{key, octave: 1};

      Expect.(
        expect(
          {
            let pitch: Pitch.t = pitch->Pitch.addHalfstep(12);
            pitch.octave;
          },
        )
        |> toEqual(pitch.octave + 1)
      );
    },
    {
      let pitch =
        {key: Key.make(~type_=C, ()), octave: 1}->Pitch.addHalfstep(1);

      let actual = pitch.key;

      let expected = Key.{type_: C, accidental: Accidental.sharp};

      Key.equals(actual, expected) ? pass : fail("");
    },
    {
      let pitch' =
        Pitch.{key: Key.make(~type_=C, ()), octave: 1}
        ->Pitch.subtractHalfstep(1);

      let pitch'' = Pitch.{key: Key.make(~type_=B, ()), octave: 0};

      Expect.(expect(pitch') |> toEqual(pitch''));
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=C, ()), octave: 1};

      let d1 = Pitch.{key: Key.make(~type_=D, ()), octave: 1};

      let actual = d1->Pitch.subtractPitch(c1);

      let expected = Interval.major2;

      Expect.(expect(actual) |> toEqual(expected));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "Accidentals",
  Accidental.[
    {
      let (actual, expected) = (flat->multiplyInt(2), doubleFlat);
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (doubleFlat->divideInt(2), flat);
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (
        Accidental.sharps(2)->subtractInt(2),
        Accidental.natural,
      );
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (
        Accidental.flats(2)->addInt(2),
        Accidental.natural,
      );
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (
        Accidental.sharps(2)->add(Accidental.sharps(1)),
        Accidental.makeWithInteger(3),
      );
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("#"), Sharps(1));

      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("##"), Sharps(2));
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (
        Accidental.makeWithString("###"),
        Sharps(3),
      );
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("b"), Flats(1));
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("bb"), Flats(2));
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("bbb"), Flats(3));
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString(""), Natural);
      Expect.(expect(actual) |> toEqual(expected));
    },
    {
      let (actual, expected) = (Accidental.makeWithString("#b#b"), Natural);
      Expect.(expect(actual) |> toEqual(expected));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "keys",
  [
    {
      let (actual, expected) = (
        Key.makeWithString("a##b"),
        Key.{type_: A, accidental: Sharps(1)},
      );

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let (actual, expected) = (
        Key.makeWithString("a#"),
        Key.{type_: A, accidental: Sharps(1)},
      );

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let actual = Key.{type_: C, accidental: Accidental.flat};
      let expected = Key.{type_: B, accidental: Natural};

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let actual = Key.{type_: C, accidental: Sharps(23)};
      let expected = Key.{type_: B, accidental: Natural};

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let actual = Key.{type_: C, accidental: Flats(13)};
      let expected = Key.{type_: B, accidental: Natural};

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let actual = Key.{type_: C, accidental: Flats(25)};
      let expected = Key.{type_: B, accidental: Natural};

      Key.equals(expected, actual) ? pass : fail("");
    },
    {
      let (key, distance, expectedKey) = KeyType.(D, (-2), B);

      KeyType.key(key, ~at=distance) == expectedKey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, (-19), F);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, 12, B);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, 0, D);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, 1, E);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, 2, F);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, (-3), A);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(D, (-301), D);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key, distance, expectedkey) = KeyType.(F, (-3), C);
      KeyType.key(key, ~at=distance) == expectedkey ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, B, 5);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, F, 2);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, D, 0);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, E, 1);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, F, 2);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(D, A, 4);

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
    {
      let (key', key'', distance) = KeyType.(F, C, (-3));

      KeyType.distance(key', ~from=key'') == distance ? pass : fail("");
    },
  ],
  assertion =>
  assertion
);

testAll(
  "pitches",
  [
    {
      let c0 = Pitch.makeWithInteger(12);

      Expect.(
        expect((c0.octave, c0.key.accidental, c0.key.type_))
        |> toEqual((0, Accidental.Natural, KeyType.C))
      );
    },
    {
      let c0 = Pitch.makeWithInteger(12);
      Expect.(
        expect(c0->Pitch.subtractHalfstep(12)->Pitch.rawValue) |> toEqual(0)
      );
    },
    {
      let pitch = Pitch.makeWithMidiNote(~midiNote=127, ());
      Expect.(expect(pitch.key) |> toEqual(Key.make(~type_=KeyType.G, ())));
    },
    {
      let pitch = Pitch.makeWithMidiNote(~midiNote=0, ());
      Expect.(expect(pitch.key) |> toEqual(Key.make(~type_=KeyType.C, ())));
    },
    {
      //TODO: not sure about this API
      let pitch =
        Pitch.makeWithMidiNote(
          ~midiNote=66,
          ~isPreferredAccidentalSharps=false,
          (),
        );
      Expect.(
        expect(pitch.key)
        |> toEqual(Key.{type_: KeyType.G, accidental: Accidental.flat})
      );
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1};

      let db1 = Pitch.{key: Key.makeWithString("db"), octave: 1};

      c1->Pitch.addInterval(Interval.minor2)->Pitch.equals(db1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1};

      let d1 = Pitch.{key: Key.makeWithString("d"), octave: 1};

      c1->Pitch.addInterval(Interval.major2)->Pitch.equals(d1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1};

      let eb1 = Pitch.{key: Key.makeWithString("eb"), octave: 1};

      c1->Pitch.addInterval(Interval.minor3)->Pitch.equals(eb1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1};

      let e1 = Pitch.{key: Key.makeWithString("e"), octave: 1};

      c1->Pitch.addInterval(Interval.major3)->Pitch.equals(e1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1};

      let c2 = Pitch.{key: Key.makeWithString("C"), octave: 2};

      c1->Pitch.addInterval(Interval.perfect8)->Pitch.equals(c2) ?
        pass : fail("");
    },
    {
      let d1 = Pitch.{key: Key.make(~type_=KeyType.D, ()), octave: 1};

      let csharp1 = Pitch.{key: Key.makeWithString("C#"), octave: 1};

      d1->Pitch.subtractInterval(Interval.minor2)->Pitch.equals(csharp1) ?
        pass : fail("");
    },
    {
      let d1 = Pitch.{key: Key.make(~type_=KeyType.D, ()), octave: 1};

      let c1 = Pitch.{key: Key.makeWithString("C"), octave: 1};

      d1->Pitch.subtractInterval(Interval.major2)->Pitch.equals(c1) ?
        pass : fail("");
    },
    {
      let p = Pitch.makeWithString("f#-5");

      let fsharp = Key.makeWithString("f#");

      Expect.(expect(p.key) |> toEqual(fsharp));
    },
    {
      let p = Pitch.makeWithString("f#-5");

      Expect.(expect(p.octave) |> toEqual(-5));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "frequency",
  [
    {
      let note = Pitch.{key: Key.make(~type_=KeyType.A, ()), octave: 4};
      Expect.(expect(note->Pitch.frequency) |> toEqual(440.0));
    },
    {
      let note = Pitch.{key: Key.make(~type_=KeyType.A, ()), octave: 4};
      let a4 = Pitch.nearest(440.0);

      Expect.(expect(a4) |> toEqual(Some(note)));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "note value conversison",
  [
    {
      let noteValue = NoteValue.{type_: Half, modifier: Dotted};

      let actual = noteValue->NoteValue.div(Sixteenth);

      let expected = 12.0;

      Expect.(expect(actual) |> toBe(expected));
    },
    {
      let noteValue = NoteValue.{type_: Half, modifier: Dotted};

      let actual = noteValue->NoteValue.div(Whole);

      let expected = 0.75;

      Expect.(expect(actual) |> toBe(expected));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "durations",
  [
    {
      let timeSignature = TimeSignature.{beats: 4, noteValue: Quarter};

      let tempo = Tempo.{timeSignature, bpm: 120.};

      let noteValue = NoteValue.makeWithType(NoteValueType.Quarter);

      let duration = tempo->Tempo.duration(~of_=noteValue, ());

      Expect.(expect(duration) |> toEqual(0.5));
    },
    {
      let timeSignature = TimeSignature.{beats: 4, noteValue: Quarter};

      let tempo = Tempo.{timeSignature, bpm: 120.};

      let noteValue =
        NoteValue.{type_: NoteValueType.Quarter, modifier: Dotted};

      let duration = tempo->Tempo.duration(~of_=noteValue, ());

      Expect.(expect(duration) |> toEqual(0.75));
    },
  ],
  assertion =>
  assertion
);

test("sample length calculations", () => {
  let rates = [
    NoteValue.{type_: Whole, modifier: Default},
    NoteValue.{type_: Half, modifier: Default},
    NoteValue.{type_: Half, modifier: Dotted},
    NoteValue.{type_: Half, modifier: Triplet},
    NoteValue.{type_: Quarter, modifier: Default},
    NoteValue.{type_: Quarter, modifier: Dotted},
    NoteValue.{type_: Quarter, modifier: Triplet},
    NoteValue.{type_: Eighth, modifier: Default},
    NoteValue.{type_: Eighth, modifier: Dotted},
    NoteValue.{type_: Sixteenth, modifier: Default},
    NoteValue.{type_: Sixteenth, modifier: Dotted},
    NoteValue.{type_: Thirtysecond, modifier: Default},
    NoteValue.{type_: Sixtyfourth, modifier: Default},
  ];

  let tempo = Tempo.make();

  let round = f =>
    f -. Js.Math.floor_float(f) >= 0.5 ?
      Js.Math.ceil_float(f) : Js.Math.floor_float(f);

  let actual =
    rates
    ->Belt.List.map(rate => tempo->Tempo.sampleLength(~of_=rate, ()))
    ->Belt.List.map(sampleLength => round(100. *. sampleLength) /. 100.);

  let expected = [
    88200.0,
    44100.0,
    66150.0,
    29401.47,
    22050.0,
    33075.0,
    14700.73,
    11025.0,
    16537.5,
    5512.5,
    8268.75,
    2756.25,
    1378.13,
  ];

  Expect.(expect(actual) |> toEqual(expected));
});

testAll(
  "scales",
  [
    {
      let cMaj = [
        Key.make(~type_=KeyType.C, ()),
        Key.make(~type_=KeyType.D, ()),
        Key.make(~type_=KeyType.E, ()),
        Key.make(~type_=KeyType.F, ()),
        Key.make(~type_=KeyType.G, ()),
        Key.make(~type_=KeyType.A, ()),
        Key.make(~type_=KeyType.B, ()),
      ];

      let cMajScale =
        Scale.{type_: ScaleType.major, key: Key.make(~type_=KeyType.C, ())};

      Expect.(expect(cMajScale |> Scale.keys) |> toEqual(cMaj));
    },
    {
      let cMin = [
        Key.make(~type_=KeyType.C, ()),
        Key.make(~type_=KeyType.D, ()),
        Key.makeWithString("Eb"),
        Key.make(~type_=KeyType.F, ()),
        Key.make(~type_=KeyType.G, ()),
        Key.makeWithString("Ab"),
        Key.makeWithString("Bb"),
      ];

      let cMinScale =
        Scale.{type_: ScaleType.minor, key: Key.make(~type_=KeyType.C, ())};

      Expect.(expect(cMinScale |> Scale.keys) |> toEqual(cMin));
    },
  ],
  assertion =>
  assertion
);

test("harmonic fields", () => {
  let cMaj =
    Scale.{type_: ScaleType.major, key: Key.make(~type_=KeyType.C, ())};

  let triads: list(Chord.t) = cMaj->Scale.harmonicField(~for_=Triad, ());

  let triadsExpected: list(Chord.t) = [
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Major, ()),
      key: Key.make(~type_=KeyType.C, ()),
      inversion: 0,
    },
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Minor, ()),
      key: Key.make(~type_=KeyType.D, ()),
      inversion: 0,
    },
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Minor, ()),
      key: Key.make(~type_=KeyType.E, ()),
      inversion: 0,
    },
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Major, ()),
      key: Key.make(~type_=KeyType.F, ()),
      inversion: 0,
    },
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Major, ()),
      key: Key.make(~type_=KeyType.G, ()),
      inversion: 0,
    },
    Chord.{
      type_: ChordType.make(~third=ChordType.ChordThirdType.Minor, ()),
      key: Key.make(~type_=KeyType.A, ()),
      inversion: 0,
    },
    Chord.{
      type_:
        ChordType.make(
          ~third=ChordType.ChordThirdType.Minor,
          ~fifth=ChordType.ChordFifthType.Diminished,
          (),
        ),
      key: Key.make(~type_=KeyType.B, ()),
      inversion: 0,
    },
  ];

  Expect.(expect(triads) |> toEqual(triadsExpected));
});

testAll(
  "chords",
  [
    {
      let cMajNotes = [
        Key.make(~type_=KeyType.C, ()),
        Key.make(~type_=KeyType.E, ()),
        Key.make(~type_=KeyType.G, ()),
      ];

      let cMaj =
        Chord.{
          type_: ChordType.make(~third=Major, ()),
          key: Key.make(~type_=KeyType.C, ()),
          inversion: 0 // TODO shouldn't have to specify inversion
        };

      Expect.(expect(cMajNotes) |> toEqual(cMaj->Chord.keys));
    },
    {
      let cMinNotes = [
        Key.make(~type_=KeyType.C, ()),
        Key.{type_: KeyType.E, accidental: Accidental.flat},
        Key.make(~type_=KeyType.G, ()),
      ];

      let cMin =
        Chord.{
          type_: ChordType.make(~third=Minor, ()),
          key: Key.make(~type_=KeyType.C, ()),
          inversion: 0 // TODO shouldn't have to specify inversion
        };

      Expect.(expect(cMinNotes) |> toEqual(cMin->Chord.keys));
    },
    {
      let c13Pitches = [
        Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1},
        Pitch.{key: Key.make(~type_=KeyType.E, ()), octave: 1},
        Pitch.{key: Key.make(~type_=KeyType.G, ()), octave: 1},
        Pitch.{
          key: Key.{type_: KeyType.B, accidental: Accidental.flat},
          octave: 1,
        },
        Pitch.{key: Key.make(~type_=KeyType.D, ()), octave: 2},
        Pitch.{key: Key.make(~type_=KeyType.F, ()), octave: 2},
        Pitch.{key: Key.make(~type_=KeyType.A, ()), octave: 2},
      ];

      let c13 =
        Chord.{
          type_:
            ChordType.make(
              ~third=Major,
              ~seventh=Dominant,
              ~extensions=[
                ChordType.ChordExtensionType.make(
                  ~type_=ChordType.ChordExtensionType.ExtensionType.Thirteenth,
                  (),
                ),
              ],
              (),
            ),
          key: Key.make(~type_=KeyType.C, ()),
          inversion: 0 //TODO: shouldn't have to specify version j
        };

      let actual = c13->Chord.pitches(~octave=1, ());

      Expect.(expect(actual) |> toEqual(c13Pitches));
    },
    {
      let cm13Pitches = [
        Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1},
        Pitch.{
          key: Key.{type_: KeyType.E, accidental: Accidental.flat},
          octave: 1,
        },
        Pitch.{key: Key.make(~type_=KeyType.G, ()), octave: 1},
        Pitch.{
          key: Key.{type_: KeyType.B, accidental: Accidental.flat},
          octave: 1,
        },
        Pitch.{key: Key.make(~type_=KeyType.D, ()), octave: 2},
        Pitch.{key: Key.make(~type_=KeyType.F, ()), octave: 2},
        Pitch.{key: Key.make(~type_=KeyType.A, ()), octave: 2},
      ];

      let cm13 =
        Chord.{
          type_:
            ChordType.make(
              ~third=Minor,
              ~seventh=Dominant,
              ~extensions=[
                ChordType.ChordExtensionType.make(
                  ~type_=ChordType.ChordExtensionType.ExtensionType.Thirteenth,
                  (),
                ),
              ],
              (),
            ),
          key: Key.make(~type_=KeyType.C, ()),
          inversion: 0 //TODO: shouldn't have to specify version j
        };

      let actual = cm13->Chord.pitches(~octave=1, ());

      Expect.(expect(actual) |> toEqual(cm13Pitches));
    },
    {
      let minorIntervals = Interval.[perfect1, minor3, perfect5];

      switch (minorIntervals->ChordType.makeWithIntervals) {
      | Some(chord) =>
        Expect.(expect(chord) |> toEqual(ChordType.make(~third=Minor, ())))
      | None => fail("")
      };
    },
    {
      let majorIntervals = Interval.[perfect1, major3, perfect5];

      switch (majorIntervals->ChordType.makeWithIntervals) {
      | Some(chord) =>
        Expect.(expect(chord) |> toEqual(ChordType.make(~third=Major, ())))
      | None => fail("")
      };
    },
    {
      let cmadd13Notes = [
        Pitch.{key: Key.make(~type_=KeyType.C, ()), octave: 1},
        Pitch.{
          key: Key.{type_: KeyType.E, accidental: Accidental.flat},
          octave: 1,
        },
        Pitch.{key: Key.make(~type_=KeyType.G, ()), octave: 1},
        Pitch.{key: Key.make(~type_=KeyType.A, ()), octave: 2},
      ];

      let cmadd13 =
        Chord.{
          type_:
            ChordType.make(
              ~third=Minor,
              ~extensions=[
                ChordType.ChordExtensionType.make(
                  ~type_=ChordType.ChordExtensionType.ExtensionType.Thirteenth,
                  (),
                ),
              ],
              (),
            ),
          key: Key.make(~type_=KeyType.C, ()),
          inversion: 0 //TODO: shouldn't have to specify version j
        };

      let actual = cmadd13->Chord.pitches(~octave=1, ());

      Expect.(expect(actual) |> toEqual(cmadd13Notes));
    },
  ],
  assertion =>
  assertion
);

testAll(
  "roman numerics",
  [
    {
      let cMaj =
        Scale.{type_: ScaleType.major, key: Key.make(~type_=KeyType.C, ())};

      let cmajNumerics = ["I", "ii", "iii", "IV", "V", "vi", "vii°"];

      let cmajChords: list(Chord.t) =
        cMaj->Scale.harmonicField(~for_=Triad, ());

      Expect.(
        expect(
          cmajChords
          ->Belt.List.map(__x => Chord.romanNumeric(__x, ~for_=cMaj))
          ->Belt.List.keepMap(Util.identity),
        )
        |> toEqual(cmajNumerics)
      );
    },
    {
      let cMin =
        Scale.{type_: ScaleType.minor, key: Key.make(~type_=KeyType.C, ())};

      let cminNumerics = ["i", "ii°", "III", "iv", "v", "VI", "VII"];

      let cminChords: list(Chord.t) =
        cMin->Scale.harmonicField(~for_=Triad, ());

      Expect.(
        expect(
          cminChords
          ->Belt.List.map(__x => Chord.romanNumeric(__x, ~for_=cMin))
          ->Belt.List.keepMap(Util.identity),
        )
        |> toEqual(cminNumerics)
      );
    },
  ],
  assertion =>
  assertion
);

test("inversions", () => {
  let c7 =
    Chord.{
      type_: ChordType.make(~third=Major, ~seventh=Dominant, ()),
      key: Key.make(~type_=KeyType.C, ()),
      inversion: 0 //TODO: shouldn't have to specify version j
    };

  let c7Inversions =
    Pitch.[
      [
        {
          key: {
            type_: KeyType.C,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.E,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.G,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.B,
            accidental: Accidental.flat,
          },
          octave: 1,
        },
      ],
      [
        {
          key: {
            type_: KeyType.E,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.G,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.B,
            accidental: Accidental.flat,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.C,
            accidental: Natural,
          },
          octave: 2,
        },
      ],
      [
        {
          key: {
            type_: KeyType.G,
            accidental: Natural,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.B,
            accidental: Accidental.flat,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.C,
            accidental: Natural,
          },
          octave: 2,
        },
        {
          key: {
            type_: KeyType.E,
            accidental: Natural,
          },
          octave: 2,
        },
      ],
      [
        {
          key: {
            type_: KeyType.B,
            accidental: Accidental.flat,
          },
          octave: 1,
        },
        {
          key: {
            type_: KeyType.C,
            accidental: Natural,
          },
          octave: 2,
        },
        {
          key: {
            type_: KeyType.E,
            accidental: Natural,
          },
          octave: 2,
        },
        {
          key: {
            type_: KeyType.G,
            accidental: Natural,
          },
          octave: 2,
        },
      ],
    ];


  Expect.(
    expect(
      c7
      ->Chord.inversions
      ->Belt.List.map(chord => Chord.pitches(chord, ~octave=1, ())),
    )
    |> toEqual(c7Inversions)
  );
});
