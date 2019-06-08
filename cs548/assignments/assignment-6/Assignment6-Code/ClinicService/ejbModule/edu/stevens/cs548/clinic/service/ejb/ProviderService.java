package edu.stevens.cs548.clinic.service.ejb;

import java.util.List;
import java.util.logging.Logger;

import javax.annotation.PostConstruct;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;

import edu.stevens.cs548.clinic.domain.IPatientDAO;
import edu.stevens.cs548.clinic.domain.IPatientDAO.PatientExn;
import edu.stevens.cs548.clinic.domain.IProviderDAO;
import edu.stevens.cs548.clinic.domain.IProviderDAO.ProviderExn;
import edu.stevens.cs548.clinic.domain.IProviderFactory;
import edu.stevens.cs548.clinic.domain.Patient;
import edu.stevens.cs548.clinic.domain.Provider;
import edu.stevens.cs548.clinic.domain.Provider.ProviderType;
import edu.stevens.cs548.clinic.domain.Treatment;
import edu.stevens.cs548.clinic.domain.TreatmentFactory;
import edu.stevens.cs548.clinic.service.dto.ProviderDto;
import edu.stevens.cs548.clinic.service.dto.ProviderSpecType;
import edu.stevens.cs548.clinic.service.dto.TreatmentDto;
import edu.stevens.cs548.clinic.service.dto.util.ProviderDtoFactory;
import edu.stevens.cs548.clinic.service.ejb.IPatientService.PatientNotFoundExn;
import edu.stevens.cs548.clinic.service.ejb.IPatientService.PatientServiceExn;

/**
 * Session Bean implementation class ProviderService
 */
@Stateless(name="ProviderServiceBean")
public class ProviderService implements IProviderServiceLocal, IProviderServiceRemote {
	
	@SuppressWarnings("unused")
	private Logger logger = Logger.getLogger(ProviderService.class.getCanonicalName());

	private IProviderFactory providerFactory;
	
	private ProviderDtoFactory providerDtoFactory;

	private IProviderDAO providerDAO;
	
	private IPatientDAO patientDAO;
	
	private TreatmentFactory treatmentFactory;

	/**
	 * Default constructor.
	 */
	public ProviderService() {
		// TODO initialize factories
	}
	
	// TODO use dependency injection and EJB lifecycle methods to initialize DAOs

	// TODO
	private EntityManager em;

	@PostConstruct
	private void initialize() {
		// TODO
	}

	/**
	 * @see IProviderService#addProvider(ProviderDto dto)
	 */
	@Override
	public long addProvider(ProviderDto dto) throws ProviderServiceExn {
		// TODO Use factory to create Provider entity, and persist with DAO
		throw new IllegalStateException("Unimplemented: ProviderService.addProvider");
	}

	/**
	 * @see IProviderService#getProvider(long)
	 */
	@Override
	public ProviderDto getProvider(long id) throws ProviderServiceExn {
		// TODO use DAO to get Provider by database key
		throw new IllegalStateException("Unimplemented: ProviderService.getProvider");
	}

	/**
	 * @see IProviderService#getProviderByNPI(long)
	 */
	@Override
	public ProviderDto getProviderByNPI(long npi) throws ProviderServiceExn {
		// TODO use DAO to get Provider by NPI
		throw new IllegalStateException("Unimplemented: ProviderService.getProviderByNPI");
	}
		
	@Override
	public long addTreatment(TreatmentDto dto) throws PatientServiceExn, ProviderServiceExn {
		try {
			Provider provider = providerDAO.getProvider(dto.getProvider());
			Patient patient = patientDAO.getPatient(dto.getPatient());
			Treatment treatment;
			if (dto.getDrugTreatment() != null) {
				treatment = treatmentFactory.createDrugTreatment(dto.getDiagnosis(), dto.getDrugTreatment().getDrug(),
						dto.getDrugTreatment().getDosage());
			} else {
				// TODO Handle the other cases
				throw new IllegalArgumentException("No treatment-specific info provided.");
			}
			return provider.addTreatment(patient, treatment);
		} catch (PatientExn e) {
			throw new PatientNotFoundExn(e.toString());
		} catch (ProviderExn e) {
			throw new ProviderNotFoundExn(e.toString());
		}
	}

	@Override
	public List<Long> getTreatments(long id) throws ProviderServiceExn {
		// TODO Use DAO to get list of treatments for the provider
		throw new IllegalStateException("Unimplemented: ProviderService.getTreatments");
	}

	@Override
	public TreatmentDto getTreatment(long id, long tid)
			throws ProviderNotFoundExn, TreatmentNotFoundExn, ProviderServiceExn {
		// TODO Export treatment DTO from Provider aggregate
		throw new IllegalStateException("Unimplemented: ProviderService.getTreatment");
	}
	
	// TODO inject resource value
	private String siteInformation;
	

	@Override
	public String siteInfo() {
		return siteInformation;
	}

	public static ProviderType getType(ProviderSpecType providerType) {
		switch (providerType) {
		case INTERNAL:
			return ProviderType.INTERNIST;
		case RADIOLOGY:
			return ProviderType.RADIOLOGIST;
		case SURGERY:
			return ProviderType.SURGEON;
		default:
			throw new IllegalStateException("Unrecognized provider type: "+providerType);
		}
	}

}
