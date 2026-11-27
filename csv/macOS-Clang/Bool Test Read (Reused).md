
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1369.51 | 0.0947684 | 66.5744ms | 905 | 640 | 228.285 | 630.209 | 0.0595395 | 1(Win) | true |
| Glaze | 1322.91 | 0.138448 | 67.536ms | 905 | 640 | 522.145 | 652.406 | 0.0944513 | 2(Loss) | true |
| simdjson (ondemand) | 308.078 | 0.106457 | 283.525ms | 905 | 4890 | 43494.6 | 2801.48 | 0.217092 | 3(Loss) | true |
