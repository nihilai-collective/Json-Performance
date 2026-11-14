
----
### Discord Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 959.803 | 0.0234511 | 9442.44ms | 83958 | 2560 | 979775 | 83421.9 | 0.00451556 | 5.32367 | 23.3074 | 4.92783 | 0.00678542 | 1.38648e-05 | 8.09557e-06 | 1(Win) | true |
| simdjson (ondemand) | 322.664 | 0.0955393 | 6612.4ms | 83958 | 160 | 8.99304e+06 | 248148 | 0.219237 | 15.789 | 87.9495 | 18.6129 | 0.0235483 | 1.4814e-05 | 3.79654e-06 | 2(Loss) | true |
