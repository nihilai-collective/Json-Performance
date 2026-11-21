
----
### Twitter Small Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1444.92 | 0.510049 | 197.447ms | 2889 | 1280 | 121072 | 1906.8 | 0.0696037 | 1.6872 | 1(Win) | true |
| Jsonifier (two-stage) | 1356.68 | 0.316753 | 217.168ms | 2889 | 4890 | 202345 | 2030.82 | 0.190177 | 1.80128 | 2(Loss) | true |
| Glaze | 1257.74 | 0.269667 | 223.326ms | 2889 | 4890 | 170639 | 2190.57 | 0.00295752 | 1.94324 | 3(Loss) | true |
| simdjson (ondemand) | 1227.84 | 0.529088 | 240.068ms | 2889 | 1280 | 180416 | 2243.91 | 0.0348044 | 1.98898 | 4(Loss) | true |
