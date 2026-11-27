
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1639.74 | 0.266155 | 5071.83ms | 676745 | 30 | 3.29224e+07 | 393596 | 0.0575286 | 1(Win) | true |
| simdjson (ondemand) | 1260.57 | 0.102903 | 6516.15ms | 676745 | 640 | 1.77646e+08 | 511987 | 0.673321 | 2(Loss) | true |
