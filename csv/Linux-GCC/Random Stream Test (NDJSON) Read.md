
----
### Random Stream Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Random%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1558.06 | 0.952214 | 10334.6ms | 4506447 | 80 | 5.51903e+10 | 2.75836e+06 | 1.54081 | 3.25234 | 14.5981 | 2.72773 | 0.0125619 | 0.080494 | 0.00708423 | 1(Win) | true |
| simdjson (ondemand) | 1202.55 | 0.230054 | 6314.73ms | 4506447 | 80 | 5.40767e+09 | 3.5738e+06 | 0.200753 | 4.22315 | 17.1187 | 3.13833 | 0.0126854 | 0.078568 | 0.0149748 | 2(Loss) | true |
