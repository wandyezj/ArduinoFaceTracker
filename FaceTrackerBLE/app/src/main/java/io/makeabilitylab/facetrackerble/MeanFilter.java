package io.makeabilitylab.facetrackerble;

import java.lang.reflect.Array;
import java.util.ArrayList;

public class MeanFilter {

    private int m_size;

    private ArrayList<Float> m_values = new ArrayList<Float>();

    public MeanFilter(int size) {
        m_size = size;
    }

    public float Mean(){
        float total = 0.0f;

        for (Float value : m_values) {
            total += value;
        }

        if (m_values.size() == 0) {
            return 0.0f;
        }

        return total / m_values.size();
    }

    public float Add(float value) {
        m_values.add(value);

        // not the most efficient
        // circular buffer would be better, whatever.
        if (m_values.size() > m_size) {
            m_values.remove(0);
        }

        // sum up all elements
        return Mean();
    }

}
