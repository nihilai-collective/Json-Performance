
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11781.4 | 0.133885 | 821.785ms | 11812 | 4890 | 8013.64 | 956.155 | 0.00356677 | 0.45328 | 2.12978 | 0.294277 | 0.000129119 | 1.9373e-05 | 6.44037e-06 | 1(Win) | true |
| Glaze | 3878.62 | 0.102187 | 1026.41ms | 11812 | 4890 | 43071.5 | 2904.33 | 0.126479 | 1.343 | 5.64045 | 0.823823 | 0.000432197 | 7.60206e-05 | 4.88221e-05 | 2(Loss) | true |
