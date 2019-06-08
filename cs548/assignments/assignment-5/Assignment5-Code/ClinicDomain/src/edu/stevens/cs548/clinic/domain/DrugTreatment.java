package edu.stevens.cs548.clinic.domain;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.DiscriminatorValue;
import javax.persistence.Entity;
import javax.persistence.Table;

import edu.stevens.cs548.clinic.domain.*;

/**
 * Entity implementation class for Entity: DrugTreatment
 * 
 */
// TODO JPA annotations
@Entity
@Table(name = "drug_treatment")
public class DrugTreatment extends Treatment implements Serializable {

    private static final long serialVersionUID = 1L;

    @Column(name = "drug")
    private String drug;
    @Column(name = "dosage")
    private float dosage;

    public String getDrug() {
	return drug;
    }

    public void setDrug(String drug) {
	this.drug = drug;
    }

    public float getDosage() {
	return dosage;
    }

    public void setDosage(float dosage) {
	this.dosage = dosage;
    }

    public <T> T export(ITreatmentExporter<T> visitor) {
	return visitor.exportDrugTreatment(this.getId(),
		this.getPatient().getId(), this.getProvider().getId(),
		this.getDiagnosis(), this.drug, this.dosage);
    }

    public DrugTreatment() {
	super();
    }

}
