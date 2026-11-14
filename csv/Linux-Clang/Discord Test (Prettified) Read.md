
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1980.1 | 0.0734637 | 4775.96ms | 83958 | 40 | 35298.3 | 40436.6 | 0.0167781 | 2.60468 | 11.0484 | 2.09804 | 0.00552181 | 3.7221e-05 | 2.9479e-05 | 1(Win) | true |
| simdjson (ondemand) | 1755.13 | 0.0462032 | 5313.17ms | 83958 | 640 | 284334 | 45619.7 | 0.0210186 | 2.92441 | 11.8163 | 1.93134 | 0.00876 | 2.42495e-05 | 1.48512e-05 | 2(Loss) | true |
