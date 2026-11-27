
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2566.94 | 0.123328 | 9258.89ms | 7351818 | 80 | 9.07764e+08 | 2.73136e+06 | 0.35392 | 0.96448 | 1(Win) | true |
| simdjson (ondemand) | 2516.44 | 0.118399 | 9439.31ms | 7351818 | 30 | 3.26464e+08 | 2.78618e+06 | 0.0514563 | 0.983835 | 2(Loss) | true |
