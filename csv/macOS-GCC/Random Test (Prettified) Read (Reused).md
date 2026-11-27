
----
### Random Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1747.35 | 0.199141 | 5658.75ms | 676745 | 160 | 8.65628e+07 | 369355 | 0.155756 | 1(Win) | true |
| simdjson (ondemand) | 1076.6 | 0.286841 | 8584.92ms | 676745 | 30 | 8.87048e+07 | 599475 | 0.529558 | 2(Loss) | true |
