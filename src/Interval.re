type t = {
  quality: Interval_Quality.t,
  degree: int,
  semitones: int,
};

// TODO: remove
let qualityToString =
  fun
  | Interval_Quality.Perfect => "perfect"
  | Diminished => "diminished"
  | Minor => "minor"
  | Major => "major"
  | Augmented => "augmented"

let toString = ({ quality, degree,  semitones }) => {

	qualityToString(quality) ++ " " ++ string_of_int(degree) ++ " " ++ string_of_int(semitones);

}

let perfect1 = {quality: Perfect, degree: 1, semitones: 0};
let perfect4 = {quality: Perfect, degree: 4, semitones: 5};
let perfect5 = {quality: Perfect, degree: 5, semitones: 7};
let perfect8 = {quality: Perfect, degree: 8, semitones: 12};
let perfect11 = {quality: Perfect, degree: 11, semitones: 17};
let perfect12 = {quality: Perfect, degree: 12, semitones: 19};
let perfect15 = {quality: Perfect, degree: 15, semitones: 24};

let minor2 = {quality: Minor, degree: 2, semitones: 1};
let minor3 = {quality: Minor, degree: 3, semitones: 3};
let minor6 = {quality: Minor, degree: 6, semitones: 8};
let minor7 = {quality: Minor, degree: 7, semitones: 10};
let minor9 = {quality: Minor, degree: 9, semitones: 13};
let minor10 = {quality: Minor, degree: 10, semitones: 15};
let minor13 = {quality: Minor, degree: 13, semitones: 20};
let minor14 = {quality: Minor, degree: 14, semitones: 22};

let major2 = {quality: Major, degree: 2, semitones: 1};
let major3 = {quality: Major, degree: 3, semitones: 3};
let major6 = {quality: Major, degree: 6, semitones: 8};
let major7 = {quality: Major, degree: 7, semitones: 10};
let major9 = {quality: Major, degree: 9, semitones: 13};
let major10 = {quality: Major, degree: 10, semitones: 15};
let major13 = {quality: Major, degree: 13, semitones: 20};
let major14 = {quality: Major, degree: 14, semitones: 22};

let diminished1 = {quality: Diminished, degree: 1, semitones: (-1)};
let diminished2 = {quality: Diminished, degree: 2, semitones: 0};
let diminished3 = {quality: Diminished, degree: 3, semitones: 2};
let diminished4 = {quality: Diminished, degree: 4, semitones: 4};
let diminished5 = {quality: Diminished, degree: 5, semitones: 6};
let diminished6 = {quality: Diminished, degree: 6, semitones: 7};
let diminished7 = {quality: Diminished, degree: 7, semitones: 9};
let diminished8 = {quality: Diminished, degree: 8, semitones: 11};
let diminished9 = {quality: Diminished, degree: 9, semitones: 12};
let diminished10 = {quality: Diminished, degree: 10, semitones: 14};
let diminished11 = {quality: Diminished, degree: 11, semitones: 16};
let diminished12 = {quality: Diminished, degree: 12, semitones: 18};
let diminished13 = {quality: Diminished, degree: 13, semitones: 19};
let diminished14 = {quality: Diminished, degree: 14, semitones: 21};
let diminished15 = {quality: Diminished, degree: 15, semitones: 23};

let augmented1 = {quality: Augmented, degree: 1, semitones: 1};
let augmented2 = {quality: Augmented, degree: 2, semitones: 3};
let augmented3 = {quality: Augmented, degree: 3, semitones: 5};
let augmented4 = {quality: Augmented, degree: 4, semitones: 6};
let augmented5 = {quality: Augmented, degree: 5, semitones: 8};
let augmented6 = {quality: Augmented, degree: 6, semitones: 10};
let augmented7 = {quality: Augmented, degree: 7, semitones: 12};
let augmented8 = {quality: Augmented, degree: 8, semitones: 13};
let augmented9 = {quality: Augmented, degree: 9, semitones: 15};
let augmented10 = {quality: Augmented, degree: 10, semitones: 17};
let augmented11 = {quality: Augmented, degree: 11, semitones: 18};
let augmented12 = {quality: Augmented, degree: 12, semitones: 20};
let augmented13 = {quality: Augmented, degree: 13, semitones: 22};
let augmented14 = {quality: Augmented, degree: 14, semitones: 24};
let augmented15 = {quality: Augmented, degree: 15, semitones: 25};

let all = [
  perfect1,
  perfect4,
  perfect5,
  perfect8,
  perfect11,
  perfect12,
  perfect15,
  minor2,
  minor3,
  minor6,
  minor7,
  minor9,
  minor10,
  minor13,
  minor14,
  major2,
  major3,
  major6,
  major7,
  major9,
  major10,
  major13,
  major14,
  diminished1,
  diminished2,
  diminished3,
  diminished4,
  diminished5,
  diminished6,
  diminished7,
  diminished8,
  diminished9,
  diminished10,
  diminished11,
  diminished12,
  diminished13,
  diminished14,
  diminished15,
  augmented1,
  augmented2,
  augmented3,
  augmented4,
  augmented5,
  augmented6,
  augmented7,
  augmented8,
  augmented9,
  augmented10,
  augmented11,
  augmented12,
  augmented13,
  augmented14,
  augmented15,
];
