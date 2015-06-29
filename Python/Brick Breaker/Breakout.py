# Eric Bachmeier
# This program is a pygame version of Breakout, the 1976 arcade game.
# June 19, 2013

# Import math and pygame libraries
import math,pygame

# Initialize PyGame
pygame.init()

# Create 800 x 600 screen
screen = pygame.display.set_mode([800, 600])

# Set window title
pygame.display.set_caption('Breakout Game - By: Eric Bachmeier')

# Define font size
font = pygame.font.Font(None, 40)

# Create background to draw on
background = pygame.Surface(screen.get_size())

# Limit speed
clock = pygame.time.Clock()

# Define colours
black = (0,0,0)
white = (255,255,255)
red = (255,0,0)

# Set size of blocks
block_width = 30
block_height = 30

# Number of blocks in each row
blockcount = 25

# This 'Sprite' class represents each block that can be collided with
class Block(pygame.sprite.Sprite):
    # Pass colour and posiitonof blocks
    def __init__(self,colour,x,y): 
        pygame.sprite.Sprite.__init__(self)
        self.image = pygame.Surface([block_width, block_height])
        self.image.fill(colour)
        self.rect = self.image.get_rect()
        # Set block start coordinates
        self.rect.x = x
        self.rect.y = y

# This 'Sprite' class represents the ball      
class Ball(pygame.sprite.Sprite):
    # Set speed and dimensions variables of the ball
    speed = 13
    width = 12
    height = 12
    # Set starting coordinates of ball
    x = 295
    y = 230
    direction = 130 # Degrees

    def __init__(self):
        # Call the 'Sprite' class
        pygame.sprite.Sprite.__init__(self)
        # Create and colour ball
        self.image = pygame.Surface([self.width, self.height])
        self.image.fill(white)
        # Get border of ball for collisions
        self.rect = self.image.get_rect()
        # Screen dimensions get information
        self.screenheight = pygame.display.get_surface().get_height()
        self.screenwidth = pygame.display.get_surface().get_width()
    
    # Function to bounce ball of horizontal surface
    def bounce(self,diff):
        self.direction = (180-self.direction)%360
        self.direction -= diff
    
    # Update ball position
    def update(self):
        # Print and update score in bottom corner
        text=font.render("SCORE: "+str(score), True, white)
        textpos = text.get_rect(centerx=background.get_width()/10)
        textpos.top = 550
        screen.blit(text, textpos)
        # Convert degrees for sin and cos
        direction_radians = math.radians(self.direction)
        # Change x and y according to position
        self.x += self.speed * math.sin(direction_radians)
        self.y -= self.speed * math.cos(direction_radians)
        # Update/move image of ball
        self.rect.x = self.x
        self.rect.y = self.y
        # Bounce for top of screen, if avoids blocks
        if self.y <= 0:
            self.bounce(0)
            self.y=1
        # Bounce for left of screen, if avoids blocks
        if self.x <= 0:
            self.direction = (360-self.direction)%360
            self.x=1
        # Bounce for right of screen, if avoids blocks
        if self.x > self.screenwidth-self.width:
            self.direction = (360-self.direction)%360
            self.x=self.screenwidth-self.width-1
        # Bounce for bottom of screen, if avoids paddle
        if self.y > 600:
            # Game over check
            return True
        else:
            return False
  
# This 'Sprite' class represents the paddle
class Player(pygame.sprite.Sprite):
    # Pass size and colour to paddle
    def __init__(self):
        # Call the 'Sprite' class
        pygame.sprite.Sprite.__init__(self)
        self.width=75
        self.height=15
        # Create and give colour to paddle
        self.image = pygame.Surface([self.width, self.height])
        self.image.fill((white))
        # Get top left corner of paddle to be passed
        self.rect = self.image.get_rect()
        self.screenheight = pygame.display.get_surface().get_height()
        self.screenwidth = pygame.display.get_surface().get_width()
        self.rect.x = 0
        self.rect.y = self.screenheight-self.height
    
    # Update the paddle
    def update(self):
        # Get mouse position
        pos = pygame.mouse.get_pos()
        # Set upper left x position of paddle to mouse position
        self.rect.x = pos[0]
        # Keep paddle on the screen
        if self.rect.x > self.screenwidth - self.width:
            self.rect.x = self.screenwidth - self.width

# Create the 'Sprite' lists used for updating
blocks = pygame.sprite.Group()
balls = pygame.sprite.Group()
allsprites = pygame.sprite.Group()

# Create the paddle object 
player = Player()
allsprites.add(player)
score = 0
# Create the ball object 
ball = Ball()
allsprites.add(ball)
balls.add(ball)
top = 0


# Five rows of blocks to create
for row in range(5): 
    # 25 columns of blocks
    for column in range(0,blockcount):
        # Create a block with attributes colour, and coordinate
        block = Block(red,column*(block_width+2)+1,top)
        blocks.add(block)
        allsprites.add(block)
    # To get to top of next row
    top += block_height+2
        
# Set both game over and exit to False
game_over = False
exit_program = False

# Main game loop
write = True
while exit_program != True:
    # 30 fps and colour screen
    clock.tick(30)
    screen.fill(black)
    # Game events
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            exit_program = True
    # Update paddle and ball if game isn't over
    if not game_over:
        player.update()
        game_over = ball.update()
    # Print game over and score notification if game over
    if game_over:
        if write == True:
            hs = []
            inFile = open('Highscores.txt','r')
            s = inFile.readline().rstrip('\n')
            # Append highscores to 'hs' list
            while s != "": 
                hs.append(int(s))
                s = inFile.readline().rstrip('\n')
            for x in range(0,len(hs)):
                if score > hs[x]:
                    # Replace proper score if higher than one in 'hs' list
                    hs.append(score)
                    hs = sorted(hs)[::-1]
                    # Delete lowest score remaining is 'hs' list
                    hs.pop()
                    break
            inFile.close()
            inFile = open('Highscores.txt','w')
            for x in range(0,len(hs)):
                # Write highscores back to 'Highscores.txt'
                inFile.write(str(hs[x])+'\n')
            inFile.close()
            write = False
        # Print game over and blit to screen
        text=font.render("GAME OVER", True, white)
        textpos = text.get_rect(centerx=background.get_width()/2)
        textpos.top = 300
        screen.blit(text, textpos)
        # Print user score and blit to screen
        text=font.render("SCORE: "+str(score), True, white)
        textpos = text.get_rect(centerx=background.get_width()/2)
        textpos.top = 340
        screen.blit(text, textpos)
        if score == hs[4] or score > hs[4]:
            # Notify if score was top 5 and blit to screen
            text=font.render("Your score was added to the top 5 file!", True, white)
            textpos = text.get_rect(centerx=background.get_width()/2)
            textpos.top = 380
            screen.blit(text, textpos)
        
    # Check ball collision with paddle
    if pygame.sprite.spritecollide(player, balls, False):
        # Diff allows user to bounce ball left or right
        diff = (player.rect.x + player.width/2) - (ball.rect.x+ball.width/2)
        ball.rect.y = screen.get_height() - player.rect.height - ball.rect.height -1
        ball.bounce(diff)
    
    # Check ball collision with blocks
    deadblocks = pygame.sprite.spritecollide(ball, blocks, True)
    if len(deadblocks) != 0:
        # Update score variable
        score += len(deadblocks)
        # Bounce the ball if block and ball collision is True
        ball.bounce(0)
                
        # End game if all blocks are gone
        if len(blocks) == 0:
            game_over = True
    
    # Draw to screen
    allsprites.draw(screen)
    pygame.display.flip()

# Quit pygame
pygame.quit()
