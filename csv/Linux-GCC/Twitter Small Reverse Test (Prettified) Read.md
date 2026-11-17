
----
### Twitter Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1011.23 | 0.0869007 | 1077.07ms | 3770 | 80 | 763.688 | 3555.41 | 0.0341146 | 5.14954 | 20.7719 | 3.92732 | 0.00136605 | 7.29443e-05 | 2.98408e-05 | 1(Win) | true |
| simdjson (ondemand) | 539.143 | 0.0332835 | 1387.79ms | 3770 | 2560 | 12611.6 | 6668.64 | 0.218416 | 9.60401 | 43.7944 | 8.76764 | 0.00874161 | 4.32071e-05 | 9.22165e-06 | 2(Loss) | true |
