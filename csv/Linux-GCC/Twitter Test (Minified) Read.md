
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1828.69 | 0.129861 | 6902.75ms | 264040 | 320 | 1.02321e+07 | 137699 | 0.411538 | 1.35356 | 1(Win) | true |
| Jsonifier (generic) | 1758.19 | 0.0643857 | 7270.89ms | 264040 | 2560 | 2.17684e+07 | 143220 | 0.445978 | 1.4078 | 2(Loss) | true |
