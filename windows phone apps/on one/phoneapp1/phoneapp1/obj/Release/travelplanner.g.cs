﻿#pragma checksum "C:\Users\lewis\Desktop\On One\PhoneApp1\PhoneApp1\travelplanner.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "56F5FEE8514BF74ABCA8FBD096498F28"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34014
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using Microsoft.Phone.Controls;
using System;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Automation.Peers;
using System.Windows.Automation.Provider;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Resources;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace PhoneApp1 {
    
    
    public partial class travelplanner : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Media.Animation.Storyboard Storyboard1;
        
        internal System.Windows.Media.Animation.Storyboard Storyboard2;
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.Canvas animationGrid;
        
        internal System.Windows.Shapes.Rectangle greyWashover;
        
        internal System.Windows.Shapes.Rectangle rectangle;
        
        internal System.Windows.Shapes.Rectangle rectangle1;
        
        internal System.Windows.Shapes.Rectangle rectangle2;
        
        internal System.Windows.Shapes.Rectangle rectangle3;
        
        internal System.Windows.Shapes.Rectangle rectangle4;
        
        internal System.Windows.Shapes.Rectangle rectangle5;
        
        internal System.Windows.Shapes.Rectangle rectangle6;
        
        internal System.Windows.Shapes.Rectangle rectangle7;
        
        internal System.Windows.Controls.Grid ContentPanel;
        
        internal Microsoft.Phone.Controls.PhoneTextBox departure;
        
        internal Microsoft.Phone.Controls.PhoneTextBox destination;
        
        internal Microsoft.Phone.Controls.DatePicker beginDatePicker;
        
        internal Microsoft.Phone.Controls.TimePicker beginTimePicker;
        
        internal Microsoft.Phone.Controls.Pivot phonePivot;
        
        internal System.Windows.Controls.Button submitButton;
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Windows.Application.LoadComponent(this, new System.Uri("/PhoneApp1;component/travelplanner.xaml", System.UriKind.Relative));
            this.Storyboard1 = ((System.Windows.Media.Animation.Storyboard)(this.FindName("Storyboard1")));
            this.Storyboard2 = ((System.Windows.Media.Animation.Storyboard)(this.FindName("Storyboard2")));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.animationGrid = ((System.Windows.Controls.Canvas)(this.FindName("animationGrid")));
            this.greyWashover = ((System.Windows.Shapes.Rectangle)(this.FindName("greyWashover")));
            this.rectangle = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle")));
            this.rectangle1 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle1")));
            this.rectangle2 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle2")));
            this.rectangle3 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle3")));
            this.rectangle4 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle4")));
            this.rectangle5 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle5")));
            this.rectangle6 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle6")));
            this.rectangle7 = ((System.Windows.Shapes.Rectangle)(this.FindName("rectangle7")));
            this.ContentPanel = ((System.Windows.Controls.Grid)(this.FindName("ContentPanel")));
            this.departure = ((Microsoft.Phone.Controls.PhoneTextBox)(this.FindName("departure")));
            this.destination = ((Microsoft.Phone.Controls.PhoneTextBox)(this.FindName("destination")));
            this.beginDatePicker = ((Microsoft.Phone.Controls.DatePicker)(this.FindName("beginDatePicker")));
            this.beginTimePicker = ((Microsoft.Phone.Controls.TimePicker)(this.FindName("beginTimePicker")));
            this.phonePivot = ((Microsoft.Phone.Controls.Pivot)(this.FindName("phonePivot")));
            this.submitButton = ((System.Windows.Controls.Button)(this.FindName("submitButton")));
        }
    }
}

