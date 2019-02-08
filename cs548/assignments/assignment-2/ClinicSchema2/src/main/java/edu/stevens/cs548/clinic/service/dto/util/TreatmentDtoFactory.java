package edu.stevens.cs548.clinic.service.dto.util;

import javax.xml.bind.JAXBElement;

import edu.stevens.cs548.clinic.service.dto.DrugTreatmentType;
import edu.stevens.cs548.clinic.service.dto.ObjectFactory;
import edu.stevens.cs548.clinic.service.dto.RadiologyTreatmentType;
import edu.stevens.cs548.clinic.service.dto.SurgeryTreatmentType;

public class TreatmentDtoFactory {
	
	ObjectFactory factory;
	
	public TreatmentDtoFactory() {
		factory = new ObjectFactory();
	}
	
	public DrugTreatmentType createDrugTreatmentType() {
		return factory.createDrugTreatmentType();
	}
	
	public JAXBElement<DrugTreatmentType> createDrugTreatmentDto (DrugTreatmentType drugTreatment) {
		return factory.createDrugTreatmentDto(drugTreatment);
	}
	
	public SurgeryTreatmentType createSurgeryTreatmentType() {
		return factory.createSurgeryTreatmentType();
	}
	
	public JAXBElement<SurgeryTreatmentType> createSurgeryTreatmentDto (SurgeryTreatmentType surgeryTreatment) {
		return factory.createSurgeryTreatmentDto(surgeryTreatment);
	}
	
	public RadiologyTreatmentType createRadiologyTreatmentType() {
		return factory.createRadiologyTreatmentType();
	}
	
	public JAXBElement<RadiologyTreatmentType> createRadiologyTreatmentDto (RadiologyTreatmentType radiologyTreatment) {
		return factory.createRadiologyTreatmentDto(radiologyTreatment);
	}
}
