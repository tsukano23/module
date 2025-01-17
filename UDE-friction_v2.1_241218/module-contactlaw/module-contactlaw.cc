/* -----------------------------------------------------------------------
* MBDyn (C) is a multibody analysis code.
* http://www.mbdyn.org
*
* Copyright (C) 1996-2017
*
* Pierangelo Masarati  <masarati@aero.polimi.it>
*
* Dipartimento di Ingegneria Aerospaziale - Politecnico di Milano
* via La Masa, 34 - 20156 Milano, Italy
* http://www.aero.polimi.it
*
* Changing this copyright notice is forbidden.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation (version 2 of the License).
* 
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
* -----------------------------------------------------------------------*/

/* -----------------------------------------------------------------------
* Module - contactlaw
*
* Implemented by
* Ryoya Hisamatsu <hisamatsu@nams.kyushu-u.ac.jp>
* Department of Marine Systems Engineering, Kyushu University
* Motooka 744, Nishi-ku, Fukuoka 819-0395, Fukuoka, Japan 
* -----------------------------------------------------------------------*/

#include "mbconfig.h"

#include <cassert>
#include <cstdio>
#include <cmath>
#include <cfloat>
#include <iostream>
#include <iomanip>
#include <limits>

#include "module-contactlaw.h"
#include "exchangevector.h"
#include "tanhfunc.h"


/* ----------------------------- contactlaw start --------------------------------------*/

/*=======================================================================================
* Constructor and Destructor
*=======================================================================================*/
//constructor
Contactlaw::Contactlaw (
	unsigned uLabel,
	const DofOwner *pDO,
	DataManager* pDM,
	MBDynParser& HP
)
: Elem(uLabel, flag(0)), UserDefinedElem(uLabel, pDO)
{
	// help message or no arg error
	if (HP.IsKeyWord("help")) {
		silent_cout(
			"help message\n"
			"==== Module: Contactlaw ====\n"
			"- Note: \n"
			"\ttest\n"
			"- Usage: \n"
			"\tContactlaw,\n"
			"\t<node_label_1>,\n"
			"\t<node_label_2>;\n"
			<< std::endl);
		if (!HP.IsArg()) {
			throw NoErr(MBDYN_EXCEPT_ARGS);
		}
	}

	std:: cout << "1" << std::endl;

	// read node1
	pNode1 = dynamic_cast<const StructNode *>(pDM->ReadNode(HP, Node::STRUCTURAL));

	// read node2
	pNode2 = dynamic_cast<const StructNode *>(pDM->ReadNode(HP, Node::STRUCTURAL));

	// read seabed object
	unsigned int uElemLabel = (unsigned int)HP.GetInt();
	pSeabed = dynamic_cast<Seabed *>(pDM->pFindElem(Elem::LOADABLE, uElemLabel));

	std:: cout << "2" << std::endl;

	
	// read k
	if (!HP.IsKeyWord("k")) {
	silent_cerr("Contactlaw(" << GetLabel() << "): keyword \"k\" expected at line " << HP.GetLineData() << std::endl);
	throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	k = HP.GetReal();

	// read c
	if (!HP.IsKeyWord("c")) {
	silent_cerr("Contactlaw(" << GetLabel() << "): keyword \"c\" expected at line " << HP.GetLineData() << std::endl);
	throw ErrGeneric(MBDYN_EXCEPT_ARGS);
	}
	c = HP.GetReal();

	std ::cout << "3" << std::endl;

	//output flag
	SetOutputFlag(pDM->fReadOutput(HP, Elem::LOADABLE));
	//export log file
	pDM->GetLogFile()
		<< "Contactlaw: " << uLabel
		<< " " << pNode1->GetLabel()
		<< " " << pNode2->GetLabel()
		<< " " << pSeabed->GetLabel()
		<< std::endl;

	std ::cout << "4" << std::endl;		
}



//destructor
Contactlaw::~Contactlaw (void)
{
	NO_OP;
	std ::cout << "5" << std::endl;
}



/*=======================================================================================
* Intial Assembly Process
*=======================================================================================*/
//set number of DOF
unsigned int
Contactlaw::iGetInitialNumDof(void) const
{
	return 0;
	std ::cout << "6" << std::endl;
}

//set initial value
void
Contactlaw::SetInitialValue(VectorHandler& XCurr)
{
	return;
	std ::cout << "7" << std::endl;
}

//set initial assembly matrix dimension
void 
Contactlaw::InitialWorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 0;
	*piNumCols = 0;
	std ::cout << "8" << std::endl;
}

//calculate residual vector for initial assembly analysis
SubVectorHandler& 
Contactlaw::InitialAssRes(
	SubVectorHandler& WorkVec,
	const VectorHandler& XCurr)
{
	WorkVec.ResizeReset(0);
	return WorkVec;
	std ::cout << "9" << std::endl;
}

//calculate Jaconbian for initial assembly analysis
VariableSubMatrixHandler&
Contactlaw::InitialAssJac(
	VariableSubMatrixHandler& WorkMat, 
	const VectorHandler& XCurr)
{
	WorkMat.SetNullMatrix();
	return WorkMat;
	std ::cout << "10" << std::endl;
}

/*=======================================================================================
* Initial Value Problem
*=======================================================================================*/
//set number of DOF
unsigned int
Contactlaw::iGetNumDof(void) const
{
	return 0;
	std ::cout << "11" << std::endl;
}

//set DOF type
DofOrder::Order
Contactlaw::GetDofType(unsigned int i) const
{
	return DofOrder::DIFFERENTIAL;
	std ::cout << "12" << std::endl;
}

//set initial value
void
Contactlaw::SetValue(
	DataManager *pDM,
	VectorHandler& X,
	VectorHandler& XP,
	SimulationEntity::Hints *ph)
{
	return;
	std ::cout << "13" << std::endl;
}

//print explanation of variables and equations
std::ostream&
Contactlaw::DescribeDof(std::ostream& out, const char *prefix, bool bInitial) const
{
}
std::ostream&
Contactlaw::DescribeEq(std::ostream& out, const char *prefix, bool bInitial) const
{
}


//set matrix dimension
void
Contactlaw::WorkSpaceDim(integer* piNumRows, integer* piNumCols) const
{
	*piNumRows = 6;
	*piNumCols = 6;	
	//std ::cout << "14" << std::endl;
}


//calculate residual vector
SubVectorHandler& 
Contactlaw::AssRes(
	SubVectorHandler& WorkVec,
	doublereal dCoef,
	const VectorHandler& XCurr, 
	const VectorHandler& XPrimeCurr)
{
	/*configuring current vector deta------------------------------------------*/
	/*current node data--------------------------------------------------*/
	//node1
	const integer iPositionIndex1 = pNode1->iGetFirstPositionIndex();
	const integer iMomentumIndex1 = pNode1->iGetFirstMomentumIndex();
	//node2
	const integer iPositionIndex2 = pNode2->iGetFirstPositionIndex();
	const integer iMomentumIndex2 = pNode2->iGetFirstMomentumIndex();

	/*calculate refrecionforces------------------------------------*/
	//seabedの定数定義
	doublereal g,Zs, nu1d, nu1s, nu2d, nu2s, vt;
	pSeabed->get(g, Zs, nu1d, nu1s, nu2d, nu2s, vt);

	/*nodedata_config-----------------------------------------------*/
	const Vec3 r1 = Vec3(
			XCurr(iPositionIndex1+1),
			XCurr(iPositionIndex1+2),
			XCurr(iPositionIndex1+3)
		);
	const Vec3 v1 = Vec3(
			XPrimeCurr(iPositionIndex1+1),
			XPrimeCurr(iPositionIndex1+2),
			XPrimeCurr(iPositionIndex1+3)
		);
	//node2
	const Vec3 r2 = Vec3(
			XCurr(iPositionIndex2+1),
			XCurr(iPositionIndex2+2),
			XCurr(iPositionIndex2+3)
		);
	const Vec3 v2 = Vec3(
			XPrimeCurr(iPositionIndex2+1),
			XPrimeCurr(iPositionIndex2+2),
			XPrimeCurr(iPositionIndex2+3)
		);

	/*configuring workvec------------------------------------------*/
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WorkVec.ResizeReset(iNumRows);
	for(int iCnt = 1; iCnt <=3; iCnt++){
		WorkVec.PutRowIndex(iCnt, iMomentumIndex1+iCnt);
	}
	for(int iCnt = 1; iCnt <=3; iCnt++){
		WorkVec.PutRowIndex(iCnt+3, iMomentumIndex2+iCnt);
	}

	//node1===================================================================

	doublereal c1;
	/*ベクトルの初期値定義------------------------------------------------*/  

	Vec3 normal_vec_1 			= Vec3(0.0,0.0,0.0);
	Vec3 internode_unitvec_1 	= Vec3(0.0,0.0,0.0);
	Vec3 axial_unitvec_1 		= Vec3(0.0,0.0,0.0);
	Vec3 lateral_unitvec_1 		= Vec3(0.0,0.0,0.0);

	doublereal z1    	= r1.dGet(3) - Zs;
	doublereal vz1   	= v1.dGet(3);
	doublereal delta1 	= std::abs(z1);

	/*反力計算-----------------------------------------------------------*/
	if (z1>0.0) {
		c1 = 0.0;
		std::cout << "Res00" << std::endl;
	} else {
		c1 = 1.0;
		//tanh(x)を使って静摩擦から動摩擦の移行を表現
	}

	//弾性床からの反力計算
	doublereal F1  = (k*delta1 -c*vz1)*c1;

	/*摩擦力計算----------------------------------------------------------*/
	//摩擦係数
	doublereal nu1 = nu1d;
	/*ベクトル------------------------------------------------------------*/

	//係留軸を含むように座標返還
	////normal_vec
	pexv.normal_vec(normal_vec_1);
	////internode_vec
	pexv.internode_vec(internode_unitvec_1, r1, r2);
	////lateralnode_vec
	pexv.lateral_vec(lateral_unitvec_1, normal_vec_1, internode_unitvec_1, r1, r2);
	////axialnode_vec
	pexv.axial_vec(axial_unitvec_1, normal_vec_1, lateral_unitvec_1, r1, r2);

	//摩擦力の負荷方向を質点の速度ベクトルをaxial(係留軸),lateral(係留軸横方向)で分解してそれぞれの反対方向に負荷させる
	////axial(axial_unitvecとv1の正射影)
	Vec3 friction_axialvec_1 		=  -pexv.op_vec(v1, axial_unitvec_1);
	////lateral(lateral_unitvecとv1の正射影)
	Vec3 friction_lateralvec_1 		=  -pexv.op_vec(v1, lateral_unitvec_1);

	//step関数で摩擦力の推移表現
	doublereal dcrit 			= 2.5; 
	doublereal x_tanh_1   		= v1.Norm()/vt;
	doublereal friction_abs_1	= ptanhf.tanh(x_tanh_1, dcrit)*nu1*F1;
	Vec3 f_friction_axial_1 	= Vec3(
							friction_abs_1*friction_axialvec_1.dGet(1),
							friction_abs_1*friction_axialvec_1.dGet(2),
							friction_abs_1*friction_axialvec_1.dGet(3) + F1
	);
	Vec3 f_friction_lateral_1 	= Vec3(
							friction_abs_1*friction_lateralvec_1.dGet(1),
							friction_abs_1*friction_lateralvec_1.dGet(2),
							friction_abs_1*friction_lateralvec_1.dGet(3) 
	);

	//node2===================================================================
	doublereal c2;
	///摩擦力計算時のFと摩擦係数定義
	doublereal F2;

	Vec3 normal_vec_2 			= Vec3(0.0,0.0,0.0);

	doublereal z2    	= r2.dGet(3) - Zs;
	doublereal vz2   	= v2.dGet(3);
	doublereal delta2 	= std::abs(z2);

	/*反力計算-----------------------------------------------------------*/
	if (z2>0.0) {
		c2 = 0.0;
		std::cout << "Res00" << std::endl;
	} else {
		c2 = 1.0;
		//tanh(x)を使って静摩擦から動摩擦の移行を表現
	}

	//弾性床からの反力計算
	F2           = (k*delta2 -c*vz2)*c2;

	/*摩擦力計算----------------------------------------------------------*/
	//摩擦係数
	doublereal nu2 = nu1d;
	/*ベクトル------------------------------------------------------------*/

	//係留軸を含むように座標返還
	////normal_vec
	pexv.normal_vec(normal_vec_2);
	/*以下はnode1と共有している内容なので計算の重複を避けるため省略*/
	////internode_vec
	//pexv.internode_vec(internode_unitvec_1, r1, r2);
	////lateralnode_vec
	//pexv.lateral_vec(lateral_unitvec_1, normal_vec_1, internode_unitvec_1, r1, r2);
	////axialnode_vec
	//pexv.axial_vec(axial_unitvec_1, normal_vec_1, lateral_unitvec_1, r1, r2);


	//摩擦力の負荷方向を質点の速度ベクトルをaxial(係留軸),lateral(係留軸横方向)で分解してそれぞれの反対方向に負荷させる
	////axial(axial_unitvecとv1の正射影)
	Vec3 friction_axialvec_2 		=  -pexv.op_vec(v2, axial_unitvec_1);
	////lateral(lateral_unitvecとv1の正射影)
	Vec3 friction_lateralvec_2 		=  -pexv.op_vec(v2, lateral_unitvec_1);

	//step関数で摩擦力の推移表現
	//doublereal dcrit 			= 2.5; 
	doublereal x_tanh_2   		= v2.Norm()/vt;
	doublereal friction_abs_2	= ptanhf.tanh(x_tanh_2, dcrit)*nu2*F2;
	Vec3 f_friction_axial_2 	= Vec3(
								friction_abs_2*friction_axialvec_2.dGet(1),
								friction_abs_2*friction_axialvec_2.dGet(2),
								friction_abs_2*friction_axialvec_2.dGet(3) + F2
	);
	Vec3 f_friction_lateral_2 	= Vec3(
								friction_abs_2*friction_lateralvec_2.dGet(1),
								friction_abs_2*friction_lateralvec_2.dGet(2),
								friction_abs_2*friction_lateralvec_2.dGet(3)
	);

	//WorkVecに代入
	WorkVec.Put(1, f_friction_axial_1 + f_friction_lateral_1);
	WorkVec.Put(4, f_friction_axial_2 + f_friction_lateral_2);
	return WorkVec;
	std ::cout << "15" << std::endl;
}


//calculate Jacobian matrix
VariableSubMatrixHandler& 
Contactlaw::AssJac(
	VariableSubMatrixHandler& WorkMat,
	doublereal dCoef, 
	const VectorHandler& XCurr,
	const VectorHandler& XPrimeCurr)
{
	FullSubMatrixHandler& WM = WorkMat.SetFull();

	//node1 current data
	const integer iMomentumIndex1 = pNode1->iGetFirstMomentumIndex();
	const integer iPositionIndex1 = pNode1->iGetFirstPositionIndex();
	const Vec3& r1 = pNode1->GetXCurr();


	//node2 current data
	const integer iMomentumIndex2 = pNode2->iGetFirstMomentumIndex();
	const integer iPositionIndex2 = pNode2->iGetFirstPositionIndex();
	const Vec3& r2 = pNode2->GetXCurr();


	//obtain vector dimension
	integer iNumRows;
	integer iNumCols;
	WorkSpaceDim(&iNumRows, &iNumCols);
	WM.ResizeReset(iNumRows, iNumCols);

	for(int iCnt = 1; iCnt<=3; iCnt++){
		WM.PutRowIndex(iCnt, iMomentumIndex1+iCnt);
		WM.PutColIndex(iCnt, iPositionIndex1+iCnt);
	}	

	for(int iCnt = 1; iCnt<=3; iCnt++){
		WM.PutRowIndex(iCnt+3, iMomentumIndex2+iCnt);
		WM.PutColIndex(iCnt+3, iPositionIndex2+iCnt);
	}


	//calculate forces
	/*
	doublereal g,Zs, nu1d, nu1s, nu2d, nu2s;
	pSeabed->get(g, Zs, nu1d, nu1s, nu2d, nu2s);
	doublereal A;
	doublereal dc1_dx;
	doublereal dF_dx;

		doublereal z = XCurr(iPositionIndex+3) - Zs;
		doublereal v = XPrimeCurr(iPositionIndex+3);
		doublereal z = XCurr(iPositionIndex1+3) - Zs;
		doublereal v = XPrimeCurr(iPositionIndex1+3);
	if (z>0.0) {
	dc1_dx = 0.0;
	std::cout << "Jac00" << std::endl;
	} else {
	dc1_dx = 1.0;
	std::cout << "Jac01" << std::endl;
	}

	A = (-c - dCoef*k)*dc1_dx;


	// set value
	//どう計算すればよいのか相談
	WM.PutCoef( 1,  1, A );
	*/
	return WorkMat;
	std ::cout << "16" << std::endl;
}


/*=======================================================================================
* Private Data
*=======================================================================================*/
//set number of private data
unsigned int
Contactlaw::iGetNumPrivData(void) const
{
	return 0;
	std ::cout << "17" << std::endl;
}

/*
//set index of private data
unsigned int
Hydrostatic::iGetPrivDataIdx(const char *s) const
{	
	static const struct {
		int index;
		char name[3];
	}

	data[] = {
			{ 1, "A"},
			{ 2, "B"},
			{ 3, "C"},
	};

	for (unsigned i = 0; i < sizeof(data) / sizeof(data[0]); ++i ) {
		if (0 == strcmp(data[i].name,s)) {
			return data[i].index;
		}
	}

	silent_cerr("Hydrostatic (" << GetLabel() << "): no private data \"" << s << "\"" << std::endl);

	return 0;	
}
//function to get private data
doublereal
Hydrostatic::dGetPrivData(unsigned int i) const;
{
	switch (i) {
	case 1:
		return a;
	case 2:
		return b;
	case 3:
		return c;
	}
	throw DataManager::ErrGeneric(MBDYN_EXCEPT_ARGS);
}
*/

/*=======================================================================================
* Configure runtime processing
*=======================================================================================*/
//describe update function
void 
Contactlaw::Update(const VectorHandler& XCurr, const VectorHandler& XPrimeCurr)
{
	return;
	std ::cout << "18" << std::endl;
}
//process before each iteration
void
Contactlaw::BeforePredict(VectorHandler& /* X */ ,
					VectorHandler& /* XP */ ,
					VectorHandler& /* XPrev */ ,
					VectorHandler& /* XPPrev */ ) const
{
	return;
	std ::cout << "19" << std::endl;
}
//process after each iteration
void
Contactlaw::AfterPredict(VectorHandler& X, VectorHandler& XP)
{
	return;
	std ::cout << "20" << std::endl;
}
//process after convergence (each time step)
void
Contactlaw::AfterConvergence(const VectorHandler& X, const VectorHandler& XP)
{
	return;
	std ::cout << "21" << std::endl;
}

/*=======================================================================================
* Output
*=======================================================================================*/
//output file 
void
Contactlaw::Output(OutputHandler& OH) const
{
	if (bToBeOutput()) {
		if (OH.UseText(OutputHandler::LOADABLE)) {
			OH.Loadable() << GetLabel()
				<< std::endl;
		}
	}
	std ::cout << "22" << std::endl;
}



/*=======================================================================================
* etc
*=======================================================================================*/
//print information of connected nodes
int
Contactlaw::iGetNumConnectedNodes(void) const
{
	return 0;
	std ::cout << "23" << std::endl;
}
void
Contactlaw::GetConnectedNodes(std::vector<const Node *>& connectedNodes) const
{
	return;
	std ::cout << "24" << std::endl;
}
//output restart file
std::ostream&
Contactlaw::Restart(std::ostream& out) const
{
	return out << "# Contactlaw (" << GetLabel() << "): not implemented yet" << std::endl;
	std ::cout << "25" << std::endl;
}

/* ----------------------------- Contactlaw end -------------------------------------- */


/*=======================================================================================
*  Module init function
*=======================================================================================*/
extern "C"
int module_init(const char *module_name, void *pdm, void *php)
{
	bool UDEset = true;

	UserDefinedElemRead *rf = new UDERead<Contactlaw>;
	if (!SetUDE("Contactlaw", rf)) {
		delete rf;
		return false;
	}

	if (!UDEset) {
		silent_cerr("Contactlaw: "
			"module_init(" << module_name << ") "
			"failed" << std::endl);
		return -1;
	}

	return 0;
	std ::cout << "26" << std::endl;
}