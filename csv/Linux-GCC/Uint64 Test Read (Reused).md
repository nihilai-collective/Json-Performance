
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.11 | 0.100084 | 68.2678ms | 1213 | 80 | 34.5758 | 656.862 | 0.0931594 | 1.3468 | 1(Win) | true |
| simdjson (reflection) | 1122.84 | 0.0490171 | 107.687ms | 1213 | 640 | 163.216 | 1030.25 | 0.0212281 | 2.14758 | 2(Loss) | true |
| Glaze | 945.95 | 0.266033 | 125.188ms | 1213 | 4890 | 51756.7 | 1222.9 | 0.0411113 | 2.541 | 3(Loss) | true |
| simdjson (ondemand) | 312.157 | 0.0253348 | 375.711ms | 1213 | 40 | 35.259 | 3705.85 | 0.00674655 | 7.87232 | 4(Loss) | true |
