
----
### Github Events Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18539.1 | 0.0619412 | 1136.41ms | 78778 | 2560 | 16130 | 4052.44 | 0.0431652 | 0.278972 | 0.830156 | 0.124578 | 2.55514e-05 | 2.14705e-05 | 1.56938e-05 | 1(Win) | true |
| Glaze | 5244.17 | 0.0658399 | 2167.6ms | 78778 | 4890 | 435055 | 14326.1 | 0.0280581 | 0.968839 | 2.87673 | 0.450253 | 8.46104e-05 | 2.18937e-05 | 1.48719e-05 | 2(Loss) | true |
| simdjson (reflection) | 633.675 | 0.11612 | 6432.12ms | 78778 | 2560 | 4.85207e+07 | 118560 | 0.265086 | 8.00511 | 29.3423 | 6.60943 | 0.0388506 | 0.000200583 | 8.93184e-05 | 3(Loss) | true |
