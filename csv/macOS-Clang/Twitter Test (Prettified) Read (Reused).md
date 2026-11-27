
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2319.83 | 0.215087 | 8367.42ms | 360584 | 160 | 1.62647e+07 | 148235 | 0.0972508 | 1(Win) | true |
| simdjson (ondemand) | 2071.52 | 0.0727505 | 9243.52ms | 360584 | 1280 | 1.86688e+07 | 166003 | 0.134559 | 2(Loss) | true |
