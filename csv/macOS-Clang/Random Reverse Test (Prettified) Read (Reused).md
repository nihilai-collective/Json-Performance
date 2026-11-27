
----
### Random Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1171.31 | 0.121708 | 7388.31ms | 676745 | 640 | 2.87823e+08 | 551003 | 0.0138073 | 1(Win) | true |
| simdjson (ondemand) | 567.902 | 0.259929 | 7353.39ms | 676745 | 160 | 1.39615e+09 | 1.13645e+06 | 0.0135441 | 2(Loss) | true |
