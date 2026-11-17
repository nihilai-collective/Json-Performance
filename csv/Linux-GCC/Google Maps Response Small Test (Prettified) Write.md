
----
### Google Maps Response Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 24008.3 | 0.0426682 | 777.38ms | 11521 | 4890 | 186.457 | 457.646 | 0.353746 | 0.229561 | 0.744814 | 0.111709 | 8.6869e-05 | 1.95784e-05 | 5.89304e-06 | 1(Win) | true |
| Glaze | 5814.34 | 0.0733948 | 927.493ms | 11521 | 4890 | 9406.32 | 1889.69 | 0.0538074 | 0.888842 | 3.91155 | 0.66496 | 0.000271399 | 2.26846e-05 | 5.53803e-06 | 2(Loss) | true |
| simdjson (reflection) | 519.799 | 0.436416 | 2868.29ms | 11521 | 320 | 2.72308e+06 | 21137.5 | 0.0798536 | 9.70287 | 37.9473 | 6.97318 | 0.0109319 | 4.66539e-05 | 2.52257e-05 | 3(Loss) | true |
