using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using System.Device.Location;
using Microsoft.Phone.Maps.Toolkit;
using Microsoft.Phone.Maps.Controls;
using System.IO.IsolatedStorage;
using PhoneApp1.Assets;
using Microsoft.Phone.Maps.Services;
using Windows.Devices.Geolocation;
using System.Windows.Shapes;
using System.Windows.Media;

namespace PhoneApp1
{
    public partial class createTimeTable : PhoneApplicationPage
    {
        GeoCoordinate asd;
        bool locationBased = false;
        public createTimeTable()
        {
            InitializeComponent();



        }

        private void loactionTrigger_Checked(object sender, RoutedEventArgs e)
        {
            pan2.Visibility = Visibility.Visible;
            locationBased = true;
            //fullPan.DefaultItem = fullPan.Items[Convert.ToInt32(1)];

        }

        private void loactionTrigger_Unchecked(object sender, RoutedEventArgs e)
        {
            locationBased = false;
            pan2.Visibility = Visibility.Collapsed;
            

        }


        private void worldMap_Tap(object sender, System.Windows.Input.GestureEventArgs e)
        {
            worldMap.Layers.Clear();
            asd = this.worldMap.ConvertViewportPointToGeoCoordinate(e.GetPosition(this.worldMap));
            Pushpin pin = new Pushpin();

            pin.GeoCoordinate = asd;

            MapLayer layer = new MapLayer();
            MapOverlay overlay = new MapOverlay();

            overlay.Content = pin;
            overlay.GeoCoordinate = asd;

            layer.Add(overlay);

            worldMap.Layers.Add(layer);
        }

        private void ApplicationBarIconButton_Click(object sender, EventArgs e)
        {
            IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

            List<timeTableHelper> timeTables = (List<timeTableHelper>)settings["timeTableListKey"];
            timeTableHelper temp;
            if (locationBased)
                temp = new timeTableHelper(titleTextBox.Text, asd);
            else
                temp = new timeTableHelper(titleTextBox.Text);
            timeTables.Add(temp);
            settings["timeTableListKey"] = timeTables;
            NavigationService.Navigate(new Uri("/selectTimeTable.xaml", UriKind.RelativeOrAbsolute));

        }

        private void fullPan_Loaded(object sender, RoutedEventArgs e)
        {

        }

        private async void Button_Click(object sender, RoutedEventArgs e)
        {

            GeocodeQuery query = new GeocodeQuery();
            query.GeoCoordinate = new GeoCoordinate(); //position.Coordinate.ToGeoCoordinate();
            query.SearchTerm = mapSearch.Text;
            
            IList<MapLocation> locations = await query.GetMapLocationsAsync();

            if (locations.Count != 0)
            {
                mapSearch.Text = "Loading...";
                // Create a small circle to mark the current location.
                Ellipse myCircle = new Ellipse();
                myCircle.Fill = new SolidColorBrush(Colors.Blue);
                myCircle.Height = 20;
                myCircle.Width = 20;
                myCircle.Opacity = 50;

                // Create a MapOverlay to contain the circle.
                MapOverlay myLocationOverlay = new MapOverlay();
                myLocationOverlay.Content = myCircle;
                myLocationOverlay.PositionOrigin = new Point(0.5, 0.5);
                myLocationOverlay.GeoCoordinate = locations[0].GeoCoordinate;

                // Create a MapLayer to contain the MapOverlay.
                MapLayer myLocationLayer = new MapLayer();
                myLocationLayer.Add(myLocationOverlay);

                // Add the MapLayer to the Map.
                worldMap.Layers.Add(myLocationLayer);

                worldMap.SetView(locations[0].GeoCoordinate, 15.0);
                mapSearch.Text = query.SearchTerm;
                MessageBoxResult result = MessageBox.Show("Tap on the map to set a location, the timetable you are creating will trigger around this area",
                "GPS", MessageBoxButton.OKCancel);
            }
            else
            {
                MessageBoxResult result = MessageBox.Show("Address could not be found, please try again",
                                "GPS", MessageBoxButton.OKCancel);
                mapSearch.Text = "";
            }

        }



    }
}