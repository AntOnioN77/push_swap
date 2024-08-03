// GENERADO DE PRUEBA BORRAR
void sort_stack(t_ciar *a, t_ciar *b)
{
    int size = a->fill;
    int min;
    int min_pos;

    while (size > 0)
    {
        min = INT_MAX;
        min_pos = -1;
        
        // Encuentra el mínimo en stack_a
		int i = 0;
        while (i < size)
        {
            if (get_top(a) < min)
            {
                min = get_top(a);
                min_pos = i;
            }
            ra(a);
			i++;
        }
        
        // Coloca el mínimo en la posición correcta
		i = 0;
        while ( i < min_pos)
		{
            	ra(a);
				i++;
		}
        // Mueve el mínimo a stack_b
        pb(a, b);
        size--;
    }
    
    // Devuelve todos los elementos a stack_a
    while (b->fill > 0)
        pa(b, a);
}