
----
### Random Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 647.075 | 0.113765 | 8464.52ms | 409725 | 640 | 3.02047e+08 | 603862 | 0.198301 | 4.69689 | 1(Win) | true |
| simdjson (ondemand) | 384.061 | 0.198022 | 6803.79ms | 409725 | 320 | 1.29886e+09 | 1.0174e+06 | 0.251546 | 7.91338 | 2(Loss) | true |
