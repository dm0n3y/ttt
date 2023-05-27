module Vdom = Virtual_dom.Vdom;
//import css file

let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~index: (int, int),
      ~active: bool,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers =
      active
        ? [Vdom.Attr.on_click(_ => inject(Update.Action.Mark(index)))] : [];
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"]), ...click_handlers],
      [PlayerMark.view(square)],
    );
  | Some(_) =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"])],
      [PlayerMark.view(square)],
    )
  };

let view = (~inject, model: Model.t) => {
  let rec mksquare =
          (sqlst: list(Model.square), index: (int, int), active: bool) => {
    switch (sqlst) {
    | [] => []
    | [sq, ...rest] =>
      let sqview = view_of_square(~inject, ~index, ~active, sq);
      let (x, y) = index;
      [sqview, ...mksquare(rest, (x, y + 1), active)];
    };
  };
  let active_sub = Model.active_subboard(model);
  let is_active = (n: int): bool => {
    switch (active_sub) {
    | None => true
    | Some(sub) => sub == n
    };
  };
  let rec mklist = (lst: list(list(Model.square)), index: int) => {
    switch (lst) {
    | [] => []
    | [sq, ...rest] =>
      let sqview = mksquare(sq, (index, 0), is_active(index));
      is_active(index)
        ? [PlayerMark.grid_view(sqview), ...mklist(rest, index + 1)]
        : [
          PlayerMark.in_active_view([PlayerMark.grid_view(sqview)]),
          ...mklist(rest, index + 1),
        ];
    };
  };
  let sqview = mklist(Model.squares(model), 0);

  Vdom.Node.div(
    [Vdom.Attr.id("board")],
    //[Vdom.Node.div([Vdom.Attr.classes(["grid"])], sqview)],
    [PlayerMark.grid_view(sqview)],
  );
};
