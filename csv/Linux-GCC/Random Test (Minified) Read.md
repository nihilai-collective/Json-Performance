
----
### Random Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1176.34 | 0.157877 | 8528.78ms | 409725 | 640 | 1.7601e+08 | 332168 | 0.335429 | 2.10439 | 1(Win) | true |
| simdjson (ondemand) | 1159.18 | 0.157339 | 8842.05ms | 409725 | 80 | 2.25032e+07 | 337086 | 0.0590628 | 2.13559 | 2(Loss) | true |
