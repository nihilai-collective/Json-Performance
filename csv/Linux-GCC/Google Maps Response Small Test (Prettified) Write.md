
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 29055.5 | 0.0781444 | 40.3772ms | 11521 | 640 | 55.8856 | 378.148 | 0.0202426 | 0.0794457 | 1(Win) | true |
| Glaze | 5555.54 | 0.580778 | 199.165ms | 11521 | 640 | 84436.3 | 1977.72 | 0.0940255 | 0.439664 | 2(Loss) | true |
| simdjson (reflection) | 596.598 | 0.207347 | 1881.15ms | 11521 | 1280 | 1.86647e+06 | 18416.6 | 0.0145017 | 4.14405 | 3(Loss) | true |
