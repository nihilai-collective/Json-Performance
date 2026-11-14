
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 787.334 | 0.081915 | 7939.88ms | 1834197 | 40 | 1.32483e+08 | 2.22171e+06 | 0.474866 | 1(Win) | true |
| Jsonifier (two-stage) | 601.546 | 0.371296 | 5085.82ms | 1834197 | 30 | 3.49716e+09 | 2.90789e+06 | 0.486227 | 2(Loss) | true |
| Glaze | 537.411 | 0.432244 | 5207.02ms | 1834197 | 40 | 7.91767e+09 | 3.25491e+06 | 0.0141551 | 3(Loss) | true |
| simdjson (reflection) | 491.383 | 0.91661 | 5953.36ms | 1834197 | 80 | 8.51747e+10 | 3.5598e+06 | 1.41142 | 4(Loss) | true |
| simdjson (ondemand) | 426.73 | 1.11896 | 6645.77ms | 1834197 | 30 | 6.31158e+10 | 4.09914e+06 | 1.04034 | 5(Loss) | true |
