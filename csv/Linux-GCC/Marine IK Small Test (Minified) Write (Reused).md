
----
### Marine IK Small Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1640.74 | 0.0963627 | 302.127ms | 4918 | 30 | 227.633 | 2858.57 | 0.0548361 | 1.49401 | 1(Win) | true |
| simdjson (reflection) | 1477.2 | 0.0210758 | 355.427ms | 4918 | 160 | 71.6453 | 3175.05 | 0.759529 | 1.66142 | 2(Loss) | true |
| Glaze | 1093.07 | 0.0964474 | 419.536ms | 4604 | 40 | 600.369 | 4016.88 | 0.0802219 | 2.24902 | 3(Loss) | true |
