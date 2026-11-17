
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1854.1 | 0.0644094 | 9103.5ms | 676745 | 320 | 1.60854e+07 | 348090 | 0.0931005 | 2.72173 | 11.9153 | 2.25211 | 0.00697182 | 0.0252861 | 7.80344e-05 | 1(Win) | true |
| simdjson (ondemand) | 1483.35 | 0.0903708 | 5659.51ms | 676745 | 160 | 2.47365e+07 | 435092 | 0.137928 | 3.44102 | 13.323 | 2.31856 | 0.0143983 | 0.0346171 | 1.79905e-05 | 2(Loss) | true |
