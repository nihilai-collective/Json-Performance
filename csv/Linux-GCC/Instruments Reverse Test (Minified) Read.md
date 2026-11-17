
----
### Instruments Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 588.74 | 0.067263 | 9331.51ms | 108313 | 320 | 4.45673e+06 | 175452 | 0.192471 | 8.61954 | 38.4257 | 7.71378 | 0.011442 | 0.000104068 | 8.05824e-05 | 1(Win) | true |
| simdjson (ondemand) | 251.254 | 0.0610574 | 5325.17ms | 108313 | 320 | 2.01633e+07 | 411119 | 0.126094 | 20.3326 | 90.6895 | 18.5027 | 0.0837972 | 0.000146797 | 0.000107761 | 2(Loss) | true |
