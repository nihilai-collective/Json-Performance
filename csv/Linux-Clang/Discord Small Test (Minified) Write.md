
----
### Discord Small Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 9569.98 | 0.279694 | 790.634ms | 4857 | 4890 | 8961.66 | 484.013 | 0.24904 | 0.573205 | 1.69261 | 0.292362 | 0.000304117 | 4.05461e-05 | 6.23139e-06 | 1(Win) | true |
| Glaze | 2727.96 | 0.221872 | 912.378ms | 4857 | 2560 | 36333.4 | 1697.97 | 0.0787545 | 1.88698 | 4.15751 | 0.632284 | 0.000214735 | 5.13917e-05 | 1.38331e-05 | 2(Loss) | true |
