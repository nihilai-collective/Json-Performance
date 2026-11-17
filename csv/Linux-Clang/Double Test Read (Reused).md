
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 461.234 | 0.12543 | 403.279ms | 1811 | 4890 | 107872 | 3744.53 | 0.79049 | 5.32909 | 1(Win) | true |
| simdjson (ondemand) | 307.403 | 0.0440659 | 590.885ms | 1811 | 80 | 490.361 | 5618.36 | 0.0131283 | 8.01674 | 2(Loss) | true |
