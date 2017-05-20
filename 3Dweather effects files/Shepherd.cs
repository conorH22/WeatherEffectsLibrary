using System.Collections;
using System.Collections.Generic;
using UnityEngine.SceneManagement;
using UnityEngine;
using UnityEngine.UI;
[RequireComponent(typeof(AudioSource))]
public class Shepherd : MonoBehaviour {
    public Text countText;
    public Text wintext;
    public AudioClip Baa;
   
    private int count;
	// Use this for initialization
	void Start () {
        count = 0;
        SetCountText();
        wintext.text = "";
       


    }
    void OnTriggerEnter(Collider other)
    {
        if(other.gameObject.CompareTag("sheep"))
        {
            other.gameObject.SetActive(false);
            AudioSource audio = GetComponent<AudioSource>();
            //yield return new WaitForSeconds(audio.clip.length);
            audio.clip = Baa;
            audio.Play();
            count = count + 1;
            SetCountText();
        }
    }

    // Update is called once per frame
    void Update () {
		
	}
    void SetCountText()
    {
        countText.text = "Score:" + count.ToString();
        if (count >= 5)
        {
            wintext.text = "You Win!";
            SceneManager.LoadScene("RealTimeScene");

        }
    }
}
