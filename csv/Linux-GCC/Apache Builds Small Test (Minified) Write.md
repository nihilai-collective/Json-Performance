
----
### Apache Builds Small Test (Minified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12080.9 | 0.236589 | 744.406ms | 2632 | 320 | 77.324 | 207.772 | 0.1944 | 0.500854 | 1.74392 | 0.292173 | 0.000381127 | 2.13716e-05 | 2.37462e-06 | 1(Win) | true |
| simdjson (reflection) | 7239.89 | 0.243784 | 757.086ms | 2632 | 40 | 28.5744 | 346.7 | 0.483045 | 0.781117 | 2.7405 | 0.457827 | 0.000379939 | 1.8997e-05 | 1.8997e-05 | 2(Loss) | true |
| Glaze | 4585.42 | 0.0927009 | 782.875ms | 2632 | 4890 | 1259.19 | 547.403 | 0.261003 | 1.19028 | 4.06725 | 0.666414 | 0.000583195 | 6.30124e-05 | 2.5407e-05 | 3(Loss) | true |
