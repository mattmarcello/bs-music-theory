include Model.ScaleType;

let ionian = {
  intervals:
    Interval.[perfect1, major2, major3, perfect4, perfect5, major6, major7],
  description: "Ionian",
};

let aeolian = {
  intervals:
    Interval.[perfect1, major2, minor3, perfect4, perfect5, minor6, minor7],
  description: "Aeolian",
};

let dorian = {
  intervals:
    Interval.[perfect1, major2, minor3, perfect4, perfect5, major6, minor7],
  description: "Dorian",
};

let mixolydian = {
  intervals:
    Interval.[perfect1, major2, major3, perfect4, perfect5, major6, minor7],
  description: "Mixolydian",
};

let phrygian = {
  intervals:
    Interval.[perfect1, minor2, minor3, perfect4, perfect5, minor6, minor7],
  description: "Phrygian",
};

let lydian = {
  intervals:
    Interval.[
      perfect1,
      major2,
      major3,
      diminished5,
      perfect5,
      major6,
      major7,
    ],
  description: "Lydian",
};

let locrian = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      minor3,
      perfect4,
      diminished5,
      minor6,
      minor7,
    ],
  description: "Locrian",
};

let locrian = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      minor3,
      perfect4,
      diminished5,
      minor6,
      minor7,
    ],
  description: "Locrian",
};

let major = {intervals: ionian.intervals, description: "Major"};
let minor = {intervals: aeolian.intervals, description: "Minor"};
let harmonicMinor = {
  intervals:
    Interval.[perfect1, major2, minor3, perfect4, perfect5, minor6, major7],
  description: "Harmonic Minor",
};
let melodicMinor = {
  intervals:
    Interval.[perfect1, major2, minor3, perfect4, perfect5, major6, minor7],
  description: "Harmonic Minor",
};

let pentatonicMajor = {
  intervals: Interval.[perfect1, minor3, perfect4, perfect5, major7],
  description: "Pentatonic Major",
};

let pentatonicMinor = {
  intervals: Interval.[perfect1, minor3, perfect4, perfect5, minor7],
  description: "Pentatonic Minor",
};

let pentatonicBlues = {
  intervals:
    Interval.[perfect1, minor3, perfect4, diminished5, perfect5, minor7],
  description: "Pentatonic Blues",
};

let pentatonicNeutral = {
  intervals: Interval.[perfect1, major2, perfect4, perfect5, minor7],
  description: "Pentatonic Neutral",
};

let dimHalf = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      minor3,
      major3,
      diminished5,
      perfect5,
      major6,
      minor7,
    ],
  description: "Half Diminished",
};

let dimWhole = {
  intervals:
    Interval.[
      perfect1,
      major2,
      minor3,
      perfect4,
      diminished5,
      minor6,
      major6,
      major7,
    ],
  description: "Half Diminished",
};

let whole = {
  intervals: Interval.[perfect1, major2, major3, diminished5, minor6, minor7],
  description: "Whole",
};

let augmented = {
  intervals: Interval.[minor3, major3, perfect5, minor6, major7],
  description: "Augmented",
};

let chromatic = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      major2,
      minor3,
      major3,
      perfect4,
      diminished5,
      perfect5,
      minor6,
      major6,
      minor7,
      major7,
    ],
  description: "Chromatic",
};

let romanianMinor = {
  intervals:
    Interval.[
      perfect1,
      major2,
      minor3,
      diminished5,
      perfect5,
      major6,
      minor7,
    ],
  description: "Romian Minor",
};

let spanishGypsy = {
  intervals:
    Interval.[perfect1, minor2, major3, perfect4, perfect5, minor6, minor7],
  description: "Spanish Gypsy",
};

let blues = {
  intervals:
    Interval.[perfect1, minor3, perfect4, diminished5, perfect5, minor7],
  description: "Blues",
};

let diatonic = {
  intervals: Interval.[perfect1, major2, major3, perfect5, major6],
  description: "diatonic",
};

let doubleHarmonic = {
  intervals:
    Interval.[perfect1, minor2, major3, perfect4, perfect5, minor6, major7],
  description: "Double Harmonic",
};

let eightToneSpanish = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      minor3,
      major3,
      perfect4,
      diminished5,
      minor6,
      minor7,
    ],
  description: "Eight Tone Spanish",
};

let enigmatic = {
  intervals:
    Interval.[perfect1, minor2, major3, diminished5, minor6, minor7, major7],
  description: "Enigmatic",
};

let leadingWholeTone = {
  intervals:
    Interval.[perfect1, major2, major3, diminished5, minor6, major6, minor7],
  description: "Leading Whole Tone",
};

let lydianAugmented = {
  intervals:
    Interval.[perfect1, major2, major3, diminished5, minor6, major6, major7],
  description: "Lydian Augmented",
};

let neopolitanMajor = {
  intervals:
    Interval.[perfect1, minor2, minor3, perfect4, perfect5, major6, major7],
  description: "Neopolitan Major",
};

let neopolitanMinor = {
  intervals:
    Interval.[perfect1, minor2, minor3, perfect4, perfect5, minor6, minor7],
  description: "Neopolitan Minor",
};

let pelog = {
  intervals: Interval.[perfect1, minor2, minor3, diminished5, minor7, major7],
  description: "Pelog",
};

let prometheus = {
  intervals: Interval.[perfect1, major2, major3, diminished5, major6, minor7],
  description: "Prometheus",
};

let prometheusNeopolitan = {
  intervals: Interval.[perfect1, minor2, major3, diminished5, major6, minor7],
  description: "Prometheus Neopolitan",
};
let sixToneSymmetrical = {
  intervals: Interval.[perfect1, minor2, major3, perfect4, minor6, major6],
  description: "Six Tone Symmetrical",
};

let superLocrian = {
  intervals:
    Interval.[perfect1, minor2, minor3, major3, diminished5, minor6, minor7],
  description: "Super Locrian",
};

let lydianMinor = {
  intervals:
    Interval.[
      perfect1,
      major2,
      major3,
      diminished5,
      perfect5,
      minor6,
      minor7,
    ],
  description: "Lydian Minor",
};

let lydianDiminished = {
  intervals:
    Interval.[
      perfect1,
      major2,
      minor3,
      diminished5,
      perfect5,
      minor6,
      minor7,
    ],
  description: "Lydian Diminished",
};

let nineToneScale = {
  intervals:
    Interval.[
      perfect1,
      major2,
      minor3,
      major3,
      diminished5,
      perfect5,
      minor6,
      major6,
      major7,
    ],
  description: "Nine Tone Scale",
};

let auxiliaryDiminished = {
  intervals:
    Interval.[
      perfect1,
      major2,
      minor3,
      perfect4,
      diminished5,
      minor6,
      major6,
      major7,
    ],
  description: "Auxiliary Diminished",
};

let auxiliaryAugmented = {
  intervals: Interval.[perfect1, major2, major3, diminished5, minor6, minor7],
  description: "Auxiliary Augmented",
};

let auxiliaryDimBlues = {
  intervals:
    Interval.[
      perfect1,
      minor2,
      minor3,
      major3,
      diminished5,
      perfect5,
      major6,
      minor7,
    ],
  description: "Auxiliary Dim Blues",
};

let majorLocrian = {
  intervals:
    Interval.[
      perfect1,
      major2,
      major3,
      perfect4,
      diminished5,
      minor6,
      minor7,
    ],
  description: "Major Locrian",
};

let overtone = {
  intervals:
    Interval.[
      perfect1,
      major2,
      major3,
      diminished5,
      perfect5,
      major6,
      minor7,
    ],
  description: "Overtone",
};

let diminishedWholeTone = {
  intervals:
    Interval.[perfect1, minor2, minor3, major3, diminished5, minor6, minor7],
  description: "Diminished Whole Tone",
};

let pureMinor = {
  intervals:
    Interval.[perfect1, major2, minor3, perfect4, perfect5, minor6, minor7],
  description: "Pure Minor",
};

let dominant7th = {
  intervals:
    Interval.[perfect1, major2, major3, perfect4, perfect5, major6, minor7],
  description: "Dominant 7th",
};

let all = [
  major,
  minor,
  harmonicMinor,
  melodicMinor,
  pentatonicMajor,
  pentatonicMinor,
  pentatonicBlues,
  pentatonicNeutral,
  ionian,
  aeolian,
  dorian,
  mixolydian,
  phrygian,
  lydian,
  locrian,
  dimHalf,
  whole,
  augmented,
  chromatic,
  romanianMinor,
  spanishGypsy,
  blues,
  diatonic,
  doubleHarmonic,
  eightToneSpanish,
  enigmatic,
  leadingWholeTone,
  lydianAugmented,
  neopolitanMajor,
  neopolitanMinor,
  pelog,
  prometheus,
  prometheusNeopolitan,
  sixToneSymmetrical,
  superLocrian,
  lydianMinor,
  lydianDiminished,
  nineToneScale,
  auxiliaryDiminished,
  auxiliaryAugmented,
  auxiliaryDimBlues,
  majorLocrian,
  overtone,
  diminishedWholeTone,
  pureMinor,
  dominant7th,
];

let equals = (t', t'') => t'.intervals == t''.intervals;
