
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2232.17 | 0.124839 | 4639.12ms | 108313 | 2560 | 8.54373e+06 | 46275.7 | 0.127795 | 1.36089 | 1(Win) | true |
| Jsonifier (two-stage) | 1502.17 | 0.0333146 | 6877.97ms | 108313 | 2560 | 1.34349e+06 | 68764.3 | 0.065852 | 2.02256 | 2(Loss) | true |
| Glaze | 1406.53 | 0.0884667 | 7353.9ms | 108313 | 1280 | 5.40298e+06 | 73439.8 | 0.0559244 | 2.16014 | 3(Loss) | true |
| simdjson (ondemand) | 877.308 | 0.107274 | 6040.02ms | 108313 | 160 | 2.5525e+06 | 117741 | 0.0743708 | 3.46373 | 4(Loss) | true |
