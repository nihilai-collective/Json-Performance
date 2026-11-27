
----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6965.05 | 0.0622558 | 826.131ms | 7932 | 2560 | 1170.35 | 1086.07 | 0.0787573 | 0.765663 | 3.49962 | 0.461549 | 0.000630112 | 7.83023e-06 | 1.32966e-06 | 1(Win) | true |
| simdjson (ondemand) | 6529.68 | 0.0579661 | 836.636ms | 7932 | 4890 | 2205.16 | 1158.49 | 0.216248 | 0.810369 | 3.82312 | 0.432426 | 0.000771099 | 1.37673e-05 | 4.89849e-06 | 2(Loss) | true |
