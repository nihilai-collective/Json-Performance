
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2537.27 | 0.259986 | 807.223ms | 1691 | 2560 | 6990.27 | 635.591 | 0.138597 | 2.12528 | 7.22176 | 1.12892 | 0.00178357 | 9.9331e-05 | 2.67963e-05 | 1(Win) | true |
| Glaze | 2347.53 | 0.154009 | 809.755ms | 1691 | 4890 | 5473.51 | 686.963 | 0.0304175 | 2.28603 | 8.78238 | 1.57836 | 0.00069803 | 8.96119e-05 | 1.58423e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 2092.43 | 0.209665 | 819.115ms | 1691 | 4890 | 12768.7 | 770.712 | 0.394538 | 2.54816 | 8.53578 | 1.34477 | 0.00101306 | 8.62258e-05 | 9.3119e-06 | 3(Loss) | true |
| simdjson (ondemand) | 1590.19 | 0.285254 | 846.124ms | 1691 | 1280 | 10711.8 | 1014.13 | 0.0355264 | 3.30948 | 11.0562 | 1.73803 | 0.000603378 | 6.69907e-05 | 6.46807e-06 | 4(Loss) | true |
