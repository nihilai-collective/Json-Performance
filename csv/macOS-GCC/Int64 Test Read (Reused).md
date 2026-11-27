
----
### Int64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1494.96 | 1.92522 | 85.6719ms | 1313 | 640 | 166424 | 837.6 | 0.0956023 | 1(Win) | true |
| Glaze | 849.167 | 0.503532 | 152.636ms | 1313 | 4890 | 269592 | 1474.59 | 0.634002 | 2(Loss) | true |
| simdjson (reflection) | 746.147 | 0.506547 | 178.576ms | 1313 | 4890 | 353370 | 1678.19 | 0.19627 | 3(Loss) | true |
| simdjson (ondemand) | 304.591 | 0.282573 | 425.333ms | 1313 | 2560 | 345459 | 4111 | 0.371112 | 4(Loss) | true |
