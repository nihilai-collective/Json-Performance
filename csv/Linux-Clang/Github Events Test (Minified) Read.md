
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1169.61 | 0.201253 | 4272.57ms | 53331 | 2560 | 1.96068e+07 | 43485.1 | 0.0325469 | 2.11542 | 1(Win) | true |
| simdjson (ondemand) | 947.574 | 0.149099 | 5522.9ms | 53331 | 320 | 2.04943e+06 | 53674.3 | 0.538314 | 2.61146 | 2(Loss) | true |
