
----
### Twitter Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16749.1 | 0.319811 | 27.3839ms | 4300 | 80 | 49.0492 | 244.838 | 0.107329 | 0.131645 | 1(Win) | true |
| Glaze | 3797.52 | 0.0949959 | 112.118ms | 4300 | 160 | 168.371 | 1079.86 | 0.127169 | 0.635465 | 2(Loss) | true |
| simdjson (reflection) | 552.936 | 0.385972 | 760.605ms | 4300 | 640 | 524420 | 7416.41 | 0.192638 | 4.46013 | 3(Loss) | true |
