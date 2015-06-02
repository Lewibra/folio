namespace PigWorldNamespace {

    partial class PigWorldForm {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing) {
            if (disposing && (components != null)) {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent() {
            this.components = new System.ComponentModel.Container();
            this.buttonPanel = new System.Windows.Forms.Panel();
            this.enableRealAudioCheckBox = new System.Windows.Forms.CheckBox();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.fasterSlowerTrackBar = new System.Windows.Forms.TrackBar();
            this.removeAllButton = new System.Windows.Forms.Button();
            this.removeWallsButton = new System.Windows.Forms.Button();
            this.stepButton = new System.Windows.Forms.Button();
            this.stopButton = new System.Windows.Forms.Button();
            this.startButton = new System.Windows.Forms.Button();
            this.demoNumber = new System.Windows.Forms.NumericUpDown();
            this.showDebugInfoCheckBox = new System.Windows.Forms.CheckBox();
            this.setupDemoButton = new System.Windows.Forms.Button();
            this.quitButton = new System.Windows.Forms.Button();
            this.currentTypeOfObjectPanel = new System.Windows.Forms.Panel();
            this.groupBox = new System.Windows.Forms.GroupBox();
            this.wolfRadioButton = new System.Windows.Forms.RadioButton();
            this.treeRadioButton = new System.Windows.Forms.RadioButton();
            this.pigFoodRadioButton = new System.Windows.Forms.RadioButton();
            this.girlPigRadioButton = new System.Windows.Forms.RadioButton();
            this.boyPigRadioButton = new System.Windows.Forms.RadioButton();
            this.timer = new System.Windows.Forms.Timer(this.components);
            this.buttonPanel.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fasterSlowerTrackBar)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.demoNumber)).BeginInit();
            this.groupBox.SuspendLayout();
            this.SuspendLayout();
            // 
            // buttonPanel
            // 
            this.buttonPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.buttonPanel.Controls.Add(this.enableRealAudioCheckBox);
            this.buttonPanel.Controls.Add(this.label2);
            this.buttonPanel.Controls.Add(this.label1);
            this.buttonPanel.Controls.Add(this.fasterSlowerTrackBar);
            this.buttonPanel.Controls.Add(this.removeAllButton);
            this.buttonPanel.Controls.Add(this.removeWallsButton);
            this.buttonPanel.Controls.Add(this.stepButton);
            this.buttonPanel.Controls.Add(this.stopButton);
            this.buttonPanel.Controls.Add(this.startButton);
            this.buttonPanel.Controls.Add(this.demoNumber);
            this.buttonPanel.Controls.Add(this.showDebugInfoCheckBox);
            this.buttonPanel.Controls.Add(this.setupDemoButton);
            this.buttonPanel.Controls.Add(this.quitButton);
            this.buttonPanel.Dock = System.Windows.Forms.DockStyle.Right;
            this.buttonPanel.Location = new System.Drawing.Point(562, 0);
            this.buttonPanel.Name = "buttonPanel";
            this.buttonPanel.Size = new System.Drawing.Size(122, 564);
            this.buttonPanel.TabIndex = 2;
            // 
            // enableRealAudioCheckBox
            // 
            this.enableRealAudioCheckBox.AutoSize = true;
            this.enableRealAudioCheckBox.Location = new System.Drawing.Point(8, 511);
            this.enableRealAudioCheckBox.Name = "enableRealAudioCheckBox";
            this.enableRealAudioCheckBox.Size = new System.Drawing.Size(114, 17);
            this.enableRealAudioCheckBox.TabIndex = 19;
            this.enableRealAudioCheckBox.Text = "Enable Real Audio";
            this.enableRealAudioCheckBox.UseVisualStyleBackColor = true;
            this.enableRealAudioCheckBox.CheckedChanged += new System.EventHandler(this.enableRealAudioCheckBox_CheckedChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 453);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(39, 13);
            this.label2.TabIndex = 18;
            this.label2.Text = "Slower";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 325);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 17;
            this.label1.Text = "Faster";
            // 
            // fasterSlowerTrackBar
            // 
            this.fasterSlowerTrackBar.Location = new System.Drawing.Point(61, 316);
            this.fasterSlowerTrackBar.Name = "fasterSlowerTrackBar";
            this.fasterSlowerTrackBar.Orientation = System.Windows.Forms.Orientation.Vertical;
            this.fasterSlowerTrackBar.Size = new System.Drawing.Size(45, 159);
            this.fasterSlowerTrackBar.TabIndex = 16;
            this.fasterSlowerTrackBar.TickStyle = System.Windows.Forms.TickStyle.Both;
            this.fasterSlowerTrackBar.Scroll += new System.EventHandler(this.fasterSlowerTrackBar_Scroll);
            // 
            // removeAllButton
            // 
            this.removeAllButton.Location = new System.Drawing.Point(15, 227);
            this.removeAllButton.Name = "removeAllButton";
            this.removeAllButton.Size = new System.Drawing.Size(91, 28);
            this.removeAllButton.TabIndex = 3;
            this.removeAllButton.Text = "Remove All";
            this.removeAllButton.UseVisualStyleBackColor = true;
            this.removeAllButton.Click += new System.EventHandler(this.removeAllButton_Click);
            // 
            // removeWallsButton
            // 
            this.removeWallsButton.Location = new System.Drawing.Point(15, 193);
            this.removeWallsButton.Name = "removeWallsButton";
            this.removeWallsButton.Size = new System.Drawing.Size(91, 28);
            this.removeWallsButton.TabIndex = 3;
            this.removeWallsButton.Text = "Remove Walls";
            this.removeWallsButton.UseVisualStyleBackColor = true;
            this.removeWallsButton.Click += new System.EventHandler(this.removeWallsButton_Click);
            // 
            // stepButton
            // 
            this.stepButton.Location = new System.Drawing.Point(15, 131);
            this.stepButton.Name = "stepButton";
            this.stepButton.Size = new System.Drawing.Size(91, 28);
            this.stepButton.TabIndex = 3;
            this.stepButton.Text = "Step";
            this.stepButton.UseVisualStyleBackColor = true;
            this.stepButton.Click += new System.EventHandler(this.stepButton_Click);
            // 
            // stopButton
            // 
            this.stopButton.Location = new System.Drawing.Point(15, 97);
            this.stopButton.Name = "stopButton";
            this.stopButton.Size = new System.Drawing.Size(91, 28);
            this.stopButton.TabIndex = 15;
            this.stopButton.Text = "Stop";
            this.stopButton.UseVisualStyleBackColor = true;
            this.stopButton.Click += new System.EventHandler(this.stopButton_Click);
            // 
            // startButton
            // 
            this.startButton.Location = new System.Drawing.Point(15, 63);
            this.startButton.Name = "startButton";
            this.startButton.Size = new System.Drawing.Size(91, 28);
            this.startButton.TabIndex = 14;
            this.startButton.Text = "Start";
            this.startButton.UseVisualStyleBackColor = true;
            this.startButton.Click += new System.EventHandler(this.startButton_Click);
            // 
            // demoNumber
            // 
            this.demoNumber.Location = new System.Drawing.Point(81, 21);
            this.demoNumber.Maximum = new decimal(new int[] {
            3,
            0,
            0,
            0});
            this.demoNumber.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.demoNumber.Name = "demoNumber";
            this.demoNumber.Size = new System.Drawing.Size(34, 20);
            this.demoNumber.TabIndex = 13;
            this.demoNumber.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            // 
            // showDebugInfoCheckBox
            // 
            this.showDebugInfoCheckBox.AutoSize = true;
            this.showDebugInfoCheckBox.Location = new System.Drawing.Point(8, 534);
            this.showDebugInfoCheckBox.Name = "showDebugInfoCheckBox";
            this.showDebugInfoCheckBox.Size = new System.Drawing.Size(109, 17);
            this.showDebugInfoCheckBox.TabIndex = 9;
            this.showDebugInfoCheckBox.Text = "Show Debug Info";
            this.showDebugInfoCheckBox.UseVisualStyleBackColor = true;
            this.showDebugInfoCheckBox.CheckedChanged += new System.EventHandler(this.showDebugInfoCheckBox_CheckedChanged);
            // 
            // setupDemoButton
            // 
            this.setupDemoButton.Location = new System.Drawing.Point(3, 16);
            this.setupDemoButton.Name = "setupDemoButton";
            this.setupDemoButton.Size = new System.Drawing.Size(74, 28);
            this.setupDemoButton.TabIndex = 7;
            this.setupDemoButton.Text = "Setup Demo";
            this.setupDemoButton.UseVisualStyleBackColor = true;
            this.setupDemoButton.Click += new System.EventHandler(this.setupDemoButton_Click);
            // 
            // quitButton
            // 
            this.quitButton.Location = new System.Drawing.Point(15, 282);
            this.quitButton.Name = "quitButton";
            this.quitButton.Size = new System.Drawing.Size(91, 28);
            this.quitButton.TabIndex = 2;
            this.quitButton.Text = "Quit";
            this.quitButton.UseVisualStyleBackColor = true;
            this.quitButton.Click += new System.EventHandler(this.quitButton_Click);
            // 
            // currentTypeOfObjectPanel
            // 
            this.currentTypeOfObjectPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.currentTypeOfObjectPanel.Location = new System.Drawing.Point(0, 507);
            this.currentTypeOfObjectPanel.Name = "currentTypeOfObjectPanel";
            this.currentTypeOfObjectPanel.Size = new System.Drawing.Size(562, 57);
            this.currentTypeOfObjectPanel.TabIndex = 1;
            // 
            // groupBox
            // 
            this.groupBox.Controls.Add(this.wolfRadioButton);
            this.groupBox.Controls.Add(this.treeRadioButton);
            this.groupBox.Controls.Add(this.pigFoodRadioButton);
            this.groupBox.Controls.Add(this.girlPigRadioButton);
            this.groupBox.Controls.Add(this.boyPigRadioButton);
            this.groupBox.Location = new System.Drawing.Point(3, 510);
            this.groupBox.Name = "groupBox";
            this.groupBox.Size = new System.Drawing.Size(553, 51);
            this.groupBox.TabIndex = 0;
            this.groupBox.TabStop = false;
            this.groupBox.Text = "Current type of object to add";
            // 
            // wolfRadioButton
            // 
            this.wolfRadioButton.AutoSize = true;
            this.wolfRadioButton.Location = new System.Drawing.Point(378, 20);
            this.wolfRadioButton.Name = "wolfRadioButton";
            this.wolfRadioButton.Size = new System.Drawing.Size(47, 17);
            this.wolfRadioButton.TabIndex = 4;
            this.wolfRadioButton.TabStop = true;
            this.wolfRadioButton.Text = "Wolf";
            this.wolfRadioButton.UseVisualStyleBackColor = true;
            this.wolfRadioButton.CheckedChanged += new System.EventHandler(this.wolfRadioButton_CheckedChanged);
            // 
            // treeRadioButton
            // 
            this.treeRadioButton.AutoSize = true;
            this.treeRadioButton.Location = new System.Drawing.Point(286, 20);
            this.treeRadioButton.Name = "treeRadioButton";
            this.treeRadioButton.Size = new System.Drawing.Size(47, 17);
            this.treeRadioButton.TabIndex = 3;
            this.treeRadioButton.TabStop = true;
            this.treeRadioButton.Text = "Tree";
            this.treeRadioButton.UseVisualStyleBackColor = true;
            this.treeRadioButton.CheckedChanged += new System.EventHandler(this.treeRadioButton_CheckedChanged);
            // 
            // pigFoodRadioButton
            // 
            this.pigFoodRadioButton.AutoSize = true;
            this.pigFoodRadioButton.Location = new System.Drawing.Point(194, 20);
            this.pigFoodRadioButton.Name = "pigFoodRadioButton";
            this.pigFoodRadioButton.Size = new System.Drawing.Size(67, 17);
            this.pigFoodRadioButton.TabIndex = 2;
            this.pigFoodRadioButton.TabStop = true;
            this.pigFoodRadioButton.Text = "Pig Food";
            this.pigFoodRadioButton.UseVisualStyleBackColor = true;
            this.pigFoodRadioButton.CheckedChanged += new System.EventHandler(this.pigFoodRadioButton_CheckedChanged);
            // 
            // girlPigRadioButton
            // 
            this.girlPigRadioButton.AutoSize = true;
            this.girlPigRadioButton.Location = new System.Drawing.Point(102, 20);
            this.girlPigRadioButton.Name = "girlPigRadioButton";
            this.girlPigRadioButton.Size = new System.Drawing.Size(58, 17);
            this.girlPigRadioButton.TabIndex = 1;
            this.girlPigRadioButton.TabStop = true;
            this.girlPigRadioButton.Text = "Girl Pig";
            this.girlPigRadioButton.UseVisualStyleBackColor = true;
            this.girlPigRadioButton.CheckedChanged += new System.EventHandler(this.girlPigRadioButton_CheckedChanged);
            // 
            // boyPigRadioButton
            // 
            this.boyPigRadioButton.AutoSize = true;
            this.boyPigRadioButton.Location = new System.Drawing.Point(10, 20);
            this.boyPigRadioButton.Name = "boyPigRadioButton";
            this.boyPigRadioButton.Size = new System.Drawing.Size(61, 17);
            this.boyPigRadioButton.TabIndex = 0;
            this.boyPigRadioButton.TabStop = true;
            this.boyPigRadioButton.Text = "Boy Pig";
            this.boyPigRadioButton.UseVisualStyleBackColor = true;
            this.boyPigRadioButton.CheckedChanged += new System.EventHandler(this.boyPigRadioButton_CheckedChanged);
            // 
            // timer
            // 
            this.timer.Interval = 1000;
            this.timer.Tick += new System.EventHandler(this.timer_Tick);
            // 
            // PigWorldForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(684, 564);
            this.Controls.Add(this.groupBox);
            this.Controls.Add(this.currentTypeOfObjectPanel);
            this.Controls.Add(this.buttonPanel);
            this.Name = "PigWorldForm";
            this.Text = "Pig PigWorld";
            this.buttonPanel.ResumeLayout(false);
            this.buttonPanel.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.fasterSlowerTrackBar)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.demoNumber)).EndInit();
            this.groupBox.ResumeLayout(false);
            this.groupBox.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel buttonPanel;
        private System.Windows.Forms.Panel currentTypeOfObjectPanel;
        private System.Windows.Forms.Button quitButton;
        private System.Windows.Forms.Button setupDemoButton;
        private System.Windows.Forms.CheckBox showDebugInfoCheckBox;
        private System.Windows.Forms.NumericUpDown demoNumber;
        private System.Windows.Forms.Button stepButton;
        private System.Windows.Forms.Button stopButton;
        private System.Windows.Forms.Button startButton;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TrackBar fasterSlowerTrackBar;
        private System.Windows.Forms.Button removeAllButton;
        private System.Windows.Forms.Button removeWallsButton;
        private System.Windows.Forms.CheckBox enableRealAudioCheckBox;
        private System.Windows.Forms.GroupBox groupBox;
        private System.Windows.Forms.RadioButton wolfRadioButton;
        private System.Windows.Forms.RadioButton treeRadioButton;
        private System.Windows.Forms.RadioButton pigFoodRadioButton;
        private System.Windows.Forms.RadioButton girlPigRadioButton;
        private System.Windows.Forms.RadioButton boyPigRadioButton;
        private System.Windows.Forms.Timer timer;
    }
}

