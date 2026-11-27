
----
### Google Maps Response Small Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 22751.1 | 0.226558 | 759.835ms | 11521 | 320 | 383.077 | 482.934 | 0.463511 | 0.24819 | 0.82571 | 0.097561 | 8.6798e-05 | 3.87879e-05 | 2.27845e-05 | 1(Win) | true |
| Glaze | 5542.62 | 0.150954 | 918.159ms | 11521 | 2560 | 22923.5 | 1982.33 | 0.161343 | 0.951892 | 3.9126 | 0.665481 | 0.000226895 | 8.6459e-05 | 5.22822e-05 | 2(Loss) | true |
| simdjson (reflection) | 525.276 | 0.146006 | 2822.08ms | 11521 | 2560 | 2.38773e+06 | 20917.2 | 0.461831 | 9.68044 | 38.0418 | 7.00811 | 0.0114673 | 9.53761e-05 | 4.83831e-05 | 3(Loss) | true |
