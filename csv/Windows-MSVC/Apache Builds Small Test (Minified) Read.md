
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1310.47 | 0.189898 | 194.754ms | 2632 | 4890 | 64694.3 | 1915.4 | 0.522988 | 2.29654 | 1(Win) | true |
| Jsonifier | 1266.71 | 0.270875 | 200.122ms | 2632 | 640 | 18438.9 | 1981.56 | 0.377062 | 2.37684 | 2(Loss) | true |
| Glaze | 941.587 | 0.0834335 | 268.499ms | 2632 | 4890 | 24190.3 | 2665.79 | 0.459232 | 3.2019 | 3(Loss) | true |
| simdjson (ondemand) | 761.969 | 0.1178 | 332.604ms | 2632 | 4890 | 73637.8 | 3294.19 | 0.270434 | 3.9627 | 4(Loss) | true |
