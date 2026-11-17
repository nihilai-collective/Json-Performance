
----
### Twitter Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 6369.81 | 0.0284737 | 5405.57ms | 360584 | 4890 | 1.15546e+06 | 53985.8 | 0.00653152 | 0.476939 | 1(Win) | true |
| simdjson (ondemand) | 4657.01 | 0.0360357 | 7387.56ms | 360584 | 2560 | 1.81262e+06 | 73841.4 | 0.00111092 | 0.652439 | 2(Loss) | true |
