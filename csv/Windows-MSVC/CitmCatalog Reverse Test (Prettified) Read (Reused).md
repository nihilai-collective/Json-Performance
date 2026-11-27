
----
### CitmCatalog Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/CitmCatalog%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1024.23 | 0.289279 | 7006.43ms | 1151920 | 320 | 3.08058e+09 | 1.07256e+06 | 0.397059 | 2.96712 | 1(Win) | true |
| simdjson (ondemand) | 696.101 | 0.311075 | 5023.05ms | 1151920 | 80 | 1.92806e+09 | 1.57816e+06 | 0.00237613 | 4.36601 | 2(Loss) | true |
