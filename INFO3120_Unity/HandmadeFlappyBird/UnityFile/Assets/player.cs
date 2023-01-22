using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class player : MonoBehaviour
{
    public Rigidbody2D rBody;
    public float jumpBoost;
    public AudioSource jumpingSound;
    public AudioSource collisionSound;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        Vector3 spotPos = transform.position;
        if (Input.GetKeyDown(KeyCode.Space)||Input.GetKeyDown(KeyCode.Mouse0))
        {
            Vector2 jump = new Vector2(0.0f, jumpBoost);
            rBody.AddForce(jump);
            jumpingSound.Play();
        }
        if (spotPos.y > 4)
        {
            collisionSound.Play();
            SceneManager.LoadScene("GameScene");
        }
        
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        collisionSound.Play();
        SceneManager.LoadScene("GameScene");
    }
}
