module Vdom = Virtual_dom.Vdom;
//here is an example of building a Vdom.Node.t with attributes and children
//
// Vdom.Node.div(
//   [Vdom.Attr.id("board")],// a list of attributes, like id, class, style, etc
//   [
//     Vdom.Node.div([Vdom.Attr.classes(["row"])], []),// a list of children
//   ],
// );

// the code above would generate html like this
// <div id="board">
//   <div class="row"></div>
// </div>

// build a Vdom.Node.t for each square
// The click handler will call the inject function, which will send an action to the update function
// You can define the type of index with any other format, but remember to synchronize the type with the update.re(i)
let view_of_square =
    (
      ~inject: Update.Action.t => Vdom.Event.t,
      ~index: int,
      square: Model.square,
    )
    : Vdom.Node.t =>
  switch (square.marked) {
  | None =>
    let click_handlers = [
      Vdom.Attr.on_click(_ => inject(Update.Action.Mark(index))),
    ];
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"]), ...click_handlers],//only empty square can be clicked
      [PlayerMark.view(square)],
    );
  | Some(_) =>
    Vdom.Node.div(
      [Vdom.Attr.classes(["square"])],
      [PlayerMark.view(square)],
    )
  };

// function squares and player_turn in Model.re might be helpful to gather information from Model.t
// use view_of_square to build a list of Vdom.Node.t
// use PlayerMark.grid_view to transfer the list of Vdom.Node.t to a Vdom.Node.t with proper layout
let view = (~inject, model: Model.t) => {
  //TODO
  Vdom.Node.div(
    [Vdom.Attr.id("board")],
    [],
  );
};
