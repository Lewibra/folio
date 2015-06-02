using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Drawing;       // For Color
using System.Diagnostics;   // Allow Debug.Assert
using System.Media;         // For SoundPlayer

namespace PigWorldNamespace {

    /// <summary>
    /// A Pig is a type of Animal that eats PigFood, and mates with other Pigs. The
    /// behaviour of Pigs is implemented in the DoSomething method in this class.
    /// 
    /// There are two subclasses of Pig: GirlPig and BoyPig. GirlPigs have a unique
    /// method called TryToMakeBaby. While BoyPigs do not have this method, 
    /// BoyPigs invoke a GirlPig's TryToMakeBaby method, so both pigs must cooperate 
    /// to make a new baby. GirlPigs have the final say in making a baby and can 
    /// reject a request to make a baby.
    /// 
    /// Original author: Ryan Heise 
    /// Converted & modified by: Jim Reye
    /// </summary>
    public abstract class Pig : Animal {

        // The safe distance from a wolf. If a wolf is closer than this distance,
        // then the pig should run away.
        private const double SAFE_DISTANCE_FROM_WOLF = 2.5;

        // A reference to the mother of this pig, when the pig is created by the TryToMakeBaby method.
        // Otherwise, null.
        private Pig mother;

        // A reference to the father of this pig, when the pig is created by the TryToMakeBaby method.
        // Otherwise, null.
        private Pig father;

        private Color color;  // The colour of this pig.
        public Color Color { get { return color; } }

        // The pieces of rope that have been dropped (if any). As new pieces
        // of rope are dropped, they are added to this list. I.e. the newest piece is
        // at the end of the List.
        // If this pig currently has no pieces of rope on the ground, then 
        // this List is empty -- i.e. its Count is zero -- but ropePieces is never null.
        public List<RopePiece> ropePieces = new List<RopePiece>();

        // When a pig would otherwise be looking for food, but there is no food in
        // the pigWorld at the moment, the pig will move in the wanderDirection. 
        private Direction wanderDirection = Direction.GetRandomDirection();

        static SoundPlayer gruntAudio = Util.LoadSound(@"Resources\pig_grunt.wav");
        static SoundPlayer shriekAudio = Util.LoadSound(@"Resources\pig_shriek.wav");

        /// <summary>
        /// Constructs a new Pig at, or near, the specified position. 
        /// If the desired position is already occupied by another LifeForm, 
        /// then the pig will be placed in a nearby Cell. 
        /// If no nearby Cells are free, then the pig will not be added to the pigWorld.
        /// 
        /// This constructor is protected since only Pig subclasses should be
        /// able to create a pig.
        /// </summary>
        /// <param name="pigWorld"> the pigWorld that this pig is entering </param>
        /// <param name="position"> the preferred position for the new pig </param>
        /// <param name="color"> the pig's colour (blue or pink) </param>
        /// <param name="mother"> the pig's mother (may be null)</param>
        /// <param name="father"> the pig's father (may be null)</param>
        protected Pig(PigWorld pigWorld, Position position, Color color, GirlPig mother, BoyPig father) {
            this.color = color;  // Must be set before AddToWorld is called.
            this.mother = mother;
            this.father = father;

            AddToWorld(pigWorld, position);  // Must be called before any sounds are played.
        }

        /// <summary>
        /// This method is called every unit of time by the PigWorld to give the Pig a
        /// chance to do something.
        /// </summary>
        protected override void DoSomething() {

            // Do not modify this method!

            if (IsTired()) {  // After producing offspring.
                Rest();
            } else if (IsWolfNearby()) {
                RunFromWolf();
            } else if (IsHungry) {
                LookForFoodUsingRope();
            } else if (IsInTheMoodForLove()) {
                LookForPig();
            } else {
                // Do nothing.

                // Do not modify, delete, or move the debugAnimalAction line below, 
                // or the Debug Info will not show correctly in the GUI, and that could be confusing.
                debugAnimalAction = "Do nothing";
            }
        }

        /// <summary>
        /// Look for the nearest pig of the opposite gender.
        /// This is an "abstract" method which means that the actual code
        /// is implemented in the two derived classes, BoyPig and GirlPig.
        /// </summary>
        protected abstract void LookForPig();

        /// <summary>
        /// Delete any ropePieces currently being trailed by (i.e. owned by) this pig.
        /// </summary>
        public void ClearRope() {
            // Write your code here.
            //for each ropePiece in ropePieces, delete it
            foreach (RopePiece element in ropePieces) {
                element.Delete();
            }
            //remove the rope pieces from the gui
            ropePieces.Clear();

        }

        /// <summary>
        /// When a pig is deleted, its rope must be deleted as well.
        /// </summary>
        public override void Delete() {
            base.Delete();
            ClearRope();
        }

        /// <summary>
        /// First the pig looks to see if there is any PigFood in its current Cell.
        /// If there is, the pig picks it up, eats it, and does nothing more. I.e. the pig stays where it is.
        /// Otherwise, the pig looks for the nearest PigFood, using the FindNearest method. 
        /// If there isn't any food anywhere in the pigWorld, the pig does nothing.
        /// If there is food, then the pig (tries to) move one square in the direction 
        /// of that food. If the move fails (e.g. because there's a wall in the way, 
        /// or any other reason), then the pig simply remains where it is.
        /// </summary>
        public void LookForFood() {
            // Do not modify, delete, or move the debugAnimalAction line below, 
            // or the Debug Info will not show correctly in the GUI, and that could be confusing.
            debugAnimalAction = "LookForFood";

            // Write your code here.
            //Create a boolean to check if the pig is on food
            //it will be true if it is ontop of food, false otherwise
            bool currentCellFoodCheck = Cell.Exists(typeof(PigFood));
            if (currentCellFoodCheck == true) {
                //Store the food picked up as food in a variable and eat it
                Thing food = Cell.PickUp(typeof(PigFood));
                base.Eat(food);

            }
                //if the pig was not ontop of food, it'll start searching for it
            else if (currentCellFoodCheck == false) {
                //Find the nearest pigfood
                Echo echo = FindNearest(typeof(PigFood));
                //if there is no food, do nothing
                if (echo == null) {
                } else {
                    //else, get the adjacent cell in the direction of the pig food
                    Cell targetFoodCell = Cell.GetAdjacentCell(echo.direction);
                    //if there is a wall in the way, do nothing
                    if (targetFoodCell == null) {
                    }
                        //else check if there's any life forms in the way
                    else {
                        LifeForm adjacentLifeForm = targetFoodCell.LifeFormOccupant;
                        //if there's no life form in the target cell, it will move
                        if (adjacentLifeForm == null) {
                            base.Move(targetFoodCell);

                        }
                    }
                }
            }
        }

        ///<summary>
        ///Created this method to stay under 50 lines for the lookForFoodUsingRope
        ///method
        ///If the pig is surrounded in ropes, this method can be called to move to
        ///the oldest rope
        /// Pre: A list of ropes is gathered and plugged into this method
        /// Post: The rope in the 8 cells surrounding the pig with the longest distance,
        /// will be selected to move to.
        /// <para name="list">The list full of the ropes surrounding the pig</para>
        /// </summary>
        private void moveToOldestRope(List<RopePiece> list) {
            //creat a list to store the distances of the rope
            List<int> ropeDistanceList = new List<int>();
            int ropePieceCounter = 0;
            //for each ropepiece around the pig, get the distance to it
            //and add it to ropeDistanceList
            foreach (RopePiece element in list) {
                int ropeDistance = list[ropePieceCounter].GetDistanceFromOwner();
                ropeDistanceList.Add(ropeDistance);
                ropePieceCounter += 1;
            }
            //Get the index of the element in ropeDistanceList with the max distance
            int indexOfOldestRopePiece = ropeDistanceList.IndexOf(ropeDistanceList.Max());
            //the index value of that is relevant to it's rope piece
            RopePiece oldestRopePiece = list[indexOfOldestRopePiece];
            DropRope();
            //move to that rope piece
            base.Move(oldestRopePiece.Cell);
        }

        /// <summary>
        /// this method is used to move to the closest direction to food, and
        /// it considers what's blocking the pig when making the decision of which
        /// cell has the closest angle to the food
        /// Pre: the pig knows that there are adjacent cells it can move to
        /// Post: the pig moves to the adjacentCell that is not blocked
        ///       and has the closest angle to the targeted food
        /// </summary>
        /// <param name="DirectionList">parameter to hold directionList</param>
        /// <param name="FoodDirection">parameter to hold doodDirection</param>
        /// <param name="ConvertedAnglesToFood">parameter to hold convertedAnglesToFood</param>
        private void moveToClosestDirection(List<double> DirectionList, double FoodDirection
                , List<double> AnglesToFood) {
            //set up a counter for the foreach statement below
            int foreachCounter = 0;
            //set up an int to represent the maximum degrees
            int maxDegrees = 360;
            //goes through each direction in directionList to find it's 
            //angle that is closest to the food
            foreach (double element in DirectionList) {
                //angle holds the difference between the food direction and each direction of the adjacent cells
                double angle = (Math.Abs(DirectionList[foreachCounter] - FoodDirection)) % maxDegrees;
                //on an axis, 359 degrees is closer to 0 than 3 is
                //but 359 - 0 = 359 and 3 - 0 = 3, which says 3 is closer.
                //to fix this, if angle is greater than 180, we convert it
                //by minusing it from 360 or max degrees
                //now 359 --> 1 --> 1 - 0 = 1, showing that 359 degrees is closer to 0.
                if (angle > Direction.SOUTH.Degrees) {
                    angle = maxDegrees - angle;
                }
                //add these angles to convertedAnglesToFood list
                AnglesToFood.Add(angle);
                foreachCounter += 1;
            }
            //the index of the smallest value in convertedAnglesToFood is the index
            //to the cell with the closest angle in directionList
            int closestIndex = AnglesToFood.IndexOf(AnglesToFood.Min());
            DropRope();
            base.Move(DirectionList[closestIndex]);
        }

        /// <summary>
        /// Rope-based look-for-food method
        /// </summary>
        private void LookForFoodUsingRope() {
            // Do not modify, delete, or move the debugAnimalAction line below, 
            // or the Debug Info will not show correctly in the GUI, and that could be confusing.
            debugAnimalAction = "LookForFood";

            // Write your code here.
            //Create a boolean to check if the pig is on food
            //it will be true if it is ontop of food, false otherwise
            bool currentCellFoodCheck = Cell.Exists(typeof(PigFood));
            if (currentCellFoodCheck == true) {
                //Store the food picked up as food in a variable and eat it
                ClearRope();
                Thing food = Cell.PickUp(typeof(PigFood));
                base.Eat(food);
            }

                //if the pig was not ontop of food, it'll start searching for it using rope
            else if (currentCellFoodCheck == false) {
                //Find the nearest pigfood
                Echo echo = FindNearest(typeof(PigFood));
                if (echo != null) {
                    //get the direction in degrees to the food
                    double foodDirection = echo.direction.Degrees;

                    Cell targetFoodCell = Cell.GetAdjacentCell(echo.direction);
                    //Define these lists that will be required to help the pig
                    //find food through the shortest angle
                    //List to hold the surrounding ropes around the pig
                    List<RopePiece> ropePieceList = new List<RopePiece>();
                    //List that holds the free adjacent cells around the pig
                    List<Cell> cellList = new List<Cell>();
                    //List that holds the direction of degrees of the cells in cellList
                    List<double> directionList = new List<double>();
                    //
                    List<double> anglesToFood = new List<double>();

                    //Cell tally of cells that have no walls or living things in them
                    int cellsNotBlockedCount = 0;
                    //Cell tally of celsl that have ropes things in them
                    int ropeCellCount = 0;
                    //Cell tally of cells that do not have walls, living things or ropes in them
                    int moveableCellCount = 0;
                    //Scan the 8 cells surrounding the pig to get info
                    //about if it is blocked or not
                    for (int i = 0; i < Direction.NUMBER_POSSIBLE; i++) {
                        //Get the reference to the adjacent cell
                        Direction direction = Direction.GetAdjacentCellDirection(i);
                        Cell adjacentCell = Cell.GetAdjacentCell(direction);

                        //If a cell isn't blocked, it's info is added to a list
                        if (CanMove(direction) == true) {
                            cellsNotBlockedCount += 1;
                            if (GetMyRopePiece(adjacentCell) == null) {
                                moveableCellCount += 1;
                                //Adds the adjacent cell's Cell component to a list
                                cellList.Add(adjacentCell);
                                //Adds the adjacent cell's Direction component to a list
                                directionList.Add(direction.Degrees);
                            } else if (GetMyRopePiece(adjacentCell) != null) {
                                ropeCellCount += 1;
                                //Adds the RopePiece component of the adjacent cell to a list
                                ropePieceList.Add(GetMyRopePiece(adjacentCell));
                            }
                        }
                    }
                    //If the pig is trapped, do nothing
                    if ((moveableCellCount == 0) && (ropeCellCount == 0)) {
                    }
                        //If the pig has surrounded itself in it's rope, it will move to
                        //the oldest piece within the 8 cells around the pig
                    else if (ropeCellCount == cellsNotBlockedCount) {
                        //Move to the oldest rope
                        moveToOldestRope(ropePieceList);
                    }
                        //if the pig is surrounded by walls, objects or rope, but there
                        //are cells for it to move to, it will select the cell
                        //that has the closest direction angle to the angle of the
                        //pig to the food
                    else if ((moveableCellCount >= 1) && (moveableCellCount <= Direction.NUMBER_POSSIBLE)) {
                        moveToClosestDirection(directionList, foodDirection, anglesToFood);
                    }
                } else if (echo == null) {
                    //if there's no food in the world, the pigs will jsut wander around
                    ClearRope();
                    WanderAround();
                }
            }
        }

        /// <summary>
        /// When a pig would otherwise be looking for food, but there is no food in
        /// the pigWorld at the moment, the pig will move in the wanderDirection. 
        /// If a pig is wandering and it bumps into an obstacle, it will randomly
        /// assign a new wander direction and then continue wandering.
        /// </summary>
        protected void WanderAround() {
            int count = 0;
            while (!CanMove(wanderDirection) && count < 20) {
                wanderDirection = Direction.GetRandomDirection();
                count += 1;
            }

            Move(wanderDirection);
        }

        /// <summary>
        /// Move in ANY random direction that is possible, i.e. not obstructed by a wall, etc.
        /// Because the pig is panicking, it might move towards a threat, such as a Wolf.
        /// </summary>
        protected void Panic() {
            int count = 0;
            Direction direction;

            do {
                direction = Direction.GetRandomDirection();
                count += 1;
            } while (!CanMove(direction) && count < 20);

            Move(direction);
        }

        /// <summary>
        /// This method makes the pig drop rope onto the current cell.
        /// 
        /// Note that, when a rope is being used, the pig must 
        /// call DropRope BEFORE the pig moves from its current cell, 
        /// because ropes are used to keep a history of where a pig has been,
        /// which excludes its current location (unless it is revisiting a cell).
        /// </summary>
        void DropRope() {
            // Create the rope on the current cell
            Position position = Cell.Position;
            RopePiece newRopePiece = new RopePiece(PigWorld, this, position);

            // Add it to the previous rope pieces.
            ropePieces.Add(newRopePiece);
        }

        /// <summary>
        /// Accesses a piece of rope on the specified cell owned by this pig.
        /// If there is more than one piece of rope on that cell owned by this pig,
        /// then the most recently placed will be returned.
        /// If no ropes owned by this pig are on that cell, null is returned.
        /// </summary>
        /// <returns> the requested rope from that Cell. </returns>
        public RopePiece GetMyRopePiece(Cell cell) {
            List<RopePiece> ropes = cell.InspectAll<RopePiece>();
            RopePiece bestRopeSoFar = null;

            foreach (RopePiece ropePiece in ropes) {

                if (ropePiece.OwnerPig == this) {
                    if (bestRopeSoFar == null) {
                        bestRopeSoFar = ropePiece;
                    } else {
                        if (ropePiece.GetDistanceFromOwner() < bestRopeSoFar.GetDistanceFromOwner())
                            bestRopeSoFar = ropePiece;
                    }
                }
            }
            return bestRopeSoFar;
        }

        /// <summary>
        /// Determines if there is a wolf nearby.
        /// </summary>
        /// <returns> true if there is a wolf nearby, or false otherwise. </returns>
        public bool IsWolfNearby() {
            Echo echo = FindNearest(typeof(Wolf));

            return (echo != null && echo.distance < SAFE_DISTANCE_FROM_WOLF);
        }

        /// <summary>
        /// This method will make the pig try to run in the opposite direction of the nearest wolf.
        /// </summary>
        public void RunFromWolf() {
            // Do not modify, delete, or move the debugAnimalAction line below, 
            // or the Debug Info will not show correctly in the GUI, and that could be confusing.
            debugAnimalAction = "RunFromWolf";

            Echo echo = FindNearest(typeof(Wolf));
            //if there is a wolf nearby, run in the opposite direction
            if (echo != null) {
                Direction targetDirection = echo.direction;
                Direction targetOppositeDirection = targetDirection.GetOppositeDirection();
                bool moveBool = base.Move(targetOppositeDirection);
                //if the pig is blocked, panic
                if (moveBool == false) {
                    Panic();
                }
            }

            // Write your code here.
        }

        /// <summary>
        /// Tests to see if this object is indeed a child of possibleParent.
        /// </summary>
        /// <param name="possibleParent"> The Pig who's past is in question, or a null
        /// reference </param>
        /// <returns> true if this pig is a child of possibleParent </returns>
        public bool IsParent(Pig possibleParent) {
            if (this.mother == possibleParent)
                return true;
            if (this.father == possibleParent)
                return true;
            return false;
        }

        /// <summary>
        /// Tests if this and the other pig are full brothers/sisters.  That is,
        /// tests that both pigs have the same two parents.
        /// </summary>
        /// <param name="possibleSibling"> A Pig ... or perhaps a null reference </param>
        /// <returns> true if this pig and the other pig have the same two parents.  </returns>
        protected bool IsSibling(Pig pig) {
            if ((pig.mother == null) || (pig.father == null))
                return false;
            if ((this.mother == pig.mother) && (this.father == pig.father))
                return true;
            return false;
        }

        /// <summary>
        /// Plays a grunting sound.
        /// 
        /// Note that if your program calls the Grunt or Shriek methods too rapidly,
        /// you'll hear a stuttering sound instead of the proper sounds. 
        /// This is because each call to these methods terminates any sound that is already being played. 
        /// I.e. calling too rapidly means that only the first part of each sound will be played, 
        /// resulting in a sound that is like stuttering.  Unfortunately, there is no easy way to 
        /// overcome this.
        /// </summary>
        public void Grunt() {
            if (PigWorld.EnableRealAudio) {
                gruntAudio.Play();
            }
        }

        /// <summary>
        /// Plays a shrieking sound.
        /// 
        /// See comments for the Grunt method with regards to stuttering sounds 
        /// if this method is called too rapidly.
        /// </summary>
        public void Shriek() {
            if (PigWorld.EnableRealAudio) {
                shriekAudio.Play();
            }
        }
    }
}
