#ifndef UKF_H
#define UKF_H

#include "measurement_package.h"
#include "Eigen/Dense"
#include <vector>
#include <string>
#include <fstream>

using Eigen::MatrixXd;
using Eigen::VectorXd;

class UKF {
public:

  ///* initially set to false, set to true in first call of ProcessMeasurement
  bool is_initialized_;

  ///* if this is false, laser measurements will be ignored (except for init)
  bool use_laser_;

  ///* if this is false, radar measurements will be ignored (except for init)
  bool use_radar_;

  ///* state vector: [pos1 pos2 vel_abs yaw_angle yaw_rate] in SI units and rad
  VectorXd x_;

  ///* state covariance matrix
  MatrixXd P_;

  ///* predicted sigma points matrix
  MatrixXd Xsig_pred_;

  ///* Weights of sigma points  
  VectorXd weights_;

  ///* Process noise standard deviation longitudinal acceleration in m/s^2
  float std_a_;

  ///* Process noise standard deviation yaw acceleration in rad/s^2
  float std_yawdd_;

  ///* Laser measurement noise standard deviation position1 in m
  float std_laspx_;

  ///* Laser measurement noise standard deviation position2 in m
  float std_laspy_;

  ///* Radar measurement noise standard deviation radius in m
  float std_radr_;

  ///* Radar measurement noise standard deviation angle in rad
  float std_radphi_;

  ///* Radar measurement noise standard deviation radius change in m/s
  float std_radrd_ ;

  ///* State dimension
  int n_x_;

  ///* Augmented state dimension
  int n_aug_;

  ///* Sigma point spreading parameter
  float lambda_;

    ///* time when the state is true, in us  
  long long time_us_;

  long long previous_timestamp_;


  /**
   * Constructor
   */
  UKF();

  /**
   * Destructor
   */
  virtual ~UKF();

  /**
   * ProcessMeasurement
   * @param meas_package The latest measurement data of either radar or laser
   */
  void ProcessMeasurement(MeasurementPackage meas_package);

  /**
   * Prediction Predicts sigma points, the state, and the state covariance
   * matrix
   * @param delta_t Time between k and k+1 in s
   */
  void Prediction(float delta_t);

  /**
   * Updates the state and the state covariance matrix using a laser measurement
   * @param meas_package The measurement at k+1
   */
  void UpdateLidar(VectorXd &z);

  /**
   * Updates the state and the state covariance matrix using a radar measurement
   * @param meas_package The measurement at k+1
   */
  void UpdateRadar(VectorXd &z);

  void AugmentedSigmaPoints(MatrixXd &Xsig_aug);

  void SigmaPointPrediction(float delta_t, MatrixXd &Xsig_aug);

  void PredictMeanAndCovariance(void );

  void PredictLidarMeasurement(int n_z, VectorXd &z_pred, VectorXd &Zsig, MatrixXd &S );

  void PredictRadarMeasurement(int n_z, VectorXd &z_pred, VectorXd &Zsig, MatrixXd &S );

  void UpdateState(int n_z, VectorXd &z, VectorXd &z_pred, VectorXd &Zsig, MatrixXd &S);


};

#endif /* UKF_H */
