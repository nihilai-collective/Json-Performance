
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1964.67 | 0.0767005 | 4694.14ms | 83958 | 4890 | 4.77802e+06 | 40754.1 | 0.0452374 | 1.25933 | 1(Win) | true |
| Jsonifier | 1830.54 | 0.204837 | 4873.89ms | 83958 | 640 | 5.13762e+06 | 43740.5 | 0.284799 | 1.35162 | 2(Loss) | true |
| Glaze | 1776.89 | 0.11663 | 5049.14ms | 83958 | 4890 | 1.35063e+07 | 45061.1 | 0.16552 | 1.39251 | 3(Loss) | true |
| simdjson (ondemand) | 1510.39 | 0.181994 | 6087.72ms | 83958 | 640 | 5.95721e+06 | 53012 | 0.324977 | 1.63832 | 4(Loss) | true |
