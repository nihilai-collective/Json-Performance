
----
### Twitter Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 19549.9 | 0.0375081 | 23.7438ms | 4300 | 2560 | 15.8467 | 209.761 | 0.124986 | 0.110359 | 1(Win) | true |
| Glaze | 4621.17 | 0.0744104 | 92.7877ms | 4300 | 160 | 69.7622 | 887.394 | 0.0359069 | 0.519557 | 2(Loss) | true |
| simdjson (reflection) | 540.589 | 0.325902 | 724.544ms | 4300 | 320 | 195582 | 7585.8 | 0.184442 | 4.56295 | 3(Loss) | true |
