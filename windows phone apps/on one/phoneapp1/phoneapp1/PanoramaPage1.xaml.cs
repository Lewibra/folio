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
using System.ComponentModel;
using System.IO.IsolatedStorage;

namespace PhoneApp1
{
    public partial class PanoramaPage1 : PhoneApplicationPage
    {
        private int dayInt;
        private string day = System.DateTime.Now.DayOfWeek.ToString();
        timeTableHelper table;
        int mon = 0;
        int tues = 1;
        int wed = 2;
        int thurs = 3;
        int fri = 4;
        int sat = 5;
        int sun = 6;
        List<timeTableHelper> timeTables;
        IsolatedStorageSettings settings;
        public PanoramaPage1()
        {
            InitializeComponent();
            settings = IsolatedStorageSettings.ApplicationSettings;
            timeTables = (List<timeTableHelper>)settings["timeTableListKey"];
            calculateTable();


            
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            

            switch (day)
            {
                case "Monday":
                    dayInt = 0;
                    break;
                case "Tuesday":
                    dayInt = 1;
                    break;
                case "Wednesday":
                    dayInt = 2;
                    break;
                case "Thursday":
                    dayInt = 3;
                    break;
                case "Friday":
                    dayInt = 4;
                    break;
                case "Saturday":
                    dayInt = 5;
                    break;
                case "Sunday":
                    dayInt = 6;
                    break;
                default:
                    dayInt = 0;
                    break;
            }


            myPanorama.DefaultItem = myPanorama.Items[Convert.ToInt32(dayInt)];

            
            base.OnNavigatedTo(e);
        }

        private void calculateTable()
        {
            table = PhoneApplicationService.Current.State["param"] as timeTableHelper;
            monday.DisplayMemberPath = "dateName";
            tuesday.DisplayMemberPath = "dateName";
            wedsnesday.DisplayMemberPath = "dateName";
            thursday.DisplayMemberPath = "dateName";
            friday.DisplayMemberPath = "dateName";
            saturday.DisplayMemberPath = "dateName";
            sunday.DisplayMemberPath = "dateName";
            
            if ((timeTables.Find(x => x.name == table.name).getDay(mon) != null))
            {
                foreach (ScheduledItem t in (timeTables.Find(x => x.name == table.name).getDay(mon)))
                {
                    
                    monday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(tues) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(tues))
                {
                    tuesday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(wed) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(wed))
                {
                    wedsnesday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(thurs) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(thurs))
                {
                    thursday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(fri) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(fri))
                {
                    friday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(sat) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(sat))
                {
                    saturday.Items.Add(t);

                }
            }
            if (timeTables.Find(x => x.name == table.name).getDay(sun) != null)
            {
                foreach (ScheduledItem t in timeTables.Find(x => x.name == table.name).getDay(sun))
                {
                    sunday.Items.Add(t);

                }
            }

            settings["timeTableListKey"] = timeTables;


        }

        public void ApplicationBarAddButton_Click(object sender, EventArgs e)
        {
            PhoneApplicationService.Current.State["param"] = table;
            NavigationService.Navigate(new Uri("/addTimeToTable.xaml", UriKind.Relative));

        }

        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            NavigationService.Navigate(new Uri("/selectTimeTable.xaml", UriKind.Relative));
        }

        private void all_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }
    }
}