
----
### Instruments Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5024.94 | 0.104482 | 867.839ms | 7932 | 80 | 197.914 | 1505.4 | 0.192269 | 1.07144 | 4.89397 | 0.782653 | 0.000855711 | 6.30358e-06 | 0 | 1(Win) | true |
| simdjson (ondemand) | 4048.53 | 0.0400242 | 900.996ms | 7932 | 320 | 178.965 | 1868.47 | 0.0512045 | 1.2999 | 5.9734 | 0.895487 | 0.00156368 | 1.06373e-05 | 0 | 2(Loss) | true |
