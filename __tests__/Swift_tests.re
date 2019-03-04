open Jest;

testAll(
  "pitches",
  [
    {
      let c0 = Pitch.make(`IntegerLiteral(12));

      Expect.(
        expect((c0.octave, c0.key.accidental, c0.key.type_))
        |> toEqual((0, Accidental.Natural, KeyType.C))
      );
    },
    {
      let c0 = Pitch.make(`IntegerLiteral(12));
      Expect.(
        expect(c0->Pitch.subtractHalfstep(12)->Pitch.rawValue) |> toEqual(0)
      );
    },
    {
      let pitch = Pitch.make(`MidiNote(127));
      Expect.(expect(pitch.key) |> toEqual(Key.make(`Type(KeyType.G))));
    },
    {
      let pitch = Pitch.make(`MidiNote(0));
      Expect.(expect(pitch.key) |> toEqual(Key.make(`Type(KeyType.C))));
    },
    {
      let pitch = Pitch.make(`MidiNote(0));
      Expect.(expect(pitch.key) |> toEqual(Key.make(`Type(KeyType.C))));
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
      let c1 = PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let db1 = PitchType.{key: Key.make(`StringLiteral("db")), octave: 1};

      c1->Pitch.addInterval(Interval.minor2)->Pitch.equal(db1) ?
        pass : fail("");
    },
    {
      let c1 = PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let d1 = PitchType.{key: Key.make(`StringLiteral("d")), octave: 1};

      c1->Pitch.addInterval(Interval.major2)->Pitch.equal(d1) ?
        pass : fail("");
    },
    {
      let c1 = PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let eb1 = PitchType.{key: Key.make(`StringLiteral("eb")), octave: 1};

      c1->Pitch.addInterval(Interval.minor3)->Pitch.equal(eb1) ?
        pass : fail("");
    },
    {
      let c1 = PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let e1 = PitchType.{key: Key.make(`StringLiteral("e")), octave: 1};

      c1->Pitch.addInterval(Interval.major3)->Pitch.equal(e1) ?
        pass : fail("");
    },
    {
      let c1 = PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let c2 = PitchType.{key: Key.make(`StringLiteral("C")), octave: 2};

      c1->Pitch.addInterval(Interval.perfect8)->Pitch.equal(c2) ?
        pass : fail("");
    },
    {
      let d1 = PitchType.{key: Key.make(`Type(KeyType.D)), octave: 1};

      let csharp1 =
        PitchType.{key: Key.make(`StringLiteral("C#")), octave: 1};

      d1->Pitch.subtractInterval(Interval.minor2)->Pitch.equal(csharp1) ?
        pass : fail("");
    },
    {
      let d1 = PitchType.{key: Key.make(`Type(KeyType.D)), octave: 1};

      let c1 = PitchType.{key: Key.make(`StringLiteral("C")), octave: 1};

      d1->Pitch.subtractInterval(Interval.major2)->Pitch.equal(c1) ?
        pass : fail("");
    },
    {
      let p = Pitch.make(`StringLiteral("f#-5"));

      let fsharp = Key.make(`StringLiteral("f#"));

      Expect.(expect(p.key) |> toEqual(fsharp));
    },
    {
      let p = Pitch.make(`StringLiteral("f#-5"));

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
      let note = PitchType.{key: Key.make(`Type(KeyType.A)), octave: 4};
      Expect.(expect(note->Pitch.frequency) |> toEqual(440.0));
    },
    {
      let note = PitchType.{key: Key.make(`Type(KeyType.A)), octave: 4};
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

      let noteValue = NoteValue.make(`Type(NoteValueType.Quarter));

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

  let tempo = Tempo.default;

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
        Key.make(`Type(KeyType.C)),
        Key.make(`Type(KeyType.D)),
        Key.make(`Type(KeyType.E)),
        Key.make(`Type(KeyType.F)),
        Key.make(`Type(KeyType.G)),
        Key.make(`Type(KeyType.A)),
        Key.make(`Type(KeyType.B)),
      ];

      let cMajScale =
        ScaleT.{type_: ScaleType.major, key: Key.make(`Type(KeyType.C))};

      Expect.(expect(cMajScale |> Pitch.ScaleKeys.get) |> toEqual(cMaj));
    },
    {
      let cMin = [
        Key.make(`Type(KeyType.C)),
        Key.make(`Type(KeyType.D)),
        Key.make(`StringLiteral("Eb")),
        Key.make(`Type(KeyType.F)),
        Key.make(`Type(KeyType.G)),
        Key.make(`StringLiteral("Ab")),
        Key.make(`StringLiteral("Bb")),
      ];

      let cMinScale =
        ScaleT.{type_: ScaleType.minor, key: Key.make(`Type(KeyType.C))};

      Expect.(expect(cMinScale |> Pitch.ScaleKeys.get) |> toEqual(cMin));
    },
  ],
  assertion =>
  assertion
);

test("harmonic fields", () => {
  let cMaj =
    ScaleT.{type_: ScaleType.major, key: Key.make(`Type(KeyType.C))};

  let triads: list(Chord.t) = cMaj->Scale.harmonicField(~for_=Triad, ());

  let triadsExpected: list(ChordT.t) = [
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Major, ()),
      key: Key.make(`Type(KeyType.C)),
      inversion: 0,
    },
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Minor, ()),
      key: Key.make(`Type(KeyType.D)),
      inversion: 0,
    },
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Minor, ()),
      key: Key.make(`Type(KeyType.E)),
      inversion: 0,
    },
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Major, ()),
      key: Key.make(`Type(KeyType.F)),
      inversion: 0,
    },
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Major, ()),
      key: Key.make(`Type(KeyType.G)),
      inversion: 0,
    },
    Chord.{
      type_: ChordTypeT.make(~third=ChordTypeT.ChordThirdType.Minor, ()),
      key: Key.make(`Type(KeyType.A)),
      inversion: 0,
    },
    Chord.{
      type_:
        ChordTypeT.make(
          ~third=ChordTypeT.ChordThirdType.Minor,
          ~fifth=ChordTypeT.ChordFifthType.Diminished,
          (),
        ),
      key: Key.make(`Type(KeyType.B)),
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
        Key.make(`Type(KeyType.C)),
        Key.make(`Type(KeyType.E)),
        Key.make(`Type(KeyType.G)),
      ];

      let cMaj =
        ChordT.{
          type_: ChordTypeT.make(~third=Major, ()),
          key: Key.make(`Type(KeyType.C)),
          inversion: 0 // TODO shouldn't have to specify inversion
        };

      Expect.(expect(cMajNotes) |> toEqual(cMaj->Chord.keys));
    },
    {
      let cMinNotes = [
        Key.make(`Type(KeyType.C)),
        Key.{type_: KeyType.E, accidental: Accidental.flat},
        Key.make(`Type(KeyType.G)),
      ];

      let cMin =
        ChordT.{
          type_: ChordTypeT.make(~third=Minor, ()),
          key: Key.make(`Type(KeyType.C)),
          inversion: 0 // TODO shouldn't have to specify inversion
        };

      Expect.(expect(cMinNotes) |> toEqual(cMin->Chord.keys));
    },
    {
      let c13Pitches = [
        PitchType.{key: Key.make(`Type(KeyType.C)), octave: 1},
        PitchType.{key: Key.make(`Type(KeyType.E)), octave: 1},
        PitchType.{key: Key.make(`Type(KeyType.G)), octave: 1},
        PitchType.{
          key: Key.{type_: KeyType.B, accidental: Accidental.flat},
          octave: 1,
        },
        PitchType.{key: Key.make(`Type(KeyType.D)), octave: 2},
        PitchType.{key: Key.make(`Type(KeyType.F)), octave: 2},
        PitchType.{key: Key.make(`Type(KeyType.A)), octave: 2},
      ];

      let c13 =
        ChordT.{
          type_:
            ChordTypeT.make(
              ~third=Major,
              ~seventh=Dominant,
              ~extensions=[
                ChordTypeT.ChordExtensionType.make(
                  ~type_=ChordTypeT.ChordExtensionType.ExtensionType.Thirteenth,
                  (),
                )
                ->Belt.Option.getExn //TODO: this is a horrible API ,
              ],
              (),
            ),
          key: Key.make(`Type(KeyType.C)),
          inversion: 0 //TODO: shouldn't have to specify version j
        };

      let actual = c13->Chord.pitches(~octave=1, ());

      Expect.(expect(actual) |> toEqual(c13Pitches));
    },
  ],
  assertion =>
  assertion
);
