
----
### Random Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14261.2 | 1.59826 | 64.234ms | 9255 | 2560 | 250481 | 618.9 | 4.2247 | 1(Win) | true |
| Glaze | 2745.17 | 0.309258 | 334.408ms | 9255 | 2560 | 253103 | 3215.2 | 1.36192 | 2(Loss) | true |
| simdjson (reflection) | 301.839 | 0.492244 | 2860.21ms | 9255 | 640 | 1.326e+07 | 29241.6 | 1.0316 | 3(Loss) | true |
