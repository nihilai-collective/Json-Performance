
----
### Instruments Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5182.78 | 0.0622503 | 4137.84ms | 183677 | 640 | 283300 | 33798.1 | 0.0268486 | 0.989218 | 5.22434 | 0.869494 | 0.000704651 | 4.87439e-06 | 2.87529e-06 | 1(Win) | true |
| simdjson (ondemand) | 4138.72 | 0.179417 | 5020.21ms | 183677 | 40 | 230655 | 42324.2 | 0.154185 | 1.24472 | 6.47991 | 0.930139 | 0.00196731 | 2.04163e-06 | 1.36108e-07 | 2(Loss) | true |
