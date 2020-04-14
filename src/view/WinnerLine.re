module Vdom = Virtual_dom.Vdom;

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
        let x = (2 * min_c + 1) * 10;
        (x, x);
      }
      : (4, 56);
  let (y1, y2) =
    min_r == max_r
      ? {
        let y = (2 * min_r + 1) * 10;
        (y, y);
      }
      : (4, 56);
  svg(
    "svg",
    [Vdom.Attr.id("winner-line"), attr("viewBox", "0 0 60 60")],
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
