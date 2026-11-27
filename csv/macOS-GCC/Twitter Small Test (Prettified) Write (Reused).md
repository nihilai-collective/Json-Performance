
----
### Twitter Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 14328.1 | 2.46282 | 30.337ms | 4300 | 4890 | 242961 | 286.207 | 3.40636 | 1(Win) | true |
| Glaze | 4046.18 | 0.329192 | 104.555ms | 4300 | 2560 | 28496.1 | 1013.5 | 0.0691153 | 2(Loss) | true |
| simdjson (reflection) | 424.478 | 0.572978 | 998.735ms | 4300 | 80 | 245127 | 9660.8 | 0.099272 | 3(Loss) | true |
