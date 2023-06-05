open Virtual_dom.Vdom;

let line = ((x1, y1), (x2, y2)) =>
  Node.create_svg(
    "line",
    ~attr=
      Attr.many(
        Attr.[
          create("x1", string_of_int(x1)),
          create("y1", string_of_int(y1)),
          create("x2", string_of_int(x2)),
          create("y2", string_of_int(y2)),
        ],
      ),
    [],
  );

let (a, b) = (1, 59);
let view =
  Node.div(
    ~attr=Attr.classes(["grid-lines"]),
    [
      Node.create_svg(
        "svg",
        ~attr=attr("viewBox", "0 0 60 60"),
        [
          line((20, a), (20, b)),
          line((40, a), (40, b)),
          line((a, 20), (b, 20)),
          line((a, 40), (b, 40)),
        ],
      ),
    ],
  );
