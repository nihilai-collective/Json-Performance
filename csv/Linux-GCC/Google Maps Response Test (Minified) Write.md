
----
### Google Maps Response Test (Minified) Write Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12905.6 | 0.138837 | 814.619ms | 11812 | 80 | 117.487 | 872.862 | 0.0100255 | 0.410711 | 1.8736 | 0.221639 | 8.46597e-05 | 1.90484e-05 | 2.11649e-06 | 1(Win) | true |
| simdjson (reflection) | 9556.57 | 0.10909 | 851.793ms | 11812 | 40 | 66.141 | 1178.75 | 0.00706914 | 0.548021 | 2.32916 | 0.343041 | 0.000171436 | 3.38639e-05 | 8.46597e-06 | 2(Loss) | true |
| Glaze | 4569.75 | 0.0964957 | 993.296ms | 11812 | 2560 | 14485 | 2465.08 | 0.0436757 | 1.12588 | 4.62606 | 0.716983 | 0.000167071 | 4.7125e-05 | 2.64231e-05 | 3(Loss) | true |
