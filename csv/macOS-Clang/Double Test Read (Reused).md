
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 1040.62 | 0.114916 | 168.239ms | 1811 | 4890 | 17788 | 1659.69 | 0.345484 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1039.31 | 0.468205 | 191.075ms | 1811 | 640 | 38743.9 | 1661.79 | 1.27341 | 1(Tie) | true |
| Glaze | 903.067 | 0.264548 | 210.809ms | 1811 | 80 | 2047.85 | 1912.49 | 0.10665 | 3(Loss) | true |
| simdjson (ondemand) | 309.262 | 0.0979893 | 592.884ms | 1811 | 30 | 898.386 | 5584.6 | 0.00238746 | 4(Loss) | true |
