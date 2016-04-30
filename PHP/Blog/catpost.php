<?php require('includes/config.php'); 


$stmt = $db->prepare('SELECT catID,catTitle FROM blog_cats WHERE catSlug = :catSlug');
$stmt->execute(array(':catSlug' => $_GET['id']));
$row = $stmt->fetch();

//if post does not exists redirect user.
if($row['catID'] == ''){
	header('Location: ./');
	exit;
}

?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title>Blog - <?php echo $row['catTitle'];?></title>
    <link rel="stylesheet" href="style/normalize.css">
    <link rel="stylesheet" href="style/main.css">
</head>
<body>

	<div id="wrapper">
        
        <h1>Blog</h1>
        <ul id='adminmenu'>
            <li><a href="./">Blog Index</a></li>
        </ul>
        <div class='clear'></div>
        <hr />

        <div id='main'>
            
            <?php	
		try {
            
            $pages = new Paginator('4','p');

            $stmt = $db->prepare('SELECT blog_posts.postID FROM blog_posts, blog_post_cats WHERE blog_posts.postID = blog_post_cats.postID AND blog_post_cats.catID = :catID');
            $stmt->execute(array(':catID' => $row['catID']));

            //pass number of records to
            $pages->set_total($stmt->rowCount());
            
            $total = $stmt->rowCount();
            
            if($total < 1) {
                echo "<p>There are no posts in " . $row['catTitle'] . "</p>";
            }
            else {
                echo "<p>Posts in " . $row['catTitle'] . "</p>";  
            }
            
			$stmt = $db->prepare('
            SELECT 
                blog_posts.postID, blog_posts.postTitle, blog_posts.postSlug, blog_posts.postDesc, blog_posts.postDate 
            FROM 
                blog_posts,
                blog_post_cats
            WHERE
                 blog_posts.postID = blog_post_cats.postID
                 AND blog_post_cats.catID = :catID
            ORDER BY 
                postID DESC
            '.$pages->get_limit());
			$stmt->execute(array(':catID' => $row['catID']));
			while($row = $stmt->fetch()){
                
				echo '<div>';
                
                    echo '<h1><a href="'.$row['postSlug'].'">'.$row['postTitle'].'</a></h1>';
				    echo '<p>Posted on '.date('F jS, Y', strtotime($row['postDate'])).' at '.date('g:ia', strtotime($row['postDate'])).' in ';

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
					echo '<p>'.$row['postDesc'].'</p>';				
					echo '<p><a href="'.$row['postSlug'].'">Read More</a></p>';				
				echo '</div>';

			}
            
            echo $pages->page_links('c-'.$_GET['id'].'&');

		} catch(PDOException $e) {
		    echo $e->getMessage();
		}

		?>

        </div>

        <div id='sidebar'>
            <?php require('includes/sidebar.php'); ?>
        </div>
	</div>
</body>
</html>