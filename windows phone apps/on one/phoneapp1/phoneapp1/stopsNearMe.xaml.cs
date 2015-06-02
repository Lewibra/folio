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
using PhoneApp1.Assets;
using System.ComponentModel;
using System.Device.Location;
using System.Text;
using Microsoft.Phone.Maps.Services;
using System.Windows.Shapes;
using System.Windows.Media;
using Microsoft.Phone.Maps.Controls;
using System.Windows.Media.Animation;


namespace PhoneApp1
{
    public partial class Page6 : PhoneApplicationPage
    {
        string location;
        Stop stops;
        translinkJson tlink;
        List<Stop> tempBusStops;
        IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;
        gps currentLocation;
        double longitude;
        double latitude;
        GeoCoordinate geoPosition;
        string street;
        string houseNumber;


        string[] ids = new string[3];
        string[] nearbystops = new string[5];
        Stop[] stopDetails = new Stop[5];
        HttpClient client;
        public Page6()
        {   
            InitializeComponent();

            Canvas.SetZIndex(ContentPanel, 0);
            Canvas.SetZIndex(animationGrid, 2);
            Storyboard1.Begin();
            client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new Windows.Web.Http.Headers.HttpCredentialsHeaderValue("Basic", Base64Encode("tracy.lewis:3i!76&U0uc{&"));
            client.DefaultRequestHeaders.Accept.Add(new Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue("application/json"));
            gps newGps = new gps("newGPS");
            getNearestStop();
            

            //Array.Copy((Stop[])settings["busInfo"], 0, stopDetails, 0, 5);

        }


        public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }



        public async Task getNearestStop()
        {
            Geolocator myGeolocator = new Geolocator();

            if (myGeolocator.LocationStatus == PositionStatus.Disabled)
            {
                MessageBoxResult result = MessageBox.Show("Please turn your GPS on to use this feature", "Sorry!", MessageBoxButton.OKCancel);
            }
            else {

            Geoposition myGeoposition = await myGeolocator.GetGeopositionAsync();
            Geocoordinate myGeocoordinate = myGeoposition.Coordinate;
            GeoCoordinate myGeoCoordinate = ConvertGeocoordinate(myGeocoordinate);

            var query = new ReverseGeocodeQuery() { GeoCoordinate = myGeoCoordinate };
            
            //var geoCodeResults = await query.GetMapLocationsAsync();
            //while(geoCodeResults.Count == 0)
            //{
            //    geoCodeResults = await query.GetMapLocationsAsync();
            //}
           // var address = geoCodeResults.First().Information.Address;
           // houseNumber = address.HouseNumber;
           // street = address.Street;
           // string district = address.District;



            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/suggest?input=" + query.GeoCoordinate.Latitude.ToString() + ", " + query.GeoCoordinate.Longitude.ToString() + "&maxResults=3&filter=0"));

            if (response.IsSuccessStatusCode)
            {

                string json = await response.Content.ReadAsStringAsync();

                Debug.WriteLine("API OK: " + json);


                try
                {
                    rootSuggestions deserialized = JsonConvert.DeserializeObject<rootSuggestions>(json);

                    ids[0] = deserialized.Suggestions[0].Id;
                    ids[1] = deserialized.Suggestions[1].Id;
                    ids[2] = deserialized.Suggestions[2].Id;


                }
                catch
                {

                }

            }
            else
            {
                Debug.WriteLine("API ERROR: " + await response.Content.ReadAsStringAsync());
            }


            response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/stops-nearby/" + ids[0] + "?radiusM=2000&useWalkingDistance=true&maxResults=5"));


            if (response.IsSuccessStatusCode)
            {

                string json = await response.Content.ReadAsStringAsync();

                Debug.WriteLine("API OK: " + json);


                try
                {
                    nearStopClass deserialized = JsonConvert.DeserializeObject<nearStopClass>(json);


                    for (int i = 0; i < 5; i++)
                    {
                        nearbystops[i] = deserialized.NearbyStops[i].StopId;
                    }

                }
                catch
                {

                }

            }
            else
            {
                Debug.WriteLine("API ERROR: " + await response.Content.ReadAsStringAsync());
            }

            for (int i = 0; i < 5; i++)
            {
                response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/stops?ids=" + nearbystops[i]));

                if (response.IsSuccessStatusCode)
                {

                    string json = await response.Content.ReadAsStringAsync();

                    Debug.WriteLine("API OK: " + json);


                    try
                    {
                        stopRootObj deserialized = JsonConvert.DeserializeObject<stopRootObj>(json);
                        stopDetails[i] = deserialized.Stops[0];



                    }
                    catch
                    {

                    }

                }
                else
                {
                    Debug.WriteLine("API ERROR: " + await response.Content.ReadAsStringAsync());
                }

            }

            Stop[] tempArray = stopDetails.Distinct().ToArray();
            //one.Content = stopDetails[0].Description;

            await StoryboardExtensions.BeginAsync(Storyboard2);
            await StoryboardExtensions.BeginAsync(Storyboard3);


            
            //this.listBlock.Items
            //listBlock.DisplayMemberPath = "Description";
            foreach (Stop s in tempArray)
            {
                if (s != null)
                    listBlock.Items.Add(s);
            }
            
            listBlock.UpdateLayout();



            
            Dispatcher.BeginInvoke(() => { Storyboard1.Stop();
            animationGrid.Visibility = Visibility.Collapsed;
            });






            }    

        }

       


        public static GeoCoordinate ConvertGeocoordinate(Geocoordinate geocoordinate)
        {
            return new GeoCoordinate
                (
                Math.Round(geocoordinate.Point.Position.Latitude, 4),
                Math.Round(geocoordinate.Point.Position.Longitude, 4),
                geocoordinate.Altitude ?? Double.NaN,
                geocoordinate.Accuracy,
                geocoordinate.AltitudeAccuracy ?? Double.NaN,
                geocoordinate.Speed ?? Double.NaN,
                geocoordinate.Heading ?? Double.NaN
                );
        }


        private string FormatAddress(MapAddress address)
        {
            StringBuilder sb = new StringBuilder();

            sb.Append(address.HouseNumber).Append(", ")
                .Append(address.Street);


            return sb.ToString();
        }

        private void listBlock_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            
            //listBlock.SelectedItem
            var stop = listBlock.SelectedItem as Stop;
            contentView.Visibility = Visibility.Visible;
            //worldMap.Visibility = Visibility.Visible;

            worldMap.SetView(new GeoCoordinate(stop.Position.Lat, stop.Position.Lng), 15.0);
            markOnMap(new GeoCoordinate(stop.Position.Lat, stop.Position.Lng));

            //secondGrid.Margin = new Thickness(0, 500,0,0);
            stopBox.TextWrapping = TextWrapping.Wrap;
            stopBox.Text = stop.LocationDescription + "\nRoutes: ";
            foreach (PhoneApp1.Assets.Route s in stop.Routes)
            {
               stopBox.Text += s.Code + " ";
            }
            




            
            

        }

        private void markOnMap(GeoCoordinate geo)
        {
            // Create a small circle to mark the current location.
            Ellipse myCircle = new Ellipse();
            myCircle.Fill = new SolidColorBrush(Colors.Blue);
            myCircle.Height = 20;
            myCircle.Width = 20;
            myCircle.Opacity = 50;


            //Grid tempGrid = new Grid();
            //tempGrid = pushPin;


            // Create a MapOverlay to contain the circle.
            MapOverlay myLocationOverlay = new MapOverlay();
            myLocationOverlay.Content = myCircle;
            myLocationOverlay.PositionOrigin = new Point(0.5, 0.5);
            myLocationOverlay.GeoCoordinate = geo;

            // Create a MapLayer to contain the MapOverlay.
            MapLayer myLocationLayer = new MapLayer();
            myLocationLayer.Add(myLocationOverlay);

            // Add the MapLayer to the Map.
            worldMap.Layers.Add(myLocationLayer);

        }

        private void worldMap_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {

        }

    }

    public static class StoryboardExtensions
    {
        public static Task BeginAsync(this Storyboard storyboard)
        {
            System.Threading.Tasks.TaskCompletionSource<bool> tcs = new TaskCompletionSource<bool>();
            if (storyboard == null)
                tcs.SetException(new ArgumentNullException());
            else
            {
                EventHandler onComplete = null;
                onComplete = (s, e) =>
                {
                    storyboard.Completed -= onComplete;
                    tcs.SetResult(true);
                };
                storyboard.Completed += onComplete;
                storyboard.Begin();
            }
            return tcs.Task;
        }
    }
}