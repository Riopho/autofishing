#ifndef STATE_H
#define STATE_H

/*******************************************************************************
 * Author :          rio
 * Email :           riopho@163.com
 * Last modified :   2019-05-18 11:39
 * Filename :        State.h
 * Description :     
 * *****************************************************************************/
#include <iostream>
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include "RioLog.hpp"
#include "TemplateMatch.h"

#define FSM_ON_ENTRY template <class Event,class FSM> void on_entry(Event const& ev,FSM& fsm)
#define FSM_ON_EXIT template <class Event,class FSM> void on_exit(Event const& ev,FSM& fsm)
#define FSM_STATE(x) struct x : public msm::front::state<> 

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace std;

struct Event_Main{};
struct Event_Tag{};
struct Event_Type {};
struct Event_Level {};
struct Event_Begin {};
struct Event {};
struct Event_Lack {};
struct Event_a {};

struct State_: public msm::front::state_machine_def<State_>
{
	int FightCounts;
	int BuyPowerCounts;
    FSM_STATE(Unknown)
    {
        FSM_ON_ENTRY  //unknown state 
        {
			LOG_ERR << "Unknown state, pending...";
			Sleep(3000);
			if (Match("./pic/begin1.png")) 
			{
				fsm.process_event(Event_Begin());
			}
			//decide which state to trans
        }
    };
	
    FSM_STATE(Main)
    {
        FSM_ON_ENTRY  //main ui
        {
			LOG_ERR << "Enter main UI.";
			Click("./pic/main.png");
			fsm.process_event(Event());
        }
    };

	FSM_STATE(ChooseTag)
    {
        FSM_ON_ENTRY  //choose big tag
        {
			LOG_ERR << "Choose tag."; 
        }
    };

	FSM_STATE(ChooseType)
    {
        FSM_ON_ENTRY  //choose small type
        {
			LOG_ERR << "Choose type.";
        }
    };

	FSM_STATE(ChooseLevel)
    {
        FSM_ON_ENTRY  //choose level
        {
			LOG_ERR << "Choose level."; 
        }
    };

	FSM_STATE(PressBegin)
    {
        FSM_ON_ENTRY  
        {
			LOG_ERR << "ReadyPressBegin."; 
			WaitAndClick("./pic/begin1.png");
			Sleep(3000);
			
			if (Match("./pic/right.png")) 
			{
				fsm.process_event(Event_Lack());
				return;
			}
			


			fsm.process_event(Event_a());
        }
    };

	FSM_STATE(LackPower)
    {
        FSM_ON_ENTRY  
        {
			LOG_ERR << "Lack of power,";
			Click("./pic/right.png");
			LOG_ERR << "Buy power, No. " << ++fsm.BuyPowerCounts;
			fsm.process_event(Event_a());
        }
    };

	FSM_STATE(WaitFight)
	{
        FSM_ON_ENTRY  
        {
			LOG_ERR << "WaitFight.";
			WaitAndClick("./pic/begin2.png");
			fsm.process_event(Event_a());
        }
    };

	FSM_STATE(Fighting)
	{
		FSM_ON_ENTRY
		{
			LOG_ERR << "Fight begin, No." <<++fsm.FightCounts;
			if (fsm.FightCounts > TemplateMatch::Instance()->MaxFightNum) 
			{
				LOG_ERR << "All " << TemplateMatch::Instance()->MaxFightNum << " fight end.";
				fsm.stop();
				return;
			}
			while (1)
			{
				if (Match("./pic/end.png")) 
				{
					Sleep(1000);
					if (Match("./pic/end.png")) 
					{
						Sleep(1000);
						if (Match("./pic/end.png")) 
						{
							break;
						}
					}
				}
			}
			Sleep(2000);
			Click("./pic/end.png");
			fsm.process_event(Event_a());
		}
	};

	FSM_STATE(FightEnd)
	{
		FSM_ON_ENTRY
		{
			LOG_ERR << "Fight end.";
			Wait("./pic/begin1.png");
			fsm.process_event(Event_a());
		}
	};





    typedef Unknown initial_state;

    template <class Event,class FSM>  void no_transition(Event const& e, FSM&fsm,int state)
    {
        LOG_ERR << " :no transition from state " << state
            << " on event " << typeid(e).name();
    }

    //--prevstate--event--nextstate--action--guard
    struct transition_table : mpl::vector<
		//	_row   < Unknown, Event_Main, Main>,
		//	_row   < Unknown, Event_Tag, ChooseTag>,
		//_row   < Unknown, Event_Type, ChooseType>,
		//_row   < Unknown, Event_Level, ChooseLevel>,
		_row   < Unknown, Event_Begin, PressBegin>,
		//_row   < Main, Event, ChooseTag>,
		//_row   < ChooseTag, Event, ChooseType>,
		//_row   < ChooseType, Event, ChooseLevel>,
		//_row   < ChooseLevel, Event, PressBegin>,
		_row   < PressBegin, Event_Lack, LackPower>,
		_row   < LackPower, Event_a, PressBegin>,
		_row   < PressBegin, Event_a, WaitFight>,
		_row   < WaitFight, Event_a,Fighting>,
		_row   < Fighting, Event_a, FightEnd>,
		_row < FightEnd, Event_a, Unknown>
		>
	{};
};

typedef msm::back::state_machine<State_> State;

#endif /* STATE_H */
