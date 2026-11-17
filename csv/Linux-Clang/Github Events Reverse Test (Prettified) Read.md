
----
### Github Events Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1050.13 | 0.0189759 | 6649.02ms | 65103 | 4890 | 615500 | 59123 | 0.1131 | 4.90384 | 16.9365 | 3.39101 | 0.0150111 | 3.75557e-05 | 2.08824e-05 | 1(Win) | true |
| simdjson (ondemand) | 552.387 | 0.0468231 | 6146.55ms | 65103 | 2560 | 7.09048e+06 | 112398 | 0.0294556 | 9.29031 | 33.2849 | 5.97369 | 0.0524147 | 3.52206e-05 | 1.42083e-05 | 2(Loss) | true |
