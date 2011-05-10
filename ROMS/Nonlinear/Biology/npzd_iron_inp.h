      SUBROUTINE read_BioPar (model, inp, out, Lwrite)
!
!svn $Id$
!================================================== Hernan G. Arango ===
!  Copyright (c) 2002-2011 The ROMS/TOMS Group                         !
!    Licensed under a MIT/X style license                              !
!    See License_ROMS.txt                                              !
!=======================================================================
!                                                                      !
!  This routine reads in NPZD iron (Fiechter, et al. 2009) ecosystem   !
!  model input parameters. They are specified in input script          !
!  "npzd_iron.in".                                                     !
!                                                                      !
!=======================================================================
!
      USE mod_param
      USE mod_parallel
      USE mod_biology
      USE mod_ncparam
      USE mod_scalars
!
      implicit none
!
!  Imported variable declarations
!
      logical, intent(in) :: Lwrite
      integer, intent(in) :: model, inp, out
!
!  Local variable declarations.
!
      integer :: Npts, Nval, i, itrc, ng, status

      integer :: decode_line, load_i, load_l, load_r

      logical, dimension(NBT,Ngrids) :: Ltrc

      real(r8), dimension(NBT,Ngrids) :: Rbio

      real(r8), dimension(100) :: Rval

      character (len=40 ) :: KeyWord
      character (len=256) :: line
      character (len=256), dimension(100) :: Cval
!
!-----------------------------------------------------------------------
!  Read in NPZD iron (Fiechter, et al. 2009) model parameters.
!-----------------------------------------------------------------------
!
#ifdef ANA_BIOLOGY
      IF (.not.allocated(BioIni)) allocate ( BioIni(MT,Ngrids) )
#endif
      DO WHILE (.TRUE.)
        READ (inp,'(a)',ERR=10,END=20) line
        status=decode_line(line, KeyWord, Nval, Cval, Rval)
        IF (status.gt.0) THEN
          IF (TRIM(KeyWord).eq.'Lbiology') THEN
            Npts=load_l(Nval, Cval, Ngrids, Lbiology)
          ELSE IF (TRIM(KeyWord).eq.'BioIter') THEN
            Npts=load_i(Nval, Rval, Ngrids, BioIter)
#ifdef ANA_BIOLOGY
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iNO3_)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iNO3_,1))
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iPhyt)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iPhyt,1))
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iZoop)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iZoop,1))
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iSDet)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iSDet,1))
# ifdef IRON_LIMIT
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iFphy)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iFphy,1))
          ELSE IF (TRIM(KeyWord).eq.'BioIni(iFdis)') THEN
            Npts=load_r(Nval, Rval, Ngrids, BioIni(iFdis,1))
# endif
#endif
          ELSE IF (TRIM(KeyWord).eq.'PARfrac') THEN
            Npts=load_r(Nval, Rval, Ngrids, PARfrac)
          ELSE IF (TRIM(KeyWord).eq.'AttSW') THEN
            Npts=load_r(Nval, Rval, Ngrids, AttSW)
          ELSE IF (TRIM(KeyWord).eq.'AttPhy') THEN
            Npts=load_r(Nval, Rval, Ngrids, AttPhy)
          ELSE IF (TRIM(KeyWord).eq.'PhyIS') THEN
            Npts=load_r(Nval, Rval, Ngrids, PhyIS)
          ELSE IF (TRIM(KeyWord).eq.'Vm_NO3') THEN
            Npts=load_r(Nval, Rval, Ngrids, Vm_NO3)
          ELSE IF (TRIM(KeyWord).eq.'PhyMRD') THEN
            Npts=load_r(Nval, Rval, Ngrids, PhyMRD)
          ELSE IF (TRIM(KeyWord).eq.'PhyMRN') THEN
            Npts=load_r(Nval, Rval, Ngrids, PhyMRN)
          ELSE IF (TRIM(KeyWord).eq.'K_NO3') THEN
            Npts=load_r(Nval, Rval, Ngrids, K_NO3)
          ELSE IF (TRIM(KeyWord).eq.'Ivlev') THEN
            Npts=load_r(Nval, Rval, Ngrids, Ivlev)
          ELSE IF (TRIM(KeyWord).eq.'ZooGR') THEN
            Npts=load_r(Nval, Rval, Ngrids, ZooGR)
          ELSE IF (TRIM(KeyWord).eq.'ZooEED') THEN
            Npts=load_r(Nval, Rval, Ngrids, ZooEED)
          ELSE IF (TRIM(KeyWord).eq.'ZooEEN') THEN
            Npts=load_r(Nval, Rval, Ngrids, ZooEEN)
          ELSE IF (TRIM(KeyWord).eq.'ZooMRD') THEN
            Npts=load_r(Nval, Rval, Ngrids, ZooMRD)
          ELSE IF (TRIM(KeyWord).eq.'ZooMRN') THEN
            Npts=load_r(Nval, Rval, Ngrids, ZooMRN)
          ELSE IF (TRIM(KeyWord).eq.'DetRR') THEN
            Npts=load_r(Nval, Rval, Ngrids, DetRR)
          ELSE IF (TRIM(KeyWord).eq.'wPhy') THEN
            Npts=load_r(Nval, Rval, Ngrids, wPhy)
          ELSE IF (TRIM(KeyWord).eq.'wDet') THEN
            Npts=load_r(Nval, Rval, Ngrids, wDet)
#ifdef IRON_LIMIT
          ELSE IF (TRIM(KeyWord).eq.'T_Fe') THEN
            Npts=load_r(Nval, Rval, Ngrids, T_Fe)
          ELSE IF (TRIM(KeyWord).eq.'A_Fe') THEN
            Npts=load_r(Nval, Rval, Ngrids, A_Fe)
          ELSE IF (TRIM(KeyWord).eq.'B_Fe') THEN
            Npts=load_r(Nval, Rval, Ngrids, B_Fe)
          ELSE IF (TRIM(KeyWord).eq.'K_FeC') THEN
            Npts=load_r(Nval, Rval, Ngrids, K_FeC)
          ELSE IF (TRIM(KeyWord).eq.'FeRR') THEN
            Npts=load_r(Nval, Rval, Ngrids, FeRR)
# ifdef IRON_RELAX
          ELSE IF (TRIM(KeyWord).eq.'FeHmin') THEN
            Npts=load_r(Nval, Rval, Ngrids, FeHmin)
          ELSE IF (TRIM(KeyWord).eq.'FeNudgTime') THEN
            Npts=load_r(Nval, Rval, Ngrids, FeNudgTime)
          ELSE IF (TRIM(KeyWord).eq.'FeMax') THEN
            Npts=load_r(Nval, Rval, Ngrids, FeMax)
# endif
#endif
          ELSE IF (TRIM(KeyWord).eq.'TNU2') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                nl_tnu2(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'TNU4') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                nl_tnu4(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'ad_TNU2') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                ad_tnu2(i,ng)=Rbio(itrc,ng)
                tl_tnu2(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'ad_TNU4') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                ad_tnu4(i,ng)=Rbio(itrc,ng)
                ad_tnu4(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'AKT_BAK') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                Akt_bak(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'ad_AKT_fac') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                ad_Akt_fac(i,ng)=Rbio(itrc,ng)
                tl_Akt_fac(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'TNUDG') THEN
            Npts=load_r(Nval, Rval, NBT*Ngrids, Rbio)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                Tnudg(i,ng)=Rbio(itrc,ng)
              END DO
            END DO
#ifdef TS_PSOURCE
          ELSE IF (TRIM(KeyWord).eq.'LtracerSrc') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idbio(itrc)
                LtracerSrc(i,ng)=Ltrc(itrc,ng)
              END DO
            END DO
#endif
          ELSE IF (TRIM(KeyWord).eq.'Hout(idTvar)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idTvar(idbio(itrc))
                IF (i.eq.0) THEN
                  IF (Master) WRITE (out,30)                            &
     &                        'idTvar(idbio(', itrc, '))'
                  exit_flag=5
                  RETURN
                END IF
                Hout(i,ng)=Ltrc(itrc,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Hout(idTsur)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idTsur(idbio(itrc))
                IF (i.eq.0) THEN
                  IF (Master) WRITE (out,30)                            &
     &                              'idTsur(idbio(', itrc, '))'
                  exit_flag=5
                  RETURN
                END IF
                Hout(i,ng)=Ltrc(itrc,ng)
              END DO
            END DO
#if defined AVERAGES    || \
   (defined AD_AVERAGES && defined ADJOINT) || \
   (defined RP_AVERAGES && defined TL_IOMS) || \
   (defined TL_AVERAGES && defined TANGENT)
          ELSE IF (TRIM(KeyWord).eq.'Aout(idTvar)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO itrc=1,NBT
                i=idTvar(idbio(itrc))
                Aout(i,ng)=Ltrc(itrc,ng)
              END DO
            END DO
#endif
#ifdef DIAGNOSTICS_TS
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTrate)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTrate),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iThadv)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iThadv),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTxadv)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTxadv),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTyadv)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTyadv),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTvadv)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTvadv),ng)=Ltrc(i,ng)
              END DO
            END DO
# if defined TS_DIF2 || defined TS_DIF4
          ELSE IF (TRIM(KeyWord).eq.'Dout(iThdif)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iThdif),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTxdif)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTxdif),ng)=Ltrc(i,ng)
              END DO
            END DO
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTydif)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTydif),ng)=Ltrc(i,ng)
              END DO
            END DO
#  if defined MIX_GEO_TS || defined MIX_ISO_TS
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTsdif)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTsdif),ng)=Ltrc(i,ng)
              END DO
            END DO
#  endif
# endif
          ELSE IF (TRIM(KeyWord).eq.'Dout(iTvdif)') THEN
            Npts=load_l(Nval, Cval, NBT*Ngrids, Ltrc)
            DO ng=1,Ngrids
              DO i=1,NBT
                itrc=idbio(i)
                Dout(idDtrc(itrc,iTvdif),ng)=Ltrc(i,ng)
              END DO
            END DO
#endif
          END IF
        END IF
      END DO
  10  IF (Master) WRITE (out,40) line
      exit_flag=4
      RETURN
  20  CONTINUE
!
!-----------------------------------------------------------------------
!  Report input parameters.
!-----------------------------------------------------------------------
!
      IF (Lwrite) THEN
        DO ng=1,Ngrids
          IF (Lbiology(ng)) THEN
            WRITE (out,50) ng
            WRITE (out,60) BioIter(ng), 'BioIter',                      &
     &            'Number of iterations for nonlinear convergence.'
#ifdef ANA_BIOLOGY
            WRITE (out,70) BioIni(iNO3_,ng), 'BioIni(iNO3_)',           &
     &            'Nitrate initial concentration (mmol/m3).'
            WRITE (out,70) BioIni(iPhyt,ng), 'BioIni(iPhyt)',           &
     &            'Phytoplankton initial concentration (mmol/m3).'
            WRITE (out,70) BioIni(iZoop,ng), 'BioIni(iZoop)',           &
     &            'Zooplankton initial concentration (mmol/m3).'
            WRITE (out,70) BioIni(iSDet,ng), 'BioIni(iSDet)',           &
     &            'Small detritus initial concentration (mmol/m3).'
# ifdef IRON_LIMIT
            WRITE (out,70) BioIni(iFphy,ng), 'BioIni(iFphy)',           &
     &            'Phyto-assoc. Fe initial concentration (mumol/m3).'
            WRITE (out,70) BioIni(iFdis,ng), 'BioIni(iFdis)',           &
     &            'DIssolved Fe initial concentration (mumol/m3).'
# endif
#endif
            WRITE (out,80) PARfrac(ng), 'PARfrac',                      &
     &            'Fraction of shortwave radiation that is',            &
     &            'photosynthetically active (nondimensional).'
            WRITE (out,70) AttSW(ng), 'AttSW',                          &
     &            'Light attenuation of seawater (m-1).'
            WRITE (out,70) AttPhy(ng), 'AttPhy',                        &
     &            'Light attenuation by phytoplankton (m2/mmole_N).'
            WRITE (out,80) PhyIS(ng), 'PhyIS',                          &
     &            'Phytoplankton growth, initial slope of P-I curve',   &
     &            '(m2/W).'
            WRITE (out,70) Vm_NO3(ng), 'Vm_NO3',                        &
     &            'Nitrate upatake rate (day-1).'
            WRITE (out,70) PhyMRD(ng), 'PhyMRD',                        &
     &            'Phytoplankton mortality rate to Detritus (day-1)'
            WRITE (out,70) PhyMRN(ng), 'PhyMRN',                        &
     &            'Phytoplankton mortality rate to Nitrogen (day-1)'
            WRITE (out,80) K_NO3(ng), 'K_NO3',                          &
     &            'Inverse half-saturation for phytoplankton NO3',      &
     &            'uptake (1/(mmol m-3)).'
            WRITE (out,80) Ivlev(ng), 'Ivlev',                          &
     &            'Ivlev constant for zooplankton grazing',             &
     &            '(nondimensional).'
            WRITE (out,70) ZooGR(ng), 'ZooGR',                          &
     &            'Zooplankton maximum growth rate (day-1).'
            WRITE (out,80) ZooEED(ng), 'ZooEED',                        &
     &            'Zooplankton excretion efficiency to Detritus',       &
     &            'pool (nondimensional).'
            WRITE (out,80) ZooEEN(ng), 'ZooEEN',                        &
     &            'Zooplankton excretion efficiency to Nitrogen',       &
     &            'pool (nondimensional).'
            WRITE (out,70) ZooMRD(ng), 'ZooMRD',                        &
     &            'Zooplankton mortality rate to Detritus (day-1).'
            WRITE (out,70) ZooMRN(ng), 'ZooMRN',                        &
     &            'Zooplankton mortality rate to Nitrogen (day-1).'
            WRITE (out,70) DetRR(ng), 'DetRR',                          &
     &            'Detritus remineralization rate (day-1).'
            WRITE (out,70) wPhy(ng), 'wPhy',                            &
     &            'Phytoplankton sinking rate (m/day).'
            WRITE (out,70) wDet(ng), 'wDet',                            &
     &            'Detrital sinking rate (m/day).'
#ifdef IRON_LIMIT
            WRITE (out,70) T_Fe(ng), 'T_Fe',                            &
     &            'Iron uptake time scale (day-1).'
            WRITE (out,70) A_Fe(ng), 'A_Fe',                            &
     &            'Empirical Fe:C power (-).'
            WRITE (out,70) B_Fe(ng), 'B_Fe',                            &
     &            'Empirical Fe:C coefficient (1/M-C).'
            WRITE (out,70) K_FeC(ng), 'K_FeC',                          &
     &            'Fe:C at F=0.5 (muM-Fe/M-C).'
            WRITE (out,70) FeRR(ng), 'FeRR',                            &
     &            'Fe remineralization rate (day-1).'
# ifdef IRON_RELAX
            WRITE (out,70) FeHmin(ng), 'FeHmin',                        &
     &            'Minimum coastal bathymetry (m) for Fe nudging.'
            WRITE (out,70) FeNudgTime(ng), 'FeNudgTime',                &
     &            'Fe nudging time scale (days) at h <= FeHmin.'
            WRITE (out,70) FeMax(ng), 'FeMax',                          &
     &            'Fe value (mmoles/m3) used in coastal nudging.'
# endif
#endif
#ifdef TS_DIF2
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,90) nl_tnu2(i,ng), 'nl_tnu2', i,               &
     &              'NLM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# ifdef ADJOINT
              WRITE (out,90) ad_tnu2(i,ng), 'ad_tnu2', i,               &
     &              'ADM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,90) tl_tnu2(i,ng), 'tl_tnu2', i,               &
     &              'TLM Horizontal, harmonic mixing coefficient',      &
     &              '(m2/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
#ifdef TS_DIF4
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,90) nl_tnu4(i,ng), 'nl_tnu4', i,               &
     &              'NLM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# ifdef ADJOINT
              WRITE (out,90) ad_tnu4(i,ng), 'ad_tnu4', i,               &
     &              'ADM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,90) tl_tnu4(i,ng), 'tl_tnu4', i,               &
     &              'TLM Horizontal, biharmonic mixing coefficient',    &
     &              '(m4/s) for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE(out,90) Akt_bak(i,ng), 'Akt_bak', i,                &
     &             'Background vertical mixing coefficient (m2/s)',     &
     &             'for tracer ', i, TRIM(Vname(1,idTvar(i)))
            END DO
#ifdef FORWARD_MIXING
            DO itrc=1,NBT
              i=idbio(itrc)
# ifdef ADJOINT
              WRITE (out,90) ad_Akt_fac(i,ng), 'ad_Akt_fac', i,         &
     &              'ADM basic state vertical mixing scale factor',     &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
# if defined TANGENT || defined TL_IOMS
              WRITE (out,90) tl_Akt_fac(i,ng), 'tl_Akt_fac', i,         &
     &              'TLM basic state vertical mixing scale factor',     &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
# endif
            END DO
#endif
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,90) Tnudg(i,ng), 'Tnudg', i,                   &
     &              'Nudging/relaxation time scale (days)',             &
     &              'for tracer ', i, TRIM(Vname(1,idTvar(i)))
            END DO
#ifdef TS_PSOURCE
            DO itrc=1,NBT
              i=idbio(itrc)
              WRITE (out,100) LtracerSrc(i,ng), 'LtracerSrc',           &
     &              i, 'Processing point sources/Sink on tracer ', i,   &
     &              TRIM(Vname(1,idTvar(i)))
            END DO
#endif
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (Hout(idTvar(i),ng)) WRITE (out,110)                   &
     &            Hout(idTvar(i),ng), 'Hout(idTvar)',                   &
     &            'Write out tracer ', i, TRIM(Vname(1,idTvar(i)))
            END DO
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (Hout(idTsur(i),ng)) WRITE (out,110)                   &
     &            Hout(idTsur(i),ng), 'Hout(idTsur)',                   &
     &            'Write out tracer flux ', i, TRIM(Vname(1,idTvar(i)))
            END DO
#if defined AVERAGES    || \
   (defined AD_AVERAGES && defined ADJOINT) || \
   (defined RP_AVERAGES && defined TL_IOMS) || \
   (defined TL_AVERAGES && defined TANGENT)
            WRITE (out,'(1x)')
            DO itrc=1,NBT
              i=idbio(itrc)
              IF (Aout(idTvar(i),ng)) WRITE (out,110)                   &
     &            Aout(idTvar(i),ng), 'Aout(idTvar)',                   &
     &            'Write out averaged tracer ', i,                      &
     &            TRIM(Vname(1,idTvar(i)))
            END DO
#endif
#ifdef DIAGNOSTICS_TS
            WRITE (out,'(1x)')
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTrate),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTrate)',                 &
     &            'Write out rate of change of tracer ', itrc,          &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iThadv),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iThadv)',                 &
     &            'Write out horizontal advection, tracer ', itrc,      &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTxadv),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTxadv)',                 &
     &            'Write out horizontal X-advection, tracer ', itrc,    &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTyadv),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTyadv)',                 &
     &            'Write out horizontal Y-advection, tracer ', itrc,    &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTvadv),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTvadv)',                 &
     &            'Write out vertical advection, tracer ', itrc,        &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
# if defined TS_DIF2 || defined TS_DIF4
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iThdif),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iThdif)',                 &
     &            'Write out horizontal diffusion, tracer ', itrc,      &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(i,iTxdif),ng))                            &
     &          WRITE (out,110) .TRUE., 'Dout(iTxdif)',                 &
     &            'Write out horizontal X-diffusion, tracer ', itrc,    &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTydif),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTydif)',                 &
     &            'Write out horizontal Y-diffusion, tracer ', itrc,    &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
#  if defined MIX_GEO_TS || defined MIX_ISO_TS
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTsdif),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTsdif)',                 &
     &            'Write out horizontal S-diffusion, tracer ', itrc,    &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
#  endif
# endif
            DO i=1,NBT
              itrc=idbio(i)
              IF (Dout(idDtrc(itrc,iTvdif),ng))                         &
     &          WRITE (out,110) .TRUE., 'Dout(iTvdif)',                 &
     &            'Write out vertical diffusion, tracer ', itrc,        &
     &            TRIM(Vname(1,idTvar(itrc)))
            END DO
#endif
          END IF
        END DO
      END IF
!
!-----------------------------------------------------------------------
!  Rescale biological tracer parameters.
!-----------------------------------------------------------------------
!
!  Take the square root of the biharmonic coefficients so it can
!  be applied to each harmonic operator.
!
      DO ng=1,Ngrids
        DO itrc=1,NBT
          i=idbio(itrc)
          nl_tnu4(i,ng)=SQRT(ABS(nl_tnu4(i,ng)))
#ifdef ADJOINT
          ad_tnu4(i,ng)=SQRT(ABS(ad_tnu4(i,ng)))
#endif
#if defined TANGENT || defined TL_IOMS
          tl_tnu4(i,ng)=SQRT(ABS(tl_tnu4(i,ng)))
#endif
!
!  Compute inverse nudging coefficients (1/s) used in various tasks.
!
          IF (Tnudg(i,ng).gt.0.0_r8) THEN
            Tnudg(i,ng)=1.0_r8/(Tnudg(i,ng)*86400.0_r8)
          ELSE
            Tnudg(i,ng)=0.0_r8
          END IF
        END DO
      END DO

  30  FORMAT (/,' read_BioPar - variable info not yet loaded, ',        &
     &        a,i2.2,a)
  40  FORMAT (/,' read_BioPar - Error while processing line: ',/,a)
  50  FORMAT (/,/,' NPZD-IRON Model Parameters, Grid: ',i2.2,           &
     &        /,  ' ====================================',/)
  60  FORMAT (1x,i10,2x,a,t30,a)
  70  FORMAT (1p,e11.4,2x,a,t30,a)
  80  FORMAT (1p,e11.4,2x,a,t30,a,/,t32,a)
  90  FORMAT (1p,e11.4,2x,a,'(',i2.2,')',t30,a,/,t32,a,i2.2,':',1x,a)
 100  FORMAT (10x,l1,2x,a,'(',i2.2,')',t30,a,i2.2,':',1x,a)
 110  FORMAT (10x,l1,2x,a,t30,a,i2.2,':',1x,a)

      RETURN
      END SUBROUTINE read_BioPar
