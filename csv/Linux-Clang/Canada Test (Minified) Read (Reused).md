
----
### Canada Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 865.049 | 0.10986 | 8752.52ms | 2090234 | 40 | 2.56356e+08 | 2.30438e+06 | 0.900183 | 2.86204 | 1(Win) | true |
| simdjson (ondemand) | 785.801 | 0.0773216 | 9580.06ms | 2090234 | 160 | 6.15582e+08 | 2.53678e+06 | 1.25773 | 3.15067 | 2(Loss) | true |
