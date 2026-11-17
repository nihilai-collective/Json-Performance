
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2580.78 | 0.263172 | 9349.71ms | 7351818 | 30 | 1.53351e+09 | 2.71672e+06 | 0.822949 | 0.959311 | 1(Win) | true |
| simdjson (ondemand) | 2391.36 | 0.166526 | 9914.19ms | 7351818 | 80 | 1.90702e+09 | 2.93191e+06 | 0.515326 | 1.0353 | 2(Loss) | true |
