
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 16740.5 | 0.0368374 | 1258.8ms | 94653 | 4890 | 19293.8 | 5392.19 | 0.158966 | 0.30971 | 1.66818 | 0.102152 | 3.16299e-05 | 2.43274e-06 | 8.31797e-07 | 1(Win) | true |
| simdjson (stage-1) | 13960.2 | 0.0397547 | 1362.58ms | 94653 | 40 | 264.317 | 6466.12 | 0.0246215 | 0.371369 | 2.01526 | 0.0771661 | 2.11298e-05 | 5.54658e-06 | 2.64123e-07 | 2(Loss) | true |
