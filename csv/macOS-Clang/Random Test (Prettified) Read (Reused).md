
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1822.74 | 0.157888 | 9829.23ms | 676745 | 320 | 1.00012e+08 | 354080 | 0.260555 | 1(Win) | true |
| simdjson (ondemand) | 1371.68 | 0.136078 | 6365.85ms | 676745 | 640 | 2.62362e+08 | 470514 | 0.239899 | 2(Loss) | true |
