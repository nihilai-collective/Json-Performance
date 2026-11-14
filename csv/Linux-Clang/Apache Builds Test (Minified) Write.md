
----
### Apache Builds Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16402.2 | 0.0475158 | 1294.14ms | 94653 | 4890 | 33438.6 | 5503.4 | 0.0110262 | 0.309855 | 1.3301 | 0.183903 | 0.000168375 | 8.55995e-06 | 4.63862e-06 | 1(Win) | true |
| Glaze | 5647.94 | 0.0711708 | 2353.27ms | 94653 | 2560 | 331232 | 15982.5 | 0.0317685 | 0.891253 | 4.37627 | 0.666677 | 9.13864e-05 | 1.23147e-05 | 6.94973e-06 | 2(Loss) | true |
