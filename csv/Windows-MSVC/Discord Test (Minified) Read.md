
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 862.365 | 0.136995 | 6276.45ms | 56369 | 160 | 1.16689e+06 | 62337.5 | 0.114167 | 3.52312 | 1(Win) | true |
| simdjson (ondemand) | 779.445 | 0.0628705 | 6902.69ms | 56369 | 4890 | 9.19415e+06 | 68969.1 | 0.320176 | 3.89788 | 2(Loss) | true |
