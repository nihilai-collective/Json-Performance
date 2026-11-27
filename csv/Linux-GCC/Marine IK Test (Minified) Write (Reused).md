
----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1242.93 | 0.0836024 | 9372.92ms | 1922245 | 320 | 4.86529e+08 | 1.47489e+06 | 0.427787 | 1.99184 | 1(Win) | true |
| simdjson (reflection) | 1032.62 | 0.0754207 | 5410.36ms | 1922245 | 160 | 2.86836e+08 | 1.77528e+06 | 0.346409 | 2.39753 | 2(Loss) | true |
| Glaze | 885.929 | 0.129583 | 5897.45ms | 1833577 | 30 | 1.96254e+08 | 1.97379e+06 | 2.06286 | 2.79452 | 3(Loss) | true |
