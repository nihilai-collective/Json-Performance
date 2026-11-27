
----
### Instruments Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1808.44 | 0.0404556 | 7065.41ms | 4197496 | 80 | 6.41537e+07 | 2.21354e+06 | 0.108249 | 1.36899 | 1(Win) | true |
| simdjson (ondemand) | 1490.16 | 0.165126 | 8512.5ms | 4197496 | 80 | 1.57412e+09 | 2.68632e+06 | 0.747745 | 1.66141 | 2(Loss) | true |
