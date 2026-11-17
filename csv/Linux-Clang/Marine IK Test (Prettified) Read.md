
----
### Marine IK Test (Prettified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21810.8 | 0.073128 | 8196.99ms | 7351818 | 1280 | 7.07329e+07 | 321457 | 0.0311279 | 0.113503 | 1(Win) | true |
| simdjson (stage-1) | 20424.4 | 0.124073 | 8939.95ms | 7351818 | 160 | 2.90247e+07 | 343278 | 0.0797438 | 0.12121 | 2(Loss) | true |
