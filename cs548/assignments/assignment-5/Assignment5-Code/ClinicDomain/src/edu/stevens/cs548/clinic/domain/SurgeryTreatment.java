package edu.stevens.cs548.clinic.domain;

import java.util.Date;

import javax.persistence.Column;
import javax.persistence.DiscriminatorValue;
import javax.persistence.Entity;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import edu.stevens.cs548.clinic.domain.*;

@Entity
@Table(name = "surgery_treatment")
public class SurgeryTreatment extends Treatment {

    /**
     * 
     */
    private static final long serialVersionUID = 4173146640306267418L;

    @Temporal(TemporalType.DATE)
    @Column(name = "surgery_date")
    private Date surgeryDate;

    public Date getSurgeryDate() {
	return surgeryDate;
    }

    public void setSurgeryDate(Date surgeryDate) {
	this.surgeryDate = surgeryDate;
    }

    @Override
    public <T> T export(ITreatmentExporter<T> visitor) {
	return visitor.exportSurgery(this.getId(), this.getPatient().getId(),
		this.getProvider().getId(), this.getDiagnosis(),
		this.getSurgeryDate());
    }

}
