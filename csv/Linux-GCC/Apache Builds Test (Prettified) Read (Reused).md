
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2829.23 | 0.034429 | 6201.47ms | 124597 | 2560 | 535262 | 41999 | 0.135061 | 1.7899 | 8.79962 | 1.51452 | 0.00448245 | 1.19761e-05 | 8.46793e-06 | 1(Win) | true |
| simdjson (ondemand) | 2100.57 | 0.0338336 | 7606.02ms | 124597 | 4890 | 1.79121e+06 | 56567.9 | 0.213175 | 2.42793 | 9.51668 | 1.71565 | 0.00656843 | 7.29222e-06 | 3.93744e-06 | 2(Loss) | true |
