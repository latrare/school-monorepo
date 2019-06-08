package edu.stevens.cs548.clinic.service.web.soap;

import edu.stevens.cs548.clinic.service.dto.ProviderDto;
import edu.stevens.cs548.clinic.service.dto.TreatmentDto;
import edu.stevens.cs548.clinic.service.ejb.IPatientService.PatientServiceExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.ProviderNotFoundExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.ProviderServiceExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderService.TreatmentNotFoundExn;
import edu.stevens.cs548.clinic.service.ejb.IProviderServiceLocal;

// TODO Use JSR-181 annotations to specify Web service.
//Specify: endpoint interface (FQN), target namespace, service name, port name


public class ProviderWebService implements IProviderWebService {

	// TODO use CDI to inject the service
	IProviderServiceLocal service;

	@Override
	public long addProvider(ProviderDto dto) throws ProviderServiceExn {
		// TODO
		throw new IllegalStateException("ProviderWebService.addProvider");
	}

	@Override
	public ProviderDto getProvider(long id) throws ProviderServiceExn {
		// TODO
		throw new IllegalStateException("ProviderWebService.getProvider");
	}

	@Override
	public ProviderDto getProviderByNPI(long pid) throws ProviderServiceExn {
		// TODO
		throw new IllegalStateException("ProviderWebService.getProviderByNPI");
	}

	@Override
	public long addTreatment(TreatmentDto dto) throws PatientServiceExn, ProviderServiceExn {
		// TODO
		throw new IllegalStateException("ProviderWebService.addTreatment");
	}

	@Override
	public TreatmentDto getTreatment(long id, long tid) throws ProviderNotFoundExn, TreatmentNotFoundExn,
			ProviderServiceExn {
		// TODO
		throw new IllegalStateException("ProviderWebService.getTreatment");
	}

	@Override
	public String siteInfo() {
		// TODO
		throw new IllegalStateException("ProviderWebService.siteInfo");
	}

}
