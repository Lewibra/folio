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
using System.Diagnostics;
using PhoneApp1.Assets;
using Newtonsoft.Json;

namespace PhoneApp1
{
    public partial class busTimeTable : PhoneApplicationPage
    {
        HttpClient client;
        string date = "";
        List<List<Trip>> trippinTrips = new List<List<Trip>>();
        string stops = "";
        TimeSpan beginTime;
        string beginTimeString = "";
        TimeSpan concludingTime;
        string concludingTimeString = "";
        public busTimeTable()
        {
            InitializeComponent();
            client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new Windows.Web.Http.Headers.HttpCredentialsHeaderValue("Basic", Base64Encode("tracy.lewis:3i!76&U0uc{&"));
            client.DefaultRequestHeaders.Accept.Add(new Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue("application/json"));

            endTime.Value = DateTime.Now.AddHours(1.0);

            


        }

        public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }


        public async Task getBusTimeTable(string route)
        {
            animationGrid.Visibility = Visibility.Visible;
            Storyboard1.Begin();
            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/network/rest/route-timetables?routeCodes="+route+"&vehicleType=2&date="+date+"&filterToStartEndStops=false"));

            if (response.IsSuccessStatusCode)
            {

                string json = await response.Content.ReadAsStringAsync();

                Debug.WriteLine("API OK: " + json);


                try
                {
                    routeTable deserialized = JsonConvert.DeserializeObject<routeTable>(json);
                    List<Routetimetable> tempList = new List<Routetimetable>();
                    
                    foreach (Routetimetable r in deserialized.RouteTimetables)
                    {
                        trippinTrips.Add(r.Trips.ToList());
                        
                    }

                    

                    foreach (string s in trippinTrips[0][0].StopIds)
                    {
                        stops += s + ",";

                    }                  
                }
                catch
                {
                    MessageBoxResult result = MessageBox.Show("Please enter a valid bus number", "Warning", MessageBoxButton.OKCancel);
                }

            }
            else
            {
                MessageBoxResult result = MessageBox.Show("Please enter a valid bus number", "Warning", MessageBoxButton.OKCancel);
                Debug.WriteLine("API ERROR: " + await response.Content.ReadAsStringAsync());
            }

            response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/stops?ids="+stops));
            if (response.IsSuccessStatusCode)
            {

                string json = await response.Content.ReadAsStringAsync();

                Debug.WriteLine("API OK: " + json);


                try
                {
                    stopRootObj deserialized = JsonConvert.DeserializeObject<stopRootObj>(json);
                    TimeTables.Text = "";



                    for (int i = 0; i < deserialized.Stops.Length; i++ )
                    {
                       // string times = "\n";

                       // for (int j = 0; j < trippinTrips[0].Count; i++ )
                       // {
                       //     times += trippinTrips[0][j].ArrivalTimes[i] + " ";
                        //}
                        //times += "\n";

                        TimeTables.Text += "\n\n" + deserialized.Stops[i].Description + "\n";

                        TimeSpan start = TimeSpan.Parse(beginTimeString);
                        TimeSpan end = TimeSpan.Parse(concludingTimeString);
                        TimeSpan temp;

                        for (int j = 0; j < trippinTrips[0].Count(); j++ )
                        {
                            temp = TimeSpan.Parse(trippinTrips[0][j].ArrivalTimes[i].ToString("HH:mm:ss"));
                            if ((start < temp) && (temp < end))
                            {
                                TimeTables.Text += "  " + trippinTrips[0][j].ArrivalTimes[i].ToString("HH:mm") + " ";
                            }

                        }

                         
                            

                        
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

            await StoryboardExtensions.BeginAsync(Storyboard2);

            Storyboard1.Stop();
                animationGrid.Visibility = Visibility.Collapsed;
                animationGrid.Opacity = 0.0;

        }

        private void submitButton_Click(object sender, RoutedEventArgs e)
        {
            beginTimeString = ((DateTime)startTime.Value).ToString("HH:mm:ss");
            concludingTimeString = ((DateTime)endTime.Value).ToString("HH:mm:ss");
            date = ((DateTime)beginDatePicker.Value).ToString("MM-dd-yyyy");
            if (((DateTime)startTime.Value) >= ((DateTime)endTime.Value))
            {
                MessageBoxResult result = MessageBox.Show("You have entered the dates incorrectly, please try again", "Warning", MessageBoxButton.OKCancel);
            }
            else
            {

                getBusTimeTable(busNumber.Text);

            }

        }
    }

    
public class routeTable
{
public Routetimetable[] RouteTimetables { get; set; }
}

public class Routetimetable
{
public DateTime Date { get; set; }
public Route Route { get; set; }
public Trip[] Trips { get; set; }
}

public class Route
{
public string Code { get; set; }
public int Direction { get; set; }
public bool IsExpress { get; set; }
public bool IsFree { get; set; }
public bool IsPrepaid { get; set; }
public bool IsTransLinkService { get; set; }
public string Name { get; set; }
public int ServiceType { get; set; }
public int Vehicle { get; set; }
}

public class Trip
{
public DateTime[] ArrivalTimes { get; set; }
public bool ContainsStartEndStopsOnly { get; set; }
public DateTime[] DepartureTimes { get; set; }
public string Id { get; set; }
public Route Route { get; set; }
public string[] StopIds { get; set; }
public string VehicleDisplay { get; set; }
}



}