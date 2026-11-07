
----
### Int64 Test Write (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4766.37 | 0.053266 | 85.6145ms | 3862 | 160 | 27.1063 | 772.725 | 0.0743567 | 0.502285 | 1(Win) | true |
| Glaze | 2577.12 | 0.0934261 | 152.886ms | 3862 | 40 | 71.3103 | 1429.15 | 0.0478368 | 0.942666 | 2(Loss) | true |
