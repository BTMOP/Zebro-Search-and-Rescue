
#ifndef ZEBROTOPLEVELCONTROLLER_H
#define ZEBROTOPLEVELCONTROLLER_H


#include <includes/utility/datatypes/byte_array.h>
#include <includes/utility/math/vector3.h>

#include <fstream>

#include <../common-core/ZebroIdentifier.h>
#include <ProximitySensor/ProximitySensor.h>


/*
 * All the ARGoS stuff in the 'argos' namespace.
 * With this statement, you save typing argos:: every time.
 */
using namespace argos;


class ZebroTopLevelController {

public:

   /* Class constructor. */
   ZebroTopLevelController();

   /* Class destructor. */
   virtual ~ZebroTopLevelController() {}

   /*
    * This function initializes the controller.
    * The 't_node' variable points to the <parameters> section in the XML
    * file in the <controllers><footbot_diffusion_controller> section.
    */
   	virtual void Init(); // to replace

   /*
    * This function is called once every time step.
    * The length of the time step is set in the XML file.
    */
   virtual void ControlStep();

   /*
    * This function resets the controller to its state right after the
    * Init().
    * It is called when you press the reset button in the GUI.
    * In this example controller there is no need for resetting anything,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Reset() {}

   /*
    * Called to cleanup what done by Init() when the experiment finishes.
    * In this example controller there is no need for clean anything up,
    * so the function could have been omitted. It's here just for
    * completeness.
    */
   virtual void Destroy() {}
   
   void ResetCapturedNodes();
	void ResetMySearchers();
	void ResetChildrenBasekeepers();
	void ResetIgnoreSearchers();

   void CheckPositioning();
   void TrackOwnPosition();
   
   void GoForwards();
   void GoBackwards();
   void SharpLeftTurn();
   void SharpRightTurn();
   void MildLeftTurn();
   void MildRightTurn();
   void MildBackwardsLeftTurn();
   void MildBackwardsRightTurn();
   void Stop();
   void UpdateLegVelocities();
   

	void SendMessage(CByteArray& bytesToSend, ZebroIdentifier senderId, unsigned char messageNumber);
   void SendMessage(CByteArray& bytesToSend, ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier receiverId);
   void BroadcastMessage(CByteArray& bytesToSend);
   void ReceiveMessage(CByteArray message);
   void CheckForReceivedMessages();
   void SendMessageFromQueue();
	
	
	virtual void ReceiveMessage_CAPTUREACK(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, unsigned char hopsLeft, ZebroIdentifier candidateId, ZebroIdentifier capturedNodeId, ZebroIdentifier capturedNodeId2, ZebroIdentifier capturedNodeId3);
	virtual void ReceiveMessage_CAPTUREBROADCAST(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, unsigned char hopsMade, ZebroIdentifier candidateId, int receivedLevel);
	virtual void ReceiveMessage_SHAREPOSITION(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, unsigned char hopsMade, CByteArray compressedPosition, ZebroIdentifier parent);
	virtual void ReceiveMessage_DISBAND(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, CByteArray compressedPosition);
	virtual void ReceiveMessage_RECRUITNEWBASEKEEPER(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver);
	virtual void ReceiveMessage_PINGREPLY(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, CByteArray compressedPosition, unsigned char allowAsNewBasekeeper);
	virtual void ReceiveMessage_APPOINTNEWBASEKEEPER(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier newBasekeeperId, CByteArray compressedPosition, unsigned char basekeeperL);
	virtual void ReceiveMessage_RELOCATESEARCHER(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier searcherId, ZebroIdentifier basekeeperId, CByteArray compressedPosition);
	virtual void ReceiveMessage_FOUNDTARGET(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier parent, CByteArray compressedPosition);
	virtual void ReceiveMessage_FOUNDTARGETUPSTREAM(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier parent, unsigned char totalSearchers, unsigned char hopsMade, CByteArray compressedLength);
	virtual void ReceiveMessage_PATHDATA(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier to, unsigned char hopsLeftToTarget, int amountOfSearchersLeft, int sendSearchersNumber);
	virtual void ReceiveMessage_BECOMEPATHPOINT(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, ZebroIdentifier searcherId, CByteArray compressedPosition);
	virtual void ReceiveMessage_PINGALLBASEKEEPERS(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, CByteArray compressedPosition);
	virtual void ReceiveMessage_APPLYASBASEKEEPER(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver, CByteArray compressedPosition);
	virtual void ReceiveMessage_HEARTBEAT(ZebroIdentifier senderId, unsigned char messageNumber, ZebroIdentifier intendedReceiver);
	
	void SendMessage_SHAREPOSITION(ZebroIdentifier from, unsigned char messageNumber, unsigned char hopsMade, unsigned char rotatationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2, ZebroIdentifier parent);
   void SendMessage_SHAREPOSITION(ZebroIdentifier from, unsigned char messageNumber, unsigned char hopsMade, CByteArray compressedPosition, ZebroIdentifier parent);
   void SendMessage_SHAREPOSITION(ZebroIdentifier from, unsigned char messageNumber, unsigned char hopsMade, CVector3 position, ZebroIdentifier parent);
   void SendMessage_CAPTUREACK(ZebroIdentifier from, unsigned char messageNumber, unsigned char hopsLeft, ZebroIdentifier candidateId, ZebroIdentifier capturedNodeId, ZebroIdentifier capturedNodeId2, ZebroIdentifier capturedNodeId3);
   void SendMessage_CAPTUREBROADCAST(ZebroIdentifier from, unsigned char messageNumber, unsigned char hopsMade, unsigned char level, ZebroIdentifier candidateId);
   void SendMessage_FOUNDTARGET(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier parent, unsigned char rotationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2);
   void SendMessage_FOUNDTARGET(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier parent, CVector3 position);
   void SendMessage_FOUNDTARGETUPSTREAM(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier parent, unsigned char totalSearchers, unsigned char hopsMade, Real totalDistance);
   void SendMessage_FOUNDTARGETUPSTREAM(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier parent, unsigned char totalSearchers, unsigned char hopsMade, unsigned char distanceByte1, unsigned char distanceByte2);
   void SendMessage_BECOMEPATHPOINT(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier searcherId, CVector3 position);
   void SendMessage_BECOMEPATHPOINT(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier searcherId, unsigned char rotationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2);
   void SendMessage_RECRUITNEWBASEKEEPER();
   void SendMessage_PINGALLBASEKEEPERS();
   void SendMessage_PINGREPLY(ZebroIdentifier to, CVector3 position, unsigned char allowAsNewBasekeeper);
   void SendMessage_APPLYASBASEKEEPER(ZebroIdentifier toBasekeeper);
   void SendMessage_HEARTBEAT(ZebroIdentifier toBasekeeper);
   void SendMessage_APPOINTNEWBASEKEEPER(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier newBasekeeperId, unsigned char basekeeperL);
   void SendMessage_APPOINTNEWBASEKEEPER(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier newBasekeeperId, CByteArray compressedPosition, unsigned char basekeeperL);
   void SendMessage_SendMessage_RELOCATESEARCHER(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier searcherId, ZebroIdentifier basekeeperId, unsigned char rotationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2);
   void SendMessage_SendMessage_RELOCATESEARCHER(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier searcherId, ZebroIdentifier basekeeperId, CVector3 position);
	void SendMessage_DISBAND(ZebroIdentifier from, unsigned char messageNumber, unsigned char rotationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2);
   void SendMessage_DISBAND(ZebroIdentifier from, unsigned char messageNumber, CVector3 safePosition);
   void SendMessage_DISBAND(ZebroIdentifier from, unsigned char messageNumber, CByteArray compressedPosition);
   void SendMessage_PATHDATA(ZebroIdentifier from, unsigned char messageNumber, ZebroIdentifier linkToTarget, unsigned char hopsLeftToTarget, int amountOfSearchersLeft, int sendSearchersNumber);
   
	virtual void LostConnectionToChildBasekeeper(ZebroIdentifier lostChildId);
	
	unsigned char GetObstacleAvoidanceData();
   
   CVector3 GetVectorToChild(ZebroIdentifier nodeId);
	CByteArray GetCompressedVectorToChild(ZebroIdentifier nodeId);
   Real GetFarthestChildBasekeeperDistance();
   
   void AddToCapturedNodes(ZebroIdentifier nodeId);

   
   
   
   void AddToMySearchers(ZebroIdentifier nodeId);
   void RemoveFromMySearchers(ZebroIdentifier nodeId);
   void updateMySearchersTicks();
   void AddToIgnoreSearchers(ZebroIdentifier nodeId);
   void updateIgnoreSearchersTicks();
   bool IsIgnoringSearcher(ZebroIdentifier nodeId);
   
   void AddToChildrenBasekeepers(ZebroIdentifier nodeId, CVector3 position);
   void UpdateChildrenBasekeepersTicks();
   bool IsChildBasekeeper(ZebroIdentifier nodeId);
   
   
	ZebroIdentifier PopMostRecentlyActiveSearcher();
	
	ZebroIdentifier PickRandomChildBasekeeper();
   
	
	
	/* to replace*/
	CVector3 CreateWeightedAverageVector(CVector3 position1, int weight1, CVector3 position2, int weight2);
	CByteArray ConvertFractionTo2Bytes(Real input);
	CByteArray ConvertLengthTo2Bytes(Real length);
	Real Convert2BytesToFraction(CByteArray input);
	Real Convert2BytesToLength(CByteArray compressedLength);
	CByteArray CompressPosition(CVector3 position);
	CVector3 DecompressPosition(CByteArray compressedPosition);
	CVector3 DecompressPosition(unsigned char rotationByte1, unsigned char rotationByte2, unsigned char lengthByte1, unsigned char lengthByte2);

	
	
private:
	/*
    * The following variables are used as parameters for the
    * algorithm. You can set their value in the <parameters> section
    * of the XML configuration file, under the
    * <controllers><footbot_diffusion_controller> section.
    */
	/* to replace 2
	CCI_DifferentialSteeringActuator* m_pcWheels;
	CCI_FootBotProximitySensor* m_pcProximity;
	CCI_RangeAndBearingSensor* m_pcRABSens;
	CCI_RangeAndBearingActuator* m_pcRABAct;
	const CCI_RangeAndBearingSensor::SPacket* m_psFBMsg;
	CCI_PositioningSensor* m_pcPosSens;
	CRange<CRadians> m_cGoStraightAngleRange;
	*/
	
	int direction; // todo: investigate the need for this
	CByteArray savedReadings;
	CByteArray messageQueue;
	int messageQueuePointer;
	int messageQueueSize;
	CByteArray childrenBasekeepers;
	/* Maximum tolerance for the angle between
    * the robot heading direction and
    * the closest obstacle detected. */
	CDegrees m_cAlpha;
	/* Maximum tolerance for the proximity reading between
    * the robot and the closest obstacle.
    * The proximity reading is 0 when nothing is detected
    * and grows exponentially to 1 when the obstacle is
    * touching the robot.
    */
	Real m_fDelta;
	/* Wheel speed. */
	Real m_fWheelVelocity;
	/* Angle tolerance range to go straight.
    * It is set to [-alpha,alpha]. */
	
	CByteArray capturedNodes;
	
	CByteArray mySearchers;
	CByteArray ignoreSearchers;
	Real leftLegsVelocity;
	Real rightLegsVelocity;
	int overwriteSavedReadingsPointer;
	
	
	
	ProximitySensor proximitySensor;
	int previousWalkfileSpeed;
	int previousWalkfileDirection;
	int walkfileSpeed;
	int walkfileDirection;
	ofstream walkfile;
	
protected:

   
   int childrenBasekeepersTotal;
	unsigned char sendMessageId;
	ZebroIdentifier myId;
	int role;
	bool satisfied;
	int mySearchersTotal;
	int level;
	CVector3 lastMeasuredParentBasekeeperPosition;
	CVector3 absoluteParentBasekeeperPosition; // todo: this one COULD be private in SearchAndRescueBehaviour... but that would not be nice because it's an ABSOLUTE position
	ZebroIdentifier mainBasekeeper; // todo: this var is protected just because of one line of code in ZebroTopLevelController that could probably be done without
	CVector3 myTrackedPosition; // todo: I don't think so, but maybe this can be private
	Real myAngleFromNorth; // todo: this one isn't actually being used in SearchAndRescueBehaviour, but probably should be used?
	CVector3 myLastAbsolutePosition; // todo: get this variable to be a private one.
	CVector3 myAbsolutePosition; // todo: get this variable to be a private one.
	Real myRotation;
	int returnToBasekeeperFirstTurnPreference;

	int minDistance;
};

#endif



