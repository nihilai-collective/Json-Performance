
----
### Twitter Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8229.76 | 0.254963 | 768.431ms | 2963 | 4890 | 3747.59 | 343.356 | 0.312624 | 0.693909 | 1.59939 | 0.232535 | 0.000458553 | 4.99687e-05 | 1.35274e-05 | 1(Win) | true |
| Glaze | 4111.49 | 0.446239 | 801.752ms | 2963 | 1280 | 12039.6 | 687.279 | 0.337489 | 1.30765 | 3.21532 | 0.482619 | 0.000347515 | 2.21482e-05 | 1.58201e-06 | 2(Loss) | true |
