
----
### Int64 Test Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4604.01 | 0.0756383 | 88.3552ms | 3862 | 80 | 29.2905 | 799.975 | 0.370509 | 0.519718 | 1(Win) | true |
| simdjson (stage-1) | 2075.29 | 0.0495002 | 181.106ms | 3862 | 160 | 123.481 | 1774.73 | 0.0876125 | 1.17459 | 2(Loss) | true |
