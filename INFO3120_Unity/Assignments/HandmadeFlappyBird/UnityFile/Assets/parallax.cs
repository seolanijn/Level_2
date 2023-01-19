using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class parallax : MonoBehaviour
{
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

        if(transform.position.x < -20.0f)
        {
            transform.position += new Vector3(40.0f, 0.0f, 0.0f);

        }
    }
}
