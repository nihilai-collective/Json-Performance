
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2249.26 | 0.400812 | 1008.39ms | 25388 | 1280 | 2.38271e+06 | 10764.4 | 3.16657 | 1(Win) | true |
| Jsonifier (two-stage) | 2203.48 | 0.515372 | 1122.98ms | 25388 | 320 | 1.02619e+06 | 10988 | 0.814739 | 2(Loss) | true |
| simdjson (reflection) | 1796.27 | 0.226979 | 1375.22ms | 25388 | 4890 | 4.57716e+06 | 13479 | 0.0578192 | 3(Loss) | true |
| Glaze | 1505.36 | 0.217021 | 1589.21ms | 25388 | 2560 | 3.11903e+06 | 16083.8 | 0.0372907 | 4(Loss) | true |
| simdjson (ondemand) | 1311.83 | 0.256571 | 1879.04ms | 25388 | 2560 | 5.74059e+06 | 18456.6 | 0.079042 | 5(Loss) | true |
