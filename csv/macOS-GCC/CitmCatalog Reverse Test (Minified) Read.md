
----
### CitmCatalog Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 386.656 | 2.02997 | 7489.32ms | 500299 | 30 | 1.88238e+10 | 1.23397e+06 | 1.58438 | 1(Win) | true |
| simdjson (ondemand) | 271.853 | 2.06829 | 5395.21ms | 500299 | 40 | 5.27073e+10 | 1.75507e+06 | 4.86165 | 2(Loss) | true |
