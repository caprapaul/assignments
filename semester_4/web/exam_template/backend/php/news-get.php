<?php
    require 'connection.php';

    $start = $_GET["start"];
    $end = $_GET["end"];
    $category = $_GET["category"];

    $sql = "SELECT id, text, title, producer, date, category FROM news WHERE ((date BETWEEN ? AND ?) AND category=?)";

    if ($category == "All")
    {
        $sql = "SELECT id, text, title, producer, date, category FROM news WHERE date BETWEEN ? AND ?";
    }

    $stmt = $connection->prepare($sql);

    if ($category == "All")
    {
        $stmt->bind_param("ss", $start, $end);
    }
    else
    {
        $stmt->bind_param("sss", $start, $end, $category);
    }
    
    $stmt->execute();
    $stmt->bind_result($id, $text, $title, $producer, $date, $category);

    $news_list = array();

	while($stmt->fetch()) {
	    $news = new StdClass();
	    $news->id = $id;
	    $news->text = $text;
        $news->title = $title;
	    $news->producer = $producer;
	    $news->date = $date;
        $news->category = $category;

	    array_push($news_list, $news);
	}

    echo json_encode($news_list);

    $stmt->close();
?>

