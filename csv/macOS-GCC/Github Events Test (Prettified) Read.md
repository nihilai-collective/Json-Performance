
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1350.51 | 0.0547153 | 4716.07ms | 65103 | 4890 | 3.09409e+06 | 45973 | 0.175029 | 1(Win) | true |
| simdjson (ondemand) | 1008.92 | 0.0742863 | 6204.45ms | 65103 | 4890 | 1.02192e+07 | 61538.3 | 0.0102655 | 2(Loss) | true |
