using System.Collections;
using System.Collections.Generic;
using UnityEngine;
//daynight made for 3d weather effects application
// the script moves sun directional light in unity scene 360 degress via the y axis 
public class DayNight : MonoBehaviour {
    public float DayLength = 2;
    public float NightLength = 1;
    public float time = 2;
    public float hour = 0;
    public Light sun;
	// Use this for initialization
	void Start () {
       
	}
	
	// Update is called once per frame
	void Update () {
        sun.transform.Rotate(Time.deltaTime / time, 0, 0);
        hour += Time.deltaTime / time;

        if (hour >= 360)
        {
            hour=0;
        }
        if( hour >= 180)
        {
            //it is night
            time = NightLength;
            sun.intensity -= Time.deltaTime;
        }
        if (hour <= 180)
        {
            
            time = DayLength;
            sun.intensity = Time.deltaTime;
        }
        if ( sun.intensity >= 1)
        {
            sun.intensity = 1;
        }
        if (sun.intensity <= 0.2)
        {
            sun.intensity = 0;
        }


    }
}
