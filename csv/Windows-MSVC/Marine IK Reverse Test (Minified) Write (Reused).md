
----
### Marine IK Reverse Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1176.61 | 0.0905331 | 10047.5ms | 1922245 | 80 | 1.59169e+08 | 1.55803e+06 | 0.793946 | 2.10413 | 1(Win) | true |
| Glaze | 573.336 | 0.0917473 | 9540.95ms | 1833577 | 80 | 6.26406e+08 | 3.04993e+06 | 0.0636085 | 4.31822 | 2(Loss) | true |
