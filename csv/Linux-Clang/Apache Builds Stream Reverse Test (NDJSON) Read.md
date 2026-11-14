
----
### Apache Builds Stream Reverse Test (NDJSON) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Stream%20Reverse%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1463.93 | 0.118344 | 5101.02ms | 4212000 | 40 | 4.21785e+08 | 2.7439e+06 | 1.33559 | 1.69118 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1196.05 | 0.0691291 | 6010.21ms | 4212000 | 80 | 4.31211e+08 | 3.35845e+06 | 2.93805 | 2.06997 | -(Loss) | false |
