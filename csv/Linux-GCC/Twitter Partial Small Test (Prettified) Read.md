
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 6558.22 | 0.131609 | 784.871ms | 3808 | 320 | 169.958 | 553.747 | 0.131318 | 0.842442 | 3.302 | 0.383403 | 0.000262605 | 1.55922e-05 | 8.20641e-07 | 1(Win) | true |
| Jsonifier | 6493.23 | 0.288514 | 785.7ms | 3808 | 4890 | 12732.6 | 559.289 | 0.14411 | 0.8462 | 3.302 | 0.383403 | 0.000263786 | 2.56161e-05 | 7.35724e-06 | 2(Loss) | true |
| simdjson (reflection) | 6422.62 | 0.19755 | 773.72ms | 3808 | 80 | 99.8188 | 565.438 | 0.250432 | 0.859569 | 3.29333 | 0.335872 | 0.000285583 | 1.64128e-05 | 0 | 3(Loss) | true |
| simdjson (ondemand) | 6286.22 | 0.255546 | 779.203ms | 3808 | 4890 | 10657.7 | 577.707 | 0.154247 | 0.876598 | 3.30987 | 0.331408 | 0.000366788 | 3.45844e-05 | 1.6433e-05 | 4(Loss) | true |
| Glaze | 3500.88 | 0.0757559 | 821.083ms | 3808 | 4890 | 3019.82 | 1037.34 | 0.0327969 | 1.52874 | 6.58508 | 1.20746 | 0.000352771 | 1.63793e-05 | 6.12208e-06 | 5(Loss) | true |
