package edu.stevens.cs548.clinic.domain;

import javax.annotation.Generated;
import javax.persistence.metamodel.ListAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="Dali", date="2019-03-02T20:40:12.982-0500")
@StaticMetamodel(Patient.class)
public class Patient_ {
	public static volatile SingularAttribute<Patient, Long> id;
	public static volatile SingularAttribute<Patient, Long> patientId;
	public static volatile SingularAttribute<Patient, String> name;
	public static volatile ListAttribute<Patient, Treatment> treatments;
}
