
----
### Github Events Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 15623.9 | 0.164283 | 20.0937ms | 2866 | 640 | 52.8617 | 174.939 | 0.277006 | 0.135454 | 1(Win) | true |
| Glaze | 4455.82 | 0.0739898 | 64.0136ms | 2866 | 320 | 65.9159 | 613.406 | 0.121396 | 0.532074 | 2(Loss) | true |
