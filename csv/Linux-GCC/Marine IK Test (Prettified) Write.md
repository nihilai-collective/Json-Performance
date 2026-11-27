
----
### Marine IK Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5992.52 | 0.482743 | 5065.4ms | 10018896 | 30 | 1.77735e+09 | 1.59445e+06 | 1.65198 | 0.413107 | 1(Win) | true |
| Glaze | 2759.82 | 0.618654 | 5008.21ms | 9930228 | 30 | 1.35199e+10 | 3.43146e+06 | 0.838965 | 0.896943 | 2(Loss) | true |
| simdjson (reflection) | 368.577 | 0.344374 | 7870.32ms | 10018896 | 30 | 2.39092e+11 | 2.59234e+07 | 1.73064 | 6.71709 | 3(Loss) | true |
