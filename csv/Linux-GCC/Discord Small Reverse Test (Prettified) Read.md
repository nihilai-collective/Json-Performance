
----
### Discord Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 878.719 | 0.0545092 | 1452.26ms | 6701 | 160 | 2514.43 | 7272.6 | 0.0910062 | 5.89653 | 23.5739 | 4.76213 | 0.00608118 | 6.06253e-05 | 1.21251e-05 | 1(Win) | true |
| simdjson (ondemand) | 328.808 | 0.0427759 | 2669.82ms | 6701 | 320 | 22117.8 | 19435.6 | 0.0801848 | 15.6907 | 77.9331 | 16.324 | 0.0345018 | 3.68415e-05 | 1.30578e-05 | 2(Loss) | true |
