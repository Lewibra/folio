using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Threading.Tasks;
using Windows.Devices.Geolocation;
using Windows.Devices.Geolocation.Geofencing;
using System.IO.IsolatedStorage;
using Windows.UI.Core;
using System.Diagnostics;
using Windows.ApplicationModel.Background;
using Windows.Web.Http;
using Newtonsoft.Json;
using System.Device.Location;
using Microsoft.Phone.Maps.Services;

namespace PhoneApp1.Assets
{
    public partial class gps : PhoneApplicationPage
    {

        private string city;
        private string state;
        private string postCode;

        private string street;
        private string houseNo;


        string name;
        CoreDispatcher dispatcher;

        GeofenceMonitor _monitor = GeofenceMonitor.Current;

        GeoCoordinate MyCoordinate;

        private ReverseGeocodeQuery MyReverseGeocodeQuery = null;

        public gps(string name) {
            this.name = name;


            getLocations();
            

            


        }

        public double getCurrentLat()
        {
            return MyCoordinate.Latitude;
        }

        public double getCurrentLongitude()
        {
            return MyCoordinate.Longitude;
        }


        public void createGeofence(GeoCoordinate geo, double radius){
            _monitor.GeofenceStateChanged += MonitorOnGeofenceStateChanged;

            double latitude = geo.Latitude;
            double longitude = geo.Longitude;

            BasicGeoposition basicPos = new BasicGeoposition { Latitude = latitude, Longitude = longitude };
            Geofence fence = new Geofence("location", new Geocircle(basicPos, radius));

            try
            {
                _monitor.Geofences.Add(fence);
            }
            catch (Exception)
            {

            }

        }

        public void MonitorOnGeofenceStateChanged(GeofenceMonitor sender, object args)
        {
            var fences = sender.ReadReports();


            Dispatcher.BeginInvoke(new Action(() =>
            {
                foreach (var report in fences)
                {
                    if (report.Geofence.Id != "location")
                    {
                        continue;
                    }


                    if (report.NewState == GeofenceState.Entered)
                    {
                        MessageBoxResult result =
                        MessageBox.Show("you have entered " + name + " do you want to view your timetable?",
                        "Timetables",
                        MessageBoxButton.OKCancel);

                        if (result == MessageBoxResult.OK)
                        {

                            (Application.Current.RootVisual as PhoneApplicationFrame).Navigate(new Uri("/selectTimeTable.xaml", UriKind.Relative));

                        }
                        

                    }
                }
            }));

        }

        public async void getLocations()
        {


            if ((bool)IsolatedStorageSettings.ApplicationSettings["LocationConsent"] != true)
            {
                // The user has opted out of Location.
                return;
            }

            Geolocator geolocator = new Geolocator();
            geolocator.DesiredAccuracyInMeters = 50;

            try
            {
                Geoposition geoposition = await geolocator.GetGeopositionAsync(
                    maximumAge: TimeSpan.FromMinutes(5),
                    timeout: TimeSpan.FromSeconds(10)
                    );


                MyCoordinate = new GeoCoordinate(geoposition.Coordinate.Point.Position.Latitude, geoposition.Coordinate.Point.Position.Longitude);

                if (MyReverseGeocodeQuery == null || !MyReverseGeocodeQuery.IsBusy)
                {
                    MyReverseGeocodeQuery = new ReverseGeocodeQuery();
                    MyReverseGeocodeQuery.GeoCoordinate = new GeoCoordinate(MyCoordinate.Latitude, MyCoordinate.Longitude);
                    MyReverseGeocodeQuery.QueryCompleted += ReverseGeocodeQuery_QueryCompleted;
                    MyReverseGeocodeQuery.QueryAsync();
                    
                }

                
            }
            catch (Exception ex)
            {
                if ((uint)ex.HResult == 0x80004004)
                {
                    // the application does not have the right capability or the location master switch is off
                    
                }
                //else
                {
                    // something else happened acquring the location
                }
            }

        }


        private void ReverseGeocodeQuery_QueryCompleted(object sender, QueryCompletedEventArgs<IList<MapLocation>> e)
        {

            if (e.Error == null)
            {

                if (e.Result.Count > 0)
                {
                    

                    MapAddress address = e.Result[0].Information.Address;

                    city = address.City;
                    state = address.State;
                    postCode = address.PostalCode;
                    street = address.Street;
                    houseNo = address.HouseNumber;
                    //MessageBox.Show(street);

                }
            }
        }

        public static async Task GetLocationCapabilities()
        {
            try
            {
                var geolocator = new Geolocator();
                await geolocator.GetGeopositionAsync();
                var backgroundAccessStatus = await BackgroundExecutionManager.RequestAccessAsync();
                Debug.WriteLine("background access status" + backgroundAccessStatus);
            }
            catch (UnauthorizedAccessException e)
            {
                Debug.WriteLine(e);
            }
            catch (TaskCanceledException e)
            {
                Debug.WriteLine(e);
            }
        }


        public String getStreet()
        {
            return street;

        }



    private async Task Init_BackgroundGeofence()
    {
        var backgroundAccessStatus =
            await BackgroundExecutionManager.RequestAccessAsync();
        var geofenceTaskBuilder = new BackgroundTaskBuilder
        {
            Name = "GeofenceBackgroundTask",
            TaskEntryPoint = "myTask.Class1"
        };
 
        var trigger = new LocationTrigger(LocationTriggerType.Geofence);
        geofenceTaskBuilder.SetTrigger(trigger);
        var geofenceTask = geofenceTaskBuilder.Register();
        geofenceTask.Completed += (sender, args) =>
        {
            //TODO: add foreground code if needed
        };
    }



    }
}
