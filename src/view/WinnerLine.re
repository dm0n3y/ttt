module Vdom = Virtual_dom.Vdom;

let int_of = (i: Triple.index) =>
  switch (i) {
  | Zero => 0
  | One => 1
  | Two => 2
  };
let min = (i: Triple.index, j: Triple.index) =>
  switch (i, j) {
  | (Zero, _) => i
  | (_, Zero) => j
  | (One, _) => i
  | (_, One) => j
  | (Two, Two) => i
  };
let max = (i: Triple.index, j: Triple.index) =>
  switch (i, j) {
  | (Two, _) => i
  | (_, Two) => j
  | (One, _) => i
  | (_, One) => j
  | (Zero, Zero) => i
  };

let svg = Vdom.Node.create_svg;
let attr = Vdom.Attr.create;

let view = (((r0, c0), (r1, c1), (r2, c2))) => {
  let min_r = min(min(r0, r1), r2);
  let max_r = max(max(r0, r1), r2);
  let min_c = min(min(c0, c1), c2);
  let max_c = max(max(c0, c1), c2);
  let (x1, x2) =
    min_c == max_c
      ? {
        let x = (2 * int_of(min_c) + 1) * 10;
        (x, x);
      }
      : (5, 55);
  let (y1, y2) =
    min_r == max_r
      ? {
        let y = (2 * int_of(min_r) + 1) * 10;
        (y, y);
      }
      : (5, 55);
  svg(
    "svg",
    [
      Vdom.Attr.id("winner-line"),
      attr("viewBox", "0 0 60 60"),
      attr("fill", "none"),
      attr("stroke", "black"),
      attr("stroke-width", "2"),
      attr("stroke-linecap", "round"),
    ],
    [
      svg(
        "line",
        [
          attr("x1", string_of_int(x1)),
          attr("y1", string_of_int(y1)),
          attr("x2", string_of_int(x2)),
          attr("y2", string_of_int(y2)),
        ],
        [],
      ),
    ],
  );
};
