module Vdom = Virtual_dom.Vdom;

let svg = Vdom.Node.create_svg;
let attr = Vdom.Attr.create;

let view = (((r0, c0), _, (r2, c2))) => {
  let a = 4;
  let b = 56;
  let ((x1, y1), (x2, y2)) =
    if (c0 == c2) {
      let x = (2 * c0 + 1) * 10;
      ((x, a), (x, b));
    } else if (r0 == r2) {
      let y = (2 * r0 + 1) * 10;
      ((a, y), (b, y));
    } else if (Int.compare(r0, r2) == Int.compare(c0, c2)) {
      ((a, a), (b, b));
    } else {
      ((a, b), (b, a));
    };
  svg(
    "svg",
    [Vdom.Attr.classes(["winner-line"]), attr("viewBox", "0 0 60 60")],
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
