
----
### Int64 Test Write (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Int64%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2506.73 | 0.104118 | 59.6651ms | 1313 | 40 | 10.8199 | 499.525 | 0.152042 | 0.932597 | 1(Win) | true |
| simdjson (reflection) | 2421.4 | 0.0530816 | 60.9566ms | 1313 | 320 | 24.1121 | 517.128 | 0.00422991 | 0.968262 | 2(Loss) | true |
| Glaze | 1211.25 | 0.309226 | 112.355ms | 1313 | 2560 | 26161 | 1033.79 | 0.434985 | 1.98639 | 3(Loss) | true |
