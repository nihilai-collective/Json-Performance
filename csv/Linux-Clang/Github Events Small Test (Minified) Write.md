
----
### Github Events Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9529.12 | 0.30236 | 751.146ms | 1996 | 4890 | 1783.91 | 199.76 | 0.145477 | 0.63962 | 1.63477 | 0.254008 | 0.000791358 | 5.75794e-05 | 1.19872e-05 | 1(Win) | true |
| Glaze | 3923.71 | 0.18867 | 777.646ms | 1996 | 4890 | 4096.77 | 485.136 | 0.258428 | 1.39749 | 3.74549 | 0.585171 | 0.00050469 | 6.76199e-05 | 1.55731e-05 | 2(Loss) | true |
