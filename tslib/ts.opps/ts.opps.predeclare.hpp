namespace tslib {

// pre-declare template friends
template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy> class TSeries;

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> correlation(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                const TSDIM periods);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> covariance(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                                const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
                                                                const TSDIM periods);

  /*
    template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy, typename F >
    TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> applyWindowIntersection(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
    const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs,
    const U periods);
  */

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TDATA lhs,
                                                              const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TDATA lhs, const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator+(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator-(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator*(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

template<typename TDATE, typename TDATA, typename TSDIM, template<typename,typename,typename> class TSDATABACKEND, template<typename> class DatePolicy>
TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy> operator/(const TSeries<TDATE,TDATA,TSDIM,TSDATABACKEND,DatePolicy>& lhs,
                                                              const TDATA rhs);

} // namespace tslib
