#pragma once

#include "../Share/IDataWriter.h"
#include "../Share/BoostDefine.h"
#include "../Share/StdUtils.hpp"
#include "../Share/BoostMappingFile.hpp"

NS_OTP_BEGIN
class WTSTickData;
class WTSOrdQueData;
class WTSOrdDtlData;
class WTSTransData;
class WTSVariant;
NS_OTP_END

USING_NS_OTP;

class WTSBaseDataMgr;
class StateMonitor;
class UDPCaster;

class DataManager : public IDataWriterSink
{
public:
	DataManager();
	~DataManager();

public:
	bool init(WTSVariant* params, WTSBaseDataMgr* bdMgr, StateMonitor* stMonitor, UDPCaster* caster = NULL);
	void release();

	bool writeTick(WTSTickData* curTick, bool bNeedProc = true);

	bool writeOrderQueue(WTSOrdQueData* curOrdQue);

	bool writeOrderDetail(WTSOrdDtlData* curOrdDetail);

	bool writeTransaction(WTSTransData* curTrans);

	void transHisData(const char* sid);
	
	bool isSessionProceeded(const char* sid);

	WTSTickData* getCurTick(const char* code);

public:
	//////////////////////////////////////////////////////////////////////////
	//IDataWriterSink
	virtual IBaseDataMgr* getBDMgr() override;

	virtual bool canSessionReceive(const char* sid) override;

	virtual void broadcastTick(WTSTickData* curTick) override;

	virtual CodeSet* getSessionComms(const char* sid) override;

	virtual uint32_t getTradingDate(const char* pid) override;

	/*
	*	��������ģ�����־
	*	@ll			��־����
	*	@message	��־����
	*/
	virtual void outputWriterLog(WTSLogLevel ll, const char* format, ...) override;

private:
	IDataWriter*		_writer;
	FuncDeleteWriter	_remover;
	WTSBaseDataMgr*		_bd_mgr;
	StateMonitor*		_state_mon;
	UDPCaster*			_udp_caster;
};
