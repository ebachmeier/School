<?php require('includes/config.php'); 



$stmt = $db->prepare('SELECT postID, postTitle, postCont, postDate FROM blog_posts WHERE postSlug = :postSlug');
$stmt->execute(array(':postSlug' => $_GET['id']));
$row = $stmt->fetch();

//if post does not exists redirect user.
if($row['postID'] == ''){
	header('Location: ./');
	exit;
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Blog - <?php echo $row['postTitle'];?></title>
    <link rel="stylesheet" href="style/normalize.css">
    <link rel="stylesheet" href="style/main.css">
</head>
<body>

	<div id="wrapper">

		<h1>Blog</h1>
        <ul id='adminmenu'><li><a href='./'>Blog Index</a></li></ul>
        <div class='clear'></div>
        <hr />
		
        <div id='main'>
            
            <?php	
			echo '<div>';
				echo '<h1>'.$row['postTitle'].'</h1>';
				echo '<p>Posted on '.date('F jS, Y', strtotime($row['postDate']))
                    .' at '.date('g:ia', strtotime($row['postDate']))
                    .' in ';

					$stmt2 = $db->prepare('SELECT catTitle, catSlug	FROM blog_cats, blog_post_cats WHERE blog_cats.catID = blog_post_cats.catID AND blog_post_cats.postID = :postID');
					$stmt2->execute(array(':postID' => $row['postID']));

					$catRow = $stmt2->fetchAll(PDO::FETCH_ASSOC);

					$links = array();
					foreach ($catRow as $cat)
					{
					    $links[] = "<a href='c-".$cat['catSlug']."'>".$cat['catTitle']."</a>";
					}
					echo implode(", ", $links);

				echo '</p>';
				echo '<p>'.$row['postCont'].'</p>';				
			echo '</div>';
		?>

        </div>

        <div id='sidebar'>
            <?php require('includes/sidebar.php'); ?>
        </div>
	</div>
</body>
</html>