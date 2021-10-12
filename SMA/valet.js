



const direction = {
  UP:     0,
  DOWN:   1,
  LEFT:   2,
  RIGHT:  3
}

//variables

let grid = [];
let col;
let row;
let res = 40;
let a1;

//classes

class Cell{
    constructor(i, j,h ,type){
      this.i = i;
      this.j = j;
      this.h = h;
      this.type = type;
    }

    setType(type)
    {
      this.type = type;
    }
    drawCell(){
      if(this.type == 0){ //obstacle
          noFill()
          stroke(5);
      }
      if(this.type == 1){//point dedepart
        fill(0,255,0);

      }
      if(this.type == 2){ // voiture
        fill(0);
      }
      if(this.type == 3){//agent
        fill(128,0,128);
      }
      rect(this.i, this.j, this.h, this.h);
    }
}

class Agent{
  constructor(x, y, id, color){
    this.id = id;
    this.x = x;
    this.y = y;
    this.color = color;
  }



  move(direction, step) {
    switch(direction, step){
      case 0:   this.y -= step;  break;
      case 2:   this.y += step;  break;
      case 3:   this.x -= step;  break;
      case 4:   this.x += step;  break;

      
    }
  }

    show(){
      grid[this.y + row * this.x].setType(1);
      
      grid[this.y + row * this.x].drawCell();

    }
  
}

//setup and draw

function setup(){
  createCanvas(800, 800);
  col = height/res;
  row = width/res;
  a1 = new Agent(2*res, 2*res, 1, 128)
  
  for (let i = 0; i < col; i++) {
    for (let j = 0; j < row; j++) {
      if(i == 0){
        
        if(j % 2){
          grid.push(new Cell(i*res, j*res, res, 1));
        }else{
          grid.push(new Cell(i*res, j*res, res, 2))
        }
          
        
      }else{

        grid.push(new Cell(i*res,j*res,res, 0));
      }
    }


  
    
  }

}

function draw(){

  for (let i = 0; i < col*row; i++) {
    grid[i].drawCell();
  }
    a1.show();
    

  
    
  
}















   
