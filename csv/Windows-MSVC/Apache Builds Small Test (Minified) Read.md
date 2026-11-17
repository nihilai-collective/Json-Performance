
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1158.88 | 0.144413 | 222.321ms | 2632 | 320 | 3130.78 | 2165.94 | 0.565873 | 2.60135 | 1(Win) | true |
| Jsonifier | 1119.49 | 0.188968 | 226.751ms | 2632 | 2560 | 45956.3 | 2242.15 | 0.123849 | 2.6921 | 2(Loss) | true |
| Glaze | 857.002 | 0.0946134 | 295.119ms | 2632 | 4890 | 37551 | 2928.9 | 0.0650332 | 3.5175 | 3(Loss) | true |
| simdjson (ondemand) | 664.809 | 0.155627 | 380.959ms | 2632 | 640 | 22096.6 | 3775.62 | 0.0826993 | 4.54385 | 4(Loss) | true |
