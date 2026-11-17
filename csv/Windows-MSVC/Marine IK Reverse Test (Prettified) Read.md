
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2147.01 | 0.391384 | 10420.5ms | 7351818 | 80 | 1.30682e+10 | 3.26558e+06 | 0.20273 | 1.15313 | 1(Win) | true |
| Jsonifier | 2012.66 | 0.286842 | 5329.91ms | 7351818 | 40 | 3.99386e+09 | 3.48356e+06 | 0.368327 | 1.23011 | 2(Loss) | true |
| Glaze | 701.176 | 0.314729 | 7111.11ms | 7351818 | 40 | 3.96159e+10 | 9.99925e+06 | 1.29086 | 3.53092 | 3(Loss) | true |
| simdjson (ondemand) | 483.858 | 0.193144 | 10284.6ms | 7351818 | 40 | 3.13311e+10 | 1.44903e+07 | 0.60153 | 5.1168 | 4(Loss) | true |
