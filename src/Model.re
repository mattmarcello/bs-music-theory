module Accidental = {
  type t =
    | Natural
    | Flats(int)
    | Sharps(int);
};

module KeyType = {
  type t =
    | C
    | D
    | E
    | F
    | G
    | A
    | B;
};

module Key = {
  type t = {
    type_: KeyType.t,
    accidental: Accidental.t,
  };
};

module ChordThirdType = {
  type t =
    | Major
    | Minor;
};

module ChordFifthType = {
  type t =
    | Perfect
    | Diminished
    | Augmented;
};

module ChordSixthType = {
  type t =
    | Sixth;
};
module ChordSeventhType = {
  type t =
    | Major
    | Dominant
    | Diminished;
};

module ChordSuspendedType = {
  type t =
    | Sus2
    | Sus4;
};

module ExtensionType = {
  type t =
    | Ninth
    | Eleventh
    | Thirteenth;
};

module ChordExtensionType = {
  type t = {
    type_: ExtensionType.t,
    accidental: Accidental.t,
    isAdded: bool, //TODO refactor
  };
};

module ChordType = {
  type t = {
    third: ChordThirdType.t,
    fifth: ChordFifthType.t,
    sixth: option(ChordSixthType.t),
    seventh: option(ChordSeventhType.t),
    suspended: option(ChordSuspendedType.t),
    extensions: option(list(ChordExtensionType.t)),
  };
};

module Chord = {
  type t = {
    type_: ChordType.t,
    key: Key.t,
    inversion: int,
  };
};

module HarmonicField = {
  type t =
    | Triad
    | Tetrad
    | Ninth
    | Eleventh
    | Thirteenth;
};

module IntervalQuality = {
  type t =
    | Diminished
    | Perfect
    | Minor
    | Major
    | Augmented;
};

module Interval = {
  type t = {
    quality: IntervalQuality.t,
    degree: int,
    semitones: int,
  };
};

module NoteModifier = {
  type t =
    | Default
    | Dotted
    | Triplet
    | Quintuplet;
};

module NoteValueType = {
  type t =
    | DoubleWhole
    | Whole
    | Half
    | Quarter
    | Eighth
    | Sixteenth
    | Thirtysecond
    | Sixtyfourth;
};

module NoteValue = {
  type t = {
    type_: NoteValueType.t,
    modifier: NoteModifier.t,
  };
};

module Octave = {
  type t =
    | Higher
    | Lower;
};

module Pitch = {
  type t = {
    key: Key.t,
    octave: int,
  };
};

module Quality = {
  type t =
    | Diminished
    | Perfect
    | Minor
    | Major
    | Augmented;
};

module ScaleType = {
  type t = {
    intervals: list(Interval.t),
    description: string,
  };
};

module Scale = {
  type t = {
    type_: ScaleType.t,
    key: Key.t,
  };
};

module TimeSignature = {

type t = {
  beats: int,
  noteValue: NoteValueType.t,
};
}

module Tempo = {
  type t = {
    timeSignature: TimeSignature.t,
    bpm: float,
  };
};
