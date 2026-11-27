
----
### Canada Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1269.15 | 0.288644 | 992.648ms | 11579 | 640 | 403667 | 8700.8 | 0.20269 | 1(Win) | true |
| simdjson (ondemand) | 1244.61 | 0.108882 | 1006.16ms | 11579 | 4890 | 456343 | 8872.31 | 0.218128 | 2(Loss) | true |
