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
      let c1 = Pitch.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let db1 = Pitch.{key: Key.make(`StringLiteral("db")), octave: 1};

      c1->Pitch.addInterval(Interval.minor2)->Pitch.equal(db1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let d1 = Pitch.{key: Key.make(`StringLiteral("d")), octave: 1};

      c1->Pitch.addInterval(Interval.major2)->Pitch.equal(d1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let eb1 = Pitch.{key: Key.make(`StringLiteral("eb")), octave: 1};

      c1->Pitch.addInterval(Interval.minor3)->Pitch.equal(eb1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let e1 = Pitch.{key: Key.make(`StringLiteral("e")), octave: 1};

      c1->Pitch.addInterval(Interval.major3)->Pitch.equal(e1) ?
        pass : fail("");
    },
    {
      let c1 = Pitch.{key: Key.make(`Type(KeyType.C)), octave: 1};

      let c2 = Pitch.{key: Key.make(`StringLiteral("C")), octave: 2};

      c1->Pitch.addInterval(Interval.perfect8)->Pitch.equal(c2) ?
        pass : fail("");
    },
    {
      let d1 = Pitch.{key: Key.make(`Type(KeyType.D)), octave: 1};

      let csharp1 = Pitch.{key: Key.make(`StringLiteral("C#")), octave: 1};

      d1->Pitch.subtractInterval(Interval.minor2)->Pitch.equal(csharp1) ?
        pass : fail("");
    },
  ],
  assertion =>
  assertion
);
