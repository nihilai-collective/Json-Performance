
----
### Instruments Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7121.99 | 0.0566426 | 3191.5ms | 183677 | 1280 | 248429 | 24595.4 | 0.188833 | 0.714213 | 3.69028 | 0.5053 | 0.000455028 | 1.96081e-06 | 6.25248e-07 | 1(Win) | true |
| simdjson (ondemand) | 6552.53 | 0.0548204 | 3420.87ms | 183677 | 320 | 68726.9 | 26732.9 | 0.125975 | 0.786815 | 3.9878 | 0.444525 | 0.00116242 | 9.25538e-06 | 7.48597e-06 | 2(Loss) | true |
