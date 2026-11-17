
----
### Apache Builds Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1504.93 | 0.0199598 | 6747.6ms | 94653 | 2560 | 366938 | 59981.8 | 0.0590704 | 3.36986 | 15.0448 | 2.9685 | 0.00900091 | 9.90047e-06 | 4.02374e-06 | 1(Win) | true |
| simdjson (ondemand) | 1227.54 | 0.0419706 | 8082.74ms | 94653 | 640 | 609629 | 73535.7 | 0.167175 | 4.13578 | 16.629 | 3.11044 | 0.0129068 | 1.72175e-05 | 1.13078e-05 | 2(Loss) | true |
