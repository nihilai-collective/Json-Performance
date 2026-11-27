
----
### Apache Builds Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 1148.14 | 0.582993 | 5408.97ms | 124597 | 320 | 1.16495e+08 | 103494 | 0.798078 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1137.76 | 0.359984 | 6107.7ms | 124597 | 40 | 5.65378e+06 | 104438 | 0.0901719 | 1(Tie) | true |
