using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.IO.IsolatedStorage;

namespace PhoneApp1.Assets
{

    public partial class Page1 : PhoneApplicationPage
    {
        IsolatedStorageSettings settings;
        string notes;
        public Page1()
        {
            InitializeComponent();
            settings = IsolatedStorageSettings.ApplicationSettings;

            if (!settings.Contains("textBoxKey"))
            {
                notes = "";
                settings.Add("textBoxKey", notes);
                settings.Save();
            }
            notes = (string)settings["textBoxKey"];
            textB.Text = notes;
        }

        private void textB_TextInputUpdate(object sender, System.Windows.Input.TextCompositionEventArgs e)
        {
            settings["textBoxKey"] = notes;
        }

        private void textB_KeyUp(object sender, System.Windows.Input.KeyEventArgs e)
        {
            notes = textB.Text;
            settings["textBoxKey"] = notes;
        }
    }
}