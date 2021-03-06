/*
幻影游戏引擎, 2009-2016, Phantom Game Engine, http://www.aixspace.com

Design Writer :   赵德贤 Dexian Zhao
Email: yuzhou_995@hotmail.com


Copyright 2009-2016 Zhao Dexian
-------------------------------------------------------------------------------------------------


-------------------------------------------------------------------------------------------------
*/
#pragma once
#include <vector>
#include "resource.h"
#include "GCAnimationCtrl.h"
#include "PhantomManager.h"

struct	FloatTrackKey
{
	INT				nKeyIndex;
	INT				nFrameIndex;
	float			fValue;
	float			fTangentMul;
	//
	Phantom::tangent2		t1,t2;
};

struct	FloatTrackKeyControl: FloatTrackKey
{
	CRect			rcBegin;
	CRect			rcEnd;
	CRect			rcTangent1,rcTangent2;
};

__interface	IFloatAnimationDataCB
{
	VOID			GetKeyData(INT id, INT param, INT nKeyIndex, FloatTrackKey& data);
	VOID			SetKeyData(INT id, INT param, INT nKeyIndex, FloatTrackKey& data);
	INT				GetKeyCount(INT id, INT param);
	INT				InsertKey(INT id, INT param, INT nFrameIndex/*0到200之间的值*/, float fValue);
	VOID			DeleteKey(INT id, INT param, INT nKeyIndex);
	VOID			SetKeyFrame(INT id, INT param, INT nKeyIndex, INT nFrameIndex);
};

//使用三个浮点回调类来组织

struct	AnimationFloat3
{
	float	v[MAX_FLOAT_EDITOR];
};

class GCTrackEditor;

class GCFloatAnimation : public CDialogEx
{
	DECLARE_DYNAMIC(GCFloatAnimation)

public:
	GCFloatAnimation(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~GCFloatAnimation();
	struct	FloatTracks
	{
		BOOL							bCanSelect;
		Phantom::FloatAnimation*				floatPtr;
		std::vector<FloatTrackKeyControl>	tracks;
		COLORREF						trackColor;
		FloatTracks(){floatPtr = 0; bCanSelect = true;}
	};
	enum TrackPosition
	{
		TrackPosition_None	=	0,
		TrackPosition_Track,
	};
	GCTrackEditor*			m_trackDlg;
// 对话框数据
	enum { IDD = IDD_CONTROL_DLG };
	//
	BOOL						IsCanEditor(Phantom::FloatAnimation* f);
	VOID						SetEditorEnable(BOOL b);
	VOID						SetCallback(Phantom::FloatAnimation* cb, INT index, BOOL bSetView = false);//
	VOID						SetRange(float fMin, float fMax);
	FloatTrackKeyControl*			GetTrackItem(INT floatIndex, INT id);
	INT							SetMoveCursor(INT* floatSelect);
	INT							GetKeyFrameByPos(INT x);
	INT							GetPosByFrame(INT nFrame);
	INT							GetPosByValue(float fValue);
	float						GetValueByPos(INT pos);
	//
	INT							GetTrackBeginX();
	INT							GetTrackBeginY();
	VOID						ResizeScroll();
	VOID						DrawTrack(CDC& dc, FloatTracks* t, const CRect& drawRect, const CSize& keySize, FloatTrackKeyControl* trackFrom, FloatTrackKeyControl* trackTo, COLORREF clr);
	VOID						DrawKeyFrames(CDC& dc, const CRect& drawRect, const CSize& keySize, INT nFrameCount, INT nTrackCount);
	VOID						DrawTrackRect(CDC& dc, const CRect& rc, COLORREF c);
	VOID						DrawTrackTangent(CDC& dc, const CRect& rc, const Phantom::tangent2& t, COLORREF c, CRect& rcT);
	VOID						DrawTrackColor(CDC& dc, const CRect& drawRect, const CSize& keySize);
	INT							GetHeightCount(){return m_nHeightCount;}
	
	VOID						Setup(float fMin, float fMax, bool bIsColor = false, INT heightCount = 15);
	INT							m_nType;
	CPoint						m_downPoint;
	//
	int							ClampY(int y);
	
	const Phantom::FloatKey*				ConvertKey(const FloatTrackKey& k);
	VOID						LerpFrame(AnimationFloat3& ret, float fLerp);
	//
	inline	float				GetViewScale(){return (1.0f / m_fViewScale);}
	float						m_fViewScale;
	//
	inline	float				GetViewMaxValue(){return m_fViewMaxValue;}
	inline	float				GetViewMinValue(){return m_fViewMinValue;}
	//
	float						m_fViewMaxValue;
	float						m_fViewMinValue;
	VOID						OnSelectKey();
	VOID						SetSelectValue(float f);
	//
	VOID						SetFrameCount(int n);
	VOID						InvalidateFrames();
	VOID						SetNull();
	struct	SelectKey
	{
		INT						nFloatIndex;
		INT						nTrackKeyIndex;
		int						tangentSelect;
		int						downFrame;
		CPoint					downPos;
		float					fSaveValue;
		CPoint					offsetTLeft;
		CPoint					offsetTRight;
	};
	FloatTracks					m_floats[MAX_FLOAT_EDITOR];
public:
	int							m_nFrameCount;
	CImage						m_bgImage;
	CSize						m_keySize;	//一个关键帧的大小
	BOOL						m_bLButtonDown;
	BOOL						m_bMButtonDown;
	//
	INT							m_nHeightCount;
	//
	CDynamicArray<SelectKey>		m_selects;
	BOOL						IsSelect(INT nFloatIndex, INT nKeyIndex);
	//INT							m_floatIndex;
	//INT							m_nTrackSelectID;
	TrackPosition				m_trackPosition;
	CEdit						m_editName;
	BOOL						m_bEditNameMode;
	float						m_fMaxValue, m_fMinValue;
	float						m_saveValue;
	BOOL						m_bDrawSelect;
	BOOL						m_bMouseSelect;
	CRect						m_selectRect;
	enum{
		TangentSelect_None	=	0,
		TangentSelect_Left,
		TangentSelect_Right,
		TangentSelect_Full,
	};
	BOOL						m_bIsColor;
	BOOL						m_bSetFrameIndex;
	VOID						OnDeletePoint();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	BOOL	PreTranslateMessage(MSG* pMsg);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};
