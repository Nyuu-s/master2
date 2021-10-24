



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
let v1;

function keyPressed(){
  a1.toDraw = [];

  if(keyCode == UP_ARROW){
    a1.move(direction.UP, 1);
  }
  else if(keyCode == DOWN_ARROW){

    a1.move(direction.DOWN, 1);
    return;
  }
  else if(keyCode == RIGHT_ARROW){

    a1.move(direction.RIGHT, 1);
  }
  else if(keyCode == LEFT_ARROW){

    a1.move(direction.LEFT , 1);
  }
  else if(keyCode == CONTROL){

    a1.findPath(a1.cell, v1.cell);
  }
  else if(keyCode == SHIFT ){
    let c = getCell(floor(mouseX/res), floor(mouseY/res));
  
    c.type = 1;
  }
}


function getCell(i,j){
  return grid[j * row + i];
}

//setup and draw

function setup(){
  createCanvas(800, 800);
  col = floor(height/res);
  row = floor(width/res);
 
  
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

  for (let j = 0; j < row; j++) {
    for (let i = 0; i < col; i++) {
      getCell(i,j).addNeighbors();
    }  
  }
  a1 = new Agent(grid[26],1);
  v1 = new Voiture(grid[0]);

  a1.move(direction.DOWN, 2);
  console.log(a1.cell, v1.cell);
  a1.findPath(a1.cell, v1.cell);

}

function draw(){

  for (let i = 0; i < grid.length; i++) {
    grid[i].drawCell();
  }
  frameRate(10);
  for(let i =0; i<a1.toDraw.length;i++){
    let b = a1.toDraw[i]
    fill(255,0,255);
    rect(b.i*res, b.j*res, res, res);
  }
  

  a1.show();
  v1.show();


  
    
  
}















   
