package edu.stevens.cs548.clinic.service.dto.test;

import javax.xml.bind.JAXBContext;
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
import edu.stevens.cs548.clinic.service.dto.TreatmentDto;
import edu.stevens.cs548.clinic.service.dto.util.PatientDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.ProviderDtoFactory;
import edu.stevens.cs548.clinic.service.dto.util.TreatmentDtoFactory;

public class SchemaTest {

	@Before
	public void setUp() throws Exception {
		System.out.println("** Testing with choice element start");
	}

	@After
	public void tearDown() throws Exception {
		System.out.println("** Testing with choice element end");
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
			
			TreatmentDto treatmentOne = treatmentFactory.createDrugTreatmentDto();
			treatmentOne.setId(1);
			treatmentOne.setDiagnosis("Treated with some drugs.");
			treatmentOne.setPatient(1);
			treatmentOne.setProvider(1);
			DrugTreatmentType drugTreatment = new DrugTreatmentType();
			drugTreatment.setDosage("some dose");
			drugTreatment.setDrug("some drug");
			treatmentOne.setDrugTreatment(drugTreatment);
			
			System.out.println();
			marshaller.marshal(treatmentOne,System.out);
			
			TreatmentDto treatmentTwo = treatmentFactory.createSurgeryTreatmentDto();
			treatmentTwo.setId(2);
			treatmentTwo.setDiagnosis("Treated with some surgery.");
			treatmentTwo.setPatient(1);
			treatmentTwo.setProvider(1);
			SurgeryTreatmentType surgeryTreatment = new SurgeryTreatmentType();
			surgeryTreatment.setDate("2019-01-01");
			treatmentTwo.setSurgeryTreatmentType(surgeryTreatment);
			
			System.out.println();
			marshaller.marshal(treatmentTwo,System.out);
			
			TreatmentDto treatmentThree = treatmentFactory.createRadiologyTreatmentDto();
			treatmentThree.setId(3);
			treatmentThree.setDiagnosis("Treated with some radiotherapy.");
			treatmentThree.setPatient(1);
			treatmentThree.setProvider(1);
			RadiologyTreatmentType radiologyTreatment = new RadiologyTreatmentType();
			radiologyTreatment.setDate("2019-01-01");
			treatmentThree.setRadiologyTreatmentType(radiologyTreatment);
						
			System.out.println();
			marshaller.marshal(treatmentThree,System.out);

			
		} catch (JAXBException e) {
			e.printStackTrace();
		}
	}

}
