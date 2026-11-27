
----
### Twitter Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16928.4 | 0.24834 | 3428.78ms | 475954 | 1280 | 5.67545e+06 | 26813.2 | 0.0277888 | 0.297354 | 1.08564 | 0.142608 | 0.000266127 | 0.000751317 | 1.7158e-05 | 1(Win) | true |
| Glaze | 6747.67 | 0.156856 | 7476.33ms | 475954 | 4890 | 5.44419e+07 | 67268.4 | 0.0752011 | 0.748035 | 2.35134 | 0.334375 | 0.000333424 | 0.00181477 | 3.05575e-05 | 2(Loss) | true |
