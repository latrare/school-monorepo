package edu.stevens.cs548.clinic.service.dto.test;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBElement;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import edu.stevens.cs548.clinic.service.dto.DrugTreatmentType;
import edu.stevens.cs548.clinic.service.dto.PatientDto;
import edu.stevens.cs548.clinic.service.dto.ProviderDto;
import edu.stevens.cs548.clinic.service.dto.RadiologyTreatmentType;
import edu.stevens.cs548.clinic.service.dto.SurgeryTreatmentType;
import edu.stevens.cs548.clinic.service.dto.util.PatientDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.ProviderDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.TreatmentDtoFactory;

public class SchemaTest {

	@Before
	public void setUp() throws Exception {
		System.out.println("** Testing with element substitution start");
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("** Testing with element substitution end");
	}

	@Test
	public void test() {
		PatientDtoFactory patientFactory = new PatientDtoFactory();
		ProviderDtoFactory providerFactory = new ProviderDtoFactory();
		TreatmentDtoFactory treatmentFactory = new TreatmentDtoFactory();

	    try {
		    JAXBContext context = JAXBContext.newInstance("edu.stevens.cs548.clinic.service.dto");
		    Marshaller marshaller = context.createMarshaller();
		    marshaller.setProperty("jaxb.formatted.output",Boolean.TRUE);

		    PatientDto patient = patientFactory.createPatientDto();
		    patient.setId(1);
		    patient.setName("Trevor Miranda");
		    patient.setPatientId(123);
		    
		    System.out.println();
			marshaller.marshal(patient,System.out);

		    ProviderDto provider = providerFactory.createProviderDto();
		    provider.setId(1);
		    provider.setName("Some Doctor, M.D.");
		    provider.setNpi("123456789");
		    
		    System.out.println();
			marshaller.marshal(provider,System.out);
		    
		    System.out.println();
			marshaller.marshal(provider,System.out);
			
			DrugTreatmentType drugTreatmentType = treatmentFactory.createDrugTreatmentType();
			JAXBElement<DrugTreatmentType> drugTreatment = treatmentFactory.createDrugTreatmentDto(drugTreatmentType);
			drugTreatmentType.setDiagnosis("Treated with some drugs.");
			drugTreatmentType.setDosage("some dosage");
			drugTreatmentType.setId(1);
			drugTreatmentType.setPatient(1);
			drugTreatmentType.setProvider(1);
			drugTreatment.setValue(drugTreatmentType);
			
		    System.out.println();
			marshaller.marshal(drugTreatment,System.out);
			
			SurgeryTreatmentType surgeryTreatmentType = treatmentFactory.createSurgeryTreatmentType();
			JAXBElement<SurgeryTreatmentType> surgeryTreatment = treatmentFactory.createSurgeryTreatmentDto(surgeryTreatmentType);
			surgeryTreatmentType.setDiagnosis("Treated with some surgery.");
			surgeryTreatmentType.setDate("2019-01-01");
			surgeryTreatmentType.setId(2);
			surgeryTreatmentType.setPatient(1);
			surgeryTreatmentType.setProvider(1);
			surgeryTreatment.setValue(surgeryTreatmentType);
			
		    System.out.println();
			marshaller.marshal(surgeryTreatment,System.out);
			
			RadiologyTreatmentType radiologyTreatmentType = treatmentFactory.createRadiologyTreatmentType();
			JAXBElement<RadiologyTreatmentType> radiologyTreatment = treatmentFactory.createRadiologyTreatmentDto(radiologyTreatmentType);
			radiologyTreatmentType.setDate("2019-01-01");
			radiologyTreatmentType.setDiagnosis("Treated with some radiotherapy.");
			radiologyTreatmentType.setId(3);
			radiologyTreatmentType.setPatient(1);
			radiologyTreatmentType.setProvider(1);
			radiologyTreatment.setValue(radiologyTreatmentType);
			
		    System.out.println();
			marshaller.marshal(radiologyTreatment,System.out);

	    } catch (JAXBException e) {
			e.printStackTrace();
		}
	}

}
