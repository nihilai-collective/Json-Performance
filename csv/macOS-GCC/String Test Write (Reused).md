
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 6542.54 | 1.57819 | 73.1169ms | 4215 | 2560 | 240693 | 614.4 | 0.392157 | 1(Win) | true |
| simdjson (reflection) | 5311.49 | 3.21373 | 92.5041ms | 4215 | 320 | 189292 | 756.8 | 2.87474 | 2(Loss) | true |
| Glaze | 2446.88 | 2.3645 | 183.55ms | 4215 | 640 | 965667 | 1642.8 | 2.72636 | 3(Loss) | true |
