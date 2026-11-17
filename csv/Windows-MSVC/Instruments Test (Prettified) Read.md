
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1829.39 | 0.178824 | 5386.02ms | 183677 | 640 | 1.87642e+07 | 95752.3 | 0.284917 | 1.35293 | 1(Win) | true |
| Jsonifier | 1652.84 | 0.17245 | 5526.46ms | 183677 | 640 | 2.13774e+07 | 105980 | 0.505883 | 1.49749 | 2(Loss) | true |
| Glaze | 1345.61 | 0.140029 | 6682.31ms | 183677 | 640 | 2.12663e+07 | 130178 | 0.33245 | 1.83946 | 3(Loss) | true |
| simdjson (ondemand) | 1128.78 | 0.169059 | 8033.1ms | 183677 | 320 | 2.20251e+07 | 155183 | 0.0169126 | 2.19293 | 4(Loss) | true |
