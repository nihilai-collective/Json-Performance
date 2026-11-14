
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1904.09 | 0.156869 | 6706.4ms | 4197496 | 160 | 1.7402e+09 | 2.10234e+06 | 0.46852 | 1.30023 | 1(Win) | true |
| simdjson (ondemand) | 1490.88 | 0.439607 | 8569.66ms | 4197496 | 30 | 4.1797e+09 | 2.68502e+06 | 1.32184 | 1.66061 | 2(Loss) | true |
