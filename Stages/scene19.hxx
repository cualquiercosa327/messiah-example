//PRIEST BOSS ARENA


SubRoutine(InitSceneSound19)
{
	call(CDSTop);
	call(fadetoblack,2);
	call(AutoTesselation,false);
}

SubRoutine(InitScene19)
{
			InitActor(Bob1,0,Gactorangle,"elevent");
			#include "messiahscripts\enemies\c1_priestl.spt"
			call(loadpreloaddb,9);
			float(_set,timer,0);
			float(_set,VarBit,AllHelp);
			float(_set,VarBit01,AllHelp);
			float(_set,AIVisionToggle,1);
			call(PlayerInput,0);
			call(CDStop);
			call(CDForcePlay,1);
			callsub(InitSceneSound19);
			call(DisplayHUD,0);
}

Subroutine(Sub_FakeDepossesion)
{
	float(_seti,SubVar1,VColSphereSize);
	if(SubVar1<BobSphereSize || VSniperMode>0)
	{
		float(_set,SubVar1,0);	//Do this if there is not room for Bob (Narrow passages etc.)
	}

	if(SubVar1!=0)
	{
		SpawnActor(Bob1,0,0,0,TRUE);
	}
	else
	{
		vector(_settoactorpos,TmpVector);
		vector(_copyx,TmpVector,TmpFloat);
		vector(_copyy,TmpVector,TmpFloat2);
		vector(_copyz,TmpVector,TmpFloat3);
		SpawnActor(Bob1,TmpFloat,TmpFloat2,TmpFloat3);
	}

	resetbone(PlayerHeadBone);
	resetbone(2);
	call(CameraFollow,FALSE);
	call(AICon,TRUE);

	call(CheckAttached,_CANormal);
	Direction(_clr,_DIRAIRemoveFlags);
	sample(SFXDePossess,-1);
	call(ChangeSniperMode,-2,0);
}

SubRoutine(MainScene19)
{
	if(VCurSet=="arena01")
	{
		CurEnvTrigger("reset");
		call(expset1,0,-2000,0);
		if(vrnd<20 && timer<=2)
		{
			vector(_set,Gactorpos,-12605,33307,9536);
			spawnparticle(fx_windmatter,-1,Gactorpos,emptyvector,-1);
		}

		CurEnvTrigger("boss");
		if(timer<=4)
		{
			float(_set,TmpFloat,0xff2200);
			call(expset1,TmpFloat,400,-1);
		}
		else
		{
			float(_set,TmpFloat,0x000000);
			call(expset1,TmpFloat,10,-1);
		}
	}
}

SubRoutine(BackgroundTriggerChecksScene19)
{
	if(VCDToggle==0)
	{
		call(CDForcePlay,1);
		float(_set,HudTimer,1);
	}
	if(VCurSet=="arena01")
	{
		if(VarBit&=Help03)
		{
			CutScene("startup");
			call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
			call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
			float(_clr,VarBit,Help03);
		}

		if(VAICon==0)
		{
			if(VarBit01&=Help01)
			{
				setactortotrigger("arena01","debut");
				float(_clr,VarBit01,Help01);
			}
		}
		else
		{
			if(VAIClass==_AIClassBeast)
			{
				if(VarBit&=Help04)
				{
					CurEnvTrigger("boss");
					if(VTrigger==_DIREnvTrigger)
					{
						CutScene("around");
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
						sample(SFXCreepy01,-1);
						float(_clr,VarBit,Help04);
						float(_set,timer2,0);
					}
				}
				if(VarBit&=Help05)
				{
					CurEnvTrigger("reset");
					if(VTrigger==_DIREnvTrigger)
					{
						float(_set,timer2,0);
						float(_clr,VarBit,Help05);
						CutScene("around2");
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
						sample(SFXSatanGetAway,Gactorpos);
					}
				}
				if(VarBit&!=Help05 && VarBit&=Help06)
				{
					float(_add,timer2,1)
					if(timer2>=20)
					{
						KillActor();
						vector(_set,Gactorpos,-12059.91,33200.016,7846.446);
						vector(_set,Gactorangle,0,1843,0);
						InitActor(beast,Gactorpos,Gactorangle,"arena01",TRUE,1);
						float(_clr,VarBit,Help06);
						float(_set,timer2,0);
					}
				}
				if(VarBit&!=Help06 && VarBit&=Help07)
				{
					float(_add,timer2,1);
					if(timer2>=100)
					{
						float(_set,timer,1);
						float(_set,timer2,0);
						float(_clr,VarBit,Help07);
					}
				}
										
				if(Vaction==BeastAttackSequence)
				{
					if(vframe==1000)
					{
						callsub(Sub_FakeDepossesion);
						float(_set,timer,10);
					}
				}
			}

			if(timer==1)
			{
				if(VAIClass==_AIClassBeast)
				{
					if(VarBit&=Help01)
					{
						if(Vaction!=BeastAttackSequence)
						{
							CutScene("first");
							call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
							call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
							spawnaction(BeastAttackSequence);
							float(_clr,VarBit,Help01);
						}
					}
				}

				if(VAIClass==_AIClassPriest)
				{
					if(VarBit&=Help02)
					{
						if(Vaction!=PriestAttackSequence)
						{
							spawnaction(PriestAttackSequence);
							float(_clr,VarBit,Help02);
						}
					}
				}

				if(VarBit&!=Help01 && VarBit&!=Help02)
				{
					float(_set,timer,2);
				}
			}
		}

		if(VAICon==0)
		{
			if(timer==10)
			{
				float(_add,timer2,1);
				if(timer2>=300)
				{
					CutScene("end");
					call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
					call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
					float(_set,timer,11);
					float(_set,timer2,0);
				}
			}
			if(timer==11)
			{
				CurEnvTrigger("lite");
				call(SetTriggerObjFlag,1,_clr,_SXObjInvisible);
				call(expset1,0,1624,1624);
				float(_set,timer,12);
			}
			elseif(timer==12)
			{
				CurEnvTrigger("lite");
				call(expget,1,TmpFloat);
				if(TmpFloat==37)
				{
					if(VLanguage==0)
					{
						if(VCDTrack!=31)
						{
							call(cdplay,31,0);
						}
					}
					elseif(VLanguage==1 || VLanguage==3)
					{
						if(VCDTrack!=32)
						{
							call(cdplay,32,0);
						}
					}
					elseif(VLanguage==2 || VLanguage==4)
					{
						if(VCDTrack!=33)
						{
							call(cdplay,33,0);
						}
					}
					//sample(SFXSatanHologram,-1);
				}
				if(TmpFloat>=100 && TmpFloat<=110)
				{
					if(VAIClass==_AIClassAngel)
					{
						CurEnvTrigger("debut");
						if(VTrigger==_DIREnvTrigger)
						{
							KillActor();
						}
					}
				}
				if(TmpFloat==120)
				{
					if(VarBit&=Help24)
					{
						setactortotrigger("arena01","lite");
						float(_clr,VarBit,Help24);
					}
				}
				elseif(TmpFloat==1624) //is that the correct end frame ??????
				{
					CurEnvTrigger("lite");
					call(SetTriggerObjFlag,1,_or,_SXObjInvisible);
					float(_set,timer,13);
				}
			}
			elseif(timer==13)
			{
				CurEnvTrigger("lite");
				if(VTrigger==_DIREnvTrigger)
				{
					if(Vaction!=BobTalksToGod)
					{
					//	call(FadeToBlack,0);
						spawnaction(BobTalksToGod);
						CutScene("god");
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
						call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
						//sample(SFXBobGodDialogue,-1);
						if(VLanguage==0)
						{
							call(cdplay,28,0);
						}
						elseif(VLanguage==1 || VLanguage==3)
						{
							call(cdplay,29,0);
						}
						elseif(VLanguage==2 || VLanguage==4)
						{
							call(cdplay,30,0);
						}
						float(_set,timer,14);
					}
				}
			}
			elseif(timer==14)
			{
				CurEnvTrigger("bobreset");
				call(SetTriggerObjFlag,2,_clr,_SXObjInvisible);
				float(_set,timer,15);
				float(_set,timer2,0);
				float(_set,ColorRange,0x000000);
			}
			elseif(timer==15)
			{
				CurEnvTrigger("bobreset");
				float(_add,timer2,2);
				if(timer2<400)
				{
					if(timer2&=64)
					{
						float(_set,TmpFloat2,0x010101);
						float(_add,ColorRange,TmpFloat2);
						call(expset2,1,ColorRange,0);
						call(expset1,1,ColorRange,0);
					}
				}
				else
				{
					float(_set,timer2,0);
					float(_set,timer,16);
				}
			}
			elseif(timer==16)
			{
				if(VCutSceneFrame==250)
				{
					CutScene("pray");
					call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
					call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
					float(_set,timer,17);
				}
			}
			elseif(timer==17)
			{
				if(VCutSceneFrame>=700)
				{
					float(_set,timer2,0);
					float(_set,timer,19);
				}
			}
			elseif(timer==19)
			{
				CutScene("pray02");
				call(ChangeCutScene,_SXCUTflag,_or,_SXCUTnosmooth);
				call(ChangeCutScene,_SXCUTflag,_or,_SXCUTdontreset);
				float(_set,timer,21);
				float(_set,timer2,0);
			}
			elseif(timer==21)
			{
				if(VCutSceneFrame==810)
				{
					call(wCheckViewCollision,0,0,0,0);
				}
				elseif(VCutSceneFrame>=860)
				{
					call(CutSceneEnd);
					setactortotrigger("arena01","bobreset");
					call(FaceTriggerDirection);
					float(_set,timer,22);
				}
			}
			elseif(timer==22)
			{
				direction(_clr,_noDIR);
				direction(_or,_DIRForward|_DIRmove);
				CurEnvTrigger("lift");
				if(VTrigger==_DIREnvTrigger)
				{
					float(_set,timer,23);
				}
			}
			elseif(timer==23)
			{
				CurEnvTrigger("lift");
				call(KeyObjTrigger,255,1);
				kfsample(SFXLiftStart,SFXLiftMove,-1,SFXLiftEnd);
				call(FadeToBlack,0);
				float(_set,timer2,0);
				float(_set,timer,24);
			}
			elseif(timer==24)
			{
				Camera(elevator_camera_distance,elevator_camera_angle);
				Target(elevator_camera_Tdistance,elevator_camera_Tangle);

				float(_add,timer2,1)
				if(timer2>=400)
				{
					actorflag(_or,_AFLAGresetfallalt);
					call(DisplayHUD,1);
					if(HudTimer==1)
					{
						call(CDForcePlay,0);
					}
					call(LoadLevel,"stor_04",5);
				}
			}
		}
	}
}