
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 180.354 | 0.59424 | 499.838ms | 905 | 4890 | 3.95436e+06 | 4785.44 | 0.180933 | 13.6455 | 1(Win) | true |
| simdjson (ondemand) | 65.4589 | 0.126065 | 1334.93ms | 905 | 40 | 11051.3 | 13185 | 0.0379363 | 37.7351 | 2(Loss) | true |
