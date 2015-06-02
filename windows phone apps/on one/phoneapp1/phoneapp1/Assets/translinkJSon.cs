using Microsoft.Phone.Maps.Services;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Device.Location;
using System.Diagnostics;
using System.IO.IsolatedStorage;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using Windows.Devices.Geolocation;
using Windows.Web.Http;

namespace PhoneApp1.Assets
{
    class translinkJson
    {
        HttpClient client;
        gps currentLocation;
        double longitude;
        double latitude;
        GeoCoordinate geoPosition;
        string street;
        string houseNumber;
        IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

        string[] ids = new string[3];
        string[] nearbystops = new string[5];
        Stop[] stopDetails = new Stop[5];


        public translinkJson()
        {
            client = new HttpClient();
            client.DefaultRequestHeaders.Authorization = new Windows.Web.Http.Headers.HttpCredentialsHeaderValue("Basic", Base64Encode("tracy.lewis:3i!76&U0uc{&"));
            client.DefaultRequestHeaders.Accept.Add(new Windows.Web.Http.Headers.HttpMediaTypeWithQualityHeaderValue("application/json"));

            currentLocation = new gps("translink");




        }
        public static GeoCoordinate ConvertGeocoordinate(Geocoordinate geocoordinate)
        {
            return new GeoCoordinate
                (
                geocoordinate.Point.Position.Latitude,
                geocoordinate.Point.Position.Longitude,
                geocoordinate.Altitude ?? Double.NaN,
                geocoordinate.Accuracy,
                geocoordinate.AltitudeAccuracy ?? Double.NaN,
                geocoordinate.Speed ?? Double.NaN,
                geocoordinate.Heading ?? Double.NaN
                );
        }


        static bool CloseEnoughForMe(double value1, double value2, double acceptableDifference)
        {
            return Math.Abs(value1 - value2) <= acceptableDifference;
        }

        public async Task getNearestStop()
        {
            Geolocator myGeolocator = new Geolocator();
            Geoposition myGeoposition = await myGeolocator.GetGeopositionAsync();
            Geocoordinate myGeocoordinate = myGeoposition.Coordinate;
            GeoCoordinate myGeoCoordinate = ConvertGeocoordinate(myGeocoordinate);



            var query = new ReverseGeocodeQuery() { GeoCoordinate = myGeoCoordinate };
            var geoCodeResults = await query.GetMapLocationsAsync();
            var address = geoCodeResults.First().Information.Address;

            houseNumber = address.HouseNumber;
            street = address.Street;

            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/suggest?input=" + houseNumber + " " + street + "&maxResults=3&filter=0"));

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


            response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/location/rest/stops-nearby/"+ids[0]+"?radiusM=1000&useWalkingDistance=true&maxResults=5"));

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




            if (!settings.Contains("busInfo"))
            {
                settings.Add("busInfo", getStops());
                settings.Save();
            }

            settings["busInfo"] = getStops();




        }

        public Stop[] getStops()
        {
            return stopDetails;
        }

        

        private async Task APITEST()
        {
            HttpResponseMessage response = await client.GetAsync(new System.Uri("https://opia.api.translink.com.au/v1/network/rest/route-timetables?vehicleType=bus&date=10-16-2014&routeCodes=150"));

            if (response.IsSuccessStatusCode)
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




    }



    
public class stopRootObj
{
public Stop[] Stops { get; set; }
}

public class Stop
{
public string Description { get; set; }
public string Id { get; set; }
public string LandmarkType { get; set; }
public Position Position { get; set; }
public int Type { get; set; }
public bool HasParentLocation { get; set; }
public string Intersection1 { get; set; }
public string Intersection2 { get; set; }
public string LocationDescription { get; set; }
public Parentlocation ParentLocation { get; set; }
public Route[] Routes { get; set; }
public int ServiceType { get; set; }
public string StopId { get; set; }
public string StopNoteCodes { get; set; }
public string Street { get; set; }
public string Suburb { get; set; }
public string Zone { get; set; }
}

public class Position
{
public float Lat { get; set; }
public float Lng { get; set; }
}

public class Parentlocation
{
public string Description { get; set; }
public string Id { get; set; }
public string LandmarkType { get; set; }
public Position1 Position { get; set; }
public int Type { get; set; }
public string StreetName { get; set; }
public string StreetNumber { get; set; }
public string StreetType { get; set; }
public string Suburb { get; set; }
}

public class Position1
{
public float Lat { get; set; }
public float Lng { get; set; }
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

    
public class locationRoot
{
public Location[] Locations { get; set; }
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





    public class TimetablesResponse
    {
        public Routetimetable[] RouteTimetables { get; set; }
    }

    public class Routetimetable
    {
        public DateTime Date { get; set; }
        public Route Route { get; set; }
        public Trip[] Trips { get; set; }
    }

    
    public class Trip
    {
        public DateTime[] ArrivalTimes { get; set; }
        public bool ContainsStartEndStopsOnly { get; set; }
        public DateTime[] DepartureTimes { get; set; }
        public string Id { get; set; }
        public Route1 Route { get; set; }
        public string[] StopIds { get; set; }
        public string VehicleDisplay { get; set; }
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

    
public class nearStopClass
{
public Nearbystop[] NearbyStops { get; set; }
}

public class Nearbystop
{
public Distance Distance { get; set; }
public string StopId { get; set; }
}

public class Distance
{
public float DistanceM { get; set; }
public bool IsApproximate { get; set; }
}






    public class rootSuggestions
    {
        public Suggestion[] Suggestions { get; set; }
    }

    public class Suggestion
    {
        public string Description { get; set; }
        public string Id { get; set; }
        public int Type { get; set; }
    }








    



}
