type t = {
  intervals: list(Interval.t),
  description: string,
};

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
  description: "Pentatonic Major"
};
