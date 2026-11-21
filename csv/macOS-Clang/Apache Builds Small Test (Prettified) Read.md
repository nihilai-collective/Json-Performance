
----
### Apache Builds Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1438.81 | 0.339211 | 224.132ms | 3370 | 4890 | 280737 | 2233.71 | 0.310547 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1431.94 | 0.551193 | 225.312ms | 3370 | 1280 | 195896 | 2244.42 | 0.226629 | 1(Tie) | true |
| Glaze | 1295.53 | 0.130604 | 283.019ms | 3370 | 160 | 1679.58 | 2480.74 | 0.149119 | 3(Loss) | true |
| simdjson (ondemand) | 1082.94 | 0.316085 | 323.556ms | 3370 | 80 | 7039.54 | 2967.72 | 0.000842403 | 4(Loss) | true |
