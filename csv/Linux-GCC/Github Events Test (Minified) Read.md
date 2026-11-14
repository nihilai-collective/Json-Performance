
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1270.22 | 0.0225988 | 4737.21ms | 53331 | 4890 | 400389 | 40040.6 | 0.0529159 | 4.03718 | 13.8574 | 2.70936 | 0.013274 | 4.82997e-05 | 1.52729e-05 | 1(Win) | true |
| simdjson (ondemand) | 1040.38 | 0.0546591 | 5620.96ms | 53331 | 4890 | 3.49148e+06 | 48886.4 | 0.168339 | 4.93184 | 17.7619 | 3.48738 | 0.0201081 | 7.85464e-05 | 2.69184e-05 | 2(Loss) | true |
