using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics;  // Allow Debug.Assert

namespace PigWorldNamespace {

    /// <summary>
    /// Trees have simple behaviour, much simpler than Pigs.  Trees don't move, for example.
    /// 
    /// Trees simply grow pig food. Every 10th time the Tree's DoSomething method is invoked, 
    /// the Tree will attempt to deposit an item of PigFood on to an adjacent cell, provided:
    /// 1.	There are no pigs on any cell adjacent to the tree.
    /// 2.	Trees do not grow over walls, so an item of pig food is not deposited 
    ///     in an adjacent cell separated from the tree by a wall.
    /// 3.	Pig food is not deposited on to an adjacent cell already containing pig food.
    /// 
    /// Actually, conditions (2) and (3) are already guaranteed by the constructor for PigFood.  
    /// So nothing needs to be done in this class to ensure conditions (2) and (3).  
    /// 
    /// Original author: Lizveth Robles 
    /// Converted & modified by: Jim Reye
    /// </summary>
    public class Tree : Plant {
        //Define a class variable to help the DoSomething
        //Method know if it's the 10th time it has been
        //successfully exectued
        public int doSomethingCount = 0;

        /// <summary>
        /// Constructs a new Tree.
        /// </summary>
        /// <param name="pigWorld"> the PigWorld in which to create the Tree. </param>
        public Tree(PigWorld pigWorld)
            : this(pigWorld, Position.any) {  // In this context, "this" is a call to the constructor below.
        }

        /// <summary>
        /// Constructs a new Tree at the specified position. If the desired position is
        /// already occupied by another Thing, then the Tree will be placed in a
        /// nearby Cell. If there are no nearby Cells that are free, then the Tree
        /// will not be added to the pigWorld.
        /// </summary>
        /// <param name="pigWorld"></param>
        /// <param name="position"></param>
        public Tree(PigWorld pigWorld, Position position) {
            AddToWorld(pigWorld, position);
        }


        //<summary>
        //This method is used to save space in the below method
        //if it is the 10th time the step button has been clicked
        //The tree will drop food
        //Pre: doSomethingCount will be checked to see if it equals 10
        //Post: if it does, food will be dropped
        //</summary>
        public void DropTheFood() {
            if (doSomethingCount == 10) {
                DropFood();
            }
        }

        /// <summary>
        /// This method is called every unit of time by the PigWorld to give the Tree a
        /// chance to do something.
        /// 
        /// Every 10th time this method is invoked, the Tree will attempt to deposit 
        /// an item of PigFood on to an adjacent cell, as long as
        /// there are no pigs on any cell adjacent to the tree.
        /// If there are any pigs next to the tree, then it just keeps waiting for another 10 times.
        /// </summary>
        protected override void DoSomething() {
            //Add 1 to the doSomethingCount to keep track of how much times this
            //method has been executed
            doSomethingCount += 1;
            // This will detect any type of pig (both BoyPigs and GirlPigs).

            Echo echo = FindNearest(typeof(Pig));
            //if no pigs are near, drop food
            if (echo == null) {
                DropTheFood();
            } else if (echo != null) {
                double distance = echo.distance;
                //if there are pigs, and they're not in
                //adjacent cells to the tree, drop food every 10
                //If they are in the adjacent cell, reset doSomethingCount to 0
                if (distance > 1.0) {
                    DropTheFood();
                } else {
                    doSomethingCount = 0;
                }
            }
            if (doSomethingCount >= 10) {
                doSomethingCount = 0;
            }
            // Write your code here.
        }

        /// <summary>
        /// Constructs a new piece of PigFood. 
        /// The PigFood will be placed near to the Tree's position.
        /// </summary>
        public void DropFood() {
            new PigFood(this.PigWorld, Cell.Position);
        }
    }
}
