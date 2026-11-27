
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6520.32 | 1.14954 | 72.4838ms | 4215 | 4890 | 245593 | 616.494 | 0.242938 | 1(Win) | true |
| simdjson (reflection) | 5613.37 | 1.2561 | 81.8949ms | 4215 | 2560 | 207128 | 716.1 | 0.431034 | 2(Loss) | true |
| Glaze | 2575.93 | 0.47557 | 171.159ms | 4215 | 4890 | 269318 | 1560.5 | 0.34481 | 3(Loss) | true |
