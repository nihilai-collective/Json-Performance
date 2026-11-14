
----
### Bool Test Write (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 3222.24 | 0.0695377 | 756.518ms | 905 | 1280 | 44.4049 | 267.849 | 0.0218804 | 1.80883 | 7.77459 | 0.271824 | 0.00221426 | 5.09323e-05 | 1.72652e-06 | 1(Win) | true |
| simdjson (reflection) | 2955.19 | 0.120407 | 761.352ms | 905 | 4890 | 604.694 | 292.054 | 0.121811 | 1.97349 | 8.44862 | 1.05083 | 0.00110881 | 0.000101459 | 1.9659e-05 | 2(Loss) | true |
| Glaze | 674.999 | 0.0280105 | 861.124ms | 905 | 160 | 20.5235 | 1278.63 | 0.00342151 | 7.73132 | 22.0398 | 3.36685 | 0.00782459 | 0.000234807 | 0 | 3(Loss) | true |
