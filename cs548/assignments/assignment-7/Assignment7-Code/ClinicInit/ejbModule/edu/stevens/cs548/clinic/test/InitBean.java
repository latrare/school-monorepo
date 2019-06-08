package edu.stevens.cs548.clinic.test;

import java.util.logging.Logger;

import javax.annotation.PostConstruct;
import javax.ejb.LocalBean;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.inject.Inject;

import edu.stevens.cs548.clinic.service.dto.PatientDto;
import edu.stevens.cs548.clinic.service.dto.util.PatientDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.ProviderDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.TreatmentDtoFactory;
import edu.stevens.cs548.clinic.service.ejb.IPatientService.PatientServiceExn;
import edu.stevens.cs548.clinic.service.ejb.IPatientServiceLocal;
import edu.stevens.cs548.clinic.service.ejb.IProviderServiceLocal;

/**
 * Session Bean implementation class TestBean
 */
@Singleton
@LocalBean
@Startup
public class InitBean {

	private static Logger logger = Logger.getLogger(InitBean.class.getCanonicalName());

	/**
	 * Default constructor.
	 */
	public InitBean() {
	}
	
	// Do NOT use this
//	@PersistenceContext(unitName="ClinicDomain")
//	EntityManager em;
	
	@Inject
	private IPatientServiceLocal patientService;
	
	@Inject
	private IProviderServiceLocal providerService;

	@PostConstruct
	private void init() {
		/*
		 * Put your testing logic here. Use the logger to display testing output in the server logs.
		 */
		logger.info("Your name here: ");

		try {

//			IPatientDAO patientDAO = new PatientDAO(em);
//			IProviderDAO providerDAO = new ProviderDAO(em);
//			ITreatmentDAO treatmentDAO = new TreatmentDAO(em);
//
//			PatientDtoFactory patientFactory = new PatientFactory();
//			ProviderFactory providerFactory = new ProviderFactory();
//			TreatmentFactory treatmentFactory = new TreatmentFactory();
			
			PatientDtoFactory patientFactory = new PatientDtoFactory();
			ProviderDtoFactory providerFactory = new ProviderDtoFactory();
			TreatmentDtoFactory treatmentFactory = new TreatmentDtoFactory();
			
			/*
			 * Clear the database and populate with fresh data.
			 * 
			 * If we ensure that deletion of patients cascades deletes of treatments,
			 * then we only need to delete patients.
			 */
			
//			patientDAO.deletePatients();
			
//			Patient john = patientFactory.createPatient(12345678L, "John Doe");
//			patientDAO.addPatient(john);
			
			PatientDto john = patientFactory.createPatientDto();
			john.setPatientId(12345678L);
			john.setName("John Doe");
			
			patientService.addPatient(john);
			
			logger.info("Added "+john.getName()+" with id "+john.getId());;
			
			// TODO add more testing, including treatments and providers
			
		} catch (PatientServiceExn e) {

			// logger.log(Level.SEVERE, "Failed to add patient record.", e);
			IllegalStateException ex = new IllegalStateException("Failed to add patient record.");
			ex.initCause(e);
			throw ex;
			
		} 
			
	}

}
