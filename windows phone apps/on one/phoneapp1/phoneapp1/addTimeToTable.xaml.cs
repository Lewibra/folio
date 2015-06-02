using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using PhoneApp1.Assets;
using System.IO.IsolatedStorage;

namespace PhoneApp1
{
    public partial class Page5 : PhoneApplicationPage
    {
        string name;
        string description;
        DateTime begin;
        DateTime end;
        int day;
        timeTableHelper table;

        ScheduledItem item;

        public Page5()
        {
            InitializeComponent();
            table = PhoneApplicationService.Current.State["param"] as timeTableHelper;

        }

        private void addTime_event(object sender, EventArgs e)
        {
            
            begin = (DateTime)beginTimePicker.Value;
            end = (DateTime)expirationTimePicker.Value;
            day = dayList.SelectedIndex;

            item = new ScheduledItem(begin, titleTextBox.Text, contentTextBox.Text);

            table.addToTable(day, item);
            PhoneApplicationService.Current.State["param"] = table;
            //timeTables.Find(x => x.name == table.name) = table;

            NavigationService.Navigate(new Uri("/PanoramaPage1.xaml", UriKind.Relative));

        }
    }
}