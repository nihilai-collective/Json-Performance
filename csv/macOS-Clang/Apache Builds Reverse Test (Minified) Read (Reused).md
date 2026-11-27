
----
### Apache Builds Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1013.13 | 0.216164 | 5505.51ms | 94653 | 640 | 2.37401e+07 | 89098.1 | 0.893006 | 1(Win) | true |
| simdjson (ondemand) | 500.76 | 0.481193 | 5126.99ms | 94653 | 320 | 2.40768e+08 | 180262 | 3.96139 | 2(Loss) | true |
