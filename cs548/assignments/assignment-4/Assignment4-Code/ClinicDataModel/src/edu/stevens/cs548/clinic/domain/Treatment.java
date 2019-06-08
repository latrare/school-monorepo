package edu.stevens.cs548.clinic.domain;

import java.io.Serializable;

import javax.persistence.*;

/**
 * Entity implementation class for Entity: Treatment
 *
 */
/*
 * TODO
 */
@Entity
@Table(name = "TREATMENT")
@Inheritance(strategy=InheritanceType.SINGLE_TABLE)
@DiscriminatorColumn(name = "TYPE")
public abstract class Treatment implements Serializable {
	
	private static final long serialVersionUID = 1L;
	
	/*
	 * TODO
	 */
	@Id @GeneratedValue
	private long id;
	
	private String diagnosis;

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}
	
	/*
	 * TODO discriminator column
	 */
	@Column(name = "TYPE")
	private String treatmentType;
	
	public String getTreatmentType() {
		return treatmentType;
	}

	public void setTreatmentType(String treatmentType) {
		this.treatmentType = treatmentType;
	}

	public String getDiagnosis() {
		return diagnosis;
	}

	public void setDiagnosis(String diagnosis) {
		this.diagnosis = diagnosis;
	}

	/*
	 * TODO
	 */
	@ManyToOne
	@JoinColumn(name = "TREATMENT_PATIENT", nullable = true)
	private Patient patient;

	public Patient getPatient() {
		return patient;
	}

	public void setPatient(Patient patient) {
		this.patient = patient;
		// More logic in the domain model.
	}

	@ManyToOne
	@JoinColumn(name = "TREATMENT_PROVIDER", nullable = true)
	private Provider provider;
	
	public Provider getProvider() {
		return provider;
	}
	
	public void setProvider(Provider provider) {
		this.provider = provider;
	}
	
	public Treatment() {
		super();
	}
}
