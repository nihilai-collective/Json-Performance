
----
### Marine IK Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1175.64 | 0.233846 | 9908.17ms | 1922245 | 160 | 2.12741e+09 | 1.55932e+06 | 1.16706 | 2.10588 | 1(Win) | true |
| Glaze | 575.105 | 0.0807742 | 9621.18ms | 1833577 | 40 | 2.41273e+08 | 3.04055e+06 | 0.0276617 | 4.30493 | 2(Loss) | true |
