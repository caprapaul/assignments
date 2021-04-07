$(() => {
    var values = [];
    var size = { x: 4, y: 4 };
    var empty = { id: 0, i: 0 };

    init(values, size, empty);
});


function posToId(x, y, size) {
    return x + size.x * y;
}

function init(values, size, empty) {
    $("#game").width(110 * size.x)
        .height(110 * size.y);

    for (j = 0; j < size.y; j++) {
        for (i = 0; i < size.x; i++) {
            const id = posToId(i, j, size);

            var cell = $("<div></div>")
                .attr({
                    id: id,
                    class: "cell"
                })
                .text(id);

            cell.on("click", function () {
                cellClick(cell, values, empty);
            });

            values.push(cell);
        }
    }

    values[0].text(" ");

    randomize(values, empty);
    //console.log(empty);
    showGame(values, empty);
}

function randomize(values, empty) {
    for (i = 0; i < values.length; i++) {
        j = Math.floor(Math.random() * 15);

        aux = values[i];
        values[i] = values[j];
        values[j] = aux;
    }

    findEmptyIndex(values, empty);
}

function findEmptyIndex(values, empty) {
    for (i = 0; i < values.length; i++) {
        const id = values[i].attr("id");
        if (id == empty.id) {
            empty.i = i;
            return;
        }
    }
}

function showGame(values, empty) {
    var isFinished = true;
    $("#game").html("");

    for (let i = 0; i < values.length; i++) {
        if (values[i].attr("id") != i) {
            isFinished = false;
        }

        values[i].on("click", function () {
            cellClick(values[i], values, empty);
        });

        $("#game").append(values[i]);
    }

    if (isFinished) {
        $("#status").text("Finished!");
    }
}

function cellClick(cell, values, empty) {
    cellIndex = values.indexOf(cell);
    aux = values[cellIndex];
    values[cellIndex] = values[empty.i];
    values[empty.i] = aux;
    empty.i = cellIndex;

    showGame(values, empty);
}