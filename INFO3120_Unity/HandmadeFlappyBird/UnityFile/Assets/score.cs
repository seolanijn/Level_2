using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class score : MonoBehaviour
{
    private int point = 0;
    public Text pointsText;
    public void AddPoints()
    {
        point++;
        pointsText.text = "Score: " + point;
    }
}
