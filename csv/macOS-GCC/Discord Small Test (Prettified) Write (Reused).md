
----
### Discord Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14121.5 | 1.45561 | 52.5412ms | 7376 | 4890 | 257086 | 498.127 | 0.354713 | 1(Win) | true |
| Glaze | 2368.93 | 0.412959 | 295.367ms | 7376 | 2560 | 384939 | 2969.4 | 0.442567 | 2(Loss) | true |
| simdjson (reflection) | 358.732 | 0.286121 | 2178.77ms | 7376 | 320 | 1.00728e+06 | 19608.8 | 0.158859 | 3(Loss) | true |
