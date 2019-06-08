package edu.stevens.cs548.clinic.service.web.soap;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.jws.soap.SOAPBinding;

import edu.stevens.cs548.clinic.service.dto.ProviderDto;
import edu.stevens.cs548.clinic.service.dto.TreatmentDto;
import edu.stevens.cs548.clinic.service.ejb.IPatientService.PatientServiceExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.ProviderNotFoundExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.ProviderServiceExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.TreatmentNotFoundExn;

@WebService(
	name="IProviderWebPort",
	targetNamespace="http://cs548.stevens.edu/clinic/service/web/soap/provider")

// TODO Use JSR-181 annotations to specify SOAP binding (document/literal wrapped).
@SOAPBinding(
		style=SOAPBinding.Style.DOCUMENT,
		use=SOAPBinding.Use.LITERAL,
		parameterStyle=SOAPBinding.ParameterStyle.WRAPPED)
/*
 * Endpoint interface for the Provider Web service.
 */
public interface IProviderWebService {
	
	@WebMethod
	public long addProvider (
			@WebParam(name="Provider-dto",
			          targetNamespace="http://cs548.stevens.edu/clinic/dto")
			ProviderDto dto) throws ProviderServiceExn;

	@WebMethod
	@WebResult(name="Provider-dto",
			   targetNamespace="http://cs548.stevens.edu/clinic/dto")
	public ProviderDto getProvider(long id) throws ProviderServiceExn;
	
	@WebMethod
	@WebResult(name="Provider-dto",
	   		   targetNamespace="http://cs548.stevens.edu/clinic/dto")
	public ProviderDto getProviderByNPI(long pid) throws ProviderServiceExn;
	
	@WebMethod
	public long addTreatment (
			@WebParam(name="treatment-dto",
			          targetNamespace="http://cs548.stevens.edu/clinic/dto")
			TreatmentDto dto) throws PatientServiceExn, ProviderServiceExn;

	@WebMethod(operationName="ProviderGetTreatment")
	@WebResult(name="treatment-dto",
	           targetNamespace="http://cs548.stevens.edu/clinic/dto")
	public TreatmentDto getTreatment(long id, long tid) throws ProviderNotFoundExn, TreatmentNotFoundExn, ProviderServiceExn;

	@WebMethod
	public String siteInfo();

}
