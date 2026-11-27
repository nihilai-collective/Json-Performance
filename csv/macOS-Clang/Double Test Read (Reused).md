
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1074.96 | 0.0772841 | 173.611ms | 1811 | 320 | 493.378 | 1606.66 | 0.086673 | 1(Win) | true |
| Glaze | 978.459 | 0.0498238 | 181.926ms | 1811 | 640 | 495 | 1765.13 | 0.082658 | 2(Loss) | true |
| simdjson (ondemand) | 303.612 | 0.0584937 | 574.521ms | 1811 | 40 | 442.871 | 5688.52 | 0.0300222 | 3(Loss) | true |
