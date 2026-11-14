
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1163.55 | 0.105601 | 4389.93ms | 53331 | 2560 | 5.45463e+06 | 43711.3 | 0.591872 | 2.12641 | 1(Win) | true |
| simdjson (ondemand) | 983.165 | 0.0632935 | 5163.57ms | 53331 | 4890 | 5.24244e+06 | 51731.3 | 0.0567937 | 2.51683 | 2(Loss) | true |
