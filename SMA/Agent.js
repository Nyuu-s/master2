


class Agent{
    constructor(cell, id){
      this.id = id;
      this.cell = cell;
      
    }
  
  
  
    move(direction, step) {
      console.log((this.cell.j-step) * row + this.cell.i)
      let u =  grid[constrain((this.cell.j-step), 0, col) * row + this.cell.i];
      let d =  grid[constrain((this.cell.j+step), 0 , col-1 ) * row + this.cell.i ];
      let r =  grid[this.cell.j * row + constrain(this.cell.i + step, 0, row-1) ];
      let l =  grid[this.cell.j * row + constrain(this.cell.i - step, 0, row-1) ];
      
      switch(direction){
        case 0:  
                if(!(u.type == 1) ){
                  this.cell =  u;
                }

                break;
        case 1:   
                if(!(d.type == 1)){
                  this.cell=  d ;
                }
                break;
        case 2:   

                if(!(r.type == 1) ){
                  this.cell =   r ;
                }
                break;
        case 3:   
                if(!(l.type == 1)){

                  this.cell =  l ;
                }
                break;
  
        
      }
    }
  
      show(){
        //todo find center coord of this.cell and draw ellipse
        stroke(255);
        noFill();
        // ellipse(this.cell.i * res, this.cell.j*res, res);
        rect(this.cell.i * res, this.cell.j *res, res, res);
  
      }
    
  }
  