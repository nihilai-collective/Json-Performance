
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1204.4 | 0.0560988 | 4293.37ms | 53331 | 4890 | 2.7443e+06 | 42228.7 | 0.154029 | 1(Win) | true |
| simdjson (ondemand) | 797.565 | 0.730746 | 6471.36ms | 53331 | 30 | 6.5145e+06 | 63769.6 | 1.17694 | 2(Loss) | true |
