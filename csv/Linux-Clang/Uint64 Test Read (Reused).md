
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3297.95 | 0.0480583 | 115.557ms | 3873 | 80 | 23.1758 | 1119.96 | 0.132641 | 0.733617 | 1(Win) | true |
| Jsonifier (two-stage) | 3056.15 | 0.0858086 | 124.412ms | 3873 | 40 | 43.0199 | 1208.58 | 0.116664 | 0.792958 | 2(Loss) | true |
| Glaze | 1385.24 | 0.0279307 | 269.197ms | 3873 | 160 | 88.742 | 2666.39 | 0.117063 | 1.76926 | 3(Loss) | true |
| simdjson (ondemand) | 791.275 | 0.0202699 | 475.029ms | 3873 | 80 | 71.6201 | 4667.89 | 0.137186 | 3.11184 | 4(Loss) | true |
