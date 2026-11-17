
----
### Instruments Test (Prettified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 39634.4 | 0.0521305 | 520.524ms | 213963 | 30 | 216.092 | 5148.33 | 0.123512 | 0.062147 | 1(Win) | true |
| Glaze | 4010.05 | 0.21561 | 5263.48ms | 213963 | 320 | 3.85184e+06 | 50884.9 | 0.250152 | 0.617099 | 2(Loss) | true |
| simdjson (reflection) | 496.954 | 0.168412 | 5173.29ms | 213963 | 160 | 7.6509e+07 | 410604 | 0.344195 | 4.98147 | 3(Loss) | true |
