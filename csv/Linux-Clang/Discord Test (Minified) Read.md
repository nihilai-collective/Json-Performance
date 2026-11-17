
----
### Discord Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1414.54 | 0.0455865 | 4567.92ms | 56369 | 640 | 192090 | 38003.7 | 0.217343 | 3.61803 | 15.6053 | 3.11138 | 0.00744458 | 1.47743e-05 | 5.23892e-06 | 1(Win) | true |
| simdjson (ondemand) | 1205.99 | 0.0343917 | 5210.6ms | 56369 | 1280 | 300824 | 44575.7 | 0.0470296 | 4.27043 | 17.053 | 2.86634 | 0.0142706 | 8.81469e-06 | 2.99367e-06 | 2(Loss) | true |
