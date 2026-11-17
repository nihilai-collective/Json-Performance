
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1178.43 | 0.349072 | 5520.22ms | 65103 | 320 | 1.08237e+07 | 52686.2 | 0.124403 | 2.09938 | 1(Win) | true |
| Glaze | 1117.94 | 0.206359 | 5579.81ms | 65103 | 4890 | 6.42276e+07 | 55537.1 | 0.487095 | 2.21318 | 2(Loss) | true |
| Jsonifier | 1051.41 | 0.464563 | 6102.46ms | 65103 | 160 | 1.20411e+07 | 59051.2 | 0.391015 | 2.35311 | 3(Loss) | true |
| simdjson (ondemand) | 745.365 | 0.472938 | 8518.62ms | 65103 | 80 | 1.24154e+07 | 83297.5 | 0.685564 | 3.32092 | 4(Loss) | true |
