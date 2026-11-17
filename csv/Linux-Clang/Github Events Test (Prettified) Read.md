
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1464.01 | 0.0802337 | 4972.34ms | 65103 | 320 | 370492 | 42409 | 0.14524 | 3.51992 | 12.0289 | 2.32558 | 0.0115057 | 1.29602e-05 | 4.65608e-06 | 1(Win) | true |
| simdjson (ondemand) | 1196.93 | 0.0628371 | 5934.63ms | 65103 | 640 | 679951 | 51872 | 0.0608206 | 4.30311 | 15.6238 | 2.86542 | 0.0180642 | 2.23444e-05 | 7.94414e-06 | 2(Loss) | true |
