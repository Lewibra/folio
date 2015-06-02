using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Windows.Web.Http;
using System.Threading.Tasks;
using PhoneApp1.Assets;
using Newtonsoft.Json;
using System.Diagnostics;
using System.Windows.Media.Imaging;

namespace PhoneApp1
{
    public partial class travelplanner : PhoneApplicationPage
    {
        HttpClient client;
        string[] ids = new string[3];
        string[] destinationIds = new string[3];
        DateTime date;
        DateTime time;
        DateTime timeDate;
        string maxwalkingDistance = "2000";
        string startTime;

        string[] descriptions = new string[2];

        double finalCost;
        int None = 0, Bus = 2, Ferry = 4, Train = 8, Walk = 16, Tram = 32;

        List<Leg> instructions = new List<Leg>();
        public travelplanner()
        {
            InitializeComponent();
            Canvas.SetZIndex(ContentPanel, 0);
            Canvas.SetZIndex(animationGrid, 2);

            client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new Windows.Web.Http.Headers.HttpCredentialsHeaderValue("Basic", Base64Encode("tracy.lewis:3i!76&U0uc{&"));
            client.DefaultRequestHeaders.Accept.Add(new Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue("application/json"));
            finalCost = 0.0;
        }






        public async Task getStops()
        {
            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/suggest?input=" + departure.Text + "&maxResults=2&filter=0"));

            if (response.IsSuccessStatusCode)
            {
                string json = await response.Content.ReadAsStringAsync();
                Debug.WriteLine("API OK: " + json);
                try
                {
                    rootSuggestions deserialized = JsonConvert.DeserializeObject<rootSuggestions>(json);
                    ids[0] = deserialized.Suggestions[0].Id;
                    descriptions[0] = deserialized.Suggestions[0].Description;

                }
                catch
                {
                    MessageBoxResult result = MessageBox.Show("Place of departure not found, please try again", "Sorry!", MessageBoxButton.OKCancel); 
                }
            }
            else
            {
                MessageBoxResult result = MessageBox.Show("Place of departure not found, please try again", "Sorry!", MessageBoxButton.OKCancel); 
            }

            response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/suggest?input=" + destination.Text + "&maxResults=2&filter=0"));
            if (response.IsSuccessStatusCode)
            {
                string json = await response.Content.ReadAsStringAsync();
                Debug.WriteLine("API OK: " + json);
                try
                {
                    rootSuggestions deserialized = JsonConvert.DeserializeObject<rootSuggestions>(json);
                    destinationIds[0] = deserialized.Suggestions[0].Id;
                    descriptions[1] = deserialized.Suggestions[0].Description;

                }
                catch
                {
                    MessageBoxResult result = MessageBox.Show("Place of arrival not found, please try again", "Sorry!", MessageBoxButton.OKCancel); 
                }
            }
            else
            {
                MessageBoxResult result = MessageBox.Show("Place of arrival not found, please try again", "Sorry!", MessageBoxButton.OKCancel); 
            }

            response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/travel/rest/plan/"+ids[0]+"/"+destinationIds[0]+"?timeMode=0&at=" + startTime + "&walkSpeed=1&maximumWalkingDistanceM=" + maxwalkingDistance+"&api_key=special-key"));
            if (response.IsSuccessStatusCode)
            {
                string json = await response.Content.ReadAsStringAsync();
                Debug.WriteLine("API OK: " + json);
                try
                {
                    travelplan deserialized = JsonConvert.DeserializeObject<travelplan>(json);
                    int routes = 1;
                    foreach (Itinerary it in deserialized.TravelOptions.Itineraries)
                    {
                        finalCost = 0.0;

                        string tempCost = "";
                        string itineraryString = "";

                        foreach (Fare1 d in it.Fare.Fares)
                        {
                            tempCost += d.Name + ": " + d.Price.ToString("C0") + "\n";
                        }

                       // MessageBoxResult result = MessageBox.Show("Individual Prices: \n" + tempCost, "Costs", MessageBoxButton.OKCancel);
                        StackPanel g = new StackPanel();

                        TextBlock te = new TextBlock();
                        te.Text = descriptions[0] + " to " + descriptions[1] + "\n\n";
                        te.TextWrapping = TextWrapping.Wrap;
                        te.FontSize = 20;

                        g.Children.Add(te);

                        foreach (Leg l in it.Legs)
                        {
                            instructions.Add(l);
                            itineraryString += l.Instruction + "\n \n";
                            TextBlock tempTextBlock = new TextBlock();
                            tempTextBlock.Text = "\n" + l.Instruction + "\n\n";
                            tempTextBlock.TextWrapping = TextWrapping.Wrap;

                            Image img = new Image();
 


                            if (l.TravelMode == Bus)
                            {
                                img.Source = new BitmapImage(new Uri("/Assets/bus.png", UriKind.Relative));
                            }else if (l.TravelMode == Walk)
                            {
                                img.Source = new BitmapImage(new Uri("/Assets/walk.png", UriKind.Relative));
                            }else if (l.TravelMode == Train)
                            {
                                img.Source = new BitmapImage(new Uri("/Assets/train.png", UriKind.Relative));
                            }



                            if (l.TravelMode != 0 || l.TravelMode != null)
                                img.Height = 70;
                                img.Width = 70;
                                g.Children.Add(img);

                            g.Children.Add(tempTextBlock);

                        }

                        //itineraryString + tempCost;

                        PivotItem item = new PivotItem();
                        item.Header = "Route " + routes.ToString();
                        item.Content = g;
                        
                        //item.Content = itineraryString + "\n\n\n" + tempCost;
                        
                        
                        phonePivot.Items.Add(item);
                        routes++;
                    }
                    phonePivot.Visibility = Visibility.Visible;
                    
                }
                catch
                {
                    MessageBoxResult result = MessageBox.Show("You have entered the date or time incorrectly, or you have not network access", "Sorry!", MessageBoxButton.OKCancel); 
                }
            }
            else
            {
                MessageBoxResult result = MessageBox.Show("ou have entered the date or time incorrectly, or you have not network access", "Sorry!", MessageBoxButton.OKCancel); 
            }

            await StoryboardExtensions.BeginAsync(Storyboard2);


            Dispatcher.BeginInvoke(() =>
            {
                Storyboard1.Stop();
                animationGrid.Visibility = Visibility.Collapsed;
            });
        }









        public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }

        private void submitButton_Click(object sender, RoutedEventArgs e)
        {
            date = (DateTime)beginDatePicker.Value;
            time = (DateTime)beginTimePicker.Value;
            timeDate = date + time.TimeOfDay;

            startTime = timeDate.ToString("MM-dd-yyyy HH:mm:ss");
            animationGrid.Visibility = Visibility.Visible;
            Storyboard1.Begin();
            getStops();


        }
    }

    
public class travelplan
{
public Traveloptions TravelOptions { get; set; }
}

public class Traveloptions
{
public Itinerary[] Itineraries { get; set; }
public bool SearchIsInFlexiLinkArea { get; set; }
}

public class Itinerary
{
public int DurationMins { get; set; }
public DateTime EndTime { get; set; }
public Fare Fare { get; set; }
public DateTime FirstDepartureTime { get; set; }
public DateTime LastArrivalTime { get; set; }
public Leg[] Legs { get; set; }
public DateTime StartTime { get; set; }
public int Transfers { get; set; }
}

public class Fare
{
public Fare1[] Fares { get; set; }
public int MaximumZone { get; set; }
public int MinimumZone { get; set; }
public int TotalZones { get; set; }
}

public class Fare1
{
public string Name { get; set; }
public float Price { get; set; }
}

public class Leg
{
public DateTime ArrivalTime { get; set; }
public DateTime DepartureTime { get; set; }
public int DistanceM { get; set; }
public int DurationMins { get; set; }
public string FromStopId { get; set; }
public string Instruction { get; set; }
public string Polyline { get; set; }
public Route Route { get; set; }
public bool SameVehicleContinuation { get; set; }
public string ToStopId { get; set; }
public int TravelMode { get; set; }
public Tripdetails TripDetails { get; set; }
}



public class Tripdetails
{
public DateTime[] ArrivalTimes { get; set; }
public bool ContainsStartEndStopsOnly { get; set; }
public DateTime[] DepartureTimes { get; set; }
public string Id { get; set; }
public Route1 Route { get; set; }
public string[] StopIds { get; set; }
public string VehicleDisplay { get; set; }
}



}