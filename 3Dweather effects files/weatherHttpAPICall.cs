// weatherHttpAPIcall uses  the  following namespaces system,unityengine and litJson
using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;
using UnityEngine.Networking;
using UnityEngine.SceneManagement;
using LitJson; // litJson parses the json values out to string the http call from wunderground


public class weatherHttpAPICall : MonoBehaviour {
    //private and public  like jsonstring and private instance of JsonData called itemData
    private string jsonString;
    private JsonData itemData;
    private string  time; // time variable
    public float timespeed = 1.0f; 
    private float maxTime = 86400.0f;
    public DateTime currtime { get; set; }
   

    void Start()
    {
        StartCoroutine(GetText());
       
        // using system calls system time using DateTime now which gets current local time
        DateTime now = DateTime.Now;
         string format = "HH:mm:ss tt";
        // debug.log unity  prints to unity editor console 
        //where now is a struct converted to string using the string format "HH:mm:ss tt" 
        Debug.Log(now.ToString(format));


    }

    IEnumerator GetText()
    {
        // using unitywebrequst  which makes  new web request from api http call from wunderground
        UnityWebRequest www = new UnityWebRequest("http://api.wunderground.com/api/907f0105dc40c3d1/conditions/q/pws:ICOUNTYT2.json");
        www.downloadHandler = new DownloadHandlerBuffer();// using  www manages body of data from www into a new downloadhandlerbuffer
        yield return www.Send(); // returns www. send function,talks to server

        if (www.isError) // if www  send error msg(www.isError
        {
            Debug.Log(www.error);  //if no internet connection reaf json file backup
            //System.IO.File.WriteAllText("weatheruder.json", www.downloadHandler.text.ToString());
           // System.IO.File.ReadAllText(Application.dataPath + www);
        }
        else
        { //succesfull www httprequest  string jsondata equals www. downloadhandler.text
            // Show results as text// Json
            // Debug.Log(www.downloadHandler.text);
            // this prints www httprequest to debug//also reads text from external file like json file
            //  jsonString = System.IO.File.ReadAllText(Application.dataPath + www);
            jsonString = www.downloadHandler.text;
            // System.IO.File.WriteAllText("weatheruder.json", www.downloadHandler.text.ToString());
            itemData = JsonMapper.ToObject(jsonString);
            //  Debug.Log(itemData["current_observation"]["weather"]);
            // timespan that checks daylight hours between 7am and 8pm ,  else night time hours
            TimeSpan daystart = new TimeSpan(07, 0, 0); //Daytime start  note daystart est.
            TimeSpan dayEnd = new TimeSpan(20, 0, 0); // end of day light note dayend est.
            TimeSpan Tnow = DateTime.Now.TimeOfDay;
             // checks current/local time against daystart and dayEnd using if statement and conditional AND operator
             //evaluates second operand if necessary
            if ((Tnow > daystart) && (Tnow < dayEnd))
            {
                Debug.Log(" daytime");   // daytime scenes
                //relvevant weather effects are  checked against the weather tag value
                // so == tag is check for values that appear as value for weather type
                //documentj  search for current_observation , that contains weather tag
                //SceneManager.loadscene() loads  3d weather effect scenes if tag mathces relevant scene 
                if (itemData["current_observation"]["weather"].ToString() == "Rain")
                {
                    Debug.Log(" its Raining");
                    SceneManager.LoadScene("rainScene");
                }
                else  // prints warningmsg  not weather scene 
                {
                    Debug.Log("It's not Raining");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Snow")
                {
                    Debug.Log(" its Snowing");
                    SceneManager.LoadScene("SnowScene");
                }
                else
                {
                    Debug.Log("It's not Snowing");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Overcast")
                {
                    Debug.Log(" its overcast");
                    SceneManager.LoadScene("OvercastScene");

                }
                if (itemData["current_observation"]["weather"].ToString() == "Mostly Cloudy")
                {
                    Debug.Log(" its overcast");
                    SceneManager.LoadScene("OvercastScene");

                }
                else
                {
                    Debug.Log("It's not overcast");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Partly Cloudy")
                {
                    Debug.Log(" its Partly Cloudy");
                    SceneManager.LoadScene("OvercastScene");

                }
                else
                {
                    Debug.Log("It's not Partly Cloudy");
                }

                if (itemData["current_observation"]["weather"].ToString() == "Clear")
                {
                    Debug.Log(" its Clear");
                    SceneManager.LoadScene("SunScene");
                }
                else
                {
                    Debug.Log("It's not sunny");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Fog")
                {
                    Debug.Log(" its Foggy");
                    SceneManager.LoadScene("fogScene");
                }
                else
                {
                    Debug.Log("It's not Foggy");
                }

            }
            else
            {  // night  time scenes
                Debug.Log(" NightTime");
                if (itemData["current_observation"]["weather"].ToString() == "Rain")
                {
                    Debug.Log(" its Raining");
                    SceneManager.LoadScene("rainSceneNight");
                }
                else
                {
                    Debug.Log("It's not Raining");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Snow")
                {
                    Debug.Log(" its Snowing");
                    SceneManager.LoadScene("SnowSceneNight");
                }
                else
                {
                    Debug.Log("It's not Snowing");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Overcast")
                {
                    Debug.Log(" its overcast");
                    SceneManager.LoadScene("OvercastSceneNight");

                }
                else
                {
                    Debug.Log("It's not overcast");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Sun")
                {
                    Debug.Log(" its night");
                    SceneManager.LoadScene("NightScene");
                }
                else
                {
                    Debug.Log("It's not sunny");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Mostly Cloudy")
                {
                    Debug.Log(" its overcast");
                    SceneManager.LoadScene("OvercastSceneNight");

                }
                else
                {
                    Debug.Log("It's not overcast");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Clear")
                {
                    Debug.Log(" its Clear");
                    SceneManager.LoadScene("NightScene");
                }
                else
                {
                    Debug.Log("It's not sunny");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Fog")
                {
                    Debug.Log(" its Foggy");
                    SceneManager.LoadScene("fogSceneNight");
                }
                else
                {
                    Debug.Log("It's not Foggy");
                }
                if (itemData["current_observation"]["weather"].ToString() == "Partly Cloudy")
                {
                    Debug.Log(" its Partly Cloudy");
                    SceneManager.LoadScene("OvercastSceneNight");

                }
                else
                {
                    Debug.Log("It's not Partly Cloudy");
                }

            }

            // Or retrieve results as binary data
            byte[] results = www.downloadHandler.data;
        }
        

    }
   

     void Update()
    {
      
    }





}
