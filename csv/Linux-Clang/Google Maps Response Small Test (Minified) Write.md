
----
### Google Maps Response Small Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10702.9 | 0.204245 | 767.138ms | 4390 | 2560 | 1634.08 | 391.169 | 0.334212 | 0.52293 | 2.28223 | 0.324374 | 0.000335279 | 4.36895e-05 | 1.44149e-05 | 1(Win) | true |
| Glaze | 3646.46 | 0.116843 | 847.566ms | 4390 | 4890 | 8800.3 | 1148.13 | 0.16696 | 1.43902 | 5.80228 | 0.86606 | 0.000461217 | 6.03249e-05 | 2.03567e-05 | 2(Loss) | true |
