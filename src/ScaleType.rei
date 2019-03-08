type t =
  Model.ScaleType.t = {
  intervals: list(Model.Interval.t),
  description: string,
};
let make:
  (~intervals: list(Interval.t), ~description: string=?, 
  unit) => t;
let ionian: t;
let aeolian: t;
let dorian: t;
let mixolydian: t;
let phrygian: t;
let lydian: t;
let locrian: t;
let major: t;
let minor: t;
let harmonicMinor: t;
let melodicMinor: t;
let pentatonicMajor: t;
let pentatonicMinor: t;
let pentatonicBlues: t;
let pentatonicNeutral: t;
let dimHalf: t;
let dimWhole: t;
let whole: t;
let augmented: t;
let chromatic: t;
let romanianMinor: t;
let spanishGypsy: t;
let blues: t;
let diatonic: t;
let doubleHarmonic: t;
let eightToneSpanish: t;
let enigmatic: t;
let leadingWholeTone: t;
let lydianAugmented: t;
let neopolitanMajor: t;
let neopolitanMinor: t;
let pelog: t;
let prometheus: t;
let prometheusNeopolitan: t;
let sixToneSymmetrical: t;
let superLocrian: t;
let lydianMinor: t;
let lydianDiminished: t;
let nineToneScale: t;
let auxiliaryDiminished: t;
let auxiliaryAugmented: t;
let auxiliaryDimBlues: t;
let majorLocrian: t;
let overtone: t;
let diminishedWholeTone: t;
let pureMinor: t;
let dominant7th: t;
let all: list(t);
let equals: (t, t) => bool;
