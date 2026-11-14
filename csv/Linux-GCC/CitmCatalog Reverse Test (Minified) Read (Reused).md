
----
### CitmCatalog Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 747.508 | 0.0355811 | 8645.68ms | 500299 | 640 | 3.30101e+07 | 638284 | 0.534198 | 6.852 | 34.5628 | 7.19204 | 0.0144857 | 0.0128076 | 6.79281e-06 | 1(Win) | true |
| simdjson (ondemand) | 452.337 | 0.12387 | 6967.04ms | 500299 | 30 | 5.12138e+07 | 1.05479e+06 | 0.0643382 | 11.3634 | 62.3729 | 12.7893 | 0.0268023 | 0.014987 | 1.86555e-05 | 2(Loss) | true |
