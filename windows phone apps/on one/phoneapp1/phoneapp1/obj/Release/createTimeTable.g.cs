﻿#pragma checksum "C:\Users\lewis\Desktop\On One\PhoneApp1\PhoneApp1\createTimeTable.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "71844B72CE809D63A58AEB96E71F8341"
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
using Microsoft.Phone.Maps.Controls;
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
    
    
    public partial class createTimeTable : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.Grid ContentPanel;
        
        internal Microsoft.Phone.Controls.Panorama fullPan;
        
        internal Microsoft.Phone.Controls.PanoramaItem pan1;
        
        internal System.Windows.Controls.TextBlock titleLabel;
        
        internal System.Windows.Controls.TextBox titleTextBox;
        
        internal System.Windows.Controls.CheckBox loactionTrigger;
        
        internal Microsoft.Phone.Controls.PanoramaItem pan2;
        
        internal Microsoft.Phone.Controls.PhoneTextBox mapSearch;
        
        internal Microsoft.Phone.Maps.Controls.Map worldMap;
        
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
            System.Windows.Application.LoadComponent(this, new System.Uri("/PhoneApp1;component/createTimeTable.xaml", System.UriKind.Relative));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.ContentPanel = ((System.Windows.Controls.Grid)(this.FindName("ContentPanel")));
            this.fullPan = ((Microsoft.Phone.Controls.Panorama)(this.FindName("fullPan")));
            this.pan1 = ((Microsoft.Phone.Controls.PanoramaItem)(this.FindName("pan1")));
            this.titleLabel = ((System.Windows.Controls.TextBlock)(this.FindName("titleLabel")));
            this.titleTextBox = ((System.Windows.Controls.TextBox)(this.FindName("titleTextBox")));
            this.loactionTrigger = ((System.Windows.Controls.CheckBox)(this.FindName("loactionTrigger")));
            this.pan2 = ((Microsoft.Phone.Controls.PanoramaItem)(this.FindName("pan2")));
            this.mapSearch = ((Microsoft.Phone.Controls.PhoneTextBox)(this.FindName("mapSearch")));
            this.worldMap = ((Microsoft.Phone.Maps.Controls.Map)(this.FindName("worldMap")));
        }
    }
}

