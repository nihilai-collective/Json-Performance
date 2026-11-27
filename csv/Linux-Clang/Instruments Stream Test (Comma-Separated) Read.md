
----
### Instruments Stream Test (Comma-Separated) Read Results [(Here is the data we used for this test)](./json/Instruments%20Stream%20Test%20%28Comma-Separated%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28Comma-Separated%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1428.49 | 1.40929 | 9002.96ms | 4197495 | 40 | 6.23859e+10 | 2.80228e+06 | 1.17087 | 3.54402 | 17.7657 | 3.38961 | 0.000664712 | 0.0845046 | 0.00424889 | 1(Win) | true |
| simdjson (ondemand) | 1051.51 | 1.08126 | 5969.24ms | 4197495 | 80 | 1.35551e+11 | 3.80695e+06 | 1.19139 | 4.84652 | 23.2609 | 3.71908 | 0.00594175 | 0.103238 | 0.004933 | 2(Loss) | true |
