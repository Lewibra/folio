using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Diagnostics;  // Allow Debug.Assert

namespace PigWorldNamespace {

    /// <summary> 
    /// A Wolf is a type of Animal that eats Pigs, and does little else. 
    /// 
    /// Wolves simply move toward the nearest pig, and eat that pig if they catch it. 
    /// Wolves don’t sleep.  Wolves are never in the mood for love. They just keep coming after pigs. 
    /// They are the Arnold Schwarzenegger “I’ll be back” Terminators of the PigWorld.
    /// 
    /// Original author: Raymond Lister 
    /// Converted & modified by: Jim Reye
    /// </summary>
    public class Wolf : Animal {

        /// <summary>
        /// Constructs a new Wolf.
        /// </summary>
        /// <param name="pigWorld"> the PigWorld in which to create the Wolf. </param>
        public Wolf(PigWorld pigWorld)
            : this(pigWorld, Position.any) {  // In this context, "this" is a call to the constructor below.
        }

        /// <summary>
        /// Constructs a new Wolf at the specified position. If the desired position is
        /// already occupied by another LifeForm, then the Wolf will be placed in a
        /// nearby Cell. If there are no nearby Cells that are free, then the Wolf
        /// will not be added to the pigWorld.
        /// </summary>
        /// <param name="pigWorld"></param>
        /// <param name="position"></param>
        public Wolf(PigWorld pigWorld, Position position) {
            AddToWorld(pigWorld, position);
        }

        /// <summary>
        /// This method is called every unit of time by the PigWorld to give the Wolf
        /// a chance to do something.
        /// 
        /// First the Wolf looks around for the nearest pig, using the
        /// method "FindNearest". If there isn't a pig, the Wolf does nothing.
        /// If there is, then the Wolf either:
        /// (1) tries to moves one cell/square in the direction of the nearest pig, or
        /// (2) if a pig is in fact only one move away, the wolf eats the pig.
        /// 
        /// Note that if there is a wall between the Wolf and the nearest pig,
        /// then the Wolf won't move at all.
        /// </summary>
        protected override void DoSomething() {

            // This will detect any type of pig (both BoyPigs and GirlPigs).
            Echo echo = FindNearest(typeof(Pig));

            // If there are no pigs in the whole world, do nothing more.
            if (echo == null) {
            } else {
                // Otherwise, the Wolf must try to move in the direction given by the echo,
                // to fulfil the behaviour described in items (1) and (2) above.
                //
                // The Wolf's current cell/square is specified by its Cell property.
                // And the Cell class has a GetAdjacentCell method which can be used to get
                // a reference to a neighbouring Cell (if any) in the specified direction.
                Cell targetCell = Cell.GetAdjacentCell(echo.direction);

                // If the targetCell is null, then there is a wall in the way, so do nothing more.
                if (targetCell == null) {
                } else {
                    // Otherwise, see if there is a LifeForm in that targetCell, 
                    // by setting adjacentLifeForm equal to the targetCell'sLifeFormOccupant property.
                    // If there's no such LifeForm, then this will be null.
                    LifeForm adjacentLifeForm = targetCell.LifeFormOccupant;

                    // If there's no such LifeForm, then move to that targetCell, 
                    // using the Move method -- a method that is inherited from the Animal class, 
                    // i.e. all animals can move.

                    if (adjacentLifeForm == null) {
                        base.Move(targetCell);
                    }

                    // Else, if the adjacentLifeForm is a pig, (Hint: use an "is" test -- see Lecture 9),
                        // then (logically) the wolf moves to that targetCell and then eats the pig.
                        // But because a cell can contain ONLY ONE LifeForm at a time, this has to be 
                        // written as program code that eats the pig first, and then moves the wolf into
                        // the pig's cell/square.
                        // All animals can eat by using the Eat method -- a method that is also inherited 
                        // from the Animal class.
                    else if (adjacentLifeForm is Pig) {
                        base.Eat(adjacentLifeForm);
                        base.Move(targetCell);
                    } else {
                        // It's another type of LifeForm, such as a Tree or another wolf, so do nothing.
                    }
                }
            }
            // Write your code here.
        }
    }
}
