ALTER TABLE treatment DROP CONSTRAINT FK_treatment_provider_fk
ALTER TABLE treatment DROP CONSTRAINT FK_treatment_patient_fk
ALTER TABLE drug_treatment DROP CONSTRAINT FK_drug_treatment_id
ALTER TABLE surgery_treatment DROP CONSTRAINT FK_surgery_treatment_id
ALTER TABLE radiology_treatment DROP CONSTRAINT FK_radiology_treatment_id
ALTER TABLE DRUGTREATMENTRECORD DROP CONSTRAINT FK_DRUGTREATMENTRECORD_SUBJECT_ID
ALTER TABLE provider_treatment DROP CONSTRAINT FK_provider_treatment_Provider_id
ALTER TABLE provider_treatment DROP CONSTRAINT FK_provider_treatment_treatments_id
ALTER TABLE RadiologyTreatment_TREATMENTDATES DROP CONSTRAINT FK_RadiologyTreatment_TREATMENTDATES_RadiologyTreatment_id
ALTER TABLE patient_treatment DROP CONSTRAINT FK_patient_treatment_Patient_id
ALTER TABLE patient_treatment DROP CONSTRAINT FK_patient_treatment_treatments_id
DROP TABLE provider CASCADE
DROP TABLE treatment CASCADE
DROP TABLE drug_treatment CASCADE
DROP TABLE surgery_treatment CASCADE
DROP TABLE radiology_treatment CASCADE
DROP TABLE DRUGTREATMENTRECORD CASCADE
DROP TABLE patient CASCADE
DROP TABLE BILLINGRECORD CASCADE
DROP TABLE SUBJECT CASCADE
DROP TABLE provider_treatment CASCADE
DROP TABLE RadiologyTreatment_TREATMENTDATES CASCADE
DROP TABLE patient_treatment CASCADE
DELETE FROM SEQUENCE WHERE SEQ_NAME = 'SEQ_GEN'