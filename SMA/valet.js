



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
let x;

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
    x = a1.toDraw.length-1;
  }
  else if(keyCode == SHIFT ){
    let c = getCell(floor(mouseX/res), floor(mouseY/res));
    
    if(c.type == 1){
      c.type = 0;
    }
    else{
      c.type = 1;
    }
  }
  else if(keyCode == 32){
    if(a1.cell.type ){
      a1.pickAndDropCar();
    }
    
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
  v1 = new Voiture(grid[col * 2]);

  
  

  

}

function draw(){

  for (let i = 0; i < grid.length; i++) {
    grid[i].drawCell();
  }
  frameRate(10);

  //render path find

  // for(let i =0; i<a1.toDraw.length;i++){
  //   let b = a1.toDraw[i]
  //   fill( 255 / i,0,255/i);
  //   rect(b.i*res, b.j*res, res, res);
  // }
  
  if(x >= 0){
    a1.cell = a1.toDraw[x];
    if(x == 0 ){
      a1.pickAndDropCar(v1);
      
    }
    x--;
    
  }
    
    
  
  

  a1.show();
  if(a1.isHoldingCar){
    v1.cell = a1.cell;
  }
  v1.show();

  
    
  
}















   
