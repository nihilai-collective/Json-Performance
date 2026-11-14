
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1014.41 | 0.055359 | 9013.33ms | 83958 | 30 | 57279.1 | 78931.3 | 0.0277801 | 5.07918 | 23.5346 | 4.90563 | 0.00692092 | 1.86601e-05 | 9.13155e-06 | 1(Win) | true |
| simdjson (ondemand) | 318.467 | 0.229561 | 6715.21ms | 83958 | 40 | 1.33245e+07 | 251419 | 0.215288 | 16.0237 | 92.4364 | 18.4974 | 0.0217478 | 2.02482e-05 | 5.95536e-06 | 2(Loss) | true |
