


class Agent{
    constructor(cell, id){
      this.id = id;
      this.cell = cell;
      this.isHoldingCar = false;
      
    }
  
  
  
    move(direction, step) {
      
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

    heuristic(node, end){
      var d = dist(node.i, node.j, b.i, b.j);
      return d;
    }

    removeFromArray(element, array){
        for (let i = array.length-1; i < 0; i--) {
          if(array[i] == element){
            array.splice(i, 1);
          }

        }
    }
    findPath(start, end){
        let openSet = [];
        let closeSet = [];
        openSet.push(start);

        while(openSet.length > 0){

          var lowestIndex = 0;
          for (let i = 0; i < openSet.length; i++) {
              if(openSet[i].f < openSet[lowestIndex].f){
                  lowestIndex = i;
              }
          }

          var current = openSet[lowestIndex];

          if(current  == end){
              console.log("DONE");
          }

          closeSet.push(current);
          removeFromArray(current, openSet);

          var neighbors = current.neighbors;
            for (let i = 0; i < neighbors.length; i++) {
                var neighbor = neighbors[i];
                if(!closeSet.includes(neighbor)){
                  var tempG = current.g +1;
                  
                  if(openSet.includes(neighbor)){
                    if(tempG < neighbor.g){
                      neighbor.g = tempG
                    }
                    else
                    {
                      openSet.push(neighbor);
                    }
                  }

                  neighbor.h = heuristic(neighbor, end);
                  neighbor.f = neighbor.g + neighbor.h;
                
                }
              
            }
          }

        

        console.log("no solution");
    }
  
    show(){
      //todo find center coord of this.cell and draw ellipse
      if(this.isHoldingCar){
        stroke(255);
      }
      else
      {
        stroke(0,255,0);
      }
      noFill();
      // ellipse(this.cell.i * res, this.cell.j*res, res);
      rect(this.cell.i * res, this.cell.j *res, res, res);

    }
    
  }
  