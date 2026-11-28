
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1638.05 | 0.057585 | 78.1373ms | 1313 | 320 | 62.0078 | 764.431 | 0.00163523 | 1.45909 | 1(Win) | true |
| Glaze | 988.723 | 0.0367797 | 132.688ms | 1313 | 160 | 34.7151 | 1266.46 | 0.0735861 | 2.45265 | 2(Loss) | true |
| simdjson (ondemand) | 353.112 | 0.0287522 | 358.161ms | 1313 | 80 | 83.1644 | 3546.11 | 0.199559 | 6.95685 | 3(Loss) | true |
