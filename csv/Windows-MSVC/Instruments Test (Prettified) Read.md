
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1959.04 | 0.119113 | 9058.38ms | 183677 | 1280 | 1.45194e+07 | 89415.2 | 0.0646106 | 1.26341 | 1(Win) | true |
| Jsonifier | 1741.4 | 0.107628 | 5255.81ms | 183677 | 1280 | 1.50028e+07 | 100590 | 0.217238 | 1.42132 | 2(Loss) | true |
| Glaze | 1408.58 | 0.178288 | 6444.27ms | 183677 | 640 | 3.14612e+07 | 124358 | 0.537743 | 1.75721 | 3(Loss) | true |
| simdjson (ondemand) | 1243.23 | 0.144803 | 7337.02ms | 183677 | 640 | 2.66405e+07 | 140898 | 0.197117 | 1.99103 | 4(Loss) | true |
