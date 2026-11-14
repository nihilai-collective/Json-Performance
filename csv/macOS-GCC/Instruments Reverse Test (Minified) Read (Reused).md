
----
### Instruments Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 552.149 | 0.0613876 | 9857.01ms | 108313 | 1280 | 1.68819e+07 | 187079 | 0.231238 | 1(Win) | true |
| simdjson (ondemand) | 221.196 | 0.177936 | 6079.86ms | 108313 | 320 | 2.20945e+08 | 466986 | 0.358805 | 2(Loss) | true |
