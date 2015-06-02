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

namespace PhoneApp1
{
    public partial class Page3 : PhoneApplicationPage
    {
        gps location;
        List<timeTableHelper> timeTables = new List<timeTableHelper>();
        IsolatedStorageSettings settings;
        public Page3()
        {
            InitializeComponent();
            settings = IsolatedStorageSettings.ApplicationSettings;

            if (!settings.Contains("timeTableListKey"))
            {
                List<timeTableHelper> tempTimeTables = new List<timeTableHelper>();
                settings.Add("timeTableListKey", tempTimeTables);
                settings.Save();
            }

            timeTables = (List<timeTableHelper>)settings["timeTableListKey"];

            foreach (timeTableHelper t in timeTables)
            {
                NotificationListBox.DisplayMemberPath = "name";
                NotificationListBox.Items.Add(t);

            }
            

        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {


        }

        private void listbox_click(object sender, RoutedEventArgs e)
        {
            timeTableHelper temp = (timeTableHelper)NotificationListBox.SelectedItem;
            PhoneApplicationService.Current.State["param"] = temp;
            NavigationService.Navigate(new Uri("/PanoramaPage1.xaml", UriKind.Relative));
            
        }

        private void ApplicationBarSaveButton_Click(object sender, EventArgs e)
        {
            NavigationService.Navigate(new Uri("/createTimeTable.xaml", UriKind.RelativeOrAbsolute));
        }


 

        


        private async Task APITEST()
        {

            HttpClient client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new Windows.Web.Http.Headers.HttpCredentialsHeaderValue("Basic", Base64Encode("tracy.lewis:3i!76&U0uc{&"));

            client.DefaultRequestHeaders.Accept.Add(new Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue("application/json"));
            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/network/rest/route-timetables?vehicleType=bus&date=10-16-2014&routeCodes=150"));

            if(response.IsSuccessStatusCode)
            {

                string json = await response.Content.ReadAsStringAsync();

                Debug.WriteLine("API OK: " + json);
            

                try
                {
                    TimetablesResponse deserialized = JsonConvert.DeserializeObject<TimetablesResponse>(json);
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

        public static string Base64Encode(string plainText)
        {
            var plainTextBytes = System.Text.Encoding.UTF8.GetBytes(plainText);
            return System.Convert.ToBase64String(plainTextBytes);
        }

        private void OneShotLocation_Click(object sender, RoutedEventArgs e)
        {
            //location = new gps();

            //location.createGeofence(47.63, -122.1290);
            timeTables.Add(new timeTableHelper("sdsds"));
        }
        protected override void OnBackKeyPress(CancelEventArgs e)
        {
            NavigationService.Navigate(new Uri("/home.xaml", UriKind.Relative));
        }

    }

    
    public class TimetablesResponse
    {
    public Routetimetable[] RouteTimetables { get; set; }
    }

    

    public class Route1
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

    
 

    public class Location
    {
    public string Description { get; set; }
    public string Id { get; set; }
    public string LandmarkType { get; set; }
    public Position Position { get; set; }
    public int Type { get; set; }
    public string StreetName { get; set; }
    public string StreetNumber { get; set; }
    public string StreetType { get; set; }
    public string Suburb { get; set; }
    }

    public class Position
    {
    public float Lat { get; set; }
    public float Lng { get; set; }
    }

}

