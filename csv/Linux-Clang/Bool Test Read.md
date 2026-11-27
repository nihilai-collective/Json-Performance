
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1879.25 | 0.146645 | 752.834ms | 905 | 4890 | 2218.04 | 459.266 | 0.0988498 | 2.98309 | 12.926 | 2.93923 | 0.00114067 | 0.000118406 | 9.26459e-06 | 1(Win) | true |
| simdjson (stage-1) | 1131.8 | 0.0789094 | 801.862ms | 905 | 320 | 115.869 | 762.572 | 0.231249 | 4.83553 | 23.9227 | 5.47182 | 0.0116609 | 0.000117403 | 4.14365e-05 | 2(Loss) | true |
