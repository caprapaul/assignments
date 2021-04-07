const draggableElements = document.querySelectorAll(".draggable");

draggableElements.forEach(function (draggableElement) {
    dragElement(draggableElement);
});

function dragElement(element) {
    var current = { x: 0, y: 0 };
    var initial = { x: 0, y: 0 };

    var headerElement = element.querySelector("#header");

    headerElement.onmousedown = dragStart;

    function setTranslate(el, pos) {
        el.style.transform = `translate(${pos.x}px, ${pos.y}px)`;
    }

    function dragStart(e) {
        initial.x = e.clientX - current.x;
        initial.y = e.clientY - current.y;

        document.onmousemove = drag;
        document.onmouseup = dragEnd;
    }

    function dragEnd(e) {
        initial.x = current.x;
        initial.y = current.y;

        document.onmousemove = null;
        document.onmouseup = null;
    }

    function drag(e) {
        e.preventDefault();

        current.x = e.clientX - initial.x;
        current.y = e.clientY - initial.y;

        setTranslate(element, current);
    }
}

