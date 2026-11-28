
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1605.12 | 0.0604005 | 82.4031ms | 1313 | 320 | 71.0469 | 780.112 | 0.0464461 | 1.48996 | 1(Win) | true |
| Glaze | 909.854 | 0.288582 | 138.638ms | 1313 | 2560 | 40379.8 | 1376.24 | 1.11485 | 2.66603 | 2(Loss) | true |
| simdjson (ondemand) | 357.483 | 0.0492763 | 349.187ms | 1313 | 40 | 119.167 | 3502.75 | 0.193078 | 6.87173 | 3(Loss) | true |
