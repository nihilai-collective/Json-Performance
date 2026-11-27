
----
### Discord Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 14154.2 | 0.0923319 | 52.5581ms | 7376 | 320 | 67.3787 | 496.975 | 0.0163462 | 0.165863 | 1(Win) | true |
| Glaze | 3527.97 | 0.0408782 | 248.947ms | 7376 | 160 | 106.291 | 1993.87 | 0.748233 | 0.692632 | 2(Loss) | true |
