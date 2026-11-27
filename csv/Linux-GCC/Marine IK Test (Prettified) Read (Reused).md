
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2679.55 | 0.199696 | 8900.5ms | 7351818 | 80 | 2.18422e+09 | 2.61658e+06 | 0.134366 | 0.923902 | 1(Win) | true |
| simdjson (ondemand) | 2435.56 | 0.322101 | 9759.74ms | 7351818 | 160 | 1.37561e+10 | 2.8787e+06 | 0.0132349 | 1.01651 | 2(Loss) | true |
