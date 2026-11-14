
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1619.9 | 0.290579 | 639.991ms | 8051 | 4890 | 927603 | 4739.82 | 2.19105 | 1(Win) | true |
| Jsonifier | 1574.4 | 0.908738 | 556.841ms | 8051 | 320 | 628488 | 4876.8 | 0.229133 | 2(Loss) | true |
| simdjson (reflection) | 1473.82 | 1.25098 | 663.509ms | 8051 | 40 | 169889 | 5209.6 | 0.570033 | 3(Loss) | true |
| Glaze | 1347.97 | 1.67993 | 671.85ms | 8051 | 80 | 732510 | 5696 | 1.33038 | 4(Loss) | true |
| simdjson (ondemand) | 1159.89 | 0.279802 | 783.139ms | 8051 | 2560 | 878224 | 6619.6 | 0.310232 | 5(Loss) | true |
