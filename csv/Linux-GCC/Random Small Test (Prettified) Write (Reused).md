
----
### Random Small Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 23754.8 | 0.19684 | 752.174ms | 9255 | 320 | 171.169 | 371.556 | 0.500397 | 0.239636 | 0.932793 | 0.111615 | 0.00010805 | 1.65451e-05 | 4.05186e-06 | 1(Win) | true |
| Glaze | 5488.26 | 0.0734701 | 882.604ms | 9255 | 4890 | 6826.75 | 1608.21 | 0.178067 | 0.959228 | 4.47315 | 0.737007 | 0.000177696 | 2.2781e-05 | 5.72288e-06 | 2(Loss) | true |
| simdjson (reflection) | 528.738 | 0.26507 | 2399.86ms | 9255 | 640 | 1.25306e+06 | 16693.1 | 0.204736 | 9.65574 | 38.0755 | 7.28344 | 0.016546 | 6.98947e-05 | 3.61291e-05 | 3(Loss) | true |
