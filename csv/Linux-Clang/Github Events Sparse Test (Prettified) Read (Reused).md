
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8962.3 | 0.027351 | 1430.64ms | 65103 | 2560 | 9190.74 | 6927.58 | 0.00489463 | 0.577843 | 2.68664 | 0.327712 | 0.000631811 | 2.46004e-06 | 1.14002e-07 | 1(Win) | true |
| simdjson (ondemand) | 8104.32 | 0.0270427 | 1500.63ms | 65103 | 2560 | 10987.8 | 7660.98 | 0.0391187 | 0.638689 | 2.852 | 0.322981 | 0.000723127 | 2.46604e-06 | 3.72007e-07 | 2(Loss) | true |
