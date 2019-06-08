package edu.stevens.cs548.clinic.domain;

import java.io.Serializable;
import javax.persistence.*;
import edu.stevens.cs548.clinic.domain.*;

/**
 * Entity implementation class for Entity: Treatment
 *
 */
// TODO JPA annotations
@Entity
@Inheritance(strategy=InheritanceType.JOINED)
@Table(name = "treatment")
public abstract class Treatment implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	// TODO JPA annotations
	@Id @GeneratedValue
	@Column(name = "id")
	private long id;
	@Column(name = "diagnosis")
	private String diagnosis;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}
	
	public String getDiagnosis() {
		return diagnosis;
	}

	public void setDiagnosis(String diagnosis) {
		this.diagnosis = diagnosis;
	}
	
	@Enumerated
	@Column(name = "treatment_type")
	private TreatmentType treatmentType;

	// TODO JPA annotations
	@ManyToOne(cascade = CascadeType.PERSIST, targetEntity = Patient.class)
	@JoinColumn(name = "patient_fk", referencedColumnName = "id")
	private Patient patient;

	public Patient getPatient() {
		return patient;
	}

	public void setPatient(Patient patient) {
		this.patient = patient;
		if (!patient.getTreatments().contains(this))
			patient.addTreatment(this);
	}
	
	// TODO JPA annotations
	@ManyToOne(cascade = CascadeType.PERSIST, targetEntity = Provider.class)
	@JoinColumn(name = "provider_fk", referencedColumnName = "id")
	private Provider provider;

	public Provider getProvider() {
		return provider;
	}

	public void setProvider(Patient patient, Provider provider) {
		this.provider = provider;
		this.patient = patient;
		this.provider.getTreatments().add(this);
		this.patient.getTreatments().add(this);
	}
	
	public abstract <T> T export(ITreatmentExporter<T> visitor);

	public Treatment() {
		super();
	}
   
}
