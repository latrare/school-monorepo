package edu.stevens.cs548.clinic.test;

import java.util.logging.Logger;

import javax.annotation.PostConstruct;
import javax.ejb.LocalBean;
import javax.ejb.Singleton;
import javax.ejb.Startup;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

import edu.stevens.cs548.clinic.domain.DrugTreatment;
import edu.stevens.cs548.clinic.domain.IPatientDAO;
import edu.stevens.cs548.clinic.domain.IPatientDAO.PatientExn;
import edu.stevens.cs548.clinic.domain.IProviderDAO;
import edu.stevens.cs548.clinic.domain.IProviderDAO.ProviderExn;
import edu.stevens.cs548.clinic.domain.ITreatmentDAO;
import edu.stevens.cs548.clinic.domain.Patient;
import edu.stevens.cs548.clinic.domain.PatientDAO;
import edu.stevens.cs548.clinic.domain.PatientFactory;
import edu.stevens.cs548.clinic.domain.Provider;
import edu.stevens.cs548.clinic.domain.Provider.ProviderType;
import edu.stevens.cs548.clinic.domain.ProviderDAO;
import edu.stevens.cs548.clinic.domain.ProviderFactory;
import edu.stevens.cs548.clinic.domain.Treatment;
import edu.stevens.cs548.clinic.domain.TreatmentDAO;
import edu.stevens.cs548.clinic.domain.TreatmentFactory;

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
	
	// TODO inject an EM
	@PersistenceContext(unitName = "ClinicDomain")
	EntityManager em;

	@PostConstruct
	private void init() {
		/*
		 * Put your testing logic here. Use the logger to display testing output in the server logs.
		 */
		logger.info("Your name here: Trevor Miranda");

		try {

			IPatientDAO patientDAO = new PatientDAO(em);
			IProviderDAO providerDAO = new ProviderDAO(em);
			ITreatmentDAO treatmentDAO = new TreatmentDAO(em);

			PatientFactory patientFactory = new PatientFactory();
			ProviderFactory providerFactory = new ProviderFactory();
			TreatmentFactory treatmentFactory = new TreatmentFactory();
			
			/*
			 * Clear the database and populate with fresh data.
			 * 
			 * If we ensure that deletion of patients cascades deletes of treatments,
			 * then we only need to delete patients.
			 */
			
			patientDAO.deletePatients();
			
			Patient john = patientFactory.createPatient(12345678L, "John Doe");
			john.setTreatmentDAO(treatmentDAO);
			
			DrugTreatment drugTreatment = (DrugTreatment) treatmentFactory.createDrugTreatment("high blood pressure", "aspiring", (float) 100);
			treatmentDAO.addTreatment(drugTreatment);
			
			Provider providerMark = providerFactory.createProvider(123123L, "Mark Markinson", ProviderType.INTERNIST);
			providerMark.addTreatment(john, drugTreatment);
			providerDAO.addProvider(providerMark);
			patientDAO.addPatient(john);
						
			logger.info("Added "+john.getName()+" with id "+john.getId());
			
			// TODO add more testing, including treatments and providers
			
		} catch (PatientExn | ProviderExn e) {

			// logger.log(Level.SEVERE, "Failed to add patient record.", e);
			IllegalStateException ex = new IllegalStateException("Failed to add patient record.");
			ex.initCause(e);
			throw ex;
			
		} 
			
	}

}
