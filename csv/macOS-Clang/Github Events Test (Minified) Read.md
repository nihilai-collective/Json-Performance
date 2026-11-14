
----
### Github Events Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1854.63 | 0.0880454 | 2747.72ms | 53331 | 4890 | 2.85079e+06 | 27423.4 | 0.268096 | 1(Win) | true |
| Glaze | 1535.58 | 0.192147 | 3330.59ms | 53331 | 320 | 1.29607e+06 | 33121.2 | 0.0309091 | 2(Loss) | true |
| Jsonifier (two-stage) | 1482.7 | 0.119027 | 3462.8ms | 53331 | 80 | 133363 | 34302.6 | 0.116692 | 3(Loss) | true |
| simdjson (ondemand) | 877.346 | 0.0853451 | 5813.61ms | 53331 | 2560 | 6.26636e+06 | 57970.8 | 0.0854149 | 4(Loss) | true |
