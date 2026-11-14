
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2433.26 | 0.698038 | 1008.08ms | 25388 | 320 | 1.54379e+06 | 9950.4 | 0.240616 | 1(Win) | true |
| Jsonifier (two-stage) | 2153.47 | 0.821548 | 1130.54ms | 25388 | 160 | 1.3651e+06 | 11243.2 | 0.0711035 | 2(Loss) | true |
| simdjson (reflection) | 1808.98 | 0.144955 | 1348.75ms | 25388 | 4890 | 1.84062e+06 | 13384.3 | 0.00898173 | 3(Loss) | true |
| Glaze | 1536.13 | 0.198033 | 1565.1ms | 25388 | 2560 | 2.4941e+06 | 15761.6 | 0.746842 | 4(Loss) | true |
| simdjson (ondemand) | 1307.37 | 0.16244 | 1870.3ms | 25388 | 2560 | 2.31678e+06 | 18519.5 | 0.356724 | 5(Loss) | true |
