
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3064.29 | 0.0428279 | 123.538ms | 3862 | 80 | 21.1986 | 1201.94 | 0.0945494 | 0.790494 | 1(Win) | true |
| Glaze | 1489.52 | 0.0170835 | 251.238ms | 3862 | 160 | 28.55 | 2472.67 | 0.0381818 | 1.64416 | 2(Loss) | true |
| Jsonifier (two-stage) | 945.273 | 0.0453132 | 396.106ms | 3862 | 40 | 124.687 | 3896.32 | 0.0395515 | 2.60331 | 3(Loss) | true |
| simdjson (ondemand) | 698.885 | 0.0397625 | 533.581ms | 3862 | 40 | 175.638 | 5269.95 | 0.12098 | 3.52515 | 4(Loss) | true |
