



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






//setup and draw

function setup(){
  createCanvas(800, 800);
  col = floor(height/res);
  row = floor(width/res);
    
  for (let j = 0; j < row; j++) {
    for (let i = 0; i < col; i++) {
      console.log(i);
      var cell;
        if(i==0){
          if(j  % 2 == 0){
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
    
    

  
    
  
}















   
