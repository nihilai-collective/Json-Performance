
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3258.01 | 0.0512565 | 139.419ms | 4669 | 320 | 157.033 | 1366.7 | 0.0185175 | 0.744756 | 1(Win) | true |
| Jsonifier (two-stage) | 2422.39 | 0.0407869 | 188.71ms | 4669 | 320 | 179.866 | 1838.14 | 0.0424841 | 1.00756 | 2(Loss) | true |
| Glaze | 1658.21 | 0.0501803 | 271.214ms | 4669 | 80 | 145.253 | 2685.25 | 0.0558919 | 1.47763 | 3(Loss) | true |
| simdjson (reflection) | 1487.55 | 0.0669967 | 303.824ms | 4669 | 80 | 321.737 | 2993.31 | 0.0897029 | 1.64969 | 4(Loss) | true |
| simdjson (ondemand) | 993.351 | 0.159545 | 459.104ms | 4669 | 2560 | 130933 | 4482.51 | 0.245958 | 2.4779 | 5(Loss) | true |
