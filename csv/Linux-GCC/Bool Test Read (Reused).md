
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 2313.71 | 0.0327002 | 40.2079ms | 905 | 1280 | 19.0454 | 373.027 | 0.0343356 | 0.992295 | 1(Win) | true |
| Jsonifier | 2308.98 | 0.0705801 | 40.6272ms | 905 | 320 | 22.2726 | 373.791 | 0.475105 | 0.994572 | 2(Loss) | true |
| simdjson (reflection) | 1247.15 | 0.0659608 | 72.8585ms | 905 | 80 | 16.6695 | 692.038 | 0.0343072 | 1.9075 | 3(Loss) | true |
| simdjson (ondemand) | 474.007 | 0.063165 | 186.234ms | 905 | 160 | 211.641 | 1820.81 | 0.0442602 | 5.14319 | 4(Loss) | true |
