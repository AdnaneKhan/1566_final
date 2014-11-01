
class Planetary_Body {
  public:
    /**
    * @param x component of vector to rotate about
    * @param y component of vector to rotate about
    * @param z component of vector to rotate about
    * @param theta angle to rotate (in degrees)
    */
      void rotate(float x, float y, float z, float theta_degrees);
      void rotate(float rotate_vector[3], float theta);
      // TODO find out how textures will play into this.
      Planetary_Body(float rotationRate, int radius);
  private:
    /**
    * Stores a gl matrix that will be used to rotate this object prior to drawinng  it.
    */
    float[16] rotationMatrix;

    /**
    * Multiplier in float relative to the cock speed of the universe
    * value from 0 to 1, 1 means it rotates 360 degrees per tick,
    * 0 means it does not rotate
    *
    * This denotes the rotation ABOUT THE OBJECT'S OWN axis.
    */
    float rotationRate;

}
