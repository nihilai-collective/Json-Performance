
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1656.05 | 0.139642 | 4967.32ms | 83958 | 640 | 2.91734e+06 | 48349.2 | 0.0272939 | 1(Win) | true |
| simdjson (ondemand) | 1294.03 | 0.313161 | 6768.37ms | 83958 | 80 | 3.00371e+06 | 61875.2 | 0.165221 | 2(Loss) | true |
