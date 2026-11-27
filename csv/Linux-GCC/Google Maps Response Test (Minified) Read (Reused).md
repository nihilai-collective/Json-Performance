
----
### Google Maps Response Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2036.39 | 0.572034 | 595.109ms | 11812 | 4890 | 4.89643e+06 | 5531.76 | 0.101048 | 1.21016 | 1(Win) | true |
| Glaze | 1681.61 | 0.160302 | 714.227ms | 11812 | 30 | 3459.34 | 6698.8 | 0.040322 | 1.46655 | 2(Loss) | true |
| Jsonifier (two-stage) | 1644.57 | 0.347979 | 714.768ms | 11812 | 320 | 181803 | 6849.71 | 0.053851 | 1.49933 | 3(Loss) | true |
| simdjson (reflection) | 1569.47 | 0.126618 | 776.598ms | 11812 | 2560 | 211433 | 7177.45 | 0.0927699 | 1.57167 | 4(Loss) | true |
| simdjson (ondemand) | 1270.35 | 0.107853 | 997.539ms | 11812 | 30 | 2743.98 | 8867.47 | 0.264962 | 1.94339 | 5(Loss) | true |
