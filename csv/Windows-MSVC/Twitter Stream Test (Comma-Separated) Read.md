
----
### Twitter Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Twitter%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1247.45 | 0.653713 | 5456.41ms | 4219119 | 80 | 3.55682e+10 | 3.22551e+06 | 1.33581 | 2.4363 | 1(Win) | true |
| simdjson (ondemand) | 958.476 | 0.840523 | 6837.12ms | 4219119 | 80 | 9.96025e+10 | 4.19798e+06 | 0.743158 | 3.17089 | 2(Loss) | true |
