
----
### Twitter Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15261.4 | 0.151404 | 21.151ms | 2963 | 320 | 25.1479 | 185.156 | 0.0640939 | 0.140527 | 1(Win) | true |
| Glaze | 5590.78 | 0.0837676 | 52.4515ms | 2963 | 320 | 57.3616 | 505.428 | 0.00556428 | 0.420006 | 2(Loss) | true |
