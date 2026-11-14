
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1247.31 | 0.982347 | 8356.15ms | 7351818 | 30 | 9.1473e+10 | 5.6211e+06 | 0.415159 | 2.43651 | 1(Win) | true |
| Jsonifier (generic) | 1188.69 | 0.655549 | 8894.98ms | 7351818 | 80 | 1.19607e+11 | 5.8983e+06 | 0.809351 | 2.55662 | 2(Loss) | true |
