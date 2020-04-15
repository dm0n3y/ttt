module Vdom = Virtual_dom.Vdom;

let svg = Vdom.Node.create_svg;
let attr = Vdom.Attr.create;

let line = ((x1, y1), (x2, y2)) =>
  svg(
    "line",
    [
      attr("x1", string_of_int(x1)),
      attr("y1", string_of_int(y1)),
      attr("x2", string_of_int(x2)),
      attr("y2", string_of_int(y2)),
    ],
    [],
  );

let (a, b) = (1, 59);
let view =
  Vdom.Node.div(
    [Vdom.Attr.classes(["grid-lines"])],
    [
      svg(
        "svg",
        [attr("viewBox", "0 0 60 60")],
        [
          line((20, a), (20, b)),
          line((40, a), (40, b)),
          line((a, 20), (b, 20)),
          line((a, 40), (b, 40)),
        ],
      ),
    ],
  );
