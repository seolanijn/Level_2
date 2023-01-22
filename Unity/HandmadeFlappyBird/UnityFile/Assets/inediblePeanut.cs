using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class inediblePeanut : MonoBehaviour
{
    public score scoreScript;
    private bool isCounted = false;
    public float xSpeed;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 cPosition = transform.position;
        cPosition.x -= xSpeed * Time.deltaTime;
        transform.position = cPosition;

        if (transform.position.x < -11.0f)
        {
            transform.position = new Vector3(11.0f, Random.Range(-3.0f, 3.0f), 0.0f);
            isCounted = false;
        }

        if (transform.position.x < -9.0f && !isCounted)
        {
            scoreScript.AddPoints();
            isCounted = true;
        }
    }

}
