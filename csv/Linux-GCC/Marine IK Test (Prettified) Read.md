
----
### Marine IK Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2449.84 | 0.102243 | 8913.11ms | 7351818 | 80 | 6.84968e+08 | 2.86192e+06 | 0.660586 | 1.0105 | 1(Win) | true |
| simdjson (ondemand) | 2212.96 | 0.142024 | 10130.4ms | 7351818 | 80 | 1.61978e+09 | 3.16826e+06 | 0.398818 | 1.11869 | 2(Loss) | true |
