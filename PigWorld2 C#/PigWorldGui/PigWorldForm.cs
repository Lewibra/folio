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
    /// This class is the overall form for PigWorld, containing the user controls, etc.
    /// 
    /// Author: Jim Reye
    /// </summary>
    public partial class PigWorldForm : Form {

        private PigWorldView pigWorldView = new PigWorldView();  // The grid of squares/cells.



        /// <summary>
        /// Construct the PigWorldForm.
        /// </summary>
        public PigWorldForm() {
            InitializeComponent();

            this.Controls.Add(pigWorldView);

            // Ensure that the PigWorldView uses only the available space, not the entire form.
            // This must be done AFTER the PigWorldView is added to the form (by the above Add).
            pigWorldView.BringToFront();

            CancelButton = quitButton;  // Allow the Esc key to close the form.

        }

        /// <summary>
        /// Event-handler for the Setup Demo Button.
        /// </summary>
        /// <param name="sender"> the Button where this event occurred </param>
        /// <param name="e"> extra information (if any) about the event </param>
        private void setupDemoButton_Click(object sender, EventArgs e) {
            pigWorldView.PigWorld.RemoveAll();

            switch ((int)demoNumber.Value) {
                    //Setup demo 1
                case 1: pigWorldView.SetupDemo1(); break;
                    //setup demo 2
                case 2: pigWorldView.SetupDemo2(); break;
                    //setup demo 3
                case 3: pigWorldView.SetupDemo3(); break;
                default:
                    // This can only happen if the Minimum and Maximum properties of the NumericUpDown control 
                    // have NOT been set correctly, in Design View.
                    MessageBox.Show("Invalid demo number.");
                    break;
            }
        }

        /// <summary>
        /// Event-handler for the Quit Button.
        /// </summary>
        /// <param name="sender"> the Button where this event occurred </param>
        /// <param name="e"> extra information (if any) about the event </param>
        private void quitButton_Click(object sender, EventArgs e) {
            this.Close();
        }

        /// <summary>
        /// Event-handler for the Show Debug Info CheckBox.
        /// </summary>
        /// <param name="sender"> the CheckBox where this event occurred </param>
        /// <param name="e"> extra information (if any) about the event </param>
        private void showDebugInfoCheckBox_CheckedChanged(object sender, EventArgs e) {
            pigWorldView.PigWorld.ShowDebugInfo = showDebugInfoCheckBox.Checked;
        }

        private void boyPigRadioButton_CheckedChanged(object sender, EventArgs e) {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked) {
                //Spawn BoyPig when clicking a square
                pigWorldView.CurrentTypeOfObjectToAdd = typeof(BoyPig);
            }
        }

        private void girlPigRadioButton_CheckedChanged(object sender, EventArgs e) {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked) {
                //Spawn GirlPig when clicking a square
                pigWorldView.CurrentTypeOfObjectToAdd = typeof(GirlPig);
            }
        }

        private void pigFoodRadioButton_CheckedChanged(object sender, EventArgs e) {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked) {
                //Spawn PigFood when clicking a square
                pigWorldView.CurrentTypeOfObjectToAdd = typeof(PigFood);
            }
        }

        private void treeRadioButton_CheckedChanged(object sender, EventArgs e) {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked) {
                //Spawn Tree when clicking a square
                pigWorldView.CurrentTypeOfObjectToAdd = typeof(Tree);
            }
        }

        private void wolfRadioButton_CheckedChanged(object sender, EventArgs e) {
            RadioButton radioButton = (RadioButton)sender;
            if (radioButton.Checked) {
                //Spawn Wolf when clicking a square
                pigWorldView.CurrentTypeOfObjectToAdd = typeof(Wolf);
            }
        }

        private void removeAllButton_Click(object sender, EventArgs e) {
            pigWorldView.PigWorld.RemoveAll();
        }

        private void removeWallsButton_Click(object sender, EventArgs e) {
            pigWorldView.PigWorld.RemoveAllWalls();
        }

        private void stepButton_Click(object sender, EventArgs e) {
            pigWorldView.PigWorld.Step();

        }

        private void startButton_Click(object sender, EventArgs e) {
            timer.Start();
        }

        private void stopButton_Click(object sender, EventArgs e) {
            timer.Stop();
        }

        private void fasterSlowerTrackBar_Scroll(object sender, EventArgs e) {
            // Get the current speed from the speedTrackBar on the form.
            // (This will be a value in the range 0 to 10.)
            int speed = fasterSlowerTrackBar.Value;

            // Calculate the new interval, by subtracting the speed from 10 
            // (so that high speed values become low intervals), and then multiplying 
            // by 100 to convert to a value in the range 0 to 1000 milliseconds.
            int interval = (10 - speed) * 100;

            // Limit the speed, to avoid problems of things going too fast.
            if (interval < 100) {
                interval = 100;
            }

            // Tell the timer about the new interval value.
            timer.Interval = interval;
        }

        private void enableRealAudioCheckBox_CheckedChanged(object sender, EventArgs e) {
            if (enableRealAudioCheckBox.Checked == true) {
                //Audio On
                pigWorldView.PigWorld.EnableRealAudio = true;
            } else {
                //Audio Off
                pigWorldView.PigWorld.EnableRealAudio = false;
            }

        }

        private void timer_Tick(object sender, EventArgs e) {
            pigWorldView.PigWorld.Step();
        }
    }

}
