short calculate_distance( short *Num_1, short *Num_2){
    float temp = sqrt((Num_1[0] - Num_2[0]) * (Num_1[0] - Num_2[0]) + (Num_1[1] - Num_2[1]) * (Num_1[1] - Num_2[1]) + (Num_1[2] - Num_2[2]) * (Num_1[2] - Num_2[2]));
    return (short)(temp / 10 + 0.5);
}

void self_distance( short **Batch, size_t len, size_t *count){
    for ( size_t ix = 0; ix < len - 1; ix++) {
        for ( size_t jx = ix + 1; jx < len; jx++) {
            short distance = calculate_distance(Batch[ix], Batch[jx]);
            count[distance] += 1;
    }
  }
}

void double_distance( short **Batch_1, short **Batch_2, size_t len_1, size_t len_2, size_t *count){
    for ( size_t ix = 0; ix < len_1; ix++) {
        for ( size_t jx = 0; jx < len_2; jx++) {
            short distance = calculate_distance(Batch_1[ix], Batch_2[jx]);
            count[distance] += 1;
    }
  }
}