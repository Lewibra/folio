using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using System.Diagnostics;  // Allow Debug.Assert

namespace PigWorldNamespace {

    /// <summary>
    /// The View class for a Tree.
    /// 
    /// Original (AWT) author: Lizveth Robles 
    /// Converted & modified by: Jim Reye
    /// </summary>
    public class TreeView : PlantView {

        private Tree tree;  // A reference to the tree we are viewing.



        private static Image treeImage = Image.FromFile(@"Resources\tree.gif");

        /// <summary>
        /// Constructs a TreeView for the specified Tree.
        /// </summary>
        /// <param name="pigWorldView"></param>
        /// <param name="tree"> the tree to view </param>
        public TreeView(PigWorldView pigWorldView, Tree tree)
            : base(pigWorldView, tree) {

            this.tree = tree;
            InitialiseContextMenu();
        }

        // Event-handler(s) for the context-menu.
        private void dropFoodMenuItem_Click(object sender, EventArgs e) {
            tree.DropFood();
        }

        private void showIDMenuItem_Click(object sender, EventArgs e) {
            int treeId = tree.Id;
            MessageBox.Show("ID = " + treeId);
        }

        private void delete_Click(object sender, EventArgs e) {
            tree.Delete();
        }

        /// <summary>
        /// Creates the context-menu for the Tree, and specifies the names of 
        /// the event-handlers in this class, for the items in that menu.
        /// </summary>
        private void InitialiseContextMenu() {
            contextMenuStrip.ShowImageMargin = false;

            // Add the menu items to the context-menu, 
            // with their associated event-handlers.
            //Drop Food
            contextMenuStrip.Items.Add("Drop Food", null, dropFoodMenuItem_Click);
            contextMenuStrip.Items.Add("-");
            //Show ID
            contextMenuStrip.Items.Add("Show ID", null, showIDMenuItem_Click);
            contextMenuStrip.Items.Add("-");
            //Delete
            contextMenuStrip.Items.Add("Delete", null, delete_Click);

        }

        /// <summary>
        /// Displays the Tree's image on the screen.
        /// 
        /// Overrides the Paint method in the base class, ThingView.
        /// </summary>
        /// <param name="graphics"> the Graphics object on which the animal's image is displayed. </param>
        protected override void Paint(Graphics graphics) {
            graphics.DrawImage(treeImage, thingViewRectangle);
        }
    }
}
