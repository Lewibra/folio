using System;
using System.Collections.Generic;
using System.Device.Location;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PhoneApp1.Assets
{
    class timeTableHelper
    {
        public GeoCoordinate triggerLocation { get; set; }
        public string name { get; set; }
        private List<ScheduledItem>[] week = new List<ScheduledItem>[7];


        gps currentLocation;

        public timeTableHelper(string name)
        {
            this.name = name;
            for (int i = 0; i < 7; i++)
            {
                week[i] = new List<ScheduledItem>();
            }
        }

        public timeTableHelper(string name, GeoCoordinate triggerLocation)
        {
            this.name = name;
            this.triggerLocation = triggerLocation;

            for (int i = 0; i < 7; i++)
            {
                week[i] = new List<ScheduledItem>();
            }

            currentLocation = new gps(name);

            currentLocation.createGeofence(triggerLocation, 10000000.00);
            
        }


        public void addToTable(int day, ScheduledItem time)
        {
            
            week[day].Add(time);
            week[day] = week[day].OrderBy(e=> e.date.TimeOfDay).ToList();
        }

        public void removeFromTable(int day, ScheduledItem time)
        {
            week[day].Remove(time);
        }

        public List<ScheduledItem>[] getTimeTable()
        {
            return week;
        }

        public List<ScheduledItem> getDay(int day)
        {
            return week[day];
        }
        
    }

    class ScheduledItem
    {

        public DateTime date;
        public string description;
        public string name;
        public string dateName { get; set; }
        public ScheduledItem(DateTime date, string name, string description)
        {
            this.date = date;
            this.name = name;
            this.description = description;

            dateName = date.ToString("HH:mm:ss") + " " + name;
        }

    }
}
