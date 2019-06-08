package edu.stevens.cs548.clinic.billing;

import static javax.persistence.GenerationType.IDENTITY;

import java.io.Serializable;
import java.util.Date;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.NamedQuery;
import javax.persistence.OneToOne;
import javax.persistence.PrimaryKeyJoinColumn;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;

import edu.stevens.cs548.clinic.domain.Treatment;

/**
 * Entity implementation class for Entity: BillingRecord
 *
 */

@NamedQuery(name = "SearchBillingRecords", query = "select b from BillingRecord b")

@Entity
public class BillingRecord implements Serializable {

    private static final long serialVersionUID = 1L;

    public BillingRecord() {
	super();
    }

    @Id
    @GeneratedValue(strategy = IDENTITY)
    private long id;

    private String description;

    @Temporal(TemporalType.DATE)
    private Date date;

    private float amount;

    @OneToOne
    @PrimaryKeyJoinColumn
    private Treatment treatment;

    public long getId() {
	return id;
    }

    public void setId(long id) {
	this.id = id;
    }

    public String getDescription() {
	return description;
    }

    public void setDescription(String description) {
	this.description = description;
    }

    public Date getDate() {
	return date;
    }

    public void setDate(Date date) {
	this.date = date;
    }

    public float getAmount() {
	return amount;
    }

    public void setAmount(float amount) {
	this.amount = amount;
    }

    public Treatment getTreatment() {
	return treatment;
    }

    public void setTreatment(Treatment treatment) {
	this.treatment = treatment;
    }

}
