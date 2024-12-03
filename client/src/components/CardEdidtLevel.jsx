import { Formik, Form } from 'formik';
import { updateSeleccionData } from '../api/pet.api';
import '../styles/cardEdidtLevel.css'

export const CardEditLevel = () => {
  return (
    <div>
      <Formik 
        initialValues={{ nivelSeleccion_tinaco: "" }}
        onSubmit={async (values, actions) => {
          try {
            await updateSeleccionData(1, values);
            actions.resetForm(); // Limpia el formulario
          } catch (error) {
            console.error(error);
          } finally {
            actions.setSubmitting(false);
          }
        }}
      >
        {({ handleChange, handleSubmit, values, isSubmitting }) => (
          <Form className="form-container" onSubmit={handleSubmit}>
            <label className='Label'>Selecciona el nivel de agua</label>
            <input
              type="number"
              name="nivelSeleccion_tinaco" // Nombre correcto
              placeholder="Selecciona un nivel"
              onChange={handleChange}
              value={values.nivelSeleccion_tinaco}
              className="input"

            />
            <button className="button" type="submit" disabled={isSubmitting}>
              Guardar
            </button>
          </Form>
        )}
      </Formik>
    </div>
  );
};

