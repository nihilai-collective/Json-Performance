
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1181.85 | 0.190751 | 4354.68ms | 53331 | 640 | 4.31269e+06 | 43034.6 | 0.562585 | 2.09349 | 1(Win) | true |
| simdjson (ondemand) | 1071.96 | 0.208296 | 4990.42ms | 53331 | 160 | 1.56273e+06 | 47446.1 | 0.0810523 | 2.30831 | 2(Loss) | true |
