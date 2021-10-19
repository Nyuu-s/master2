



const direction = {
  UP:       0,
  DOWN:     1,
  RIGHT:    2,
  LEFT:     3
}

//variables

let grid = [];
let col;
let row;
let res = 40;
let a1;

function keyPressed(){
  if(keyCode == UP_ARROW){
    a1.move(direction.UP, 1);
  }
  else if(keyCode == DOWN_ARROW){

    a1.move(direction.DOWN, 1);
  }
  else if(keyCode == RIGHT_ARROW){

    a1.move(direction.RIGHT, 1);
  }
  else if(keyCode == LEFT_ARROW){

    a1.move(direction.LEFT , 1);
  }
}



//setup and draw

function setup(){
  createCanvas(800, 800);
  col = floor(height/res);
  row = floor(width/res);
  a1 = new Agent(new Cell(5,5),1);
  for (let j = 0; j < row; j++) {
    for (let i = 0; i < col; i++) {
      
      var cell;
        if(i==0){
          if(j  % 2 == 0 ){
            cell =  new Cell(i, j, 2); 
          }
          else
          {
            cell =  new Cell(i, j, 1); 
          }
        }
        else
        {
          cell =  new Cell(i, j, 0); 
        }
          

        grid.push(cell);
    }  
  }

}

function draw(){

  for (let i = 0; i < grid.length; i++) {
    grid[i].drawCell();
  }
  frameRate(10);
  
  a1.show();
  
    
  
}















   
